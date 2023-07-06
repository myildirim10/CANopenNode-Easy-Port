# Türkçe karakterleri ingilizce karakterler ile değiştirme fonksiyonu
def replace_turkish_chars(input_str):
  # Türkçe karakterler ve değiştirilecek ingilizce karakterlerin listesi
  turkish_chars = "ı", "İ", ".attribute = ,", "#define OD_CNT_SDO_CLI 1"
  english_chars = "i", "I", ".attribute = ODA_MB,", "#define OD_CNT_NMT 1 \
\n#define OD_CNT_EM 1 \
\n#define OD_CNT_SYNC 1 \
\n#define OD_CNT_SYNC_PROD 1 \
\n#define OD_CNT_STORAGE 1 \
\n#define OD_CNT_TIME 1 \
\n#define OD_CNT_EM_PROD 1 \
\n#define OD_CNT_HB_CONS 1 \
\n#define OD_CNT_HB_PROD 1 \
\n#define OD_CNT_SDO_SRV 1 \
\n#define OD_CNT_SDO_CLI 1 \
\n#define OD_CNT_TPDO 1 \
\n#define OD_CNT_RPDO 1"

  # Türkçe karakterleri ingilizce karakterler ile değiştir
  output_str = input_str
  for i in range(len(turkish_chars)):
    output_str = output_str.replace(turkish_chars[i], english_chars[i])

  return output_str
  
# Dosya adı
file_c = "../CANopen/driver/OD.c"
file_h = "../CANopen/driver/OD.h"

# Dosya içeriğini oku
with open(file_c, "r", encoding="utf8") as file:
  file_contents = file.read()

# Türkçe karakterleri ingilizce karakterler ile değiştir
file_contents = replace_turkish_chars(file_contents)

# Değiştirilmiş dosya içeriğini kaydet
with open(file_c, "w", encoding="utf8") as file:
  file.write(file_contents)

# Dosya içeriğini oku
with open(file_h, "r", encoding="utf8") as file:
  file_contents = file.read()

# Türkçe karakterleri ingilizce karakterler ile değiştir
file_contents = replace_turkish_chars(file_contents)

# Değiştirilmiş dosya içeriğini kaydet
with open(file_h, "w", encoding="utf8") as file:
  file.write(file_contents)