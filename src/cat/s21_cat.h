#ifndef S21_CAT_H
#define S21_CAT_H
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_formed(int f_argc, char **f_argv, char f_name[100][2000]);
int parameters_formed(int p_argc, char **p_argv, int param[100]);
void filtr_parameters(int param[100], int nr);
void flag_formed(int param[100], int f[6], int p_count);
void output(FILE *f_pr, int f[6]);
void number_format(int f_n[6], char *str_n, int f_e, char space_n[6],
                   int *n_str, int l);
int s21_strlen(char *str_c);

#endif
