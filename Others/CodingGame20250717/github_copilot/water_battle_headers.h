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