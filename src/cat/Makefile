CFLAGS = -c -Wall -Werror -Wextra -std=c11

all: style_test rebuild

s21_cat.o:
	gcc $(CFLAGS) s21_cat.c

main.o:
	gcc $(CFLAGS) main.c

s21_cat: main.o s21_cat.o
	gcc main.o s21_cat.o -o s21_cat

style_test:
	clang-format -style=Google -n *.c *.h 

editing_style:
	clang-format -style=Google -i *.c *.h

rebuild:
	make clean
	make s21_cat


clean:
	rm -rf *.o
	rm -rf s21_cat
	rm -rf *.log