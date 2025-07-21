/**Wood-2
 * @file agent_strategy.c
 * @brief Ajan hareket ve hedef seçim stratejisi
 * @details Bu kod CodingArena'daki "Cover and Shoot" mücadelesi için tasarlanmıştır.
 * 
 * Oyun Kuralları:
 * 1. Her ajan 1 turda:
 *    - En iyi siper pozisyonuna hareket etmeli
 *    - En yakın iki düşman arasından korumasız olanı vurmalı
 * 2. Zafer koşulu:
 *    - Tüm ajanların doğru siper arkasına geçmesi
 *    - En savunmasız düşmanın vurulması
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// ==================== OYUN YAPISI ====================

#define MAX_AGENTS 20    ///< Maksimum ajan sayısı
#define MAX_WIDTH  20    ///< Harita genişlik limiti
#define MAX_HEIGHT 20    ///< Harita yükseklik limiti

// Haritadaki karo tipleri
#define EMPTY 0         ///< Boş karo
#define LOW_COVER 1     ///< Alçak siper (%50 koruma)
#define HIGH_COVER 2    ///< Yüksek siper (%75 koruma)

int tile_type[MAX_WIDTH][MAX_HEIGHT]; ///< Harita karo bilgisi
int grid_width, grid_height;          ///< Harita boyutları

/**
 * @brief Ajan veri yapısı
 */
typedef struct {
    int id;         ///< Benzersiz kimlik
    int player;     ///< Takım ID (0 veya 1)
    int x, y;       ///< Mevcut konum
    int cooldown;   ///< Atış bekleme süresi
    int splashBombs;///< Özel bomba sayısı
    int wetness;    ///< Isılık seviyesi
} Agent;

Agent agents[MAX_AGENTS];    ///< Tüm ajanların listesi
int agent_count;            ///< Toplam ajan sayısı
int my_agent_count;         ///< Takımımdaki ajan sayısı
int my_id;                  ///< Takımımın ID'si

/* Yardımcı fonksiyon prototipleri */
bool does_cover_protect(int ax, int ay, int cx, int cy, int ex, int ey);
Agent get_agent_by_id(int id);
float calculate_vulnerability(Agent a, Agent enemy);

/**
 * @brief En iyi siper pozisyonunu hesaplar
 * @param a Mevcut ajan
 * @param[out] mx Seçilen x pozisyonu
 * @param[out] my Seçilen y pozisyonu
 * 
 * @details Algoritma:
 * 1. Tüm komşu karoları kontrol eder
 * 2. Her karo için bitişik siperleri değerlendirir:
 *    - Yüksek siper > Alçak siper
 *    - Çoklu düşmana koruma > Tek düşmana koruma
 * 3. En yüksek puanlı pozisyonu seçer
 */
void get_optimal_cover_position(Agent a, int* mx, int* my) {
    *mx = a.x; // Varsayılan: olduğu yerde kalsın
    *my = a.y;

    int dirs[4][2] = {{0,-1},{1,0},{0,1},{-1,0}}; // 4 yön
    int best_score = -1;

    // Tüm komşu pozisyonları değerlendir
    for (int d = 0; d < 4; d++) {
        int tx = a.x + dirs[d][0];
        int ty = a.y + dirs[d][1];

        // Geçerli pozisyon kontrolü
        if (tx < 0 || tx >= grid_width || ty < 0 || ty >= grid_height) continue;
        if (tile_type[tx][ty] != EMPTY) continue;

        // Pozisyon dolu mu kontrol et
        bool occupied = false;
        for (int j = 0; j < agent_count; j++) {
            if (agents[j].x == tx && agents[j].y == ty) {
                occupied = true;
                break;
            }
        }
        if (occupied) continue;

        // Bu pozisyon için en iyi siperi bul
        int cover_score = 0;
        int protected_enemies = 0;
        
        // 4 yöndeki siperleri kontrol et
        for (int cd = 0; cd < 4; cd++) {
            int cx = tx + dirs[cd][0];
            int cy = ty + dirs[cd][1];

            if (cx < 0 || cx >= grid_width || cy < 0 || cy >= grid_height) continue;
            if (tile_type[cx][cy] == EMPTY) continue;

            // Bu siper kaç düşmana karşı koruma sağlıyor?
            int protection_count = 0;
            for (int e = 0; e < agent_count; e++) {
                if (agents[e].player == my_id) continue;
                if (does_cover_protect(tx, ty, cx, cy, agents[e].x, agents[e].y)) {
                    protection_count++;
                }
            }

            // Siper puanı = tip * (korunan düşman + 1)
            int current_score = tile_type[cx][cy] * (1 + protection_count);
            if (current_score > cover_score) {
                cover_score = current_score;
                protected_enemies = protection_count;
            }
        }

        // Genel puanlama (ağırlıklı)
        int total_score = cover_score * 10 + protected_enemies;
        if (total_score > best_score) {
            best_score = total_score;
            *mx = tx;
            *my = ty;
        }
    }
}

/**
 * @brief En yakın iki düşman arasından en savunmasız olanı seçer
 * @param a Mevcut ajan
 * @return Seçilen düşman ID'si
 * 
 * @details Oyun kuralı gereği:
 * 1. Sadece en yakın iki düşman değerlendirilir
 * 2. Bu ikili arasında:
 *    - Koruması daha zayıf olan seçilir
 *    - Eşitse daha yakın olan tercih edilir
 */
int select_most_vulnerable_enemy(Agent a) {
    int closest_ids[2] = {-1, -1};      // En yakın iki düşman ID
    int closest_dists[2] = {INT_MAX, INT_MAX}; // Mesafeleri

    // 1. En yakın iki düşmanı bul
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].player == my_id) continue;

        int dist = abs(a.x - agents[i].x) + abs(a.y - agents[i].y);
        
        // Sıralı ekleme
        if (dist < closest_dists[0]) {
            closest_dists[1] = closest_dists[0];
            closest_ids[1] = closest_ids[0];
            closest_dists[0] = dist;
            closest_ids[0] = agents[i].id;
        } 
        else if (dist < closest_dists[1]) {
            closest_dists[1] = dist;
            closest_ids[1] = agents[i].id;
        }
    }

    // 2. Geçerli düşman yoksa fallback
    if (closest_ids[0] == -1) {
        for (int i = 0; i < agent_count; i++) {
            if (agents[i].player != my_id) {
                return agents[i].id;
            }
        }
        return -1; // Hiç düşman yok
    }

    // 3. Tek düşman varsa direkt seç
    if (closest_ids[1] == -1) {
        return closest_ids[0];
    }

    // 4. İki düşman arasında karşılaştırma
    Agent enemy1 = get_agent_by_id(closest_ids[0]);
    Agent enemy2 = get_agent_by_id(closest_ids[1]);
    
    float vuln1 = calculate_vulnerability(a, enemy1);
    float vuln2 = calculate_vulnerability(a, enemy2);

    // Savunmasızlık ve mesafeye göre seçim
    if (vuln1 > vuln2 || 
       (vuln1 == vuln2 && closest_dists[0] < closest_dists[1])) {
        return closest_ids[0];
    }
    return closest_ids[1];
}

/**
 * @brief İki nokta arasındaki siper korumasını kontrol eder
 */
bool does_cover_protect(int ax, int ay, int cx, int cy, int ex, int ey) {
    // 1. Siper ajanın yanında olmalı
    if (abs(ax - cx) + abs(ay - cy) != 1) return false;
    
    // 2. Siper ajan-düşman hattında olmalı
    if (ax == ex && ax == cx) { // Yatay hat
        return (ay < cy && cy < ey) || (ey < cy && cy < ay);
    } 
    else if (ay == ey && ay == cy) { // Dikey hat
        return (ax < cx && cx < ex) || (ex < cx && cx < ax);
    }
    return false;
}

/**
 * @brief Düşmanın savunmasızlık skorunu hesaplar
 */
float calculate_vulnerability(Agent a, Agent enemy) {
    int dx = enemy.x - a.x;
    int dy = enemy.y - a.y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    float stepx = dx / (float)steps;
    float stepy = dy / (float)steps;
    float x = a.x + stepx, y = a.y + stepy;
    
    int high = 0, low = 0; // Siper sayıcılar
    
    for (int s = 1; s < steps; s++, x += stepx, y += stepy) {
        int ix = (int)(x + 0.5), iy = (int)(y + 0.5);
        if (ix < 0 || ix >= grid_width || iy < 0 || iy >= grid_height) break;
        
        if (tile_type[ix][iy] == LOW_COVER) low++;
        else if (tile_type[ix][iy] == HIGH_COVER) high++;
    }
    
    // Savunmasızlık = 1 / (1 + high*0.75 + low*0.5)
    return 1.0f / (1.0f + high * 0.75f + low * 0.5f);
}

/**
 * @brief ID'ye göre ajan bulur
 */
Agent get_agent_by_id(int id) {
    for (int i = 0; i < agent_count; i++) {
        if (agents[i].id == id) return agents[i];
    }
    return (Agent){-1}; // Geçersiz ajan
}

/**
 * @brief Ana oyun döngüsü
 */



 // ==================== TEST SİSTEMİ ====================
#ifdef LOCAL_TESTING

// ==================== STRATEJİ TEST FONKSİYONLARI ====================
void get_move(Agent a, int* x, int* y) {
    // Gerçek stratejiniz burada
    *x = (a.x + 1) % MAX_WIDTH; // Örnek: Sağa hareket
    *y = a.y;
}


void setup_test_scenario1() {
    printf("=== Senaryo 1: Temel Hareket ===\n");
    grid_width = 3; grid_height = 3;
    
    // Haritayı sıfırla
    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++) {
            tile_type[x][y] = EMPTY;
        }
    }
    
    // Özel karolar
    tile_type[1][0] = HIGH_COVER;
    tile_type[2][2] = LOW_COVER;
    
    // Ajanları yerleştir
    agents[0] = (Agent){1, 0, 0, 0, 0, 0, 0}; // Bizim ajan
    agents[1] = (Agent){2, 1, 2, 2, 0, 0, 0}; // Düşman
    agent_count = 2; my_agent_count = 1; my_id = 0;
}

void setup_test_scenario2() {
    printf("\n=== Senaryo 2: İkili Düşman ===\n");
    grid_width = 4; grid_height = 2;
    
    // Harita reset
    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++) {
            tile_type[x][y] = EMPTY;
        }
    }
    
    // Özel karolar
    tile_type[1][0] = HIGH_COVER;
    tile_type[3][0] = LOW_COVER;
    
    // Ajanlar
    agents[0] = (Agent){1, 0, 0, 0, 0, 0, 0}; // Biz
    agents[1] = (Agent){2, 1, 2, 0, 0, 0, 0}; // Düşman 1
    agents[2] = (Agent){3, 1, 3, 1, 0, 0, 0};  // Düşman 2
    agent_count = 3; my_agent_count = 1; my_id = 0;
}

void setup_test_scenario3() {
    printf("\n=== Senaryo 3: Engel Durumu ===\n");
    grid_width = 5; grid_height = 1;
    
    // Tümü boş
    for (int x = 0; x < grid_width; x++) {
        tile_type[x][0] = EMPTY;
    }
    
    // Engel
    tile_type[2][0] = HIGH_COVER;
    
    // Ajanlar
    agents[0] = (Agent){1, 0, 0, 0, 0, 0, 0}; // Biz
    agents[1] = (Agent){2, 1, 4, 0, 0, 0, 0}; // Düşman
    agent_count = 2; my_agent_count = 1; my_id = 0;
}


void run_test(Agent* a) {
    int mx, my;
    get_optimal_cover_position(*a, &mx, &my);
    printf("Move to: (%d,%d)\n", mx, my);
    
    int target = select_most_vulnerable_enemy(*a);
    printf("Shoot target: %d\n", target);
}

void test_cover_logic() {
    printf("=== TEST 1: test_cover_logic Hareket Doğruluğu ===\n");
    Agent test_agent = {1, 5, 5, 0};
    int x, y;
    get_move(test_agent, &x, &y);
    printf("Agent %d -> (%d,%d) %s\n", 
           test_agent.id, x, y, 
           (x == 6 && y == 5) ? "✅" : "❌");
}

void run_all_tests() {
    test_cover_logic();

    setup_test_scenario1();
    setup_test_scenario2();
    setup_test_scenario3();

    // Diğer testler...
}

int main() {
    printf("===== TEST MODU-all =====\n");

	run_all_tests();
    return 0;
}

#else
// ==================== CODINGAME MAIN ====================

int main() {
    // Giriş verilerini oku
    scanf("%d", &my_id);
    int adc; scanf("%d", &adc);
    for (int i = 0, t; i < adc * 6; i++) scanf("%d", &t);

    // Harita bilgisi
    scanf("%d%d", &grid_width, &grid_height);
    for (int i = 0, x, y, t; i < grid_width * grid_height; i++) {
        scanf("%d%d%d", &x, &y, &t);
        tile_type[x][y] = t;
    }

    // Oyun döngüsü
    while (1) {
        // Ajanları güncelle
        scanf("%d", &agent_count);
        for (int i = 0; i < agent_count; i++) {
            scanf("%d%d%d%d%d%d",
                &agents[i].id, &agents[i].x, &agents[i].y,
                &agents[i].cooldown, &agents[i].splashBombs, &agents[i].wetness);
            agents[i].player = (i < 2 ? my_id : 1 - my_id); // İlk 2 ajan bizim
        }

        // Takım ajanları için komut üret
        scanf("%d", &my_agent_count);
        for (int i = 0; i < my_agent_count; i++) {
            Agent a = agents[i];
            int mx, my;
            get_optimal_cover_position(a, &mx, &my);
            int target = select_most_vulnerable_enemy(a);
            printf("%d;MOVE %d %d;SHOOT %d;MESSAGE Kurala uygun strateji\n",
                  a.id, mx, my, target);
        }
    }

    return 0;
}
#endif