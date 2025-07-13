# 42 Projeleri - Piscine ve Temel Müfredat

## Genel Bakış
Bu depo, 42 okulu müfredatı kapsamında tamamladığım **Piscine** ve **Temel Müfredat** projelerini içermektedir. 

## Projeler

### 1. Piscine
Piscine, C programlama dilinin temel kavramlarını öğretmek için tasarlanmış yoğun bir programlama kampıdır. C programlama becerilerini geliştirmek için çeşitli alıştırmalar içerir.

#### Öne Çıkan Alıştırmalar
- **C00**: Temel çıktı işlevleri (örneğin, `ft_putchar`, `ft_print_alphabet`).
- **C01**: Değişkenler ve işaretçiler (örneğin, `ft_ft`, `ft_swap`).
- **C02–C08**: Dizi manipülasyonu, bellek yönetimi ve dosya işlemleri.
- **Rush**: Konsolda desen çizimi yapan projeler (Rush 00, Rush 01).

### 2. Temel Müfredat M0: Libft
**Libft**, standart C kütüphanesindeki bazı işlevlerin yeniden yazılmasını ve ek yardımcı işlevlerin geliştirilmesini içeren bir projedir. İlerideki 42 projelerinde kullanılmak üzere temel bir kütüphane olarak tasarlanmıştır.

#### Özellikler
- **Zorunlu Kısım**: `ft_strlen`, `ft_strcpy`, `ft_atoi` gibi işlevlerin yeniden yazılması.
- **Bonus Kısım**: Bağlı liste işlevleri (örneğin, `ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`).
- **Ek İşlevler**: Proje gereksinimlerinin ötesinde eklenen yardımcı işlevler (varsa).

## Kurulum ve Kullanım

### Gereksinimler
- C derleyicisi (örneğin, `gcc`)
- Unix benzeri işletim sistemi (Linux, macOS)
- `make` aracı

### Libft Derleme
1. Libft dizinine gidin:
```bash
cd /yol/libft
```
2. Kütüphaneyi derleyin:
```bash
make
```
   - `libft.a` statik kütüphane dosyasını oluşturur.
   - Bonus işlevleri derlemek için: `make bonus`
   - Nesne dosyalarını temizlemek için: `make clean`
   - Kütüphane ve nesne dosyalarını tamamen silmek için: `make fclean`
   - Yeniden derlemek için: `make re`

### Libft Kullanımı
1. Kendi C projenize kütüphaneyi dahil edin:
```c
#include "libft.h"
```
2. Derleme sırasında kütüphaneyi bağlayın:
```bash
gcc programiniz.c -L. -lft -o programiniz
```

## Lisans
Bu proje, 42 okulu müfredatı kapsamında eğitim amaçlı geliştirilmiştir.