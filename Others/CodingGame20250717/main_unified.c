#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Veri yapıları aynı kalsın
typedef struct {
    int id;
    int player;
} AgentData;

typedef struct {
    int id;
    int x, y;
    int bombs;
} AgentState;

typedef struct {
    int x, y;
} Coordinate;

typedef struct {
    Coordinate center;
    int agent_count;
    int member_indices[10]; 
} AgentGroup;

// Global değişkenler
int my_id;
int width, height;
AgentData all_agent_data[20];
int agent_data_count;

// Mesafe hesaplama fonksiyonları aynı kalsın
int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

double euclidean_distance(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return sqrt(dx*dx + dy*dy);
}

int chebyshev_distance(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    return (dx > dy) ? dx : dy;
}

// Strateji fonksiyonları aynı kalsın
void find_enemy_groups(int enemy_agent_count, AgentState enemy_agents[], int* group_count, AgentGroup enemy_groups[]) {
    *group_count = 0;
    if (enemy_agent_count == 0) {
        return;
    }

    bool assigned_to_group[enemy_agent_count];
    memset(assigned_to_group, false, sizeof(assigned_to_group));

    int queue[enemy_agent_count];

    for (int i = 0; i < enemy_agent_count; i++) {
        if (assigned_to_group[i]) {
            continue;
        }

        AgentGroup new_group;
        new_group.agent_count = 0;
        long long total_x = 0, total_y = 0;
        
        int queue_head = 0;
        int queue_tail = 0;

        assigned_to_group[i] = true;
        new_group.member_indices[new_group.agent_count++] = i;
        total_x += enemy_agents[i].x;
        total_y += enemy_agents[i].y;
        queue[queue_tail++] = i;

        while (queue_head < queue_tail) {
            int current_idx = queue[queue_head++];

            for (int k = 0; k < enemy_agent_count; k++) {
                if (assigned_to_group[k]) {
                    continue;
                }

                if (manhattan_distance(enemy_agents[current_idx].x, enemy_agents[current_idx].y, enemy_agents[k].x, enemy_agents[k].y) <= 2) {
                    assigned_to_group[k] = true;
                    new_group.member_indices[new_group.agent_count++] = k;
                    total_x += enemy_agents[k].x;
                    total_y += enemy_agents[k].y;
                    queue[queue_tail++] = k;
                }
            }
        }

        if (new_group.agent_count > 0) {
            new_group.center.x = round((double)total_x / new_group.agent_count);
            new_group.center.y = round((double)total_y / new_group.agent_count);
            enemy_groups[*group_count] = new_group;
            (*group_count)++;
        }
    }
}

Coordinate find_best_target_for_agent(AgentState* my_agent, int group_count, AgentGroup enemy_groups[], int my_agent_count, AgentState my_agents[], bool claimed_groups[]) {
    Coordinate best_target = {-1, -1};
    int min_dist = 1000;
    int best_group_index = -1;

    for (int i = 0; i < group_count; i++) {
        if (claimed_groups[i]) continue;

        Coordinate target_pos = enemy_groups[i].center;

        bool safe_for_all_friendlies = true;
        for (int j = 0; j < my_agent_count; j++) {
            if (manhattan_distance(my_agents[j].x, my_agents[j].y, target_pos.x, target_pos.y) <= 1) {
                safe_for_all_friendlies = false;
                break;
            }
        }
        
        if (!safe_for_all_friendlies) continue;

        int dist = manhattan_distance(my_agent->x, my_agent->y, target_pos.x, target_pos.y);

        if (dist < min_dist) {
            min_dist = dist;
            best_target = target_pos;
            best_group_index = i;
        } else if (dist == min_dist) {
            if (best_target.x == -1 || target_pos.x < best_target.x) {
                best_target = target_pos;
                best_group_index = i;
            } else if (target_pos.x == best_target.x && target_pos.y < best_target.y) {
                best_target = target_pos;
                best_group_index = i;
            }
        }
    }
    
    if(best_group_index != -1) {
        claimed_groups[best_group_index] = true;
    }

    return best_target;
}

void execute_action(AgentState* my_agent, Coordinate target) {
    if (target.x == -1) {
        printf("%d;HUNKER_DOWN\n", my_agent->id);
        fflush(stdout);
        return;
    }

    double euclidean_dist = euclidean_distance(my_agent->x, my_agent->y, target.x, target.y);
    int manhattan_dist = manhattan_distance(my_agent->x, my_agent->y, target.x, target.y);
    int chebyshev_dist = chebyshev_distance(my_agent->x, my_agent->y, target.x, target.y);

    if (manhattan_dist <= 2 && my_agent->bombs > 0) {
        fprintf(stderr, "Agent ID %d (%d,%d) -> Target (%d,%d), Manhattan: %d, Bombs: %d - THROWING\n", 
                my_agent->id, my_agent->x, my_agent->y, target.x, target.y, manhattan_dist, my_agent->bombs);
        printf("%d;THROW %d %d\n", my_agent->id, target.x, target.y);
        fflush(stdout);
    } else {
        fprintf(stderr, "Agent ID %d (%d,%d) -> Target (%d,%d), Manhattan: %d, Bombs: %d - MOVING\n", 
                my_agent->id, my_agent->x, my_agent->y, target.x, target.y, manhattan_dist, my_agent->bombs);
        printf("%d;MOVE %d %d\n", my_agent->id, target.x, target.y);
        fflush(stdout);
    }
}

int main() {
    // === BAŞLANGIÇ VERİLERİNİ OKU ===
    scanf("%d", &my_id);
    scanf("%d", &agent_data_count);
    
    fprintf(stderr, "My player ID: %d, Total agents: %d\n", my_id, agent_data_count);
    
    for (int i = 0; i < agent_data_count; i++) {
        scanf("%d%d", &all_agent_data[i].id, &all_agent_data[i].player);
        int dummy[4];
        scanf("%d%d%d%d", &dummy[0], &dummy[1], &dummy[2], &dummy[3]);
        
        if (all_agent_data[i].player == my_id) {
            fprintf(stderr, "MY AGENT: ID=%d\n", all_agent_data[i].id);
        }
    }
    
    scanf("%d%d", &width, &height);
    fprintf(stderr, "Map size: %dx%d\n", width, height);
    
    for (int i = 0; i < width * height; i++) {
        int x, y, type;
        scanf("%d%d%d", &x, &y, &type);
    }
    fprintf(stderr, "Initial data reading completed\n");

    bool claimed_groups[20];

    while (1) {
        // === HER TUR VERİLERİNİ OKU (UNIFIED) ===
        AgentState my_agents[2];
        AgentState enemy_agents[20];
        int my_agent_count = 0;
        int enemy_agent_count = 0;

        int agent_count;
        scanf("%d", &agent_count);
        fprintf(stderr, "Reading %d agents this turn\n", agent_count);

        // Ajan verilerini oku
        for (int i = 0; i < agent_count; i++) {
            int id, x, y, cooldown, splash_bombs, wetness;
            scanf("%d%d%d%d%d%d", &id, &x, &y, &cooldown, &splash_bombs, &wetness);
            
            bool is_mine = false;
            for (int j = 0; j < agent_data_count; j++) {
                if (all_agent_data[j].id == id && all_agent_data[j].player == my_id) {
                    is_mine = true;
                    break;
                }
            }
            
            if (is_mine) {
                my_agents[my_agent_count].id = id;
                my_agents[my_agent_count].x = x;
                my_agents[my_agent_count].y = y;
                my_agents[my_agent_count].bombs = splash_bombs;
                my_agent_count++;
            } else {
                enemy_agents[enemy_agent_count].id = id;
                enemy_agents[enemy_agent_count].x = x;
                enemy_agents[enemy_agent_count].y = y;
                enemy_agents[enemy_agent_count].bombs = splash_bombs;
                enemy_agent_count++;
            }
        }

        // Deneysel: mystery value okuma
        int mystery_value;
        scanf("%d", &mystery_value);
        fprintf(stderr, "Mystery value: %d\n", mystery_value);
        
        for (int i = 0; i < mystery_value; i++) {
            int mystery_data;
            scanf("%d", &mystery_data);
        }

        // Tile verileri
        int tile_count;
        scanf("%d", &tile_count);
        for (int i = 0; i < tile_count; i++) {
            int x, y, type;
            scanf("%d%d%d", &x, &y, &type);
        }

        // Entity verileri
        int entity_count;
        scanf("%d", &entity_count);
        for (int i = 0; i < entity_count; i++) {
            int id, type, x, y, param1, param2;
            scanf("%d%d%d%d%d%d", &id, &type, &x, &y, &param1, &param2);
        }
        
        fprintf(stderr, "Turn data reading completed - My agents: %d, Enemy agents: %d\n", my_agent_count, enemy_agent_count);

        // === STRATEJİ UYGULA ===
        AgentGroup enemy_groups[20];
        int group_count = 0;
        find_enemy_groups(enemy_agent_count, enemy_agents, &group_count, enemy_groups);
        
        memset(claimed_groups, false, sizeof(claimed_groups));

        for (int i = 0; i < my_agent_count; i++) {
            Coordinate target = find_best_target_for_agent(&my_agents[i], group_count, enemy_groups, my_agent_count, my_agents, claimed_groups);
            execute_action(&my_agents[i], target);
        }
        
        if (my_agent_count == 0) {
            fprintf(stderr, "No agents available this turn\n");
        }
    }
    return 0;
}
