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
#include "command.h"
#include "background.h"
#include "pipe.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

//komutun bir boru hattı içerip içermediğini kontrol eder
//Eğer komutun sonunda '&' varsa, komut arka planda çalıştırılır.
void execute_command(char *command) {
    if (strchr(command, '|') != NULL) {
        execute_piped_commands(command);
        return;
    }

    int background = 0;
    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '&') {
        background = 1;  // Komut arka planda çalıştırılacak.
        command[len - 1] = '\0';
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Çocuk işlem: Komutu çalıştır.
        char *args[BUFFER_SIZE];
        int i = 0;
        char *input_file = NULL;
        char *output_file = NULL;
        char *token = strtok(command, " ");

        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                // Giriş dosyası yönlendirmesi.
                token = strtok(NULL, " ");
                if (token != NULL) {
                    input_file = token;
                } else {
                    fprintf(stderr, "Hata: Giriş dosyası belirtilmedi.\n");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(token, ">") == 0) {
                // Çıkış dosyası yönlendirmesi.
                token = strtok(NULL, " ");
                if (token != NULL) {
                    output_file = token;
                } else {
                    fprintf(stderr, "Hata: Çıkış dosyası belirtilmedi.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                args[i++] = token;
            }
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (input_file != NULL) {
            int input_fd = open(input_file, O_RDONLY);
            if (input_fd < 0) {
                perror("Giriş dosyası açılamadı");
                exit(EXIT_FAILURE);
            }
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        if (output_file != NULL) {
            int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0) {
                perror("Çıkış dosyası açılamadı");
                exit(EXIT_FAILURE);
            }
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        if (execvp(args[0], args) == -1) {
            perror("Komut çalıştırılamadı");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Ana işlem: Çocuk işlemi bekle veya arka planda çalıştır.
        if (background) {
            background_process_count++;
            printf("[pid: %d] arka planda çalışıyor...\n", pid);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    } else {
        perror("Fork başarısız");
    }
}