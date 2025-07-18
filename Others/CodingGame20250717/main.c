#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h> // round() fonksiyonu için matematik kütüphanesi

// --- Ustanın Notu: Struct Tanımlamaları (Veri Planlarımız) ---
// Stratejimiz için gerekli olan farklı veri türlerini düzenli bir şekilde
// bir arada tutmak için kullanılan veri yapıları.

// AgentData: Ajanların oyun başında verilen ve değişmeyen kimlik bilgileri.
typedef struct {
    int id;		// Ajanın benzersiz kimliği.
    int player;	// Ajanın sahibi olan oyuncunun kimliği (Biz miyiz, düşman mı?).
} AgentData;

// AgentState: Ajanların her tur değişen anlık durumları.
typedef struct {
    int id;		// Ajanın kimliği.
    int x, y;	// Ajanın haritadaki mevcut konumu.
    int splash_bombs; // Ajanın mevcut splash bomb sayısı.
    int last_x, last_y; // Önceki tur konumu (ileri-geri hareketi önlemek için).
} AgentState;

// Tile: Haritadaki tek bir karonun bilgileri.
typedef struct {
    int x, y;	// Karonun konumu.
    int type;	// Karonun türü (0:Boş, 1:Alçak Siper, 2:Yüksek Siper).
} Tile;

// EnemyGroup: Düşmanları analiz edip grupladıktan sonra elde edilen bilgileri saklar.
typedef struct {
    int center_x, center_y; // Grubun geometrik merkezi.
    int size;               // Gruptaki düşman sayısı.
    bool contains_friend;   // Bu grubun etki alanında (merkezine yakın) bir dost ajan var mı?
} EnemyGroup;

// --- Ustanın Notu: Global Değişkenler (Evrensel Bilgilerimiz) ---
// Programın farklı fonksiyonları tarafından erişilmesi gereken genel durum bilgileri.
int my_id;
int width, height;
int turn_counter = 0;
Tile map[20][10];       // Oyun haritasını saklayan 2 boyutlu dizi.
AgentState previous_agents[2]; // Ajanların bir önceki turdaki konumları.
int previous_agent_count = 0;
int esir_agent_id = -1; // "Esir" rolündeki ajanın ID'si. Oyun başında belirlenir.


// --- Ustanın Notu: Yardımcı Fonksiyonlar (Stratejimizin Araçları) ---

/**
 * @brief İki nokta arasındaki Manhattan mesafesini hesaplar.
 * @note Manhattan mesafesi, bir ızgara üzerinde hareket eden bir ajanın
 *       bir noktadan diğerine gitmek için katetmesi gereken minimum kare sayısıdır.
 *       (Yatay mesafe + Dikey mesafe). Bomba menzili gibi hesaplamalar için idealdir.
 */
int get_manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

/**
 * @brief Verilen bir konumun etrafındaki duvar/siper sayısını sayar.
 * @note Bu fonksiyon, bir ajanın ne kadar kapalı bir alanda olduğunu anlamak için kullanılır.
 *       Daha fazla duvar, ajanın "esir" olma ihtimalini artırır.
 */
int count_adjacent_walls(int x, int y) {
    int wall_count = 0;
    if (y <= 0 || map[x][y - 1].type != 0) wall_count++;
    if (y >= height - 1 || map[x][y + 1].type != 0) wall_count++;
    if (x <= 0 || map[x - 1][y].type != 0) wall_count++;
    if (x >= width - 1 || map[x + 1][y].type != 0) wall_count++;
    return wall_count;
}

/**
 * @brief Haritadaki tüm düşmanları, birbirine yakın olanları aynı gruba alacak şekilde kümelere ayırır.
 * @param enemy_agents Düşman ajanların listesi.
 * @param enemy_agent_count Düşman sayısı.
 * @param my_agents Dost ajanların listesi (dost ateşi kontrolü için).
 * @param my_agent_count Dost ajan sayısı.
 * @param groups Çıktı parametresi, bulunan gruplar bu diziye yazılır.
 * @return Bulunan toplam grup sayısını döndürür.
 * @note Bu fonksiyon, stratejimizin temelini oluşturur. Düşmanları gruplayarak
 *       en değerli hedefleri (en kalabalık grupları) belirlememizi sağlar.
 *       Merkez hesaplamasında round() kullanılarak isabet oranı artırılmıştır.
 */
int find_enemy_groups(AgentState enemy_agents[], int enemy_agent_count, AgentState my_agents[], int my_agent_count, EnemyGroup groups[]) {
    int group_count = 0;
    bool visited[enemy_agent_count];
    for (int i = 0; i < enemy_agent_count; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < enemy_agent_count; i++) {
        if (!visited[i]) {
            EnemyGroup new_group = {0, 0, 0, false};
            int total_x = 0;
            int total_y = 0;
            int member_count = 0;
            
            int queue[enemy_agent_count];
            int queue_start = 0;
            int queue_end = 0;
            
            queue[queue_end++] = i;
            visited[i] = true;

            while(queue_start < queue_end) {
                int current_idx = queue[queue_start++];
                member_count++;
                total_x += enemy_agents[current_idx].x;
                total_y += enemy_agents[current_idx].y;

                for (int j = 0; j < enemy_agent_count; j++) {
                    if (!visited[j]) {
                        if (get_manhattan_distance(enemy_agents[current_idx].x, enemy_agents[current_idx].y, enemy_agents[j].x, enemy_agents[j].y) <= 4) {
                            visited[j] = true;
                            queue[queue_end++] = j;
                        }
                    }
                }
            }

            new_group.size = member_count;
            if (new_group.size > 0) {
                new_group.center_x = round((float)total_x / new_group.size);
                new_group.center_y = round((float)total_y / new_group.size);

                for(int k=0; k < my_agent_count; k++) {
                    if(get_manhattan_distance(my_agents[k].x, my_agents[k].y, new_group.center_x, new_group.center_y) <= 2) {
                        new_group.contains_friend = true;
                        break;
                    }
                }
                groups[group_count++] = new_group;
            }
        }
    }
    return group_count;
}

// --- Ustanın Notu: Karar Fonksiyonları (Modüler Mantık) ---

/**
 * @brief "Esir Ajan" için eylem kararı verir.
 * @note Bu ajanın stratejisi basittir: Güvenli bir köşeye çekil ve menziline giren
 *       en kalabalık, güvenli düşman grubuna bomba at.
 * @param agent Karar verilecek ajanın bilgileri.
 * @param enemy_groups Tespit edilmiş düşman grupları.
 * @param group_count Düşman grup sayısı.
 * @param action_str Çıktı parametresi, üretilen komut bu string'e yazılır.
 */
void decide_esir_agent_action(AgentState* agent, EnemyGroup enemy_groups[], int group_count, char* action_str) {
    fprintf(stderr, "Ajan %d (Esir) için karar veriliyor...\n", agent->id);
    int best_move_x = 12; // Haritaya özel güvenli köşe X
    int best_move_y = 1;  // Haritaya özel güvenli köşe Y

    int best_throw_x = -1, best_throw_y = -1;
    int max_group_size = 1; // En az 2 kişilik grupları hedefle

    if (agent->splash_bombs > 0) {
        for (int g = 0; g < group_count; g++) {
            // Güvenlik kontrolleri: Dost vurma, menzil dışı olma, kendini vurma
            if (enemy_groups[g].contains_friend) continue;
            if (get_manhattan_distance(agent->x, agent->y, enemy_groups[g].center_x, enemy_groups[g].center_y) > 4) continue;
            if (get_manhattan_distance(agent->x, agent->y, enemy_groups[g].center_x, enemy_groups[g].center_y) <= 1) continue;

            // En kârlı hedefi bul
            if (enemy_groups[g].size > max_group_size) {
                max_group_size = enemy_groups[g].size;
                best_throw_x = enemy_groups[g].center_x;
                best_throw_y = enemy_groups[g].center_y;
            }
        }
    }

    // Komutu oluştur
    if (best_throw_x != -1) {
        sprintf(action_str, "%d;MOVE %d %d;THROW %d %d", agent->id, best_move_x, best_move_y, best_throw_x, best_throw_y);
    } else {
        sprintf(action_str, "%d;MOVE %d %d", agent->id, best_move_x, best_move_y);
    }
}

/**
 * @brief "Serbest Ajan" için eylem kararı verir.
 * @note Bu ajanın stratejisi daha dinamiktir: En kârlı düşman grubunu bulur,
 *       o gruba ateş etmek için en ideal pozisyona (hizalı ve en yakın) hareket eder
 *       ve menzile girdiğinde ateş eder.
 */
void decide_serbest_agent_action(AgentState* agent, EnemyGroup enemy_groups[], int group_count, char* action_str) {
    fprintf(stderr, "Ajan %d (Serbest) için karar veriliyor...\n", agent->id);
    int best_move_x = agent->x;
    int best_move_y = agent->y;
    int best_throw_x = -1, best_throw_y = -1;

    // 1. Adım: En iyi hedef grubunu seç.
    int best_target_group_idx = -1;
    int max_group_size = 1; // En az 2 kişilik grupları hedefle
    for (int g = 0; g < group_count; g++) {
        if (!enemy_groups[g].contains_friend && enemy_groups[g].size > max_group_size) {
            max_group_size = enemy_groups[g].size;
            best_target_group_idx = g;
        }
    }

    // 2. Adım: Eğer bir hedef bulunduysa, ona göre hareket ve atış planla.
    if (best_target_group_idx != -1) {
        EnemyGroup* target_group = &enemy_groups[best_target_group_idx];
        int target_x = target_group->center_x;
        int target_y = target_group->center_y;
        fprintf(stderr, "  Serbest ajan hedefi: Grup %d, Merkez(%d,%d)\n", best_target_group_idx, target_x, target_y);
        
        // 2a. Adım: Hedefe ateş etmek için en iyi pozisyonu bul.
        // Amaç: Hedefle aynı hizada (yatay/dikey) ve ajana en yakın boş kareyi bulmak.
        int best_throw_pos_x = -1, best_throw_pos_y = -1;
        int min_dist_to_throw_pos = 1000;

        for(int k=1; k<=4; k++){ // 1'den 4'e kadar olan mesafeleri tara
            int positions[4][2] = {{target_x, target_y-k}, {target_x, target_y+k}, {target_x-k, target_y}, {target_x+k, target_y}};
            for(int p=0; p<4; p++){
                int px = positions[p][0];
                int py = positions[p][1];
                if(px >= 0 && px < width && py >= 0 && py < height && map[px][py].type == 0){
                    int dist = get_manhattan_distance(agent->x, agent->y, px, py);
                    if(dist < min_dist_to_throw_pos){
                        min_dist_to_throw_pos = dist;
                        best_throw_pos_x = px;
                        best_throw_pos_y = py;
                    }
                }
            }
        }

        // Eğer uygun bir atış pozisyonu bulunduysa, hareket hedefimiz orası olur.
        if(best_throw_pos_x != -1){
            fprintf(stderr, "  En iyi atış pozisyonu: (%d,%d), Mesafe: %d\n", best_throw_pos_x, best_throw_pos_y, min_dist_to_throw_pos);
            best_move_x = best_throw_pos_x;
            best_move_y = best_throw_pos_y;
        }

        // 2b. Adım: Zaten hizadaysak ve menzildeysek, bombayı at.
        if (agent->splash_bombs > 0 && (agent->x == target_x || agent->y == target_y) && get_manhattan_distance(agent->x, agent->y, target_x, target_y) <= 4) {
            best_throw_x = target_x;
            best_throw_y = target_y;
        }
    } else {
        // 3. Adım: Uygun hedef yoksa, haritanın merkezine git.
        best_move_x = width / 2;
        best_move_y = height / 2;
    }

    // 4. Adım: Nihai komutu oluştur.
    if (best_throw_x != -1) {
        // Atış komutu önceliklidir.
        sprintf(action_str, "%d;MOVE %d %d;THROW %d %d", agent->id, agent->x, agent->y, best_throw_x, best_throw_y);
    } else {
        // Atış yoksa, hesaplanan en iyi hareket hedefine doğru bir adım at.
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        int final_move_x = agent->x;
        int final_move_y = agent->y;
        int min_dist = get_manhattan_distance(agent->x, agent->y, best_move_x, best_move_y);

        for(int j=0; j<4; j++){
            int next_x = agent->x + dx[j];
            int next_y = agent->y + dy[j];
            bool is_backtrack = (next_x == agent->last_x && next_y == agent->last_y);
            if(next_x >= 0 && next_x < width && next_y >= 0 && next_y < height && map[next_x][next_y].type == 0 && !is_backtrack){
                int dist = get_manhattan_distance(next_x, next_y, best_move_x, best_move_y);
                if(dist < min_dist){
                    min_dist = dist;
                    final_move_x = next_x;
                    final_move_y = next_y;
                }
            }
        }
        sprintf(action_str, "%d;MOVE %d %d", agent->id, final_move_x, final_move_y);
    }
}


// --- Ustanın Notu: Ana Oyun Döngüsü ---
int main() {
    // --- Başlangıç Aşaması: Sabit oyun verilerini bir kez oku ---
    scanf("%d", &my_id);
    int agent_data_count;
    scanf("%d", &agent_data_count);
    AgentData all_agent_data[agent_data_count];
    for (int i = 0; i < agent_data_count; i++) {
        scanf("%d%d", &all_agent_data[i].id, &all_agent_data[i].player);
        int dummy[4];
        scanf("%d%d%d%d", &dummy[0], &dummy[1], &dummy[2], &dummy[3]);
    }
    scanf("%d%d", &width, &height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            scanf("%d%d%d", &map[j][i].x, &map[j][i].y, &map[j][i].type);
        }
    }

    // --- Oyun Döngüsü: Her tur tekrar eden mantık ---
    while (1) {
        turn_counter++;
        // --- 1. Tur Verilerini Oku ---
        int agent_count;
        scanf("%d", &agent_count);
        
        AgentState my_agents[2];
        AgentState enemy_agents[50];
        int my_agent_idx = 0;
        int enemy_agent_idx = 0;

        for (int i = 0; i < agent_count; i++) {
            int id, x, y, cooldown, splash_bombs, wetness;
            scanf("%d%d%d%d%d%d", &id, &x, &y, &cooldown, &splash_bombs, &wetness);
            bool is_mine = false;
            for(int j = 0; j < agent_data_count; j++) {
                if(all_agent_data[j].id == id && all_agent_data[j].player == my_id) {
                    is_mine = true;
                    break;
                }
            }
            if (is_mine) {
                my_agents[my_agent_idx] = (AgentState){id, x, y, splash_bombs, -1, -1};
                for(int k = 0; k < previous_agent_count; k++) {
                    if(previous_agents[k].id == id) {
                        my_agents[my_agent_idx].last_x = previous_agents[k].x;
                        my_agents[my_agent_idx].last_y = previous_agents[k].y;
                        break;
                    }
                }
                my_agent_idx++;
            } else {
                enemy_agents[enemy_agent_idx++] = (AgentState){id, x, y, splash_bombs, -1, -1};
            }
        }

        int my_agent_count_input;
        scanf("%d", &my_agent_count_input);

        // --- 2. Rolleri Belirle (Sadece ilk turda) ---
        if (turn_counter == 1 && my_agent_idx == 2) {
            int walls1 = count_adjacent_walls(my_agents[0].x, my_agents[0].y);
            int walls2 = count_adjacent_walls(my_agents[1].x, my_agents[1].y);
            esir_agent_id = (walls1 > walls2) ? my_agents[0].id : my_agents[1].id;
            fprintf(stderr, "Esir Ajan ID: %d olarak belirlendi.\n", esir_agent_id);
        }

        // --- 3. Çevreyi Analiz Et ---
        EnemyGroup enemy_groups[50];
        int group_count = find_enemy_groups(enemy_agents, enemy_agent_idx, my_agents, my_agent_idx, enemy_groups);
        
        fprintf(stderr, "Bulunan Düşman Grubu Sayısı: %d\n", group_count);
        for(int i=0; i<group_count; i++) {
            fprintf(stderr, "  Grup %d: Merkez(%d,%d), Boyut:%d, Dost Var Mı:%d\n", i, enemy_groups[i].center_x, enemy_groups[i].center_y, enemy_groups[i].size, enemy_groups[i].contains_friend);
        }

        // --- 4. Her Ajan İçin Karar Ver ve Eyleme Geç ---
        for (int i = 0; i < my_agent_idx; i++) {
            AgentState* agent = &my_agents[i];
            char action_str[100] = "";

            // Rolüne göre uygun karar fonksiyonunu çağır
            if (agent->id == esir_agent_id) {
                decide_esir_agent_action(agent, enemy_groups, group_count, action_str);
            } 
            else {
                decide_serbest_agent_action(agent, enemy_groups, group_count, action_str);
            }
            // Üretilen komutu oyuna gönder
            printf("%s\n", action_str);
        }
        
        // --- 5. Tur Sonu: Durumu Güncelle ---
        previous_agent_count = my_agent_idx;
        for(int i = 0; i < my_agent_idx; i++) {
            previous_agents[i] = my_agents[i];
        }
    }
    return 0;
}