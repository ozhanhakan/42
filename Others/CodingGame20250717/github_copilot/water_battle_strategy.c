#include "water_battle_headers.h"

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