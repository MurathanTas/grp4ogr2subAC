
/*
* SAKARYA ÜNİVERSİTESİ 2024 GÜZ DÖNEMİ
* İŞLETİM SİSTEMLERİ PROJE ÖDEVİ
*
* Grup no 4 - 2. Öğretim -A ve C Şubesi
*
* Grup üyeleri:
* - Murathan Taş - 2C
* - Buğra Akşit - 2C
* - Selva Maramaei - 2A
* - İrem Kabil - 2C
* - Elif Yerlikaya - 2A
*/





#include "prompt.h"

//kabuk istemini göstermek için "> " yazdırır.
//Tamponun hemen temizlenmesini sağlayarak istemin gecikmeden görüntülenmesini sağlar.

void print_prompt() {
    printf("> ");
    fflush(stdout);
}