#
# SAKARYA ÜNİVERSİTESİ 2024 GÜZ DÖNEMİ
# İŞLETİM SİSTEMLERİ PROJE ÖDEVİ
#
# Grup no 4 - 2. Öğretim -A ve C Şubesi
#
# Grup üyeleri:
# - Murathan Taş - 2C
# - Buğra Akşit - 2C
# - Selva Maramaei - 2A
# - İrem Kabil - 2C
# - Elif Yerlikaya - 2A
#

program: derle calistir

derle:
	gcc -I ./include/ -o ./lib/prompt.o -c ./src/prompt.c
	gcc -I ./include/ -o ./lib/command.o -c ./src/command.c
	gcc -I ./include/ -o ./lib/background.o -c ./src/background.c
	gcc -I ./include/ -o ./lib/pipe.o -c ./src/pipe.c
	gcc -I ./include/ -Wall -Wextra -o ./bin/shell ./lib/pipe.o ./lib/background.o ./lib/prompt.o ./lib/command.o ./src/shell.c

calistir:
	./bin/shell