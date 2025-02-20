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

#include "background.h"
#include "prompt.h"

//sayaç
int background_process_count = 0;

//Arka plandaki işlemleri temizler ve durumlarını yazdırır.
// SIGCHLD sinyali alındığında çağrılır , tamamlanan arka plan işlemlerini
// bekler ve işlem sonucunu standart çıktıya yazdırır. Ardından yeni bir komut istemi görüntülenir.


void handle_background_process(int sig) {
    int status;
    pid_t pid;
    // Tüm tamamlanmış çocuk işlemleri kontrol et.
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        background_process_count--;
        printf("\n[pid: %d] retval: %d\n", pid, WEXITSTATUS(status));
        print_prompt();
    }
}
