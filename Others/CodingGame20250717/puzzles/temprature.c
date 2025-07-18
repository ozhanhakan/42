/*  	The Goal
In this exercise, you have to analyze records of temperature to find the closest to zero.

	
Sample temperatures
Here, -1 is the closest to 0.
 	Rules
Write a program that prints the temperature closest to 0 among input data. If two numbers are equally close to zero, positive integer has to be considered closest to zero (for instance, if the temperatures are -5 and 5, then display 5).
 	Game Input
Your program must read the data from the standard input and write the result on the standard output.
Input
Line 1: N, the number of temperatures to analyze

Line 2: A string with the N temperatures expressed as integers ranging from -273 to 5526

Output
Display 0 (zero) if no temperatures are provided. Otherwise, display the temperature closest to 0.
Constraints
0 ≤ N < 10000
Example
Input
5
1 -2 -8 4 5
Output
1 */

/*
Çözümün Mantığı
Sıcaklık Sayısını Oku (N): Program ilk olarak analiz edilecek sıcaklık sayısı olan N değerini okur.
Özel Durum (N=0): Eğer N sıfır ise, yani analiz edilecek hiç sıcaklık yoksa, kural gereği ekrana 0 yazdırılır ve program sonlanır.
En Yakın Sıcaklığı Başlat: Sıfıra en yakın sıcaklığı saklamak için closest_temp adında bir değişken oluşturulur. Bu değişkene başlangıçta, olası sıcaklık aralığının dışında bir değer (örneğin 5527) atanır. Bu, okunan ilk sıcaklığın her zaman sıfıra daha yakın olmasını garantiler.
Sıcaklıkları Döngüde Oku: Bir for döngüsü kurularak N adet sıcaklık tek tek okunur.
Karşılaştırma ve Güncelleme: Döngünün her adımında, okunan yeni sıcaklık (t) ile o ana kadar bulunmuş olan en yakın sıcaklık (closest_temp) karşılaştırılır:
Mutlak Değer Kontrolü: t'nin mutlak değeri, closest_temp'in mutlak değerinden küçükse, t sıfıra daha yakındır. Bu durumda closest_temp yeni t değeri ile güncellenir.
Eşitlik Durumu: Eğer mutlak değerler eşitse (örneğin -5 ve 5), kurala göre pozitif olan değer (5) seçilmelidir. Bu yüzden, t'nin closest_temp'ten büyük olup olmadığı kontrol edilir ve eğer büyükse closest_temp güncellenir.
Sonucu Yazdır: Döngü bittiğinde, closest_temp değişkeni sıfıra en yakın olan sıcaklığı tutuyor olacaktır. Bu değer ekrana yazdırılır.
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h> // INT_MAX kullanmak için

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    // Analiz edilecek sıcaklık sayısı
    int n;
    scanf("%d", &n);

    // Eğer hiç sıcaklık yoksa (n=0), 0 yazdır ve çık.
    if (n == 0) {
        printf("0\n");
        return 0;
    }

    // Sıfıra en yakın sıcaklığı saklamak için bir değişken oluştur.
    // Başlangıç değeri olarak mümkün olan en yüksek sıcaklıktan daha büyük bir değer ata.
    int closest_temp = 5527; 

    // n adet sıcaklığı okumak için döngü
    for (int i = 0; i < n; i++) {
        // -273 ile 5526 arasında bir tamsayı olan sıcaklık değeri
        int t;
        scanf("%d", &t);

        // Mevcut sıcaklığın mutlak değerini al
        int abs_t = abs(t);
        // Şu ana kadar bulunan en yakın sıcaklığın mutlak değerini al
        int abs_closest = abs(closest_temp);

        // Eğer mevcut sıcaklık sıfıra daha yakınsa, en yakın olarak onu ata.
        if (abs_t < abs_closest) {
            closest_temp = t;
        } 
        // Eğer sıfıra eşit uzaklıktalarsa, pozitif olanı seç.
        // (t > closest_temp kontrolü, t pozitif ve closest_temp negatif ise doğru sonuç verir)
        else if (abs_t == abs_closest) {
            if (t > closest_temp) {
                closest_temp = t;
            }
        }
    }

    // Cevabı yazdır.
    printf("%d\n", closest_temp);

    return 0;
}