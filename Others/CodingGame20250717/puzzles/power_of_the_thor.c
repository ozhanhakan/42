/*
	The Goal
Your program must allow Thor to reach the light of power.
 	Rules
Thor moves on a map which is 40 wide by 18 high. Note that the coordinates (X and Y) start at the top left! This means the most top left cell has the coordinates "X=0,Y=0" and the most bottom right one has the coordinates "X=39,Y=17".

Once the program starts you are given:
the variable lightX: the X position of the light of power that Thor must reach.
the variable lightY: the Y position of the light of power that Thor must reach.
the variable initialTX: the starting X position of Thor.
the variable initialTY: the starting Y position of Thor.
At the end of the game turn, you must output the direction in which you want Thor to go among:
	
N (North)
NE (North-East)
E (East)
SE (South-East)
S (South)
SW (South-West)
W (West)
NW (North-West)
Each movement makes Thor move by 1 cell in the chosen direction.
 
 
Victory Conditions
You win when Thor reaches the light of power
 
Lose Conditions
Thor moves outside the map

Initial phase
Thor starts on the map at position (3, 6). The light is at position (3, 8).

Round 1
Action S: Thor moves towards south.
New position is (3, 7).

Round 2
Action S: Thor moves towards south.
New position is (3, 8).
 	Note
Do not forget to execute the tests from the "Test cases" panel.
Beware: the tests given and the validators used to compute the score are slightly different in order to avoid hard coded solutions.
 	Game Input
The program must first read the initialization data from the standard input, then, in an infinite loop, provides on the standard output the instructions to move Thor.
Initialization input
Line 1: 4 integers lightX lightY initialTX initialTY. (lightX, lightY) indicates the position of the light. (initialTX, initialTY) indicates the initial position of Thor.
Input for a game round
Line 1: the number of remaining moves for Thor to reach the light of power: remainingTurns. You can ignore this data but you must read it.
Output for a game round
A single line providing the move to be made: N NE E SE S SW W ou NW
Constraints
0 ≤ lightX < 40
0 ≤ lightY < 18
0 ≤ initialTX < 40
0 ≤ initialTY < 18
Response time for a game round ≤ 100ms
Synopsis
The final battle of Ragnarök, the twilight of the gods is approaching. You incarnate Thor who is participating in this final battle against all the forces of evil, led by Loki, Thor's wizard brother.

Thor was wounded during a previous battle against Fenrir, the wolf-god. During the battle, Loki took advantage of the general confusion and used his magic to annihilate the magical powers of Thor’s hammer, Mjöllnir, by separating it from his soul: the light of power.

Thor, who now feels very weak, must find and reach the light of power, as fast as possible, since it is the only thing which can restore his and Mjollnir's powers.
*/
/*
Çözümün Mantığı
Başlangıç Değerlerini Oku: Program ilk olarak ışığın konumu (light_x, light_y) ve Thor'un başlangıç konumu (initial_tx, initial_ty) olmak üzere dört adet tam sayıyı okur.
Konum Takibi: Thor'un mevcut konumunu takip etmek için initial_tx ve initial_ty değerlerini thor_x ve thor_y adında yeni değişkenlere atarız. Bu değişkenler her turda güncellenecektir.
Sonsuz Döngü: Oyun, Thor ışığa ulaşana kadar devam ettiği için bir while(1) döngüsü kullanılır.
Yön Belirleme: Her turda, Thor'un ışığa göre nerede olduğunu kontrol ederiz:
Dikey Eksen (Y): Eğer Thor'un Y konumu (thor_y), ışığın Y konumundan (light_y) büyükse, Thor'un kuzeye (N) gitmesi gerekir. Küçükse, güneye (S) gitmesi gerekir. Eşitse, dikey hareket etmesine gerek yoktur.
Yatay Eksen (X): Benzer şekilde, Thor'un X konumu (thor_x), ışığın X konumundan (light_x) büyükse, batıya (W) gitmesi gerekir. Küçükse, doğuya (E) gitmesi gerekir. Eşitse, yatay hareket etmesine gerek yoktur.
Hareketi Birleştirme: Dikey ve yatay yönler birleştirilerek nihai hareket komutu oluşturulur (örneğin, "N" ve "W" birleşerek "NW" olur).
Konumu Güncelleme: Thor'un hareket komutuna göre thor_x ve thor_y değişkenleri güncellenir. Bu, bir sonraki turda doğru karar verilmesini sağlar.
Komutu Yazdırma: Oluşturulan hareket komutu ekrana yazdırılır.
Bu strateji, Thor'un her adımda ışığa olan mesafeyi en verimli şekilde azaltmasını ve en kısa yoldan hedefe ulaşmasını sağlar.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/

int main()
{
    // Işığın X konumu
    int light_x;
    // Işığın Y konumu
    int light_y;
    // Thor'un başlangıçtaki X konumu
    int initial_tx;
    // Thor'un başlangıçtaki Y konumu
    int initial_ty;
    // Başlangıç değerlerini standart girdiden oku
    scanf("%d%d%d%d", &light_x, &light_y, &initial_tx, &initial_ty);

    // Thor'un mevcut konumunu takip etmek için değişkenler oluştur ve başlangıç değerlerini ata
    int thor_x = initial_tx;
    int thor_y = initial_ty;

    // Oyun döngüsü
    while (1) {
        // Kalan tur sayısı. Bu değeri okumak zorundayız ama çözüm için kullanmayacağız.
        int remaining_turns;
        scanf("%d", &remaining_turns);

        // Yönü belirlemek için boş karakter dizileri oluştur.
        // Dikey (Kuzey/Güney) ve yatay (Batı/Doğu) hareketleri ayrı ayrı belirleyeceğiz.
        char move_y[2] = ""; 
        char move_x[2] = "";

        // Dikey (Y ekseni) hareketi belirle
        // Eğer Thor, ışıktan daha güneydeyse (Y değeri büyükse), kuzeye gitmeli.
        if (thor_y > light_y) {
            strcpy(move_y, "N");
            thor_y--; // Thor'un Y konumunu kuzeye hareket ettiği için güncelle.
        }
        // Eğer Thor, ışıktan daha kuzeydeyse (Y değeri küçükse), güneye gitmeli.
        else if (thor_y < light_y) {
            strcpy(move_y, "S");
            thor_y++; // Thor'un Y konumunu güneye hareket ettiği için güncelle.
        }

        // Yatay (X ekseni) hareketi belirle
        // Eğer Thor, ışıktan daha doğudaysa (X değeri büyükse), batıya gitmeli.
        if (thor_x > light_x) {
            strcpy(move_x, "W");
            thor_x--; // Thor'un X konumunu batıya hareket ettiği için güncelle.
        }
        // Eğer Thor, ışıktan daha batıdaysa (X değeri küçükse), doğuya gitmeli.
        else if (thor_x < light_x) {
            strcpy(move_x, "E");
            thor_x++; // Thor'un X konumunu doğuya hareket ettiği için güncelle.
        }

        // Belirlenen dikey ve yatay yönleri birleştirerek ekrana yazdır.
        // Örneğin, move_y "N" ve move_x "E" ise, "NE" yazdırılır.
        // Eğer hareket sadece dikeyse (örn. "S"), move_x boş olacağı için sadece "S" yazdırılır.
        printf("%s%s\n", move_y, move_x);
    }

    return 0;
}