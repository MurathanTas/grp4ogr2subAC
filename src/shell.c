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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "prompt.h"
#include "background.h"
#include "pipe.h"
#include "command.h"

#define BUFFER_SIZE 1024

int main()
{
    // girdi için tampon
    char input[BUFFER_SIZE];

    struct sigaction sa;
    sa.sa_handler = &handle_background_process;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    while (1)
    {

        print_prompt();

        // kullanıcıdan girdi al
        if (fgets(input, BUFFER_SIZE, stdin) == NULL)
        {
            perror("Girdi okunamadı");
            continue;
        }

        // Yeni satır karakterini kaldır.
        input[strcspn(input, "\n")] = '\0';

        // "quit" komutu girildiyse kabuğu sonlandır.
        if (strcmp(input, "quit") == 0)
        {
            printf("Arka plan işlemleri bekleniyor...\n");

            // Tüm arka plan işlemlerinin tamamlanmasını bekle.
            while (background_process_count > 0)
            {
                sleep(1);
            }
            printf("Kabuk kapatılıyor...\n");
            break;
        }
        // Eğer geçerli bir komut varsa, çalıştır.
        if (strlen(input) > 0)
        {
            execute_command(input);
        }
    }

    return 0;
}