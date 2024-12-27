

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






#ifndef PROMPT_H
#define PROMPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 1024

//kabuğun kullanıcı girişini kabul etmeye hazır olduğunu göstermek için kullanılır.
void print_prompt();

#endif