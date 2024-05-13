#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int param_form(int ar_c, char **ar_v, char pr[100], char v[100][2000]);
void s21_strcpy(char *str1, char *str2);
void deleting_line(int ac, char **a_v);
int file_form(char pr[100], int nn, char file_n[100][1000], char v[100][2000]);
void modication_param(char pr[100], int modpr[11], int nn);
int sampl_form(char pr, char s_mpl[300][2000], int s_n, int *err, char *v);
int analysis(FILE *fpr, char s_mpl[300][2000], int s_n, int count_f,
             int modpr[11], char *file_n);
int s21_strstr(char *str1, char *str2);
int s21_strcasestr(char *str1, char *str2);

#endif
