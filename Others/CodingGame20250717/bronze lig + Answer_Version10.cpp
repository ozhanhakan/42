#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <utility>

// --- Sabitler ve Veri Yapıları ---
const std::string BOT_VERSION = "v5.4_Dynamic_Targeting";
const int SPLASH_BOMB_RANGE = 4;
const int SPLASH_DAMAGE_RADIUS = 1;

struct Agent {
    int id, player, x, y, cooldown, optimal_range, soaking_power, splash_bombs, wetness;
    int initial_cooldown;
    bool is_mine;
    bool exists = true;
};

struct Action {
    std::string move_action = "";
    std::string combat_action = "";
};

struct EvaluatedAction {
    Action action;
    int score = -1e9;
};

// --- Global Değişkenler ---
int width, height;
std::vector<std::vector<int>> grid_types;
std::map<int, Agent> agents;
int my_id;

// --- Yardımcı Fonksiyonlar ---
int manhattan_distance(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool is_valid_position(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    return grid_types[y][x] == 0;
}

// --- Strateji Fonksiyonları ---
int find_primary_target() {
    int best_target_id = -1;
    int highest_threat_score = -1e9;
    for (auto const& [enemy_id, enemy] : agents) {
        if (enemy.is_mine || !enemy.exists) continue;
        int current_threat_score = 0;
        if (enemy.wetness >= 9) { current_threat_score += 10000; }
        bool is_imminent_threat = false;
        if (enemy.cooldown == 0) {
            for (auto const& [my_id, my_agent] : agents) {
                if (my_agent.is_mine && my_agent.exists) {
                    if (manhattan_distance(enemy.x, enemy.y, my_agent.x, my_agent.y) <= enemy.optimal_range * 2) {
                        is_imminent_threat = true; break;
                    }
                }
            }
        }
        if (is_imminent_threat) { current_threat_score += 500; }
        current_threat_score += enemy.wetness * 10;
        int min_dist_to_friendly = 1e9;
        for (auto const& [my_id, my_agent] : agents) {
            if (my_agent.is_mine && my_agent.exists) {
                min_dist_to_friendly = std::min(min_dist_to_friendly, manhattan_distance(enemy.x, enemy.y, my_agent.x, my_agent.y));
            }
        }
        current_threat_score -= min_dist_to_friendly * 5;
        if (current_threat_score > highest_threat_score) {
            highest_threat_score = current_threat_score;
            best_target_id = enemy_id;
        }
    }
    return best_target_id;
}


// *** KARAR VERME MEKANİZMASI GÜNCELLENDİ (DİNAMİK HEDEFLEME) ***
Action decide_agent_action(int agent_id, int primary_target_id) {
    const auto& agent = agents.at(agent_id);
    EvaluatedAction best_action_combo;

    // --- Takım Durum Analizi ---
    int my_agent_count = 0, enemy_agent_count = 0;
    float squad_center_x = 0, squad_center_y = 0;
    for(auto const& [id, a] : agents) {
        if(a.exists) {
            if(a.is_mine) {
                my_agent_count++; squad_center_x += a.x; squad_center_y += a.y;
            } else { enemy_agent_count++; }
        }
    }
    if (my_agent_count > 0) { squad_center_x /= my_agent_count; squad_center_y /= my_agent_count; }
    bool is_desperate = my_agent_count < enemy_agent_count;

    Agent target_agent;
    bool has_target = (primary_target_id != -1 && agents.count(primary_target_id));
    if (has_target) { target_agent = agents.at(primary_target_id); }

    // Her olası HAREKET + SALDIRI kombinasyonunu değerlendir
    for (int y_offset = -2; y_offset <= 2; ++y_offset) {
        for (int x_offset = -2; x_offset <= 2; ++x_offset) {
            int nx = agent.x + x_offset, ny = agent.y + y_offset;
            if (!is_valid_position(nx, ny) && (nx != agent.x || ny != agent.y)) continue;
            
            Action current_action;
            int positional_score = 0;
            int combat_score = 0;

            // --- POZİSYON PUANLAMASI ---
            for (auto const& [other_id, other_agent] : agents) {
                if (other_agent.is_mine && other_agent.exists && other_agent.id != agent.id) {
                    if (manhattan_distance(nx, ny, other_agent.x, other_agent.y) < 3) {
                        positional_score -= (4 - manhattan_distance(nx, ny, other_agent.x, other_agent.y)) * 50;
                    }
                }
            }
            if (has_target) {
                positional_score += (manhattan_distance(agent.x, agent.y, target_agent.x, target_agent.y) - manhattan_distance(nx, ny, target_agent.x, target_agent.y)) * 10;
            }
            int current_dist_to_com = manhattan_distance(agent.x, agent.y, squad_center_x, squad_center_y);
            int new_dist_to_com = manhattan_distance(nx, ny, squad_center_x, squad_center_y);
            if (current_dist_to_com > 4) {
                 positional_score += (current_dist_to_com - new_dist_to_com) * 8;
            }

            // --- SAVAŞ PUANLAMASI ---
            if (agent.cooldown == 0) {
                // A. BOMBA seçeneğini değerlendir (YENİ DİNAMİK MANTIK)
                int bomb_score = 0; std::string bomb_command = "";
                if (agent.splash_bombs > 0) {
                    int best_cluster_size = 0;
                    int best_anchor_id = -1;

                    // Her bir düşmanı potansiyel bir "çapa" olarak değerlendir
                    for(auto const& [anchor_id, anchor_enemy] : agents) {
                        if (anchor_enemy.is_mine || !anchor_enemy.exists) continue;
                        if (manhattan_distance(nx, ny, anchor_enemy.x, anchor_enemy.y) > SPLASH_BOMB_RANGE) continue;
                        
                        int current_cluster_size = 0; bool friend_in_blast = false;
                        // Çapanın etrafındaki etki alanını kontrol et
                        for (int dy = -SPLASH_DAMAGE_RADIUS; dy <= SPLASH_DAMAGE_RADIUS; ++dy) {
                            for (int dx = -SPLASH_DAMAGE_RADIUS; dx <= SPLASH_DAMAGE_RADIUS; ++dx) {
                                int check_x = anchor_enemy.x + dx, check_y = anchor_enemy.y + dy;
                                for (auto const& [id, other] : agents) {
                                    if (other.exists && other.x == check_x && other.y == check_y) {
                                        if (other.is_mine) { friend_in_blast = true; break; }
                                        else { current_cluster_size++; }
                                    }
                                } if(friend_in_blast) break;
                            } if(friend_in_blast) break;
                        }

                        if (!friend_in_blast && current_cluster_size > best_cluster_size) {
                            best_cluster_size = current_cluster_size;
                            best_anchor_id = anchor_id;
                        }
                    }

                    if (best_cluster_size >= 2) {
                        bomb_score = 200 * best_cluster_size;
                        bomb_command = "THROW " + std::to_string(agents.at(best_anchor_id).x) + " " + std::to_string(agents.at(best_anchor_id).y);
                    } else if (best_cluster_size == 1 && is_desperate) {
                        bomb_score = 160;
                        bomb_command = "THROW " + std::to_string(agents.at(best_anchor_id).x) + " " + std::to_string(agents.at(best_anchor_id).y);
                    }
                }

                // B. ATIŞ seçeneğini değerlendir
                int shoot_score = 0; std::string shoot_command = "";
                if (has_target) {
                    int dist = manhattan_distance(nx, ny, target_agent.x, target_agent.y);
                    if (dist <= (agent.optimal_range * 2) - 2) { 
                        shoot_score = 150 - dist;
                        shoot_command = "SHOOT " + std::to_string(primary_target_id);
                    }
                }

                // C. En iyi saldırıyı seç
                if (bomb_score > shoot_score) {
                    combat_score = bomb_score; current_action.combat_action = bomb_command;
                } else {
                    combat_score = shoot_score; current_action.combat_action = shoot_command;
                }
            }
            
            int total_score = positional_score + combat_score;
            if (total_score > best_action_combo.score) {
                best_action_combo.score = total_score;
                if (nx != agent.x || ny != agent.y) {
                    current_action.move_action = "MOVE " + std::to_string(nx) + " " + std::to_string(ny);
                }
                best_action_combo.action = current_action;
            }
        }
    }
    return best_action_combo.action;
}


// --- Ana Program Döngüsü ---
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    std::cin >> my_id; std::cin.ignore();
    int agent_data_count; std::cin >> agent_data_count; std::cin.ignore();
    for (int i = 0; i < agent_data_count; i++) {
        Agent a;
        std::cin >> a.id >> a.player >> a.initial_cooldown >> a.optimal_range >> a.soaking_power >> a.splash_bombs; std::cin.ignore();
        a.is_mine = (a.player == my_id); a.cooldown = 0; a.wetness = 0; agents[a.id] = a;
    }
    std::cin >> width >> height; std::cin.ignore();
    grid_types.assign(height, std::vector<int>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int tile_x, tile_y, tile_type;
            std::cin >> tile_x >> tile_y >> tile_type; std::cin.ignore();
            grid_types[tile_y][tile_x] = tile_type;
        }
    }
    while (true) {
        for(auto& entry : agents) { entry.second.exists = false; }
        int remaining_agents; std::cin >> remaining_agents; std::cin.ignore();
        for (int i = 0; i < remaining_agents; i++) {
            int id, x, y, cooldown, splash_bombs, wetness;
            std::cin >> id >> x >> y >> cooldown >> splash_bombs >> wetness; std::cin.ignore();
            if (agents.count(id)) {
                agents[id].x = x; agents[id].y = y; agents[id].cooldown = cooldown;
                agents[id].splash_bombs = splash_bombs; agents[id].wetness = wetness; agents[id].exists = true;
            }
        }
        int my_agent_count; std::cin >> my_agent_count; std::cin.ignore();
        int primary_target_id = find_primary_target();
        for (auto const& [id, agent] : agents) {
            if (agent.is_mine && agent.exists) {
                Action final_action = decide_agent_action(id, primary_target_id);
                std::string command = std::to_string(id);
                if (!final_action.move_action.empty()) { command += ";" + final_action.move_action; }
                if (!final_action.combat_action.empty()) { command += ";" + final_action.combat_action; }
                command += ";MESSAGE " + BOT_VERSION;
                std::cout << command << std::endl;
            }
        }
    }
    return 0;
}