#include "water_battle_headers.h"

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