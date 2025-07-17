#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// --- Ustanın Notu: Struct Tanımlamaları (Güncellendi) ---
// Artık ajanların kime ait olduğunu bilmemiz gerekiyor. Bu yüzden AgentData yapısını kullanacağız.
typedef struct {
    int id;
    int player; // 0 mı, 1 mi? Bu bilgi ajanın dost mu düşman mı olduğunu belirler.
    // Bu görev için diğer bilgiler (cooldown, range vs.) şimdilik gereksiz.
} AgentData;

// Her tur değişen bilgileri tutmak için ayrı bir yapı.
typedef struct {
    int id;
    int x;
    int y;
    int wetness; // Islaklık seviyesi, hedefimizi belirlemek için en önemli bilgi.
} AgentState;

int main()
{
    // --- Ustanın Notu: Başlangıç Bilgilerini Okuma ve SAKLAMA ---
    int my_id;
    scanf("%d", &my_id);

    int agent_data_count;
    scanf("%d", &agent_data_count);

    // Bütün ajanların temel bilgilerini saklamak için bir dizi oluşturalım.
    AgentData all_agent_data[agent_data_count];
    for (int i = 0; i < agent_data_count; i++) {
        all_agent_data[i].id = i; // ID'yi doğrudan atayalım
        scanf("%d%d", &all_agent_data[i].id, &all_agent_data[i].player);
        // Kalan gereksiz bilgileri okuyup geçelim.
        int shoot_cooldown, optimal_range, soaking_power, splash_bombs;
        scanf("%d%d%d%d", &shoot_cooldown, &optimal_range, &soaking_power, &splash_bombs);
    }

    // Harita bilgilerini okuyup geçiyoruz, bu görevde ihtiyacımız yok.
    int width, height;
    scanf("%d%d", &width, &height);
    for (int i = 0; i < width * height; i++) {
        int x, y, tile_type;
        scanf("%d%d%d", &x, &y, &tile_type);
    }

    // --- Ustanın Notu: Oyun Döngüsü (Game Loop) ---
    while (1) {
        int agent_count;
        scanf("%d", &agent_count);

        // Her turdaki ajan durumlarını saklamak için bir dizi.
        AgentState current_states[agent_count];
        for (int i = 0; i < agent_count; i++) {
            current_states[i].id = i; // ID'yi atayalım
            scanf("%d%d%d", &current_states[i].id, &current_states[i].x, &current_states[i].y);
            // Kalan gereksiz bilgileri okuyup geçelim.
            int cooldown, splash_bombs;
            scanf("%d%d%d", &cooldown, &splash_bombs, &current_states[i].wetness);
        }

        // --- Ustanın Notu: Hedef Belirleme Mekanizması ---
        int target_id = -1;
        int max_wetness = -1;

        // Bütün ajanları kontrol et
        for (int i = 0; i < agent_count; i++) {
            int current_agent_id = current_states[i].id;
            int current_agent_player = -1;

            // Bu ajanın kime ait olduğunu bul (dost mu, düşman mı?)
            for (int j = 0; j < agent_data_count; j++) {
                if (all_agent_data[j].id == current_agent_id) {
                    current_agent_player = all_agent_data[j].player;
                    break;
                }
            }

            // Eğer ajan düşmansa (player ID'si bizimkiyle aynı değilse)
            if (current_agent_player != my_id) {
                // Bu düşmanın ıslaklığı, şimdiye kadar gördüğümüz en yüksek ıslaklıktan fazla mı?
                if (current_states[i].wetness > max_wetness) {
                    // Evet, fazla. Yeni hedefimiz bu düşman.
                    max_wetness = current_states[i].wetness;
                    target_id = current_states[i].id;
                }
            }
        }

        // Bizim kontrolümüzdeki ajan sayısı okunur.
        int my_agent_count;
        scanf("%d", &my_agent_count);

        // --- Ustanın Notu: Eylem Komutlarını Oluşturma ---
        // Eğer bir hedef bulunduysa (yani oyunda en az bir düşman varsa)
        if (target_id != -1) {
            // Kendi ajanlarımızın her biri için aynı komutu ver.
            for (int i = 0; i < my_agent_count; i++) {
                // Çıktı formatı: "SHOOT <hedef_id>"
                printf("SHOOT %d\n", target_id);
            }
        } else {
            // Eğer hiç düşman kalmadıysa, ne olur ne olmaz diye bekleme komutu verelim.
            for (int i = 0; i < my_agent_count; i++) {
                printf("HUNKER_DOWN\n");
            }
        }
    }

    return 0;
}