/*
 	The Goal
The goal for your program is to safely land the "Mars Lander" shuttle, the landing ship which contains the Opportunity rover. Mars Lander is guided by a program, and right now the failure rate for landing on the NASA simulator is unacceptable.

This puzzle is the second level of the "Mars Lander" trilogy. The controls are the same as the previous level but you must now control the angle in order to succeed.
 	Rules
Built as a game, the simulator puts Mars Lander on a limited zone of Mars sky.

	The zone is 7000m wide and 3000m high.

There is a unique area of flat ground on the surface of Mars, which is at least 1000 meters wide.
Every second, depending on the current flight parameters (location, speed, fuel ...), the program must provide the new desired tilt angle and thrust power of Mars Lander:
	Angle goes from -90° to 90° . Thrust power goes from 0 to 4 .
 
The game simulates a free fall without atmosphere. Gravity on Mars is 3.711 m/s² . For a thrust power of X, a push force equivalent to X m/s² is generated and X liters of fuel are consumed. As such, a thrust power of 4 in an almost vertical position is needed to compensate for the gravity on Mars.

For a landing to be successful, the ship must:
land on flat ground
land in a vertical position (tilt angle = 0°)
vertical speed must be limited ( ≤ 40m/s in absolute value)
horizontal speed must be limited ( ≤ 20m/s in absolute value)
 	Note
Tests and validators are only slightly different. A program that passes a given test will pass the corresponding validator without any problem.
 	Game Input
The program must first read the initialization data from standard input. Then, within an infinite loop, the program must read the data from the standard input related to Mars Lander's current state and provide to the standard output the instructions to move Mars Lander.
Initialization input
Line 1: the number surfaceN of points used to draw the surface of Mars.
Next surfaceN lines: a couple of integers landX landY providing the coordinates of a ground point. By linking all the points together in a sequential fashion, you form the surface of Mars which is composed of several segments. For the first point, landX = 0 and for the last point, landX = 6999
Input for one game turn
A single line with 7 integers: X Y hSpeed vSpeed fuel rotate power
X,Y are the coordinates of Mars Lander (in meters).
hSpeed and vSpeed are the horizontal and vertical speed of Mars Lander (in m/s). These can be negative depending on the direction of Mars Lander.
fuel is the remaining quantity of fuel in liters. When there is no more fuel, the power of thrusters falls to zero.
rotate is the angle of rotation of Mars Lander expressed in degrees.
power is the thrust power of the landing ship.
Output for one game turn
A single line with 2 integers: rotate power :
rotate is the desired rotation angle for Mars Lander. Please note that for each turn the actual value of the angle is limited to the value of the previous turn +/- 15°.
power is the desired thrust power. 0 = off. 4 = maximum power. Please note that for each turn the value of the actual power is limited to the value of the previous turn +/- 1.
Constraints
2 ≤ surfaceN < 30
0 ≤ X < 7000
0 ≤ Y < 3000
-500 < hSpeed, vSpeed < 500
0 ≤ fuel ≤ 2000
-90 ≤ rotate ≤ 90
0 ≤ power ≤ 4
Response time per turn ≤ 100ms
Example
Initialization input
6         	(surfaceN) Surface made of 6 points
0 1500      	(landX landY)
1000 2000	(landX landY)
2000 500	(landX landY) Start of flat ground
3500 500	(landX landY) End of flat ground
5000 1500	(landX landY)
6999 1000	(landX landY)
No output expected
You can ignore this but you need to read the values.
Input for turn 1
5000 2500 -50 0 1000 90 0	(X Y hSpeed vSpeed fuel rotate power)
Output for turn 1
-45 4 (rotate power)
Requested rotation to the right, maximum thrust power
Input for turn 2
4950 2498 -51 -3 999 75 1	(X Y hSpeed vSpeed fuel rotate power)
Tilt angle changed only by 15° and thrust power only by 1
Output for turn 2
-45 4 (rotate power)
Same request as previous turn
Input for turn 3
4898 2493 -53 -6 997 60 2	(X Y hSpeed vSpeed fuel rotate power)
Output for turn 3
-45 4 (rotate power)
Same request as previous turn
Synopsis
Same place, the next day. You have joined Jeff and Mike in the crisis meeting room of the Kennedy Space Center.
 
“OK, I see you got the general idea. Mike, what do you think of our new recruit so far? ”
“There's still a long way to go... ”
“Oh c'mon Mike, you're always so skeptical! ”
 
Jeff turns and glares at you with his steel-blue eyes.

“ But he IS right! This first test was just a warm-up. Now you'll need to deal with more challenging situations. You see, we must be prepared to face anything, the success of the mission depends upon it! ”
*/

/*
Harika, Mars Lander'ın ikinci seviyesine geçiyoruz. Bu seviyede işler biraz daha karmaşıklaşıyor çünkü artık sadece dikey hızı değil, aynı zamanda yatay konumu ve hızı da kontrol etmemiz gerekiyor. Bunun için geminin dönüş açısını (rotate) akıllıca kullanmalıyız.

Çözümün Mantığı
Bu seviyedeki temel amaç, aracı önce yatay olarak güvenli iniş bölgesinin üzerine getirmek, ardından dikey olarak hızını kontrol ederek güvenli bir şekilde indirmektir.

İniş Alanını Bulma (Initialization):

Program başladığında, Mars yüzeyini oluşturan tüm noktaların koordinatlarını okuruz.
Bu noktaları tarayarak Y koordinatları aynı olan iki ardışık nokta buluruz. Bu iki nokta, iniş için uygun olan düz alanı belirtir.
Bu düz alanın başlangıç (landing_x1), bitiş (landing_x2) ve yükseklik (landing_y) değerlerini bir kenara not ederiz.
Hedef Belirleme (Game Loop):

Her turda, aracın o anki durumunu (X, Y, hSpeed, vSpeed vb.) okuruz.
Ana hedefimiz, aracın X koordinatını, iniş alanının tam ortasına getirmektir. Bu hedef noktayı target_x = (landing_x1 + landing_x2) / 2 olarak hesaplarız.
Kontrol Stratejisi (PID Benzeri Yaklaşım):

Bu tür kontrol problemlerini çözmek için genellikle PID (Proportional-Integral-Derivative) kontrolörler kullanılır. Biz burada daha basitleştirilmiş bir PD (Proportional-Derivative) mantığı kullanacağız.
Hedef Açı (target_angle): Geminin ne kadar eğileceğini belirler. Bu, iki şeye bağlıdır:
Konum Hatası (Proportional): Araç, hedef X noktasından ne kadar uzakta? Uzaksa, hedefe doğru daha çok eğilmesi gerekir. Bu, (target_x - X) ile orantılıdır.
Hız Hatası (Derivative): Aracın yatay hızı ne kadar? Hızı çok yüksekse, yavaşlamak için ters yöne eğilmesi gerekir. Bu da (target_hSpeed - hSpeed) ile orantılıdır. Yatay hız için hedefimiz 0'dır, ancak hedefe ulaşmak için geçici olarak hızlanmamız gerekebilir. Basit bir yaklaşımla, yatay hızı da hesaba katarak frenleme yaparız.
Hedef Güç (target_power): Geminin itki gücünü belirler. Bu da dikey hıza bağlıdır:
Eğer dikey hız (vSpeed) çok fazlaysa (örn: -39'dan küçükse), düşüşü yavaşlatmak için itkiyi 4'e çıkarırız.
Eğer dikey hız kontrol altındaysa, itkiyi 3'te tutarak yakıt tasarrufu yapar ve kontrollü bir alçalma sağlarız.
Kodu Uygulama:

Başlangıçta yüzey verileri okunur ve düz iniş alanı bulunur.
Oyun döngüsü içinde:
Hedef X konumu ile mevcut X konumu ve yatay hız arasındaki farka göre bir target_angle hesaplanır. Bu hesaplamada katsayılar (P_gain, D_gain) kullanılarak geminin tepkileri ayarlanır.
Hesaplanan açı, geminin fiziksel limitleri olan -90 ve +90 derece arasında sınırlandırılır.
Dikey hıza bakılarak target_power (3 veya 4) belirlenir.
Son olarak, hesaplanan target_angle ve target_power ekrana yazdırılır.
Bu strateji, geminin önce hedefe doğru yatay olarak süzülmesini, hedefe yaklaştıkça yavaşlayıp pozisyon almasını ve son olarak dikey hızını kontrol ederek yumuşak bir iniş yapmasını sağlar.
*/

/*
düzeltme

İniş Alanını Bulma: Bu kısım aynı kalıyor. Program başlangıçta düz iniş alanını tespit eder.

Kontrol Stratejisi (Daha İyi Ayarlanmış PD Kontrolör):

Hedef Açı (target_angle): Geminin ne kadar eğileceğini belirleyen mantığı iyileştiriyoruz.
Konum Hatası (P): (hedef_X - mevcut_X) farkına göre orantısal bir tepki verilir.
Hız Hatası (D): (hedef_hız - mevcut_hız) farkına göre sönümleyici bir tepki verilir. Bu, geminin hedefe yaklaşırken aşırı hızlanmasını veya hedefi geçmesini engeller.
Yeni Katsayılar: p_gain ve d_gain katsayılarını çok daha hassas ve düşük değerlere çektim. Bu, geminin daha yumuşak ve orantılı manevralar yapmasını sağlar.
Radyan/Derece Hatası Düzeltildi: Artık gereksiz dönüşümler yok. Kontrolcü doğrudan hedef açıyı (derece cinsinden) hesaplıyor.
Hedef Güç (target_power): Bu mantık büyük ölçüde aynı kalıyor, ancak küçük bir ekleme yapılıyor:
Dikey hız (vSpeed) çok yüksekse (< -39), gücü 4'e çıkararak fren yaparız.
Yeni Kural: Eğer gemi çok dik bir açıyla eğilmişse (> 20 derece), dikey itki azalır ve gemi irtifa kaybeder. Bu irtifa kaybını telafi etmek ve düşüşü yavaşlatmak için, dik açılarda bile gücü 4'e çıkarırız.
Diğer tüm durumlarda, kontrollü alçalma için güç 3 olarak ayarlanır.
Son Aşama İniş Mantığı:

Gemi iniş alanının tam üzerine geldiğinde ve hem yatay hem de dikey hızı güvenli limitler içindeyse, tüm odağı dikey inişe veririz:
Dönüş açısı 0'a ayarlanır.
Dikey hıza göre güç 3 veya 4 olarak ayarlanarak yumuşak bir iniş hedeflenir.
Bu güncellenmiş mantık, geminin daha stabil, daha az agresif ve daha öngörülebilir hareket etmesini sağlayarak güvenli bir şekilde iniş yapmasına olanak tanır.
*/

