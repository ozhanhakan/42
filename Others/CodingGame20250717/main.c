#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Ustanın Notu: Ajanlarımızın bilgilerini ve hedeflerini saklamak için
// basit yapılar oluşturalım. Bu, kodumuzu daha okunaklı yapacak.
typedef struct {
    int x;
    int y;
} Target;

typedef struct {
    int id;
    int x;
    int y;
    Target target; // Her ajanın bir hedefi olacak
} Agent;

int main()
{
    // Ustanın Notu: Bu başlangıç bilgileri bizim görevimiz için gereksiz.
    // Sadece okuyup geçiyoruz ki programın akışı bozulmasın.
    int my_id;
    scanf("%d", &my_id);
    int agent_data_count;
    scanf("%d", &agent_data_count);
    for (int i = 0; i < agent_data_count; i++) {
        int agent_id, player, shoot_cooldown, optimal_range, soaking_power, splash_bombs;
        scanf("%d%d%d%d%d%d", &agent_id, &player, &shoot_cooldown, &optimal_range, &soaking_power, &splash_bombs);
    }
    int width;
    int height;
    scanf("%d%d", &width, &height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int x, y, tile_type;
            scanf("%d%d%d", &x, &y, &tile_type);
        }
    }

    // Ustanın Notu: İki ajanımızı ve hedeflerini burada tanımlayalım.
    Agent my_agents[2];
    my_agents[0].target.x = 6;
    my_agents[0].target.y = 1;
    my_agents[1].target.x = 6;
    my_agents[1].target.y = 3;

    // Oyun döngüsü
    while (1) {
        // Ustanın Notu: Her tur başında ajanlarımızın güncel konumlarını okuyacağız.
        int agent_count;
        scanf("%d", &agent_count);
        for (int i = 0; i < agent_count; i++) {
            int agent_id, x, y, cooldown, splash_bombs, wetness;
            scanf("%d%d%d%d%d%d", &agent_id, &x, &y, &cooldown, &splash_bombs, &wetness);
            
            // Ustanın Notu: Gelen verinin bizim ajanımıza ait olup olmadığını kontrol etmeliyiz.
            // Şimdilik basitçe ilk okuduğumuz iki ajanın bizim olduğunu varsayalım.
            // Bu varsayımı daha sonra düzeltebiliriz.
            if (i < 2) {
                my_agents[i].id = agent_id;
                my_agents[i].x = x;
                my_agents[i].y = y;
            }
        }
        
        int my_agent_count;
        scanf("%d", &my_agent_count);
        for (int i = 0; i < my_agent_count; i++) {
            // Ustanın Notu: Artık her ajan için mantıklı bir hareket komutu üreteceğiz.
            // Bu döngü bizim iki ajanımız için çalışacak.
            Agent current_agent = my_agents[i];
            int target_x = current_agent.target.x;
            int target_y = current_agent.target.y;
            int current_x = current_agent.x;
            int current_y = current_agent.y;

            // En basit strateji: Önce X ekseninde hedefe git, sonra Y ekseninde.
            if (current_x < target_x) {
                // Hedef sağda, sağa git
                printf("MOVE %d %d\n", current_x + 1, current_y);
            } else if (current_x > target_x) {
                // Hedef solda, sola git
                printf("MOVE %d %d\n", current_x - 1, current_y);
            } else if (current_y < target_y) {
                // X tamam, hedef aşağıda, aşağı git
                printf("MOVE %d %d\n", current_x, current_y + 1);
            } else if (current_y > target_y) {
                // X tamam, hedef yukarıda, yukarı git
                printf("MOVE %d %d\n", current_x, current_y - 1);
            } else {
                // Zaten hedeftesin, bekle.
                printf("MOVE %d %d\n", current_x, current_y);
            }
        }
    }

    return 0;
}