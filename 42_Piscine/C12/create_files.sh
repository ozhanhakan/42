#!/bin/bash

# Dosya kontrolü
if [ ! -f "dosya_listesi.txt" ]; then
  echo "Hata: dosya_listesi.txt bulunamadı!"
  exit 1
fi

# Satır satır oku
while IFS= read -r line; do
  # Boş satırları atla
  [[ -z "$line" ]] && continue

  # " : " ile ayır ve trimle (baştaki/sondaki boşlukları sil)
  if [[ "$line" == *" : "* ]]; then
    folder=$(echo "$line" | awk -F" : " '{gsub(/^[ \t]+|[ \t]+$/, "", $1); print $1}')
    file=$(echo "$line" | awk -F" : " '{gsub(/^[ \t]+|[ \t]+$/, "", $2); print $2}')
    
    # Klasörü oluştur ve dosyayı touch'la
    mkdir -p "$folder"
    touch "${folder}/${file}"
  else
    echo "Hatalı format: $line"
  fi
done < dosya_listesi.txt