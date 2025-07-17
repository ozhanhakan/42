#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// --- Ustanın Notu: Struct Tanımlamaları ---
// Bir 'struct', birbiriyle ilişkili değişkenleri tek bir isim altında toplamamızı sağlayan bir veri yapısıdır.
// Tıpkı bir kimlik kartının ad, soyad, doğum tarihi gibi bilgileri bir arada tutması gibi.

// 'Target' adında yeni bir veri türü oluşturuyoruz.
// Bu yapı, bir hedefin x ve y koordinatlarını bir arada tutacak.
typedef struct {
    int x; // Hedefin yatay (x) konumu
    int y; // Hedefin dikey (y) konumu
} Target;

// 'Agent' adında başka bir veri türü oluşturuyoruz.
// Bu yapı, bir ajanımıza ait tüm önemli bilgileri içerecek.
typedef struct {
    int id;         // Ajanın oyun tarafından verilen benzersiz kimlik numarası
    int x;          // Ajanın haritadaki mevcut yatay (x) konumu
    int y;          // Ajanın haritadaki mevcut dikey (y) konumu
    Target target;  // Ajanın gitmesi gereken hedef. 'Target' yapısını burada kullanıyoruz.
} Agent;

int main()
{
    // --- Ustanın Notu: Başlangıç Bilgilerini Okuma (Setup Phase) ---
    // Bu bölümdeki bilgiler, bizim basit "hedefe git" görevimiz için gerekli değil.
    // Ancak oyun sistemi bu bilgileri bize gönderiyor ve programımızın çökmemesi için
    // onları okuyup bir değişkene atamamız gerekiyor. Bu değişkenleri daha sonra hiç kullanmayacağız.

    int my_id; // Benim oyuncu kimliğim (0 veya 1)
    scanf("%d", &my_id);

    int agent_data_count; // Oyundaki toplam ajan sayısı
    scanf("%d", &agent_data_count);
    for (int i = 0; i < agent_data_count; i++) {
        // Bu döngü, oyundaki her bir ajanın özelliklerini okur.
        // Bizim için önemsiz olan bu bilgileri sadece okuyup geçiyoruz.
        int agent_id, player, shoot_cooldown, optimal_range, soaking_power, splash_bombs;
        scanf("%d%d%d%d%d%d", &agent_id, &player, &shoot_cooldown, &optimal_range, &soaking_power, &splash_bombs);
    }

    int width, height; // Haritanın genişliği ve yüksekliği
    scanf("%d%d", &width, &height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Bu döngü, haritadaki her bir karonun (tile) bilgisini okur.
            // Şimdilik duvarları dikkate almadığımız için bu bilgiyi de sadece okuyup geçiyoruz.
            int x, y, tile_type;
            scanf("%d%d%d", &x, &y, &tile_type);
        }
    }

    // --- Ustanın Notu: Kendi Ajanlarımızı ve Hedeflerimizi Hazırlama ---
    // 'Agent' yapısını kullanarak iki ajanlık bir dizi oluşturuyoruz. Bu bizim takımımız.
    Agent my_agents[2];

    // PDF'te belirtilen hedefleri ajanlarımıza atıyoruz.
    // 0 numaralı ajanımızın hedefi (6, 1)
    my_agents[0].target.x = 6;
    my_agents[0].target.y = 1;

    // 1 numaralı ajanımızın hedefi (6, 3)
    my_agents[1].target.x = 6;
    my_agents[1].target.y = 3;

    // --- Ustanın Notu: Oyun Döngüsü (Game Loop) ---
    // 'while (1)' sonsuz bir döngü oluşturur. Oyun bitene kadar her turda bu döngü tekrar çalışacak.
    while (1) {
        // Her tur başında, oyundaki tüm ajanların güncel durumları bize verilir.
        int agent_count;
        scanf("%d", &agent_count);
        for (int i = 0; i < agent_count; i++) {
            // Yine gereksiz bilgilerle birlikte ajanların güncel konumları okunur.
            int agent_id, x, y, cooldown, splash_bombs, wetness;
            scanf("%d%d%d%d%d%d", &agent_id, &x, &y, &cooldown, &splash_bombs, &wetness);
            
            // Basit bir varsayım: Bize verilen ilk iki ajanın bizim ajanlarımız olduğunu kabul ediyoruz.
            // Bu, en basit başlangıçtır. 0. ajanımızı dizimizin 0. indeksine, 1. ajanımızı 1. indekse yerleştiriyoruz.
            if (i < 2) {
                my_agents[i].id = agent_id; // Ajanın ID'sini al
                my_agents[i].x = x;         // Ajanın güncel X konumunu al
                my_agents[i].y = y;         // Ajanın güncel Y konumunu al
            }
        }
        
        // Bizim kontrolümüzdeki ajan sayısı okunur. Bu her zaman 2 olacak.
        int my_agent_count;
        scanf("%d", &my_agent_count);

        // --- Ustanın Notu: Eylem Karar Mekanizması ---
        // Bu döngü, bizim her bir ajanımız için (toplam 2 tane) birer kez çalışacak.
        for (int i = 0; i < my_agent_count; i++) {
            // O an işlem yaptığımız ajanı daha kolay erişim için bir değişkene alalım.
            Agent current_agent = my_agents[i];
            
            // Hedef koordinatlarını ve mevcut koordinatları daha kısa isimli değişkenlere atayalım.
            int target_x = current_agent.target.x;
            int target_y = current_agent.target.y;
            int current_x = current_agent.x;
            int current_y = current_agent.y;

            // Stratejimiz: "Önce X eksenini hizala, sonra Y eksenini hizala."
            // Bu, duvarları görmezden gelen en basit yol bulma mantığıdır.

            // 1. Adım: Ajanın X konumu, hedefin X konumundan farklı mı?
            if (current_x < target_x) {
                // Mevcut X, hedeften küçükse, hedef sağdadır. Sağa doğru BİR adım at.
                printf("MOVE %d %d\n", current_x + 1, current_y);
            } else if (current_x > target_x) {
                // Mevcut X, hedeften büyükse, hedef soldadır. Sola doğru BİR adım at.
                printf("MOVE %d %d\n", current_x - 1, current_y);
            }
            // 2. Adım: Eğer X konumları aynıysa, sıra Y konumunu kontrol etmeye geldi.
            else if (current_y < target_y) {
                // Mevcut Y, hedeften küçükse, hedef aşağıdadır. Aşağıya doğru BİR adım at.
                printf("MOVE %d %d\n", current_x, current_y + 1);
            } else if (current_y > target_y) {
                // Mevcut Y, hedeften büyükse, hedef yukarıdadır. Yukarıya doğru BİR adım at.
                printf("MOVE %d %d\n", current_x, current_y - 1);
            } else {
                // Hem X hem de Y konumları hedefe eşitse, ajanımız hedefe ulaşmıştır.
                // Olduğu yerde kalması için kendi konumuna "hareket et" komutu veriyoruz.
                printf("MOVE %d %d\n", current_x, current_y);
            }
        }
    }

    return 0;
}