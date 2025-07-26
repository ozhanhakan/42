### **Bot Stratejisi v4.10 - C++'a Geçiş Kılavuzu**

**Hazırlayan:** Copilot
**Kullanıcı:** @ozhanhakan
**Tarih:** 2025-07-25

Merhaba Hakan,

Bu belge, üzerinde çalıştığımız son bot kodunun (v4.10) arkasındaki mantığı ve C++ kavramlarını, C geçmişi olan bir yazılımcının anlayacağı şekilde açıklamak için hazırlandı. Amacımız, kodun sadece ne yaptığını değil, neden o şekilde yapıldığını da anlamanı sağlamak.

---

### **1. Genel Bakış: Botumuzun Beyni Nasıl Çalışıyor?**

Botumuzun karar verme mekanizması, karmaşık bir satranç oyuncusu gibi düşünülebilir. Her tur, "Şu an yapabileceğim en akıllı hamle nedir?" diye sorar. v4.10 versiyonu, iki ana düşünce yapısına sahip:

1.  **Öncelikli Fırsatçılık (Refleks):** Bot, herhangi bir derin hesaplamaya girmeden önce, gözünün önündeki en bariz ve karlı fırsatı arar. Bu, bizim için "dost ateşi riski olmadan birden fazla düşmanı vurabilecek bir bomba atışı" anlamına gelir. Eğer böyle bir fırsat varsa, bot hiç düşünmeden bu "refleks" hamlesini yapar. Bu, oyunun seyrini anında değiştirebilecek kritik anları kaçırmamamızı sağlar.

2.  **Dengeli Strateji (Planlama):** Eğer bariz bir bomba fırsatı yoksa, bot daha derin bir analiz moduna geçer. Olası her hareketini ve o hareketin sonucunda yapabileceği atışları bir puanlama sisteminden geçirir. Bu sistem üç temel şeyi dengeler:
    *   **Saldırganlık:** Birincil hedefe ne kadar etkili bir şekilde saldırabilirim?
    *   **Pozisyon Alma:** Hedefe yaklaşırken aynı zamanda kendimi nasıl güvende tutabilirim?
    *   **Takım Oyunu:** Diğer ajanlarımın yolunu tıkıyor muyum? Onlardan güvenli bir mesafede miyim?

Bu iki mod, botumuzu hem anlık fırsatları kaçırmayan bir avcı hem de uzun vadeli planlar yapan bir stratejist yapar.

---

### **2. Kodun Detaylı Analizi**

Şimdi kodun bölümlerini tek tek inceleyelim.

#### **Bölüm A: Kurulum ve Veri Yapıları**

Bu bölüm, programımızın temel taşlarını ve kullanacağı veri "kaplarını" tanımlar.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <utility>

// --- Sabitler ve Veri Yapıları ---
const std::string BOT_VERSION = "v4.10_Preemptive_Bombing";
const int SPLASH_BOMB_RANGE = 4;
const int SPLASH_DAMAGE_RADIUS = 1;

/*
 * Agent (Ajan) Yapısı:
 * C'deki struct'lara çok benzer. Bir ajanın sahip olduğu tüm bilgileri
 * (ID, konumu, canı, vb.) bir arada tutan bir veri paketidir.
 * C++'da struct'lar, içlerine fonksiyonlar da alabilirler ama biz burada
 * sadece veri saklamak için kullanıyoruz.
 */
struct Agent {
    int id, player, x, y, cooldown, optimal_range, soaking_power, splash_bombs, wetness;
    int initial_cooldown;
    bool is_mine;
    bool exists = true;
};

/*
 * Action (Aksiyon) Yapısı:
 * Bir ajanın bir turda yapabileceği hareket ve savaş komutlarını
 * bir arada saklamak için kullanılır. Başlangıçta boş string'ler içerir.
 */
struct Action {
    std::string move_action = "";
    std::string combat_action = "";
};

// ... (Diğer yapılar ve global değişkenler)
```

**C'den C++'a Geçiş Notları:**
*   `#include <iostream>`: C'deki `stdio.h`'ın C++'taki karşılığıdır. `std::cout` (ekrana yazdırma) ve `std::cin` (ekrandan okuma) için gereklidir.
*   `std::string`: C'deki `char*` veya `char[]` dizilerinin çok daha güçlü ve güvenli halidir. Bellek yönetimini kendi yapar, boyutunu bilir ve `+` operatörü ile kolayca birleştirilebilir.
*   `const`: C'deki `const` ile aynıdır, bir değişkenin değerinin program boyunca değiştirilemeyeceğini belirtir.

---

#### **Bölüm B: Stratejinin Kalbi - `decide_agent_action` Fonksiyonu**

Bu fonksiyon, bir ajanın o tur ne yapacağına karar veren ana beyindir.

```cpp
Action decide_agent_action(int agent_id, int primary_target_id) {
    // 1. Gerekli verileri al
    const auto& agent = agents.at(agent_id);

    // 2. ÖNCELİKLİ BOMBA KONTROLÜ (Refleks Modu)
    // Bu blok, diğer her şeyden önce çalışır.
    // "Durduğum yerden karlı bir bomba atışı yapabilir miyim?" diye sorar.
    if (agent.cooldown == 0 && agent.splash_bombs > 0) {
        // ... bomba atılacak en iyi konumu arayan döngüler ...
        
        // Eğer iyi bir fırsat bulunduysa:
        if (best_splash_pos.first != -1) {
            Action immediate_action; // Hemen yeni bir aksiyon oluştur.
            immediate_action.combat_action = "THROW ..."; // Bomba komutunu ata.
            return immediate_action; // Diğer hesaplamaları atla ve direkt bu aksiyonu döndür.
        }
    }

    // 3. HİBRİT STRATEJİ (Planlama Modu)
    // Eğer anlık bomba fırsatı yoksa, bu bölüm çalışır.
    EvaluatedAction best_action_combo; // Olası en iyi (puan, aksiyon) ikilisini saklar.

    // Ajanın gidebileceği her olası konumu (5x5 alan) bir döngü ile gez.
    for (int y_offset = -2; y_offset <= 2; ++y_offset) {
        for (int x_offset = -2; x_offset <= 2; ++x_offset) {
            int nx = agent.x + x_offset; // Yeni X konumu
            int ny = agent.y + y_offset; // Yeni Y konumu
            
            // ... Bu (nx, ny) pozisyonu için puanlama yapılır ...
            
            // a. Pozisyon Puanı: Dosta yakın mı? Hedefe yakın mı?
            int positional_score = 0;
            // Dosta yakınsa AĞIR CEZA ver.
            positional_score -= 200; 
            // Hedefe yaklaştırıyorsa ÖDÜL ver.
            positional_score += 20;

            // b. Savaş Puanı: Bu pozisyondan ateş edebilir miyim?
            int combat_score = 0;
            // Eğer ateş edilebiliyorsa, YÜKSEK ÖDÜL ver.
            combat_score += 130;
            
            // c. Toplam Puan = Pozisyon Puanı + Savaş Puanı
            int total_score = positional_score + combat_score;

            // Eğer bu hamlenin toplam puanı, şimdiye kadar bulduğumuz en iyi puandan yüksekse:
            if (total_score > best_action_combo.score) {
                // Bu hamleyi "en iyi hamle" olarak güncelle.
                best_action_combo.score = total_score;
                best_action_combo.action = current_action;
            }
        }
    }
    
    // 4. En iyi bulunan aksiyonu geri döndür.
    return best_action_combo.action;
}
```

**C'den C++'a Geçiş Notları:**
*   `for (auto const& ...)`: Bu, "Range-based for loop" olarak bilinen çok kullanışlı bir C++ özelliğidir. `agents` gibi bir koleksiyonun (örneğin `std::map` veya `std::vector`) her bir elemanını tek tek gezmeyi sağlar. C'deki `for (int i=0; i<size; ++i)` döngüsünün daha okunaklı ve güvenli halidir.
    *   `auto`: Değişkenin türünü derleyicinin otomatik olarak belirlemesini sağlar. `other_id`'nin `int`, `other_agent`'ın `Agent` olduğunu kendi anlar.
    *   `const&`: "const reference" (sabit referans) demektir. Elemanı kopyalamak yerine, onun orijinaline bir "takma ad" ile erişir. Bu, özellikle büyük yapılar (`struct`) için performansı artırır. `const` olması, bu takma ad üzerinden orijinal veriyi değiştiremeyeceğimizi garanti eder.
*   **Nesne Yönelimli Düşünce (Giriş):** Fonksiyonun farklı mantık bloklarına ("Refleks", "Planlama") ayrılması, nesne yönelimli programlamadaki "Single Responsibility Principle" (Tek Sorumluluk Prensibi) fikrine bir giriştir. Her kod parçasının net ve tek bir görevi olmalıdır.

---

### **3. Ana Döngü - `main()` Fonksiyonu**

Bu, programımızın başlangıç noktasıdır ve oyunun sonsuz döngüsünü yönetir.

```cpp
int main() {
    // 1. Başlangıç Ayarları
    // Oyunun başında bir kerelik okunacak veriler (ajan bilgileri, harita boyutu vb.)
    
    // 2. Sonsuz Oyun Döngüsü
    while (true) {
        // a. Tur Verilerini Oku
        // Her turun başında değişen verileri (ajanların yeni konumları, canları vb.) oku.
        
        // b. Birincil Hedefi Seç
        // O turda odaklanılacak en mantıklı düşmanı seçen fonksiyonu çağır.
        int primary_target_id = find_primary_target();
        
        // c. Her Ajan İçin Karar Ver
        // Kendi ajanlarımızın her biri için bir döngü başlat.
        for (auto const& [id, agent] : agents) {
            if (agent.is_mine && agent.exists) {
                // Her bir ajan için ana beyin fonksiyonunu çağır.
                Action final_action = decide_agent_action(id, primary_target_id);
                
                // d. Komutu Oluştur ve Gönder
                // Fonksiyondan dönen aksiyonları birleştirerek oyun motorunun anlayacağı
                // "ID;MOVE X Y;SHOOT ID" formatında bir komut oluştur.
                std::string command = ...;
                
                // Oluşturulan komutu ekrana yazdır (oyun motoruna gönder).
                std::cout << command << std::endl;
            }
        }
    }
    return 0;
}
```

Umarım bu detaylı açıklama, kodun arkasındaki mantığı ve C++'ın getirdiği yenilikleri anlamanda yardımcı olmuştur. Bu bilgileri sindirdikten sonra kodu çalıştırdığında, ajanlarının neden o belirli hareketleri yaptığını çok daha net bir şekilde görebileceksin. Başka sorun olursa çekinme!