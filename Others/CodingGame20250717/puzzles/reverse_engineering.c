#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Reverse Engineering Challenge - En Başarılı Çözüm (XNOR + Modulo)
 * Bu kod, 314 proje puanı getiren son ve en etkili hipotezdir.
 * Temel mantık, bir çıkışın kendisine bağlı AKTİF sinyal sayısının
 * ÇİFT olup olmadığını kontrol eden XNOR (Eşitlik) kapısıdır.
 * Sonuç, 'F' gibi geçersiz çıktılar vermemek için Modulo 5 ile
 * geçerli A-E aralığına çekilir.
 */
int main()
{
    // --- Başlangıç Girdileri ---
    // Oyunun başında bir kereliğine mahsus verilen 3 tamsayıyı okuyoruz.
    int num_signals; // Toplam sinyal sayısı (hipotez)
    scanf("%d", &num_signals);
    int num_outputs; // Toplam çıkış sayısı (hipotez)
    scanf("%d", &num_outputs);
    int num_wires; // Her turda okunacak kablo bağlantısı sayısı (hipotez)
    scanf("%d", &num_wires);
    fgetc(stdin); // Tamsayılardan sonra kalan satır sonu karakterini temizle.

    // --- Hafıza Ayırma ---
    // Gerekli diziler için hafızada yer ayırıyoruz.
    bool *signals = malloc(num_signals * sizeof(bool)); // Sinyallerin durumunu tutar (aktif/pasif)
    bool *outputs = malloc(num_outputs * sizeof(bool)); // Çıkışların durumunu tutar (aktif/pasif)
    
    // XNOR mantığı için sadece aktif girişleri saymamız yeterli.
    // Bu dizi, her bir çıkışa kaç tane AKTİF sinyalin bağlandığını sayacak.
    int *active_inputs_per_output = malloc(num_outputs * sizeof(int));

    // --- Oyun Döngüsü ---
    // Bu döngü, oyun bitene kadar her turda bir kez çalışır.
    while (1) {
        // --- Tur Başı Hazırlık ---
        // Her turun başında sinyal durumlarını sıfırlıyoruz.
        for (int i = 0; i < num_signals; i++) {
            signals[i] = false;
        }

        // Turun sinyal girişlerini (4 karakter) okuyoruz.
        char in_char;
        for (int i = 0; i < 4; i++) {
            scanf(" %c\n", &in_char);
            if (i < num_signals) {
                // '#' karakteri sinyalin AKTİF (true), '_' ise PASİF (false) olduğunu gösterir.
                signals[i] = (in_char == '#');
            }
        }
        
        // Her turun başında sayaçlarımızı ve çıkışlarımızı sıfırlıyoruz.
        for (int i = 0; i < num_outputs; i++) {
            outputs[i] = false;
            active_inputs_per_output[i] = 0;
        }

        // --- Veri Toplama: Kabloları Oku ve Say ---
        // Bu tur için tüm kablo bağlantılarını okuyoruz.
        for (int i = 0; i < num_wires; i++) {
            int s_idx, o_idx;
            scanf("%d %d", &s_idx, &o_idx);

            // Geçerli bir bağlantı ise...
            if (s_idx >= 0 && s_idx < num_signals && o_idx >= 0 && o_idx < num_outputs) {
                // Eğer bu kablonun bağlı olduğu sinyal AKTİF ise...
                if (signals[s_idx]) {
                    // ...ilgili çıkışın "aktif giriş sayacını" bir artır.
                    active_inputs_per_output[o_idx]++;
                }
            }
        }
        fgetc(stdin); // Kablo listesinden sonraki satır sonu karakterini temizle.

        // --- Karar Verme: Hipotezleri Uygula ---
        int active_outputs = 0;
        for (int i = 0; i < num_outputs; i++) {
            // 1. ADIM: XNOR MANTIĞI (Yüksek Puanlı Testleri Çözen Kısım)
            // Bir çıkışa bağlı aktif sinyal sayısının ÇİFT olup olmadığını kontrol et.
            // (0, 2, 4, 6... birer çift sayıdır)
            if (active_inputs_per_output[i] % 2 == 0) {
                // Eğer sayı çift ise, çıkışı AKTİF (true) yap.
                outputs[i] = true;
            } else {
                // Eğer sayı tek ise, çıkışı PASİF (false) yap.
                outputs[i] = false;
            }
            
            // Toplam aktif çıkış sayısını say.
            if (outputs[i]) {
                active_outputs++;
            }
        }

        // 2. ADIM: MODULO 5 MANTIĞI (Puanı Fırlatan Kısım)
        // `active_outputs` sayısı 5, 6 veya daha fazla olabilir. Bu da 'F' gibi geçersiz
        // bir eyleme yol açar. Bunu engellemek için sonucun 5'e bölümünden kalanı alırız.
        // Sonuç her zaman 0, 1, 2, 3, veya 4 olur.
        // Örnek: 5 % 5 = 0 ('A'), 6 % 5 = 1 ('B')
        int final_action_index = active_outputs % 5;
        
        // Sonucu 'A' karakterine ekleyerek doğru eylemi bul (A, B, C, D, E).
        char action = 'A' + final_action_index;
        
        // Sonucu yazdır.
        printf("%c\n", action);
    }

    // Program bittiğinde ayrılan hafızayı sisteme geri ver.
    free(signals);
    free(outputs);
    free(active_inputs_per_output);
    return 0;
}

/** final score : 10, proje puanı 216, en yüksek skor.
 * Reverse Engineering Challenge - Hypothesis 12 (NAND with Modulo)
 * Based on user insight. The core logic (NAND) might be correct, but the
 * final count wraps around. Using modulo 5 to map the result to the
 * 5 valid actions (A-E).
 */
/* int main()
{
    int num_signals;
    scanf("%d", &num_signals);

    int num_outputs;
    scanf("%d", &num_outputs);

    int num_wires;
    scanf("%d", &num_wires);
    fgetc(stdin);

    bool *signals = malloc(num_signals * sizeof(bool));
    bool *outputs = malloc(num_outputs * sizeof(bool));
    
    int *total_inputs_per_output = malloc(num_outputs * sizeof(int));
    int *active_inputs_per_output = malloc(num_outputs * sizeof(int));

    // Game loop
    while (1) {
        for (int i = 0; i < num_signals; i++) {
            signals[i] = false;
        }

        char in_char;
        for (int i = 0; i < 4; i++) {
            scanf(" %c\n", &in_char);
            if (i < num_signals) {
                signals[i] = (in_char == '#');
            }
        }
        
        for (int i = 0; i < num_outputs; i++) {
            outputs[i] = false;
            total_inputs_per_output[i] = 0;
            active_inputs_per_output[i] = 0;
        }

        for (int i = 0; i < num_wires; i++) {
            int s_idx, o_idx;
            scanf("%d %d", &s_idx, &o_idx);

            if (s_idx >= 0 && s_idx < num_signals && o_idx >= 0 && o_idx < num_outputs) {
                total_inputs_per_output[o_idx]++;
                if (signals[s_idx]) {
                    active_inputs_per_output[o_idx]++;
                }
            }
        }
        fgetc(stdin);

        int active_outputs = 0;
        for (int i = 0; i < num_outputs; i++) {
            // Using corrected NAND logic as the base
            if (total_inputs_per_output[i] > 0) {
                if (total_inputs_per_output[i] == active_inputs_per_output[i]) {
                    outputs[i] = false;
                } else {
                    outputs[i] = true;
                }
            }
            
            if (outputs[i]) {
                active_outputs++;
            }
        }

        // Apply the modulo logic as suggested
        // There are 5 valid actions (A,B,C,D,E), so we use modulo 5.
        int final_action_index = active_outputs % 5;
        
        char action = 'A' + final_action_index;
        
        printf("%c\n", action);
    }

    free(signals);
    free(outputs);
    free(total_inputs_per_output);
    free(active_inputs_per_output);
    return 0;
} */