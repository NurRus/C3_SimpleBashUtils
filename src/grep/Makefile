CFLAGS = -c -Wall -Werror -Wextra -std=c11

all: style_test rebuild

s21_grep.o:
	gcc $(CFLAGS) s21_grep.c

main.o:
	gcc $(CFLAGS) main.c

s21_grep: main.o s21_grep.o
	gcc main.o s21_grep.o -o s21_grep

style_test:
	clang-format -style=Google -n *.c *.h 

editing_style:
	clang-format -style=Google -i *.c *.h

rebuild:
	make clean
	make s21_grep

clean:
	rm -rf *.o
	rm -rf s21_grep
	rm -rf *.log