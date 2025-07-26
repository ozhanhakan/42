#include "water_battle_headers.h"

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