#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 30  // Maksimum harita boyutu
#define MAX_GROUPS 3
#define MAX_AGENTS 100
#define BOMB_RANGE 3  // Gerçek menzil değeri

typedef struct {
    int id;
    int x, y;
    int bombs;
    bool is_mine;
    int stuck_count;
    int last_x, last_y;
} Agent;

typedef struct {
    int x, y;
    bool bombed;
    int enemy_count;
} Group;

// Global değişkenler
int width, height;
int my_id;
int grid[MAX_SIZE][MAX_SIZE];
Agent agents[MAX_AGENTS];
int agent_count = 0;
int my_agent_count = 0;
Group groups[MAX_GROUPS];
bool groups_initialized = false;

// Yardımcı fonksiyonlar
bool is_valid(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height && grid[x][y] == 0;
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int count_enemies(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return 0;
    
    int count = 0;
    for (int i = 0; i < agent_count; i++) {
        if (!agents[i].is_mine && 
            abs(agents[i].x - x) <= 1 && 
            abs(agents[i].y - y) <= 1) {
            count++;
        }
    }
    return count;
}

bool has_friendly(int x, int y) {
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].is_mine && 
            abs(agents[i].x - x) <= 1 && 
            abs(agents[i].y - y) <= 1) {
            return true;
        }
    }
    return false;
}

// Düşman gruplarını bul
void find_enemy_groups() {
    fprintf(stderr, "Finding enemy groups...\n");
    
    // Grupları sıfırla
    for (int i = 0; i < MAX_GROUPS; i++) {
        groups[i].x = -1;
        groups[i].y = -1;
        groups[i].bombed = false;
        groups[i].enemy_count = 0;
    }
    
    // Düşman yoğunluğunu hesapla
    int density[MAX_SIZE][MAX_SIZE] = {0};
    
    for (int i = 0; i < agent_count; i++) {
        if (!agents[i].is_mine) {
            // Bu düşmanın etrafındaki karelerin yoğunluğunu artır
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = agents[i].x + dx;
                    int ny = agents[i].y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        density[nx][ny]++;
                    }
                }
            }
        }
    }
    
    // En yoğun grupları bul
    for (int g = 0; g < MAX_GROUPS; g++) {
        int best_x = -1, best_y = -1, max_density = 0;
        
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (density[x][y] > max_density && !has_friendly(x, y)) {
                    // Önceki gruplarla çakışma kontrolü
                    bool overlap = false;
                    for (int i = 0; i < g; i++) {
                        if (groups[i].x != -1 && 
                            abs(groups[i].x - x) < 3 && 
                            abs(groups[i].y - y) < 3) {
                            overlap = true;
                            break;
                        }
                    }
                    
                    if (!overlap) {
                        max_density = density[x][y];
                        best_x = x;
                        best_y = y;
                    }
                }
            }
        }
        
        if (best_x != -1) {
            groups[g].x = best_x;
            groups[g].y = best_y;
            groups[g].bombed = false;
            groups[g].enemy_count = count_enemies(best_x, best_y);
            
            fprintf(stderr, "Group %d found at (%d,%d) with density %d and %d enemies\n", 
                   g, best_x, best_y, max_density, groups[g].enemy_count);
            
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
        } else {
            fprintf(stderr, "No valid group %d found\n", g);
        }
    }
    
    groups_initialized = true;
}

// Her ajan için en iyi hedefi bul
void assign_targets(int* agent_targets) {
    for (int i = 0; i < agent_count; i++) {
        if (!agents[i].is_mine) continue;
        
        int best_target = -1;
        int min_dist = 1000;
        
        // Bombalanmamış gruplar arasından en yakın olanı seç
        for (int g = 0; g < MAX_GROUPS; g++) {
            if (groups[g].x == -1 || groups[g].bombed) continue;
            
            int dist = manhattan_distance(agents[i].x, agents[i].y, groups[g].x, groups[g].y);
            if (dist < min_dist) {
                min_dist = dist;
                best_target = g;
            }
        }
        
        // Hiç bombalanmamış grup kalmadıysa, en yakın grubu seç
        if (best_target == -1) {
            for (int g = 0; g < MAX_GROUPS; g++) {
                if (groups[g].x == -1) continue;
                
                int dist = manhattan_distance(agents[i].x, agents[i].y, groups[g].x, groups[g].y);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_target = g;
                }
            }
        }
        
        agent_targets[i] = best_target;
    }
}

// İyileştirilmiş hareket algoritması
void move_to(Agent* agent, int tx, int ty, int* mx, int* my) {
    // Önceki konumu kaydet (takılma tespiti için)
    agent->last_x = agent->x;
    agent->last_y = agent->y;
    
    // Hedefe yönelme vektörü
    int dx = tx > agent->x ? 1 : (tx < agent->x ? -1 : 0);
    int dy = ty > agent->y ? 1 : (ty < agent->y ? -1 : 0);
    
    // Hedefe mesafe
    int dist_x = abs(tx - agent->x);
    int dist_y = abs(ty - agent->y);
    
    // X veya Y ekseninde öncelik belirle
    bool x_priority = dist_x > dist_y;
    
    // Takılmayı önlemek için hamle seçenekleri
    int options[4][2];
    int option_count = 0;
    
    // Hedefe doğru tercih edilen hamleler
    if (x_priority) {
        if (dx != 0 && is_valid(agent->x + dx, agent->y))
            options[option_count][0] = agent->x + dx, options[option_count++][1] = agent->y;
        if (dy != 0 && is_valid(agent->x, agent->y + dy))
            options[option_count][0] = agent->x, options[option_count++][1] = agent->y + dy;
    } else {
        if (dy != 0 && is_valid(agent->x, agent->y + dy))
            options[option_count][0] = agent->x, options[option_count++][1] = agent->y + dy;
        if (dx != 0 && is_valid(agent->x + dx, agent->y))
            options[option_count][0] = agent->x + dx, options[option_count++][1] = agent->y;
    }
    
    // Alternatif yönler
    int dirs[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    for (int i = 0; i < 4; i++) {
        int nx = agent->x + dirs[i][0];
        int ny = agent->y + dirs[i][1];
        if (is_valid(nx, ny)) {
            // Önceki konuma geri dönmemeye çalış (eğer takıldıysa)
            if (agent->stuck_count < 3 || !(nx == agent->last_x && ny == agent->last_y)) {
                options[option_count][0] = nx;
                options[option_count++][1] = ny;
            }
        }
    }
    
    // En iyi seçeneği bul
    if (option_count > 0) {
        int best_opt = 0;
        int min_opt_dist = 1000;
        
        for (int i = 0; i < option_count; i++) {
            int d = manhattan_distance(options[i][0], options[i][1], tx, ty);
            if (d < min_opt_dist) {
                min_opt_dist = d;
                best_opt = i;
            }
        }
        
        *mx = options[best_opt][0];
        *my = options[best_opt][1];
    } else {
        // Hareket edemiyorsa yerinde kal
        *mx = agent->x;
        *my = agent->y;
    }
    
    // Takılma durumunu güncelle
    if (*mx == agent->x && *my == agent->y) {
        agent->stuck_count++;
        fprintf(stderr, "Agent %d stuck at (%d,%d) for %d turns\n", 
               agent->id, agent->x, agent->y, agent->stuck_count);
    } else if (*mx == agent->last_x && *my == agent->last_y) {
        agent->stuck_count++;
        fprintf(stderr, "Agent %d going back and forth between (%d,%d) and (%d,%d) for %d turns\n",
               agent->id, agent->last_x, agent->last_y, agent->x, agent->y, agent->stuck_count);
    } else {
        agent->stuck_count = 0;
    }
}

// Oyun stratejisini uygula
void execute_turn() {
    // İlk turda düşman gruplarını bul
    if (!groups_initialized) {
        find_enemy_groups();
    }
    
    // Grupları güncelle
    for (int i = 0; i < MAX_GROUPS; i++) {
        if (groups[i].x != -1) {
            groups[i].enemy_count = count_enemies(groups[i].x, groups[i].y);
        }
    }
    
    // Grupları raporla
    fprintf(stderr, "Groups: ");
    for (int i = 0; i < MAX_GROUPS; i++) {
        if (groups[i].x != -1) {
            fprintf(stderr, "[G%d:(%d,%d):%d enemies:%s] ", 
                  i, groups[i].x, groups[i].y, groups[i].enemy_count,
                  groups[i].bombed ? "bombed" : "not_bombed");
        } else {
            fprintf(stderr, "[G%d:invalid] ", i);
        }
    }
    fprintf(stderr, "\n");
    
    // Ajanları raporla
    fprintf(stderr, "My agents: ");
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].is_mine) {
            fprintf(stderr, "[ID:%d at (%d,%d) with %d bombs] ", 
                  agents[i].id, agents[i].x, agents[i].y, agents[i].bombs);
        }
    }
    fprintf(stderr, "\n");
    
    // Her ajan için hedef belirle
    int agent_targets[MAX_AGENTS];
    assign_targets(agent_targets);
    
    // Ajanları hedeflerine göre yönlendir
    for (int i = 0; i < agent_count; i++) {
        if (!agents[i].is_mine) continue;
        
        int target = agent_targets[i];
        if (target == -1) {
            // Hedef yoksa merkeze git
            int mx, my;
            move_to(&agents[i], width/2, height/2, &mx, &my);
            printf("%d;MOVE %d %d;MESSAGE Patrolling center\n", 
                  agents[i].id, mx, my);
            continue;
        }
        
        // Hedef var, bomba atabilir miyiz?
        int dist = manhattan_distance(agents[i].x, agents[i].y, 
                                     groups[target].x, groups[target].y);
        
        if (agents[i].bombs > 0 && dist <= BOMB_RANGE && !groups[target].bombed) {
            printf("%d;THROW %d %d;MESSAGE Bombing G%d\n", 
                  agents[i].id, groups[target].x, groups[target].y, target);
            groups[target].bombed = true;
        } else {
            // Hedefe doğru ilerle
            int mx, my;
            move_to(&agents[i], groups[target].x, groups[target].y, &mx, &my);
            
            if (groups[target].bombed) {
                printf("%d;MOVE %d %d;MESSAGE Moving to G%d (already bombed)\n", 
                      agents[i].id, mx, my, target);
            } else {
                printf("%d;MOVE %d %d;MESSAGE Moving to G%d (dist:%d)\n", 
                      agents[i].id, mx, my, target, dist);
            }
        }
    }
}

// Tüm girdiyi oku
void read_input() {
    static bool first_turn = true;
    
    // İlk turdaysak oyun ayarlarını oku
    if (first_turn) {
        scanf("%d", &my_id);
        
        int agent_data_count;
        scanf("%d", &agent_data_count);
        for (int i = 0; i < agent_data_count; i++) {
            int id, player, cooldown, range, power, bombs;
            scanf("%d%d%d%d%d%d", &id, &player, &cooldown, &range, &power, &bombs);
        }
        
        scanf("%d%d", &width, &height);
        fprintf(stderr, "Map dimensions: %dx%d\n", width, height);
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int tx, ty, t;
                scanf("%d%d%d", &tx, &ty, &t);
                if (tx >= 0 && tx < width && ty >= 0 && ty < height) {
                    grid[tx][ty] = t;
                }
            }
        }
        
        first_turn = false;
    }
    
    // Her tur için ajan bilgilerini oku
    scanf("%d", &agent_count);
    agent_count = agent_count < MAX_AGENTS ? agent_count : MAX_AGENTS;
    
    for (int i = 0; i < agent_count; i++) {
        int id, x, y, cooldown, bombs, wetness;
        scanf("%d%d%d%d%d%d", &id, &x, &y, &cooldown, &bombs, &wetness);
        
        // İlk defa bu ajanı görüyorsak, başlat
        if (i == 0 || agents[i].id != id) {
            agents[i].id = id;
            agents[i].last_x = x;
            agents[i].last_y = y;
            agents[i].stuck_count = 0;
        }
        
        agents[i].x = x;
        agents[i].y = y;
        agents[i].bombs = bombs;
        agents[i].is_mine = false;  // Varsayılan olarak düşman
    }
    
    // Kendi ajanlarımızın sayısını oku
    scanf("%d", &my_agent_count);
    my_agent_count = my_agent_count < agent_count ? my_agent_count : agent_count;
    
    // İlk my_agent_count ajanı bizim olarak işaretle
    for (int i = 0; i < my_agent_count; i++) {
        agents[i].is_mine = true;
    }
}

int main() {
    int turn = 0;
    while (turn++ < 100) {
        read_input();
        execute_turn();
        fflush(stdout);
    }
    return 0;
}