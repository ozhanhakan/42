#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <limits>

/**
 * @brief Ajanın özelliklerini ve durumunu tutan yapı.
 */
struct Agent {
    int id, player, x, y, cooldown, splash_bombs, wetness;
};

/**
 * @brief Ana oyun döngüsü.
 */
int main() {
    std::cerr << "Bilgi: Kod Sürümü 5.8 (C++ tam işlevsellik, dayanıklı getline, gelişmiş debug, tur sonlandırma)\n";

    // Başlangıç girişleri
    std::string line;
    int my_id = 0;
    std::cerr << "Bilgi: my_id okunuyor\n";
    if (!std::getline(std::cin, line)) {
        std::cerr << "Hata: my_id satırı okunamadı\n";
        return 1;
    }
    std::stringstream ss(line);
    if (!(ss >> my_id)) {
        std::cerr << "Hata: my_id ayrıştırılamadı, satır: " << line << "\n";
        return 1;
    }
    std::cerr << "Bilgi: my_id=" << my_id << "\n";

    int agent_data_count = 0;
    std::cerr << "Bilgi: agent_data_count okunuyor\n";
    if (!std::getline(std::cin, line)) {
        std::cerr << "Hata: agent_data_count satırı okunamadı\n";
        return 1;
    }
    ss.clear();
    ss.str(line);
    if (!(ss >> agent_data_count) || agent_data_count < 0 || agent_data_count > 10) {
        std::cerr << "Hata: agent_data_count ayrıştırılamadı veya geçersiz, satır: " << line << "\n";
        return 1;
    }
    std::cerr << "Bilgi: agent_data_count=" << agent_data_count << "\n";

    std::vector<Agent> agents(agent_data_count);
    for (int i = 0; i < agent_data_count; ++i) {
        std::cerr << "Bilgi: Ajan " << i << " verileri okunuyor\n";
        if (!std::getline(std::cin, line)) {
            std::cerr << "Hata: Ajan " << i << " satırı okunamadı\n";
            return 1;
        }
        ss.clear();
        ss.str(line);
        int shoot_cooldown = 0, optimal_range = 0, soaking_power = 0, splash_bombs = 0;
        if (!(ss >> agents[i].id >> agents[i].player >> shoot_cooldown >> optimal_range >> soaking_power >> splash_bombs)) {
            std::cerr << "Hata: Ajan " << i << " verileri ayrıştırılamadı, satır: " << line << "\n";
            return 1;
        }
        agents[i].x = -1;
        agents[i].y = -1;
        agents[i].cooldown = 0;
        agents[i].splash_bombs = splash_bombs;
        agents[i].wetness = 0;
        std::cerr << "Bilgi: Ajan " << agents[i].id << ": player=" << agents[i].player << "\n";
    }

    int width = 0, height = 0;
    std::cerr << "Bilgi: Harita boyutları okunuyor\n";
    if (!std::getline(std::cin, line)) {
        std::cerr << "Hata: Harita boyutları satırı okunamadı\n";
        return 1;
    }
    ss.clear();
    ss.str(line);
    if (!(ss >> width >> height) || width <= 0 || height <= 0) {
        std::cerr << "Hata: Harita boyutları ayrıştırılamadı, satır: " << line << "\n";
        return 1;
    }
    std::cerr << "Bilgi: Harita genişlik=" << width << ", yükseklik=" << height << "\n";

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cerr << "Bilgi: Harita karesi (" << j << "," << i << ") okunuyor\n";
            if (!std::getline(std::cin, line)) {
                std::cerr << "Hata: Harita karesi (" << j << "," << i << ") satırı okunamadı\n";
                return 1;
            }
            ss.clear();
            ss.str(line);
            int x = 0, y = 0, tile_type = 0;
            if (!(ss >> x >> y >> tile_type)) {
                std::cerr << "Hata: Harita karesi (" << j << "," << i << ") ayrıştırılamadı, satır: " << line << "\n";
                return 1;
            }
            std::cerr << "Bilgi: Harita karesi (" << j << "," << i << "): x=" << x << ", y=" << y << ", tile_type=" << tile_type << "\n";
        }
    }
    std::cerr << "Bilgi: Başlangıç girişleri tamamlandı\n";

    // Oyun döngüsü
    while (true) {
        std::cerr << "Bilgi: Yeni tur başlatılıyor\n";
        int agent_count = 0;
        std::cerr << "Bilgi: agent_count okunuyor\n";
        if (!std::getline(std::cin, line)) {
            std::cerr << "Hata: agent_count satırı okunamadı, giriş verisi tükenmiş olabilir\n";
            break; // Döngüden çık, yerel test için sonlandır
        }
        ss.clear();
        ss.str(line);
        if (!(ss >> agent_count) || agent_count < 0 || agent_count > 10) {
            std::cerr << "Hata: agent_count ayrıştırılamadı veya geçersiz, satır: " << line << "\n";
            return 1;
        }
        std::cerr << "Bilgi: agent_count=" << agent_count << "\n";

        for (int i = 0; i < agent_count; ++i) {
            std::cerr << "Bilgi: Ajan " << i << " durumu okunuyor\n";
            if (!std::getline(std::cin, line)) {
                std::cerr << "Hata: Ajan " << i << " durumu satırı okunamadı\n";
                return 1;
            }
            ss.clear();
            ss.str(line);
            int id = 0, x = -1, y = -1, cooldown = 0, splash_bombs = 0, wetness = 0;
            if (!(ss >> id >> x >> y >> cooldown >> splash_bombs >> wetness)) {
                std::cerr << "Hata: Ajan " << i << " durumu ayrıştırılamadı, satır: " << line << "\n";
                return 1;
            }
            for (Agent& agent : agents) {
                if (agent.id == id) {
                    agent.x = x;
                    agent.y = y;
                    agent.cooldown = cooldown;
                    agent.splash_bombs = splash_bombs;
                    agent.wetness = wetness;
                    std::cerr << "Bilgi: Ajan " << id << ": (" << x << "," << y << "), wetness=" << wetness << "\n";
                    break;
                }
            }
        }

        int my_agent_count = 0;
        std::cerr << "Bilgi: my_agent_count okunuyor\n";
        if (!std::getline(std::cin, line)) {
            std::cerr << "Hata: my_agent_count satırı okunamadı\n";
            return 1;
        }
        ss.clear();
        ss.str(line);
        if (!(ss >> my_agent_count) || my_agent_count < 0 || my_agent_count > agent_count) {
            std::cerr << "Hata: my_agent_count ayrıştırılamadı veya geçersiz (agent_count=" << agent_count << "), satır: " << line << "\n";
            return 1;
        }
        std::cerr << "Bilgi: my_agent_count=" << my_agent_count << "\n";

        std::cerr << "Bilgi: my_agent_count sonrası yeni satır okunuyor\n";
        if (!std::getline(std::cin, line)) {
            std::cerr << "Hata: my_agent_count sonrası yeni satır okunamadı\n";
            return 1;
        }
        std::cerr << "Bilgi: Yeni satır: " << (line.empty() ? "boş" : line) << "\n";

        for (int i = 0; i < agent_count - my_agent_count; ++i) {
            std::cerr << "Bilgi: Rakip komut " << i << " okunuyor\n";
            if (!std::getline(std::cin, line)) {
                std::cerr << "Hata: Rakip komut " << i << " okunamadı\n";
                return 1;
            }
            std::cerr << "Bilgi: Rakip komut " << i << ": " << line << "\n";
        }

        int current_turn = 0, total_turns = 0;
        std::cerr << "Bilgi: Tur bilgileri okunuyor\n";
        if (!std::getline(std::cin, line)) {
            std::cerr << "Hata: Tur bilgileri satırı okunamadı\n";
            return 1;
        }
        ss.clear();
        ss.str(line);
        if (!(ss >> current_turn >> total_turns)) {
            std::cerr << "Hata: Tur bilgileri ayrıştırılamadı, satır: " << line << "\n";
            return 1;
        }
        std::cerr << "Bilgi: Tur " << current_turn << " / " << total_turns << "\n";

        std::vector<int> active_ids;
        std::cerr << "Bilgi: Aktif ajanlar aranıyor\n";
        for (const Agent& agent : agents) {
            if (agent.player == my_id && agent.wetness < 100) {
                active_ids.push_back(agent.id);
                std::cerr << "Bilgi: Aktif ajan bulundu: ID=" << agent.id << "\n";
            }
        }

        std::cerr << "Bilgi: Ajan ID’leri sıralanıyor\n";
        std::sort(active_ids.begin(), active_ids.end());
        for (int id : active_ids) {
            std::cerr << "Bilgi: Sıralı aktif ajan ID: " << id << "\n";
        }

        std::cerr << "Bilgi: Komutlar yazdırılıyor\n";
        for (int i = 0; i < my_agent_count; ++i) {
            if (i >= static_cast<int>(active_ids.size())) {
                std::cerr << "Hata: my_agent_count (" << my_agent_count << ") aktif ajan sayısından fazla (" << active_ids.size() << ")\n";
                return 1;
            }
            std::stringstream command;
            command << active_ids[i] << ";HUNKER_DOWN";
            std::cout << command.str() << "\n";
            std::cerr << "Bilgi: Çıktıya yazılan komut: " << command.str() << "\n";
            std::cout.flush();
        }

        std::cout.flush();
        std::cerr << "Bilgi: Tur tamamlandı, stdout temizlendi\n";
    }

    std::cerr << "Bilgi: Oyun döngüsü sonlandırıldı\n";
    return 0;
}