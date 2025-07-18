include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// --- Ustanın Notu: Struct Tanımlamaları (Veri Planlarımız) ---

typedef struct {
    int id;
    int player;
} AgentData;

typedef struct {
    int id;
    int x, y;
    int splash_bombs;
    int last_x, last_y;
} AgentState;

typedef struct {
    int x, y;
    int type;
} Tile;

typedef struct {
    int center_x, center_y;
    int size;
    bool contains_friend;
} EnemyGroup;


// --- Ustanın Notu: Global Değişkenler ---
int my_id;
int width, height;
int turn_counter = 0;
Tile map[20][10];
AgentState previous_agents[2];
int previous_agent_count = 0;
int esir_agent_id = -1;


// --- Ustanın Notu: Yardımcı Fonksiyonlar ---

int get_manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int count_adjacent_walls(int x, int y) {
    int wall_count = 0;
    if (y <= 0 || map[x][y - 1].type != 0) wall_count++;
    if (y >= height - 1 || map[x][y + 1].type != 0) wall_count++;
    if (x <= 0 || map[x - 1][y].type != 0) wall_count++;
    if (x >= width - 1 || map[x + 1][y].type != 0) wall_count++;
    return wall_count;
}

int find_enemy_groups(AgentState enemy_agents[], int enemy_agent_count, AgentState my_agents[], int my_agent_count, EnemyGroup groups[]) {
    int group_count = 0;
    bool visited[enemy_agent_count];
    for (int i = 0; i < enemy_agent_count; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < enemy_agent_count; i++) {
        if (!visited[i]) {
            EnemyGroup new_group = {0, 0, 0, false};
            int total_x = 0;
            int total_y = 0;
            int member_count = 0;
            
            int queue[enemy_agent_count];
            int queue_start = 0;
            int queue_end = 0;
            
            queue[queue_end++] = i;
            visited[i] = true;

            while(queue_start < queue_end) {
                int current_idx = queue[queue_start++];
                member_count++;
                total_x += enemy_agents[current_idx].x;
                total_y += enemy_agents[current_idx].y;

                for (int j = 0; j < enemy_agent_count; j++) {
                    if (!visited[j]) {
                        if (get_manhattan_distance(enemy_agents[current_idx].x, enemy_agents[current_idx].y, enemy_agents[j].x, enemy_agents[j].y) <= 4) {
                            visited[j] = true;
                            queue[queue_end++] = j;
                        }
                    }
                }
            }

            new_group.size = member_count;
            if (new_group.size > 0) {
                new_group.center_x = round((float)total_x / new_group.size);
                new_group.center_y = round((float)total_y / new_group.size);

                for(int k=0; k < my_agent_count; k++) {
                    if(get_manhattan_distance(my_agents[k].x, my_agents[k].y, new_group.center_x, new_group.center_y) <= 2) {
                        new_group.contains_friend = true;
                        break;
                    }
                }
                groups[group_count++] = new_group;
            }
        }
    }
    return group_count;
}

// --- Ustanın Notu: Karar Fonksiyonları (Modüler Mantık) ---

// "Esir Ajan" için eylem kararı verir.
void decide_esir_agent_action(AgentState* agent, EnemyGroup enemy_groups[], int group_count, char* action_str) {
    fprintf(stderr, "Ajan %d (Esir) için karar veriliyor...\n", agent->id);
    int best_move_x = 12;
    int best_move_y = 1;

    int best_throw_x = -1, best_throw_y = -1;
    int max_group_size = 1;

    if (agent->splash_bombs > 0) {
        for (int g = 0; g < group_count; g++) {
            if (enemy_groups[g].contains_friend) continue;
            if (get_manhattan_distance(agent->x, agent->y, enemy_groups[g].center_x, enemy_groups[g].center_y) > 4) continue;
            if (get_manhattan_distance(agent->x, agent->y, enemy_groups[g].center_x, enemy_groups[g].center_y) <= 1) continue;

            if (enemy_groups[g].size > max_group_size) {
                max_group_size = enemy_groups[g].size;
                best_throw_x = enemy_groups[g].center_x;
                best_throw_y = enemy_groups[g].center_y;
            }
        }
    }

    if (best_throw_x != -1) {
        sprintf(action_str, "%d;MOVE %d %d;THROW %d %d", agent->id, best_move_x, best_move_y, best_throw_x, best_throw_y);
    } else {
        sprintf(action_str, "%d;MOVE %d %d", agent->id, best_move_x, best_move_y);
    }
}

// "Serbest Ajan" için eylem kararı verir.
void decide_serbest_agent_action(AgentState* agent, EnemyGroup enemy_groups[], int group_count, char* action_str) {
    fprintf(stderr, "Ajan %d (Serbest) için karar veriliyor...\n", agent->id);
    int best_move_x = agent->x;
    int best_move_y = agent->y;
    int best_throw_x = -1, best_throw_y = -1;

    int best_target_group_idx = -1;
    int max_group_size = 1;
    for (int g = 0; g < group_count; g++) {
        if (!enemy_groups[g].contains_friend && enemy_groups[g].size > max_group_size) {
            max_group_size = enemy_groups[g].size;
            best_target_group_idx = g;
        }
    }

    if (best_target_group_idx != -1) {
        EnemyGroup* target_group = &enemy_groups[best_target_group_idx];
        int target_x = target_group->center_x;
        int target_y = target_group->center_y;
        fprintf(stderr, "  Serbest ajan hedefi: Grup %d, Merkez(%d,%d)\n", best_target_group_idx, target_x, target_y);
        
        int best_throw_pos_x = -1, best_throw_pos_y = -1;
        int min_dist_to_throw_pos = 1000;

        for(int k=1; k<=4; k++){
            int positions[4][2] = {{target_x, target_y-k}, {target_x, target_y+k}, {target_x-k, target_y}, {target_x+k, target_y}};
            for(int p=0; p<4; p++){
                int px = positions[p][0];
                int py = positions[p][1];
                if(px >= 0 && px < width && py >= 0 && py < height && map[px][py].type == 0){
                    int dist = get_manhattan_distance(agent->x, agent->y, px, py);
                    if(dist < min_dist_to_throw_pos){
                        min_dist_to_throw_pos = dist;
                        best_throw_pos_x = px;
                        best_throw_pos_y = py;
                    }
                }
            }
        }

        if(best_throw_pos_x != -1){
            fprintf(stderr, "  En iyi atış pozisyonu: (%d,%d), Mesafe: %d\n", best_throw_pos_x, best_throw_pos_y, min_dist_to_throw_pos);
            best_move_x = best_throw_pos_x;
            best_move_y = best_throw_pos_y;
        }

        if (agent->splash_bombs > 0 && (agent->x == target_x || agent->y == target_y) && get_manhattan_distance(agent->x, agent->y, target_x, target_y) <= 4) {
            best_throw_x = target_x;
            best_throw_y = target_y;
        }
    } else {
        best_move_x = width / 2;
        best_move_y = height / 2;
    }

    if (best_throw_x != -1) {
        sprintf(action_str, "%d;MOVE %d %d;THROW %d %d", agent->id, agent->x, agent->y, best_throw_x, best_throw_y);
    } else {
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        int final_move_x = agent->x;
        int final_move_y = agent->y;
        int min_dist = get_manhattan_distance(agent->x, agent->y, best_move_x, best_move_y);

        for(int j=0; j<4; j++){
            int next_x = agent->x + dx[j];
            int next_y = agent->y + dy[j];
            bool is_backtrack = (next_x == agent->last_x && next_y == agent->last_y);
            if(next_x >= 0 && next_x < width && next_y >= 0 && next_y < height && map[next_x][next_y].type == 0 && !is_backtrack){
                int dist = get_manhattan_distance(next_x, next_y, best_move_x, best_move_y);
                if(dist < min_dist){
                    min_dist = dist;
                    final_move_x = next_x;
                    final_move_y = next_y;
                }
            }
        }
        sprintf(action_str, "%d;MOVE %d %d", agent->id, final_move_x, final_move_y);
    }
}


// --- Ustanın Notu: Ana Oyun Döngüsü ---
int main() {
    scanf("%d", &my_id);
    int agent_data_count;
    scanf("%d", &agent_data_count);
    AgentData all_agent_data[agent_data_count];
    for (int i = 0; i < agent_data_count; i++) {
        scanf("%d%d", &all_agent_data[i].id, &all_agent_data[i].player);
        int dummy[4];
        scanf("%d%d%d%d", &dummy[0], &dummy[1], &dummy[2], &dummy[3]);
    }
    scanf("%d%d", &width, &height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            scanf("%d%d%d", &map[j][i].x, &map[j][i].y, &map[j][i].type);
        }
    }

    while (1) {
        turn_counter++;
        int agent_count;
        scanf("%d", &agent_count);
        
        AgentState my_agents[2];
        AgentState enemy_agents[50];
        int my_agent_idx = 0;
        int enemy_agent_idx = 0;

        for (int i = 0; i < agent_count; i++) {
            int id, x, y, cooldown, splash_bombs, wetness;
            scanf("%d%d%d%d%d%d", &id, &x, &y, &cooldown, &splash_bombs, &wetness);
            bool is_mine = false;
            for(int j = 0; j < agent_data_count; j++) {
                if(all_agent_data[j].id == id && all_agent_data[j].player == my_id) {
                    is_mine = true;
                    break;
                }
            }
            if (is_mine) {
                my_agents[my_agent_idx] = (AgentState){id, x, y, splash_bombs, -1, -1};
                for(int k = 0; k < previous_agent_count; k++) {
                    if(previous_agents[k].id == id) {
                        my_agents[my_agent_idx].last_x = previous_agents[k].x;
                        my_agents[my_agent_idx].last_y = previous_agents[k].y;
                        break;
                    }
                }
                my_agent_idx++;
            } else {
                enemy_agents[enemy_agent_idx++] = (AgentState){id, x, y, splash_bombs, -1, -1};
            }
        }

        int my_agent_count_input;
        scanf("%d", &my_agent_count_input);

        if (turn_counter == 1 && my_agent_idx == 2) {
            int walls1 = count_adjacent_walls(my_agents[0].x, my_agents[0].y);
            int walls2 = count_adjacent_walls(my_agents[1].x, my_agents[1].y);
            esir_agent_id = (walls1 > walls2) ? my_agents[0].id : my_agents[1].id;
            fprintf(stderr, "Esir Ajan ID: %d olarak belirlendi.\n", esir_agent_id);
        }

        EnemyGroup enemy_groups[50];
        int group_count = find_enemy_groups(enemy_agents, enemy_agent_idx, my_agents, my_agent_idx, enemy_groups);
        
        fprintf(stderr, "Bulunan Düşman Grubu Sayısı: %d\n", group_count);
        for(int i=0; i<group_count; i++) {
            fprintf(stderr, "  Grup %d: Merkez(%d,%d), Boyut:%d, Dost Var Mı:%d\n", i, enemy_groups[i].center_x, enemy_groups[i].center_y, enemy_groups[i].size, enemy_groups[i].contains_friend);
        }

        for (int i = 0; i < my_agent_idx; i++) {
            AgentState* agent = &my_agents[i];
            char action_str[100] = "";

            if (agent->id == esir_agent_id) {
                decide_esir_agent_action(agent, enemy_groups, group_count, action_str);
            } 
            else {
                decide_serbest_agent_action(agent, enemy_groups, group_count, action_str);
            }
            printf("%s\n", action_str);
        }
        
        previous_agent_count = my_agent_idx;
        for(int i = 0; i < my_agent_idx; i++) {
            previous_agents[i] = my_agents[i];
        }
    }
    return 0;
}