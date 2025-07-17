#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// --- Ustanın Notu: Struct Tanımlamaları (Veri Planlarımız) ---
// Bu yapılar, farklı bilgileri düzenli kutularda saklamamızı sağlar.

// AgentData: Ajanların oyun başında verilen ve değişmeyen kimlik bilgileri.
typedef struct { 
    int id;       // Ajanın benzersiz kimliği.
    int player;   // Ajanın sahibi olan oyuncunun kimliği (Biz miyiz, düşman mı?).
} AgentData;

// AgentState: Ajanların her tur değişen anlık durumları.
typedef struct { 
    int id;       // Ajanın kimliği.
    int x, y;     // Ajanın haritadaki mevcut konumu.
} AgentState;

// Tile: Haritadaki tek bir karonun bilgileri.
typedef struct { 
    int x, y;     // Karonun konumu.
    int type;     // Karonun türü (0:Boş, 1:Alçak Siper, 2:Yüksek Siper).
} Tile;

// --- Ustanın Notu: Global Değişkenler (Evrensel Bilgilerimiz) ---
// Bu değişkenlere programın her yerinden erişebiliriz.
int my_id;
int width, height;
// Haritanın kendisini saklamak için 2 boyutlu bir 'Tile' dizisi.
// map[x][y] diyerek doğrudan o koordinattaki karonun bilgisine ulaşabiliriz.
Tile map[20][10]; 

// --- Ustanın Notu: Yardımcı Fonksiyon: Siper Seviyesi Hesaplama ---
// Bu fonksiyon, kod tekrarını önleyen ve işi uzmanına yaptıran küçük bir alet gibidir.
// Görevi: Verilen bir (x, y) konumunun etrafındaki siperleri kontrol edip,
// o noktanın ne kadar korunaklı olduğunu söylemek.
int get_cover_level_at(int x, int y) {
    int best_cover = 0; // Başlangıçta hiç koruma yok varsayalım.
    // Bitişikteki 4 karoyu kontrol et ve en yüksek siper değerini bul.
    if (y > 0 && map[x][y - 1].type > best_cover) best_cover = map[x][y - 1].type;
    if (y < height - 1 && map[x][y + 1].type > best_cover) best_cover = map[x][y + 1].type;
    if (x > 0 && map[x - 1][y].type > best_cover) best_cover = map[x - 1][y].type;
    if (x < width - 1 && map[x + 1][y].type > best_cover) best_cover = map[x + 1][y].type;
    return best_cover; // Bulunan en iyi siper seviyesini döndür.
}

int main()
{
    // --- Başlangıç Aşaması: Bilgileri Topla ve Hazırlan ---
    scanf("%d", &my_id);
    int agent_data_count;
    scanf("%d", &agent_data_count);
    AgentData all_agent_data[agent_data_count];
    for (int i = 0; i < agent_data_count; i++) {
        scanf("%d%d", &all_agent_data[i].id, &all_agent_data[i].player);
        int dummy[4]; // Gereksiz bilgileri okuyup atmak için geçici bir yer.
        scanf("%d%d%d%d", &dummy[0], &dummy[1], &dummy[2], &dummy[3]);
    }
    scanf("%d%d", &width, &height);
    // Haritayı oku ve 'map' dizimize yerleştir. Bu, stratejimizin temelidir.
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            scanf("%d%d%d", &map[j][i].x, &map[j][i].y, &map[j][i].type);
        }
    }

    // --- Oyun Döngüsü: Karar ve Eylem ---
    while (1) {
        int agent_count;
        scanf("%d", &agent_count);
        
        AgentState my_agents[2];
        AgentState enemy_agents[agent_count];
        int my_agent_idx = 0;
        int enemy_agent_idx = 0;

        // Gelen ajan verilerini oku ve dost/düşman olarak ayır.
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
                my_agents[my_agent_idx++] = (AgentState){id, x, y};
            } else {
                enemy_agents[enemy_agent_idx++] = (AgentState){id, x, y};
            }
        }

        int my_agent_count_input;
        scanf("%d", &my_agent_count_input);

        // --- Stratejinin Kalbi: Her Ajan İçin Ayrı Karar Mekanizması ---
        for (int i = 0; i < my_agent_idx; i++) {
            int current_x = my_agents[i].x;
            int current_y = my_agents[i].y;
            
            // --- Adım 1: Bu ajan için en iyi HAREKET noktasını bul ---
            int best_move_x = current_x;
            int best_move_y = current_y;
            int max_my_cover = -1;
            int dx[] = {0, 0, 1, -1}; // Bitişikteki karelere gitmek için yönler
            int dy[] = {1, -1, 0, 0};
            for(int j = 0; j < 4; j++) {
                int next_x = current_x + dx[j];
                int next_y = current_y + dy[j];
                // Gidilecek yer harita içinde ve boş bir karo mu?
                if (next_x >= 0 && next_x < width && next_y >= 0 && next_y < height && map[next_x][next_y].type == 0) {
                    int cover = get_cover_level_at(next_x, next_y);
                    // Eğer bu hamle, şimdiye kadar bulduğumuzdan daha iyi bir siper sağlıyorsa...
                    if (cover > max_my_cover) {
                        max_my_cover = cover; // ...yeni en iyi siper seviyemiz bu olur.
                        best_move_x = next_x; // ...ve yeni en iyi hareket hedefimiz bu kare olur.
                        best_move_y = next_y;
                    }
                }
            }

            // --- Adım 2: Bu ajan için en zayıf BÖLGESEL düşmanı bul ---
            int local_target_id = -1;
            int min_enemy_cover = 3; // Mümkün olan en yüksek korumadan (2) daha büyük bir değerle başla.
            for (int j = 0; j < enemy_agent_idx; j++) {
                // Bu mantık, ajanın ve düşmanın haritanın aynı yarısında olup olmadığını kontrol eder.
                bool same_side = (current_x < width / 2 && enemy_agents[j].x < width / 2) || // İkisi de solda mı?
                                 (current_x >= width / 2 && enemy_agents[j].x >= width / 2); // VEYA ikisi de sağda mı?
                
                if (same_side) { // Eğer düşman, ajanın kendi bölgesindeyse...
                    int cover = get_cover_level_at(enemy_agents[j].x, enemy_agents[j].y);
                    // ...bu bölgesel düşmanın koruması, şimdiye kadar bulduğumuz en zayıfından daha mı az?
                    if (cover < min_enemy_cover) {
                        min_enemy_cover = cover; // Evet, yeni en zayıf bu.
                        local_target_id = enemy_agents[j].id; // Hedefimiz bu ajan olsun.
                    }
                }
            }
            
            // --- Adım 3: Nihai Komutu Oluştur ve Yazdır ---
            // Her ajanın kendi ID'si, kendi bulduğu en iyi HAREKET ve kendi bulduğu en zayıf HEDEF ile komut oluşturulur.
            printf("%d;MOVE %d %d;SHOOT %d\n", my_agents[i].id, best_move_x, best_move_y, local_target_id);
        }
    }
    return 0;
}