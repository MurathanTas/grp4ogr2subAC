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
* - Elif Yerlikaya - 2A
*/

#include "pipe.h"  
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h> 

void execute_piped_commands(char *commands) {
    char *cmds[BUFFER_SIZE]; // Komutları tutmak için bir dizi.
    int cmd_count = 0; // Komut sayısını takip etmek için.

    // Komutları '|' karakterine göre ayır.
    char *token = strtok(commands, "|");
    while (token != NULL) {
        cmds[cmd_count++] = token; 
        token = strtok(NULL, "|"); 
    }

    // Her komut arasındaki boru hatları için gerekli dosya tanıtıcılarını tutacak dizi.
    int pipefds[2 * (cmd_count - 1)];
    for (int i = 0; i < cmd_count - 1; i++) {
        // Pipe oluştur.
        if (pipe(pipefds + i * 2) < 0) {
            perror("Pipe oluşturulamadı");
            exit(EXIT_FAILURE);
        }
    }

    int pid;
    for (int i = 0; i < cmd_count; i++) {
        pid = fork(); 

        if (pid == 0) { 
            // Eğer bu süreç ilk komut değilse, giriş akışını bağla.
            if (i > 0) {
                dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
            }
            // Eğer bu süreç son komut değilse, çıkış akışını bağla.
            if (i < cmd_count - 1) {
                dup2(pipefds[i * 2 + 1], STDOUT_FILENO);
            }

            // Pipe dosya tanıtıcılarını kapat (çocuk sürecin işine yaramaz).
            for (int j = 0; j < 2 * (cmd_count - 1); j++) {
                close(pipefds[j]);
            }

            // Komutu ve argümanlarını ayır.
            char *args[BUFFER_SIZE];
            int arg_count = 0;
            char *arg_token = strtok(cmds[i], " ");
            while (arg_token != NULL) {
                args[arg_count++] = arg_token; 
                arg_token = strtok(NULL, " ");
            }
            args[arg_count] = NULL; 

            if (execvp(args[0], args) == -1) {
                perror("Komut çalıştırılamadı");
                exit(EXIT_FAILURE);
            }
        } else if (pid < 0) { // Eğer fork başarısız olursa.
            perror("Fork başarısız");
            exit(EXIT_FAILURE);
        }
    }

    // Ana süreçte, tüm pipe dosya tanıtıcılarını kapat.
    for (int i = 0; i < 2 * (cmd_count - 1); i++) {
        close(pipefds[i]);
    }

    // Çocuk süreçlerin tamamlanmasını bekle.
    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }
}
