#ifndef WATER_BATTLE_HEADERS_H
#define WATER_BATTLE_HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>

/**
 * HYDRO HAVOC - ULTRA OPTIMIZED WATER BATTLE BOT v2.0
 * Dosya 1/5: Temel tanımlar, yapılar ve sabitler
 */

// SABITLER
#define MAX_WIDTH 20
#define MAX_HEIGHT 10
#define MAX_AGENTS 10
#define SPLASH_BOMB_RANGE 4
#define SPLASH_DAMAGE_RADIUS 1
#define SPLASH_DAMAGE 30
#define WETNESS_THRESHOLD 50
#define HIGH_WETNESS_THRESHOLD 70
#define CRITICAL_WETNESS_THRESHOLD 80
#define ELIMINATION_THRESHOLD 100
#define MAX_POSITIONS 5
#define MIN_AGENT_DISTANCE 3
#define SIMULATION_DEPTH 3
#define DANGER_BUFFER_DISTANCE 2
#define MAX_SAFE_WETNESS 40

// ENUMLAR
typedef enum {
    STRATEGY_AGGRESSIVE,
    STRATEGY_BALANCED,
    STRATEGY_DEFENSIVE,
    STRATEGY_SURVIVAL
} StrategyMode;

typedef enum {
    ROLE_ATTACKER,
    ROLE_DEFENDER,
    ROLE_SUPPORT
} AgentRole;

typedef enum {
    TERRAIN_EMPTY = 0,
    TERRAIN_LIGHT_COVER = 1,
    TERRAIN_HEAVY_COVER = 2
} TerrainType;

// YAPILAR
typedef struct {
    int id;
    int player;
    int x, y;
    int shoot_cooldown;
    int current_cooldown;
    int optimal_range;
    int soaking_power;
    int splash_bombs;
    int wetness;
    bool is_mine;
    bool exists;
    int last_positions[MAX_POSITIONS][2];
    int position_index;
    int stuck_count;
    int target_id;
    bool can_hit_target;
    int turns_since_last_shot;
    bool is_in_danger;
    int retreat_turns;
    bool hunker_down_planned;
    int last_hit_turn;
    int damage_taken_recently;
    int successful_hits;
    int failed_actions;
    int shots_fired;
    int shots_landed;
    AgentRole role;
    int priority_score;
    int threat_score;
    bool is_retreating;
    int survival_score;
} Agent;

typedef struct {
    int x, y;
    int type;
} Tile;

typedef struct {
    int x, y;
    int score;
    int enemy_count;
    int friendly_count;
    float avg_enemy_wetness;
    bool valid;
} BombTarget;

typedef struct {
    int x;
    int y;
    int score;
} Position;

// GLOBAL DEĞİŞKENLER
extern int width, height;
extern int my_id;
extern int enemy_id;
extern Tile grid[MAX_WIDTH][MAX_HEIGHT];
extern Agent agents[MAX_AGENTS];
extern int agent_count;
extern int my_agent_count;
extern int enemy_agent_count;
extern int turn;
extern StrategyMode current_strategy;
extern int score_difference;
extern int primary_target_id;
extern int primary_target_wetness;
extern int secondary_target_id;
extern time_t turn_start_time;
extern bool time_pressure;
extern int consecutive_missed_shots;

// TAKTİKSEL HARİTALAR
extern int control_map[MAX_WIDTH][MAX_HEIGHT];
extern int enemy_density[MAX_WIDTH][MAX_HEIGHT];
extern int danger_map[MAX_WIDTH][MAX_HEIGHT];
extern int strategic_value_map[MAX_WIDTH][MAX_HEIGHT];
extern int cover_value_map[MAX_WIDTH][MAX_HEIGHT];
extern int path_cost[MAX_WIDTH][MAX_HEIGHT];
extern bool visited[MAX_WIDTH][MAX_HEIGHT];
extern bool los_map[MAX_WIDTH][MAX_HEIGHT][MAX_WIDTH][MAX_HEIGHT];

// FONKSİYON TANIMLARI
// Yardımcı fonksiyonlar
int manhattan_distance(int x1, int y1, int x2, int y2);
int min(int a, int b);
int max(int a, int b);
bool is_valid_position(int x, int y);
bool is_position_recent(Agent *agent, int x, int y);
void update_position_history(Agent *agent);
bool can_shoot(Agent *agent);
bool can_shoot_target(Agent *shooter, Agent *target);
bool can_throw_bomb(Agent *agent, int target_x, int target_y);
bool line_of_sight(int x1, int y1, int x2, int y2);
void reset_los_cache();
bool is_too_close_to_friendly_agents(int x, int y, Agent *current_agent);
float calculate_cover_factor(Agent *shooter, Agent *target);
int calculate_damage(Agent *shooter, Agent *target);

// Harita güncelleme fonksiyonları
void update_enemy_density();
void update_danger_map();
void update_cover_value_map();
void update_control_map();
void update_strategic_value_map();

// Strateji fonksiyonları
void evaluate_strategy_mode();
void assign_agent_roles();
BombTarget find_best_splash_target(Agent *agent);
int find_best_target(Agent *agent, bool *can_hit);

// Hareket fonksiyonları
bool find_improved_cover(Agent *agent, int enemy_x, int enemy_y, int *cover_x, int *cover_y);
void find_escape_route(Agent *agent, int *move_x, int *move_y);
bool find_optimal_range_position(Agent *agent, Agent *target, int *move_x, int *move_y);
bool approach_target(Agent *agent, Agent *target, int *move_x, int *move_y);
bool find_strategic_area_position(Agent *agent, int *move_x, int *move_y);
bool is_agent_contributing(Agent *agent);
void activate_idle_agent(Agent *agent, int *move_x, int *move_y);
void find_strategic_position(Agent *agent, int *move_x, int *move_y);

// Ana program fonksiyonları
void coordinate_team_strategy();
void read_input();
void execute_strategy();

#endif // WATER_BATTLE_HEADERS_H



/**
 * HYDRO HAVOC - ULTRA OPTIMIZED WATER BATTLE BOT v2.0
 * Dosya 3/5: Harita güncelleme ve analiz fonksiyonları
 */

void update_enemy_density() {
    memset(enemy_density, 0, sizeof(enemy_density));
    
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || agents[i].is_mine) continue;
        
        for (int x = max(0, agents[i].x - 5); x < min(width, agents[i].x + 6); x++) {
            for (int y = max(0, agents[i].y - 5); y < min(height, agents[i].y + 6); y++) {
                int distance = manhattan_distance(x, y, agents[i].x, agents[i].y);
                if (distance <= 5) {
                    int value = (6 - distance) * (100 - min(99, agents[i].wetness)) / 100;
                    enemy_density[x][y] += value;
                }
            }
        }
    }
}

void update_danger_map() {
    memset(danger_map, 0, sizeof(danger_map));
    
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || agents[i].is_mine) continue;
        
        int max_range = agents[i].optimal_range * 2;
        
        for (int x = max(0, agents[i].x - max_range); x < min(width, agents[i].x + max_range + 1); x++) {
            for (int y = max(0, agents[i].y - max_range); y < min(height, agents[i].y + max_range + 1); y++) {
                int distance = manhattan_distance(x, y, agents[i].x, agents[i].y);
                
                if (distance <= max_range) {
                    int threat_factor = 100 - min(95, agents[i].wetness);
                    int danger = (distance <= agents[i].optimal_range) ? 
                                agents[i].soaking_power : agents[i].soaking_power / 2;
                    danger = danger * threat_factor / 100;
                    
                    if (agents[i].splash_bombs > 0 && distance <= SPLASH_BOMB_RANGE + SPLASH_DAMAGE_RADIUS) {
                        danger += 10;
                    }
                    
                    if (grid[x][y].type == 0) {
                        danger_map[x][y] += danger;
                    }
                }
            }
        }
    }
    
    // Anti-clustering tehlike bölgeleri
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || !agents[i].is_mine) continue;
        
        for (int j = i + 1; j < MAX_AGENTS; j++) {
            if (!agents[j].exists || !agents[j].is_mine) continue;
            
            int distance = manhattan_distance(agents[i].x, agents[i].y, agents[j].x, agents[j].y);
            
            if (distance <= MIN_AGENT_DISTANCE) {
                int midpoint_x = (agents[i].x + agents[j].x) / 2;
                int midpoint_y = (agents[i].y + agents[j].y) / 2;
                
                for (int x = max(0, midpoint_x - 2); x <= min(width - 1, midpoint_x + 2); x++) {
                    for (int y = max(0, midpoint_y - 2); y <= min(height - 1, midpoint_y + 2); y++) {
                        if (grid[x][y].type == 0) {
                            danger_map[x][y] += 20;
                        }
                    }
                }
            }
        }
    }
}

void update_cover_value_map() {
    memset(cover_value_map, 0, sizeof(cover_value_map));
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (grid[x][y].type <= 0) continue;
            
            int cover_value = grid[x][y].type * 5;
            
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    
                    if (nx < 0 || nx >= width || ny < 0 || ny >= height || (dx == 0 && dy == 0)) continue;
                    
                    if (grid[nx][ny].type == 0) {
                        cover_value_map[nx][ny] += cover_value;
                        cover_value_map[nx][ny] -= danger_map[nx][ny] / 3;
                    }
                }
            }
        }
    }
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (grid[x][y].type > 0 || !is_valid_position(x, y)) continue;
            
            int cover_count = 0;
            
            for (int i = 0; i < MAX_AGENTS; i++) {
                if (!agents[i].exists || agents[i].is_mine) continue;
                
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int cx = x + dx;
                        int cy = y + dy;
                        
                        if (cx < 0 || cx >= width || cy < 0 || cy >= height) continue;
                        
                        if (grid[cx][cy].type > 0) {
                            int enemy_x = agents[i].x;
                            int enemy_y = agents[i].y;
                            
                            int vx = enemy_x - x;
                            int vy = enemy_y - y;
                            
                            int cx_vec = cx - x;
                            int cy_vec = cy - y;
                            
                            if ((vx * cx_vec + vy * cy_vec) > 0) {
                                cover_count++;
                                break;
                            }
                        }
                    }
                }
            }
            
            cover_value_map[x][y] += cover_count * 10;
        }
    }
}

void update_control_map() {
    memset(control_map, 0, sizeof(control_map));
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (grid[x][y].type > 0) {
                control_map[x][y] = -999;
                continue;
            }
            
            int min_friendly_dist = INT_MAX;
            int min_enemy_dist = INT_MAX;
            
            for (int i = 0; i < MAX_AGENTS; i++) {
                if (!agents[i].exists) continue;
                
                int dist = manhattan_distance(x, y, agents[i].x, agents[i].y);
                
                if (agents[i].wetness >= WETNESS_THRESHOLD) {
                    dist *= 1.5f;
                }
                
                if (agents[i].is_mine) {
                    min_friendly_dist = min(dist, min_friendly_dist);
                } else {
                    min_enemy_dist = min(dist, min_enemy_dist);
                }
            }
            
            control_map[x][y] = min_enemy_dist - min_friendly_dist;
        }
    }
}

void update_strategic_value_map() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (grid[x][y].type > 0) {
                strategic_value_map[x][y] = -100;
                continue;
            }
            
            strategic_value_map[x][y] = control_map[x][y];
            strategic_value_map[x][y] -= danger_map[x][y] / 2;
            
            if (current_strategy == STRATEGY_AGGRESSIVE) {
                strategic_value_map[x][y] += enemy_density[x][y] * 2;
            } else if (current_strategy == STRATEGY_BALANCED) {
                strategic_value_map[x][y] += enemy_density[x][y];
            } else {
                strategic_value_map[x][y] -= enemy_density[x][y];
            }
            
            strategic_value_map[x][y] += cover_value_map[x][y];
            
            if (x <= 1 || x >= width - 2 || y <= 1 || y >= height - 2) {
                strategic_value_map[x][y] -= 10;
            }
        }
    }
}


/**
 * HYDRO HAVOC - ULTRA OPTIMIZED WATER BATTLE BOT v2.0
 * Dosya 4/5: Strateji ve hedefleme fonksiyonları
 */

void evaluate_strategy_mode() {
    int total_team_wetness = 0;
    int total_enemy_wetness = 0;
    int team_high_wetness_count = 0;
    int enemy_high_wetness_count = 0;
    int team_critical_wetness = 0;
    
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (agents[i].exists) {
            if (agents[i].is_mine) {
                total_team_wetness += agents[i].wetness;
                if (agents[i].wetness >= WETNESS_THRESHOLD) {
                    team_high_wetness_count++;
                }
                if (agents[i].wetness >= CRITICAL_WETNESS_THRESHOLD) {
                    team_critical_wetness++;
                }
            } else {
                total_enemy_wetness += agents[i].wetness;
                if (agents[i].wetness >= WETNESS_THRESHOLD) {
                    enemy_high_wetness_count++;
                }
            }
        }
    }
    
    float avg_team_wetness = (my_agent_count > 0) ? total_team_wetness / (float)my_agent_count : 0;
    float avg_enemy_wetness = (enemy_agent_count > 0) ? total_enemy_wetness / (float)enemy_agent_count : 0;
    
    current_strategy = STRATEGY_BALANCED;
    
    if (my_agent_count <= 1) {
        current_strategy = STRATEGY_SURVIVAL;
    } else if (my_agent_count < enemy_agent_count) {
        current_strategy = STRATEGY_DEFENSIVE;
    } else if (team_critical_wetness > 0 || avg_team_wetness > avg_enemy_wetness + 20) {
        current_strategy = STRATEGY_DEFENSIVE;
    } else if (team_high_wetness_count >= 2) {
        current_strategy = STRATEGY_DEFENSIVE;
    } else if (enemy_high_wetness_count > 0 && avg_enemy_wetness > avg_team_wetness) {
        current_strategy = STRATEGY_AGGRESSIVE;
    } else if (enemy_agent_count < my_agent_count) {
        current_strategy = STRATEGY_AGGRESSIVE;
    }
    
    fprintf(stderr, "Strategy Mode: %s (Team: %d, Enemy: %d, Avg Wetness: %.1f vs %.1f, High Wetness: %d vs %d)\n", 
            (current_strategy == STRATEGY_AGGRESSIVE) ? "AGGRESSIVE" : 
            (current_strategy == STRATEGY_BALANCED) ? "BALANCED" :
            (current_strategy == STRATEGY_DEFENSIVE) ? "DEFENSIVE" : "SURVIVAL",
            my_agent_count, enemy_agent_count, avg_team_wetness, avg_enemy_wetness, 
            team_high_wetness_count, enemy_high_wetness_count);
}

void assign_agent_roles() {
    int attacker_count = 0;
    int defender_count = 0;
    
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || !agents[i].is_mine) continue;
        
        if (attacker_count < my_agent_count / 2 + my_agent_count % 2) {
            agents[i].role = ROLE_ATTACKER;
            attacker_count++;
        } else if (defender_count < my_agent_count / 3) {
            agents[i].role = ROLE_DEFENDER;
            defender_count++;
        } else {
            agents[i].role = ROLE_SUPPORT;
        }
    }
    
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || !agents[i].is_mine) continue;
        
        if (agents[i].wetness >= HIGH_WETNESS_THRESHOLD && agents[i].role == ROLE_ATTACKER) {
            for (int j = 0; j < MAX_AGENTS; j++) {
                if (!agents[j].exists || !agents[j].is_mine) continue;
                if (agents[j].role != ROLE_ATTACKER && agents[j].wetness < WETNESS_THRESHOLD) {
                    AgentRole temp = agents[i].role;
                    agents[i].role = agents[j].role;
                    agents[j].role = temp;
                    break;
                }
            }
        }
    }
    
    fprintf(stderr, "Role assignments: ");
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || !agents[i].is_mine) continue;
        
        fprintf(stderr, "Agent %d: %s (W%d), ", agents[i].id,
               (agents[i].role == ROLE_ATTACKER) ? "ATTACKER" :
               (agents[i].role == ROLE_DEFENDER) ? "DEFENDER" : "SUPPORT",
               agents[i].wetness);
    }
    fprintf(stderr, "\n");
}

BombTarget find_best_splash_target(Agent *agent) {
    BombTarget best_target = {-1, -1, -999, 0, 0, 0.0f, false};
    
    if (agent->splash_bombs <= 0) {
        return best_target;
    }
    
    for (int x = max(0, agent->x - SPLASH_BOMB_RANGE); x < min(width, agent->x + SPLASH_BOMB_RANGE + 1); x++) {
        for (int y = max(0, agent->y - SPLASH_BOMB_RANGE); y < min(height, agent->y + SPLASH_BOMB_RANGE + 1); y++) {
            if (grid[x][y].type > 0 || !can_throw_bomb(agent, x, y)) {
                continue;
            }
            
            int enemy_affected = 0;
            int friendly_affected = 0;
            float total_enemy_wetness = 0.0f;
            int enemies_near_elimination = 0;
            
            for (int i = 0; i < MAX_AGENTS; i++) {
                if (!agents[i].exists) continue;
                
                int splash_distance = manhattan_distance(x, y, agents[i].x, agents[i].y);
                if (splash_distance <= SPLASH_DAMAGE_RADIUS) {
                    if (agents[i].is_mine) {
                        friendly_affected++;
                    } else {
                        enemy_affected++;
                        total_enemy_wetness += agents[i].wetness;
                        
                        if (agents[i].wetness + SPLASH_DAMAGE >= ELIMINATION_THRESHOLD) {
                            enemies_near_elimination++;
                        }
                    }
                }
            }
            
            if (friendly_affected > 0) continue;
            if (enemy_affected == 0) continue;
            
            int score = enemy_affected * 60;
            
            if (enemy_affected > 0) {
                float avg_enemy_wetness = total_enemy_wetness / enemy_affected;
                score += (int)(30.0f * (100.0f - min(99.0f, avg_enemy_wetness)) / 100.0f);
            }
            
            score += enemies_near_elimination * 150;
            
            if (primary_target_id != -1) {
                for (int i = 0; i < MAX_AGENTS; i++) {
                    if (agents[i].exists && !agents[i].is_mine && 
                        agents[i].id == primary_target_id) {
                        int dist = manhattan_distance(x, y, agents[i].x, agents[i].y);
                        if (dist <= SPLASH_DAMAGE_RADIUS) {
                            score += 50;
                        }
                        break;
                    }
                }
            }
            
            if (score > best_target.score) {
                best_target.x = x;
                best_target.y = y;
                best_target.score = score;
                best_target.enemy_count = enemy_affected;
                best_target.friendly_count = 0;
                best_target.avg_enemy_wetness = (enemy_affected > 0) ? 
                                               total_enemy_wetness / enemy_affected : 0;
                best_target.valid = true;
            }
        }
    }
    
    return best_target;
}

int find_best_target(Agent *agent, bool *can_hit) {
    int best_target_id = -1;
    int best_score = -1;
    *can_hit = false;
    
    if (primary_target_id != -1) {
        for (int i = 0; i < MAX_AGENTS; i++) {
            if (agents[i].exists && !agents[i].is_mine && agents[i].id == primary_target_id) {
                if (can_shoot_target(agent, &agents[i])) {
                    int damage = calculate_damage(agent, &agents[i]);
                    if (damage > 0) {
                        *can_hit = true;
                        return primary_target_id;
                    }
                }
                break;
            }
        }
    }
    
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || agents[i].is_mine) continue;
        
        if (can_shoot_target(agent, &agents[i])) {
            int damage = calculate_damage(agent, &agents[i]);
            
            if (damage > 0) {
                *can_hit = true;
                
                int target_score = damage * 3;
                
                target_score += (int)(damage * (100.0f - min(99.0f, (float)agents[i].wetness)) / 100.0f);
                
                if (agents[i].wetness + damage >= ELIMINATION_THRESHOLD) {
                    target_score += 200;
                } else if (agents[i].wetness + damage >= HIGH_WETNESS_THRESHOLD) {
                    target_score += 50;
                }
                
                target_score += agents[i].soaking_power * 2;
                
                for (int j = 0; j < MAX_AGENTS; j++) {
                    if (agents[j].exists && agents[j].is_mine && agents[j].id != agent->id && 
                        agents[j].target_id == agents[i].id) {
                        target_score += 30;
                        break;
                    }
                }
                
                if (agent->role == ROLE_ATTACKER) {
                    target_score += damage * 2;
                } else if (agent->role == ROLE_DEFENDER) {
                    int dist = manhattan_distance(agent->x, agent->y, agents[i].x, agents[i].y);
                    if (dist <= agent->optimal_range) {
                        target_score += 40;
                    }
                }
                
                if (target_score > best_score) {
                    best_score = target_score;
                    best_target_id = agents[i].id;
                }
            }
        }
    }
    
    if (best_target_id == -1) {
        int min_dist = INT_MAX;
        
        for (int i = 0; i < MAX_AGENTS; i++) {
            if (!agents[i].exists || agents[i].is_mine) continue;
            
            int dist = manhattan_distance(agent->x, agent->y, agents[i].x, agents[i].y);
            if (dist < min_dist) {
                min_dist = dist;
                best_target_id = agents[i].id;
            }
        }
        
        *can_hit = false;
    }
    
    return best_target_id;
}


/**
 * HYDRO HAVOC - ULTRA OPTIMIZED WATER BATTLE BOT v2.0
 * Dosya 2/5: Yardımcı fonksiyonlar ve temel hesaplamalar
 */

// GLOBAL DEĞİŞKEN TANIMLARI
int width, height;
int my_id;
int enemy_id;
Tile grid[MAX_WIDTH][MAX_HEIGHT];
Agent agents[MAX_AGENTS];
int agent_count = 0;
int my_agent_count = 0;
int enemy_agent_count = 0;
int turn = 0;
StrategyMode current_strategy = STRATEGY_BALANCED;
int score_difference = 0;
int primary_target_id = -1;
int primary_target_wetness = 0;
int secondary_target_id = -1;
time_t turn_start_time;
bool time_pressure = false;
int consecutive_missed_shots = 0;

// TAKTİKSEL HARİTALAR
int control_map[MAX_WIDTH][MAX_HEIGHT];
int enemy_density[MAX_WIDTH][MAX_HEIGHT];
int danger_map[MAX_WIDTH][MAX_HEIGHT];
int strategic_value_map[MAX_WIDTH][MAX_HEIGHT];
int cover_value_map[MAX_WIDTH][MAX_HEIGHT];
int path_cost[MAX_WIDTH][MAX_HEIGHT];
bool visited[MAX_WIDTH][MAX_HEIGHT];
bool los_map[MAX_WIDTH][MAX_HEIGHT][MAX_WIDTH][MAX_HEIGHT];

// YARDIMCI FONKSİYONLAR
int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

bool is_valid_position(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height && grid[x][y].type == 0;
}

bool is_position_recent(Agent *agent, int x, int y) {
    for (int i = 0; i < MAX_POSITIONS; i++) {
        if (agent->last_positions[i][0] == x && agent->last_positions[i][1] == y) {
            return true;
        }
    }
    return false;
}

void update_position_history(Agent *agent) {
    agent->position_index = (agent->position_index + 1) % MAX_POSITIONS;
    agent->last_positions[agent->position_index][0] = agent->x;
    agent->last_positions[agent->position_index][1] = agent->y;
}

bool can_shoot(Agent *agent) {
    return agent->current_cooldown == 0;
}

bool can_shoot_target(Agent *shooter, Agent *target) {
    if (shooter->current_cooldown > 0) {
        return false;
    }
    int distance = manhattan_distance(shooter->x, shooter->y, target->x, target->y);
    return distance <= shooter->optimal_range * 2;
}

bool can_throw_bomb(Agent *agent, int target_x, int target_y) {
    if (agent->splash_bombs <= 0) {
        return false;
    }
    return manhattan_distance(agent->x, agent->y, target_x, target_y) <= SPLASH_BOMB_RANGE;
}

bool line_of_sight(int x1, int y1, int x2, int y2) {
    if (los_map[x1][y1][x2][y2]) {
        return true;
    }
    if (los_map[x2][y2][x1][y1]) {
        return true;
    }
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;
    int x = x1, y = y1;
    
    while (true) {
        if (x == x2 && y == y2) break;
        
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
        
        if (x != x2 || y != y2) {
            if (x < 0 || x >= width || y < 0 || y >= height || grid[x][y].type > 0) {
                return false;
            }
        }
    }
    
    los_map[x1][y1][x2][y2] = true;
    los_map[x2][y2][x1][y1] = true;
    return true;
}

void reset_los_cache() {
    memset(los_map, 0, sizeof(los_map));
}

bool is_too_close_to_friendly_agents(int x, int y, Agent *current_agent) {
    if (current_strategy == STRATEGY_SURVIVAL) {
        return false;
    }
    
    int close_agents = 0;
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (!agents[i].exists || !agents[i].is_mine || agents[i].id == current_agent->id) continue;
        
        int distance = manhattan_distance(x, y, agents[i].x, agents[i].y);
        if (distance < MIN_AGENT_DISTANCE) {
            close_agents++;
            
            if (current_strategy == STRATEGY_AGGRESSIVE && 
                current_agent->target_id != -1 && 
                agents[i].target_id == current_agent->target_id) {
                
                for (int j = 0; j < MAX_AGENTS; j++) {
                    if (agents[j].exists && !agents[j].is_mine && agents[j].id == current_agent->target_id) {
                        int target_dist = manhattan_distance(x, y, agents[j].x, agents[j].y);
                        if (target_dist <= 3 && agents[j].wetness >= 80) {
                            return false;
                        }
                        break;
                    }
                }
            }
        }
    }
    
    if (current_strategy == STRATEGY_DEFENSIVE && close_agents <= 1) {
        return false;
    }
    
    return close_agents > 0;
}

float calculate_cover_factor(Agent *shooter, Agent *target) {
    if (!line_of_sight(shooter->x, shooter->y, target->x, target->y)) {
        int dx = target->x - shooter->x;
        int dy = target->y - shooter->y;
        int sx = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
        int sy = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
        int err = abs(dx) - abs(dy);
        int e2;
        int x = shooter->x, y = shooter->y;
        
        while (!(x == target->x && y == target->y)) {
            e2 = 2 * err;
            if (e2 > -abs(dy)) {
                err -= abs(dy);
                x += sx;
            }
            if (e2 < abs(dx)) {
                err += abs(dx);
                y += sy;
            }
            
            if (x >= 0 && x < width && y >= 0 && y < height) {
                if (grid[x][y].type == TERRAIN_LIGHT_COVER) return 0.5f;
                if (grid[x][y].type == TERRAIN_HEAVY_COVER) return 0.75f;
            }
        }
    }
    return 0.0f;
}

int calculate_damage(Agent *shooter, Agent *target) {
    int distance = manhattan_distance(shooter->x, shooter->y, target->x, target->y);
    float damage = shooter->soaking_power;
    
    if (distance <= shooter->optimal_range) {
        // Tam hasar
    } else if (distance <= shooter->optimal_range * 2) {
        damage *= 0.5f;
    } else {
        return 0;
    }
    
    float cover_reduction = calculate_cover_factor(shooter, target);
    
    if (target->hunker_down_planned || target->turns_since_last_shot > 0) {
        cover_reduction = fmaxf(cover_reduction, 0.25f);
    }
    
    damage *= (1.0f - cover_reduction);
    
    return (int)damage;
}
