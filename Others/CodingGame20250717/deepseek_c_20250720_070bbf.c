#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_AGENTS 20
#define MAX_WIDTH  20
#define MAX_HEIGHT 20

int tile_type[MAX_WIDTH][MAX_HEIGHT];
int grid_width, grid_height;

typedef struct {
    int id;
    int player;
    int x, y;
    int cooldown;
    int splashBombs;
    int wetness;
} Agent;

Agent agents[MAX_AGENTS];
int agent_count, my_agent_count, my_id;

void get_best_cover_move(Agent a, int* mx, int* my) {
    *mx = a.x;
    *my = a.y;

    int dirs[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
    int bestScore = -1;
    int bestDist = 999;

    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++) {
            if (tile_type[x][y] == 0) continue; // Skip empty tiles
            
            // Score: 2 for high cover, 1 for low cover
            int coverScore = tile_type[x][y];
            
            for (int d = 0; d < 4; d++) {
                int tx = x + dirs[d][0];
                int ty = y + dirs[d][1];

                // Check if target position is valid and empty
                if (tx < 0 || tx >= grid_width || ty < 0 || ty >= grid_height) continue;
                if (tile_type[tx][ty] != 0) continue;

                // Check if position is occupied by enemy
                bool occupied = false;
                for (int j = 0; j < agent_count; j++) {
                    if (agents[j].x == tx && agents[j].y == ty && agents[j].player != my_id) {
                        occupied = true;
                        break;
                    }
                }
                if (occupied) continue;

                // Check if position is occupied by friendly
                for (int j = 0; j < agent_count; j++) {
                    if (agents[j].x == tx && agents[j].y == ty && agents[j].player == my_id) {
                        occupied = true;
                        break;
                    }
                }
                if (occupied) continue;

                int dist = abs(a.x - tx) + abs(a.y - ty);
                if (dist > 1) continue; // Only consider adjacent moves

                // Check if cover is between agent and any enemy
                bool cover_between = false;
                for (int i = 0; i < agent_count; i++) {
                    Agent enemy = agents[i];
                    if (enemy.player == my_id) continue;

                    if (a.x == enemy.x && a.x == x) {
                        if ((a.y < y && y < enemy.y) || (enemy.y < y && y < a.y)) cover_between = true;
                    } else if (a.y == enemy.y && a.y == y) {
                        if ((a.x < x && x < enemy.x) || (enemy.x < x && x < a.x)) cover_between = true;
                    }
                }

                // Calculate score: higher cover score first, then cover between, then distance
                int score = coverScore * 100 + (cover_between ? 10 : 0) + (10 - dist);
                
                if (score > bestScore || (score == bestScore && dist < bestDist)) {
                    bestScore = score;
                    bestDist = dist;
                    *mx = tx;
                    *my = ty;
                    fprintf(stderr,
                        "[GEOMETRIC MOVE] Agent %d → Cover(%d,%d) type %d, MOVE(%d,%d), dist=%d\n",
                        a.id, x, y, tile_type[x][y], tx, ty, dist);
                }
            }
        }
    }

    if (bestScore == -1)
        fprintf(stderr,
            "[GEOMETRIC MOVE] Agent %d → No valid cover MOVE\n", a.id);
}

int select_least_protected_enemy(Agent a) {
    int best_id = -1;
    int min_cover = 999;
    int min_dist = 999;

    for (int i = 0; i < agent_count; i++) {
        Agent enemy = agents[i];
        if (enemy.player == my_id || (enemy.x == a.x && enemy.y == a.y)) continue;

        int dx = enemy.x - a.x, dy = enemy.y - a.y;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
        if (steps == 0) continue;

        float stepx = dx / (float)steps;
        float stepy = dy / (float)steps;
        float x = a.x + stepx, y = a.y + stepy;
        int cover_count = 0;

        for (int s = 1; s < steps; s++, x += stepx, y += stepy) {
            int ix = (int)(x + 0.5), iy = (int)(y + 0.5);
            if (ix < 0 || ix >= grid_width || iy < 0 || iy >= grid_height) break;
            if (tile_type[ix][iy] == 1 || tile_type[ix][iy] == 2) cover_count++;
        }

        int dist = abs(dx) + abs(dy);
        if (cover_count < min_cover || (cover_count == min_cover && dist < min_dist)) {
            best_id = enemy.id;
            min_cover = cover_count;
            min_dist = dist;
        }
    }

    // If no target found with cover analysis, just pick first available enemy
    if (best_id == -1) {
        for (int i = 0; i < agent_count; i++) {
            if (agents[i].player != my_id) {
                best_id = agents[i].id;
                break;
            }
        }
    }

    fprintf(stderr,
        "[SHOOT ANALYSIS] Agent %d → Target %d with cover=%d, dist=%d\n",
        a.id, best_id, min_cover, min_dist);

    return best_id;
}

int main() {
    scanf("%d", &my_id);
    int adc; scanf("%d", &adc);
    for (int i = 0, t; i < adc * 6; i++) scanf("%d", &t);

    scanf("%d%d", &grid_width, &grid_height);
    for (int i = 0, x, y, t; i < grid_width * grid_height; i++) {
        scanf("%d%d%d", &x, &y, &t);
        tile_type[x][y] = t;
    }

    while (1) {
        scanf("%d", &agent_count);
        for (int i = 0; i < agent_count; i++) {
            scanf("%d%d%d%d%d%d",
                &agents[i].id, &agents[i].x, &agents[i].y,
                &agents[i].cooldown, &agents[i].splashBombs, &agents[i].wetness);
            agents[i].player = (i < 2 ? my_id : 1 - my_id);
        }

        scanf("%d", &my_agent_count);
        for (int i = 0; i < my_agent_count; i++) {
            Agent a = agents[i];
            int mx, my;
            get_best_cover_move(a, &mx, &my);
            int tid = select_least_protected_enemy(a);
            printf("%d;MOVE %d %d;SHOOT %d;MESSAGE Cover move, shoot weakest\n", 
                  a.id, mx, my, tid);
        }
    }

    return 0;
}