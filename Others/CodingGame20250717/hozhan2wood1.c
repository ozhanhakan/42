//wood1 completed
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX_AGENTS 30
#define MAX_WIDTH 20
#define MAX_HEIGHT 10
#define BOMB_RANGE 4
#define MAX_ENEMY_GROUPS 3

typedef struct {
    int id, player, x, y;
    int splashBombs;
    bool has_thrown_bomb;
    int bomb_target_x, bomb_target_y;
} Agent;

typedef struct {
    int x, y;
    bool destroyed;
    bool already_bombed;
    bool initialized;
} EnemyGroup;

int width, height;
int tile_type[MAX_WIDTH][MAX_HEIGHT];
Agent agents[MAX_AGENTS];
int agent_count, my_agent_count, my_id;
EnemyGroup enemy_groups[MAX_ENEMY_GROUPS] = {{0}};
int current_group_index = 0;
bool groups_initialized = false;

bool is_valid_position(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height && tile_type[x][y] == 0;
}

bool has_friendly_fire(int x, int y) {
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].player == my_id && 
            abs(agents[i].x - x) <= 1 && 
            abs(agents[i].y - y) <= 1) {
            return true;
        }
    }
    return false;
}

// Düşman sayısını hesapla
int count_enemies_in_group(int center_x, int center_y) {
    int count = 0;
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].player != my_id && 
            abs(agents[i].x - center_x) <= 1 && 
            abs(agents[i].y - center_y) <= 1) {
            count++;
        }
    }
    return count;
}

// Başlangıçtaki düşman gruplarını bul
void initialize_enemy_groups() {
    fprintf(stderr, "Initializing enemy groups...\n");
    
    // Düşman haritasını oluştur
    bool enemy_map[MAX_WIDTH][MAX_HEIGHT] = {false};
    int density[MAX_WIDTH][MAX_HEIGHT] = {0};
    
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].player != my_id) {
            if (agents[i].x >= 0 && agents[i].x < width && 
                agents[i].y >= 0 && agents[i].y < height) {
                enemy_map[agents[i].x][agents[i].y] = true;
            }
        }
    }

    // Düşman yoğunluğunu hesapla
    for (int x = 1; x < width-1; x++) {
        for (int y = 1; y < height-1; y++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (enemy_map[x+dx][y+dy]) {
                        density[x][y]++;
                    }
                }
            }
        }
    }

    // En yoğun 3 noktayı bul
    for (int g = 0; g < MAX_ENEMY_GROUPS; g++) {
        int max_density = 0;
        int best_x = -1, best_y = -1;
        
        for (int x = 1; x < width-1; x++) {
            for (int y = 1; y < height-1; y++) {
                if (density[x][y] > max_density && !has_friendly_fire(x,y)) {
                    bool already_targeted = false;
                    for (int i = 0; i < g; i++) {
                        if (enemy_groups[i].initialized && 
                            abs(enemy_groups[i].x - x) < 3 && abs(enemy_groups[i].y - y) < 3) {
                            already_targeted = true;
                            break;
                        }
                    }
                    
                    if (!already_targeted) {
                        max_density = density[x][y];
                        best_x = x;
                        best_y = y;
                    }
                }
            }
        }
        
        if (best_x != -1) {
            enemy_groups[g].x = best_x;
            enemy_groups[g].y = best_y;
            enemy_groups[g].destroyed = false;
            enemy_groups[g].already_bombed = false;
            enemy_groups[g].initialized = true;
            
            fprintf(stderr, "Enemy group %d found at (%d,%d) with density %d\n", 
                   g, best_x, best_y, max_density);
            
            // Bu bölgeyi temizle
            for (int dx = -2; dx <= 2; dx++) {
                for (int dy = -2; dy <= 2; dy++) {
                    int nx = best_x + dx;
                    int ny = best_y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        density[nx][ny] = 0;
                    }
                }
            }
        }
    }
    
    groups_initialized = true;
}
// update_enemy_groups() fonksiyonunda şu kısmı değiştirin
void update_enemy_groups() {
    // Bomba atılan grupları kontrol et
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].player == my_id && agents[i].has_thrown_bomb) {
            int bomb_x = agents[i].bomb_target_x;
            int bomb_y = agents[i].bomb_target_y;
            
            // DEBUG: Bomba atılan bölgedeki düşmanları kontrol et
            int enemies_at_target = count_enemies_in_group(bomb_x, bomb_y);
            fprintf(stderr, "DEBUG: Bomba atılan konum (%d,%d)'de %d düşman var\n", 
                   bomb_x, bomb_y, enemies_at_target);
            
            // Hedef grubu bul
            for (int g = 0; g < MAX_ENEMY_GROUPS; g++) {
                if (enemy_groups[g].initialized && 
                    enemy_groups[g].x == bomb_x && 
                    enemy_groups[g].y == bomb_y) {
                    
                    // Bu gruba bomba atıldı olarak işaretle
                    enemy_groups[g].already_bombed = true;
                    enemy_groups[g].destroyed = true;
                    
                    fprintf(stderr, "Group %d at (%d,%d) marked as DESTROYED after bomb hit!\n", 
                          g, enemy_groups[g].x, enemy_groups[g].y);
                }
            }
            
            // Bomba atma durumunu sıfırla
            agents[i].has_thrown_bomb = false;
        }
    }
    
    // ÖNEMLİ: Bu kısmı kaldırıyoruz veya devre dışı bırakıyoruz!
    // Gruplar sadece bombalandığında "destroyed" olacak
    // Düşman sayısı 0 olsa bile grupları destroyed olarak işaretlememeliyiz
    
    /* 
    // Grupların mevcut durumunu kontrol et - BU KISMI KALDIRIYORUZ
    for (int g = 0; g < MAX_ENEMY_GROUPS; g++) {
        if (enemy_groups[g].initialized && !enemy_groups[g].destroyed) {
            int enemies = count_enemies_in_group(enemy_groups[g].x, enemy_groups[g].y);
            fprintf(stderr, "DEBUG: Group %d at (%d,%d) has %d enemies\n", 
                   g, enemy_groups[g].x, enemy_groups[g].y, enemies);
                   
            if (enemies == 0) {
                enemy_groups[g].destroyed = true;
                fprintf(stderr, "Group %d at (%d,%d) confirmed DESTROYED by enemy count!\n", 
                      g, enemy_groups[g].x, enemy_groups[g].y);
            }
        }
    }
    */
    
    // Bunun yerine, sadece düşman sayısını raporlayalım
    for (int g = 0; g < MAX_ENEMY_GROUPS; g++) {
        if (enemy_groups[g].initialized && !enemy_groups[g].destroyed) {
            int enemies = count_enemies_in_group(enemy_groups[g].x, enemy_groups[g].y);
            fprintf(stderr, "DEBUG: Group %d at (%d,%d) has %d enemies\n", 
                   g, enemy_groups[g].x, enemy_groups[g].y, enemies);
        }
    }
    
    // Grupların durumunu raporla
    int active_count = 0;
    fprintf(stderr, "Groups status: ");
    for (int g = 0; g < MAX_ENEMY_GROUPS; g++) {
        if (enemy_groups[g].initialized) {
            fprintf(stderr, "[G%d:(%d,%d):%s:%s] ", 
                  g, enemy_groups[g].x, enemy_groups[g].y,
                  enemy_groups[g].destroyed ? "destroyed" : "active",
                  enemy_groups[g].already_bombed ? "bombed" : "not_bombed");
            
            if (!enemy_groups[g].destroyed) {
                active_count++;
            }
        }
        else {
            fprintf(stderr, "[G%d:not_initialized] ", g);
        }
    }
    fprintf(stderr, "\nActive groups: %d\n", active_count);
}

void move_to_target(Agent a, int target_x, int target_y, int* mx, int* my) {
    int dx = (target_x > a.x) ? 1 : (target_x < a.x) ? -1 : 0;
    int dy = (target_y > a.y) ? 1 : (target_y < a.y) ? -1 : 0;

    if (dx != 0 && is_valid_position(a.x + dx, a.y)) {
        *mx = a.x + dx;
        *my = a.y;
        return;
    }
    if (dy != 0 && is_valid_position(a.x, a.y + dy)) {
        *mx = a.x;
        *my = a.y + dy;
        return;
    }

    int directions[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    for (int i = 0; i < 4; i++) {
        int nx = a.x + directions[i][0];
        int ny = a.y + directions[i][1];
        if (is_valid_position(nx, ny)) {
            *mx = nx;
            *my = ny;
            return;
        }
    }

    *mx = a.x;
    *my = a.y;
}

void update_current_target() {
    // Öncelikli hedefi seç (yok edilmemiş, bombalanmamış ve geçerli olan)
    current_group_index = -1;
    for (int i = 0; i < MAX_ENEMY_GROUPS; i++) {
        if (enemy_groups[i].initialized && !enemy_groups[i].destroyed && !enemy_groups[i].already_bombed) {
            current_group_index = i;
            break;
        }
    }
    
    // Eğer bombalanmamış grup yoksa, yok edilmemiş herhangi bir grup seç
    if (current_group_index == -1) {
        for (int i = 0; i < MAX_ENEMY_GROUPS; i++) {
            if (enemy_groups[i].initialized && !enemy_groups[i].destroyed) {
                current_group_index = i;
                break;
            }
        }
    }
    
    if (current_group_index == -1) {
        fprintf(stderr, "WARNING: No valid targets found!\n");
    } else {
        fprintf(stderr, "Current target is group %d at (%d,%d) %s\n", 
               current_group_index, 
               enemy_groups[current_group_index].x, 
               enemy_groups[current_group_index].y,
               enemy_groups[current_group_index].already_bombed ? "(already bombed)" : "");
    }
}

void assign_targets() {
    bool assigned[MAX_AGENTS] = {false};
    
    if (current_group_index >= 0 && current_group_index < MAX_ENEMY_GROUPS && 
        enemy_groups[current_group_index].initialized && 
        !enemy_groups[current_group_index].destroyed) {
        
        EnemyGroup target = enemy_groups[current_group_index];
        int best_agent = -1;
        int min_dist = INT_MAX;
        
        // Ana hedefe en yakın ajanı bul
        for (int i = 0; i < agent_count; i++) {
            if (agents[i].player == my_id && !assigned[i] && agents[i].id != 0) {
                int dist = abs(agents[i].x - target.x) + abs(agents[i].y - target.y);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_agent = i;
                }
            }
        }
        
        if (best_agent != -1) {
            assigned[best_agent] = true;
            Agent* a = &agents[best_agent];
            int dist = abs(a->x - target.x) + abs(a->y - target.y);
            
            if (dist <= BOMB_RANGE && a->splashBombs > 0 && !target.already_bombed) {
                // Bomba at - ama sadece önceden bombalanmamışsa
                a->has_thrown_bomb = true;
                a->bomb_target_x = target.x;
                a->bomb_target_y = target.y;
                
                printf("%d;THROW %d %d;MESSAGE Bombing G%d\n", 
                      a->id, target.x, target.y, current_group_index);
            } else {
                // Hareket et
                int mx, my;
                move_to_target(*a, target.x, target.y, &mx, &my);
                
                // Eğer grup bombalandıysa, bunu belirt
                if (target.already_bombed) {
                    printf("%d;MOVE %d %d;MESSAGE G%d already bombed\n", 
                          a->id, mx, my, current_group_index);
                } else {
                    printf("%d;MOVE %d %d;MESSAGE Moving to G%d\n", 
                          a->id, mx, my, current_group_index);
                }
            }
        }
    }
    
    // Diğer gruplar için ajanlar ata
    for (int g = 0; g < MAX_ENEMY_GROUPS; g++) {
        if (g == current_group_index || !enemy_groups[g].initialized || enemy_groups[g].destroyed) 
            continue;
        
        int best_agent = -1;
        int min_dist = INT_MAX;
        
        for (int i = 0; i < agent_count; i++) {
            if (agents[i].player == my_id && !assigned[i] && agents[i].id != 0) {
                int dist = abs(agents[i].x - enemy_groups[g].x) + 
                           abs(agents[i].y - enemy_groups[g].y);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_agent = i;
                }
            }
        }
        
        if (best_agent != -1) {
            assigned[best_agent] = true;
            Agent* a = &agents[best_agent];
            int dist = abs(a->x - enemy_groups[g].x) + abs(a->y - enemy_groups[g].y);
            
            if (dist <= BOMB_RANGE && a->splashBombs > 0 && !enemy_groups[g].already_bombed) {
                // Bomba at - ama sadece önceden bombalanmamışsa
                a->has_thrown_bomb = true;
                a->bomb_target_x = enemy_groups[g].x;
                a->bomb_target_y = enemy_groups[g].y;
                
                printf("%d;THROW %d %d;MESSAGE Bombing G%d\n", 
                      a->id, enemy_groups[g].x, enemy_groups[g].y, g);
            } else {
                int mx, my;
                move_to_target(*a, enemy_groups[g].x, enemy_groups[g].y, &mx, &my);
                
                // Eğer grup bombalandıysa, bunu belirt
                if (enemy_groups[g].already_bombed) {
                    printf("%d;MOVE %d %d;MESSAGE G%d already bombed\n", 
                          a->id, mx, my, g);
                } else {
                    printf("%d;MOVE %d %d;MESSAGE Moving to G%d\n", 
                          a->id, mx, my, g);
                }
            }
        }
    }
    
    // Kalan ajanları merkeze yönlendir
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].player == my_id && !assigned[i] && agents[i].id != 0) {
            int mx, my;
            move_to_target(agents[i], width/2, height/2, &mx, &my);
            printf("%d;MOVE %d %d;MESSAGE Patrolling\n", agents[i].id, mx, my);
        }
    }
}

void read_all_input() {
    scanf("%d", &agent_count);
    for (int i = 0; i < agent_count; i++) {
        int id, x, y, cooldown, bombs, wetness;
        scanf("%d%d%d%d%d%d", &id, &x, &y, &cooldown, &bombs, &wetness);
        
        int found = 0;
        for (int j = 0; j < MAX_AGENTS; j++) {
            if (agents[j].id == id) {
                agents[j].x = x;
                agents[j].y = y;
                agents[j].splashBombs = bombs;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            for (int j = 0; j < MAX_AGENTS; j++) {
                if (agents[j].id == 0) {
                    agents[j] = (Agent){id, (j < 2) ? my_id : 1 - my_id, x, y, bombs, 
                                       false, -1, -1};
                    break;
                }
            }
        }
    }
    
    scanf("%d", &my_agent_count);
}

int main() {
    scanf("%d", &my_id);
    int agent_data_count;
    scanf("%d", &agent_data_count);
    for (int i = 0; i < agent_data_count; i++) {
        int id, player, cooldown, range, power, bombs;
        scanf("%d%d%d%d%d%d", &id, &player, &cooldown, &range, &power, &bombs);
    }
    
    scanf("%d%d", &width, &height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int tx, ty, t;
            scanf("%d%d%d", &tx, &ty, &t);
            tile_type[tx][ty] = t;
        }
    }

    int turn = 0;
    while (turn++ < 40) {
        read_all_input();
        
        // Düşman gruplarını yalnızca bir kez başlangıçta tespit et
        if (!groups_initialized) {
            initialize_enemy_groups();
        } else {
            // Sadece mevcut grupların durumunu güncelle
            update_enemy_groups();
        }
        
        update_current_target();
        assign_targets();
        fflush(stdout);
    }

    return 0;
}