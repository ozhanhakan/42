#!/bin/sh

# /etc/passwd dosyasındaki yorum satırlarını kaldır, her iki satırda birini al, 
# login isimlerini ters çevir, ters alfabetik sırayla sıralar, ve belirtilen satır aralığındaki loginleri yazdırır.
cat /etc/passwd | sed '/^#/d' | sed -n 'n;p' | cut -d ':' -f 1 | rev | sort -r | sed -n "$FT_LINE1,$FT_LINE2 p" | tr '\n' ', ' | sed 's/, $/./' | tr -d '\n'
