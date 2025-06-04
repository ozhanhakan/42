Libft dokümanını incelerken yaptığım değerlendirmeler.
hozhan:
Merhaba arkadaşlar, Libft Part-1 hakkında bir kuralı yanlış mı anlıyorum emin olamadım. Kural yoruma açık geldi bana, external functions ile sadece orijinal fonksiyonu kullanmayı mı yasaklıyor yoksa libft.h içinde bulunan kendi yazdığımız ft_ fonksiyonları da yasaklıyor mu kural? Yasaklamadığını düşünen çok arkadaş var,  kural gereği yasak konmuş olabilir mi? Kural kılavuzunda bir açıklamaya ihtiyaç olduğunu düşünüyorum. (edited) 
Screenshot_20250603-150752_Samsung Notes.jpg
 
![alt text](image.png)



yuyumaz
  3:34 PM
static olarak kendi fonksiyonlarimizi yazabiliyoruz, ancak izin verilen fonksiyonlar dahilinde. yani ornegin printf kullanimi bu fonksiyonlar icin de yasakli. mesela ft_calloc icin yardimci fonksiyon yazdik diyelim, bu fonksiyonun icerisinde de sadece malloc kullanimina izin var.
ben bu sekilde anladim. (edited) 
:white_tick:
2

3:35
libft.h icindeki fonksiyonlarimizi kullanabiliyoruz
:white_tick:
1

Hakan Özhan
:house_with_garden:  Yesterday at 3:41 PM
Without relying standart functions dememiş. Bu yüzden kendi yazdığımız dahil her dış fonksiyonu yasaklıyor sanırım.
4 replies


Ercan Deniz
:point_up:  Yesterday at 3:53 PM
Naçizane tavsiyemi söyleyeyim. Bu şekilde kullanmanda sorun olmaz. Zaten gidip o kendin yazdığın kodu alıp buraya koyacaksın. Bir şey fark etmeyecek. Buradaki yasak olarak addedilen şeyler kolaya kaçmayı engellemek için. Hazır fonksiyon kullanma demek istiyor. Bu kadar ince eleyip sık dokunmaya gerek yok. Hedeflenen kazanımları öğrenmeye bakın.
:pray:
1
:heavy_plus_symbol:
3



Hamza
  Yesterday at 4:41 PM
relying on, çok güzel kelime seçimi. adamlar senin kaç fonksiyona böldüğünle ilgilenmiyor. başka fonksiyonlara güvenme demiş. hatta sonra bu söylediğine istisna getirmek zorunda kalmış malloc'a izin vermiş . konu tamamen tüm implementasyonu sen mi yazıyorsun başkasına mı güveniyorsun üzerine anlatılıyor.
:pray:
1



Arda Aycan
:speech_bubble:  Yesterday at 5:25 PM
Part 1 de ki fonksiyonlar harici fonksiyon kullanilmadan yazilacak ancak static yardimci fonksiyonlar yazabilirsin. Part 2 de yazdigin fonksiyonlari kullanabilirsin.

Yardımcı Fonksiyon Çağırma Konusu Hakkında
Öncelikle dokümanı daha dikkatli okumamı sağlayan tüm arkadaşlara teşekkür ederim.
ödev kurallarını yanlış anlamaya bağlı değerlendirme yapılmaması için bu kavram konusunu incelemeyi çok önemli buluyorum.
III.1 Technical considerations: [Madde 2]
If you need helper functions to break down a more complex function, define them as static functions to restrict their scope to the appropriate file.
Bu kurala göre bir fonksiyon içinde yardımcı fonksiyon çağırma kuralı o fonksiyonu static olarak nitelemek. mesela benden çok ileride olan ve ft_atoi de boşluk kontrolünü yapan bazı arkadaşlarım, static int ft_is_space şeklinde bu kurala uygun fonksiyon yazdıklarını hatırlattılar.
Kendi yazdığımız fonksiyonlara nerede izin verildiği "III.3 Part 2 - Additional functions " kısmında da belirtiliyor.
III.3 Part 2 - Additional functions
Some of the functions from Part 1 may be useful for implementing the functions below.
  Bu bilgiye göre, sadece bu aşamada Part-1 içinde kendi yazdığımız fonksiyonları yardımcı fonksiyon olarak kullanabiliriz.



III.2 Part 1 - Libc functions 
To begin, you must reimplement a set of functions from the libc. 
Your version will have the same prototypes and behaviors as the originals, 
adhering strictly to their definitions in the man page. The only difference will be their names,
 as they must start with the ’ft_’ prefix. For example, strlen becomes ft_strlen.
Yazacağımız fonksiyonların Orjinaliyle aynı prototip ve davranışa sahip olması istenirken 
manual page kesinlikle bağlı kalınması gere