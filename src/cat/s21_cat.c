#include "s21_cat.h"

int file_formed(int f_argc, char **f_argv, char f_name[100][2000]) {
  int fc = 0;
  if (f_argc > 1) {
    int n = 1, f = 0, i = 0;
    while (i < f_argc) {
      if (f_argv[i][0] == '-') {
        n++;
        f++;
      }
      if (f > 0 && f_argv[i][0] != '-') i = f_argc;
      i++;
    }
    for (int i = n; i < f_argc; i++) {
      if (fc < 100 - 1) {
        strcpy(f_name[fc], f_argv[i]);
        fc++;
      }
    }
  }
  return fc;
}

int parameters_formed(int p_argc, char **p_argv, int param[100]) {
  int p_count = 0;
  if (p_argc > 1) {
    const char *short_options = "+benstv";
    const struct option long_options[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'},
        {NULL, no_argument, NULL, 0}};
    do {
      param[p_count] =
          getopt_long(p_argc, p_argv, short_options, long_options, NULL);
      if (param[p_count] == '?')
        param[p_count] = -1;
      else
        p_count++;
    } while (param[p_count - 1] != -1);
    p_count--;
  }
  return p_count;
}

void filtr_parameters(int param[100], int p_count) {
  int f = 0;
  for (int i = 0; i < p_count; i++)
    if (param[i] != 'b' && param[i] != 'e' && param[i] != 'n' &&
        param[i] != 's' && param[i] != 't' && param[i] != 'v')
      fprintf(stderr, "usage: s21_cat [-benstuv] [file ...]\n");
  for (int i = 0; i < p_count - 1; i++) {
    for (int j = i + 1; j < p_count; j++)
      if (param[j] == param[i]) param[j] = '0';
  }
  for (int i = 0; i < p_count; i++)
    if (param[i] == 'b') f++;
  for (int i = 0; i < p_count; i++)
    if (param[i] == 'n' && f > 0) param[i] = '0';
  f = 0;
}

void flag_formed(int param[100], int f[6], int p_count) {
  for (int i = 0; i < 6; i++) f[i] = 0;
  for (int i = 0; i < p_count; i++) {
    if (param[i] == 'b') f[0] = 1;
    if (param[i] == 'e') f[1] = 1;
    if (param[i] == 'n') f[2] = 1;
    if (param[i] == 's') f[3] = 1;
    if (param[i] == 't') f[4] = 1;
    if (param[i] == 'v') f[5] = 1;
  }
}

void output(FILE *f_pr, int f[6]) {
  int f_enter = 0, number_str = 0, length_str, i = 0;
  char *str = (char *)malloc(sizeof(char) * (2000 + 1)), space[6];
  for (i = 0; i < 2000; i++) str[i] = '\0';
  while (!feof(f_pr) && fgets(str, 2000 - 1, f_pr)) {
    length_str = s21_strlen(str);
    if (str[length_str] != '\0') length_str++;
    if (str[0] == '\n')
      f_enter++;
    else
      f_enter = 0;
    number_format(f, str, f_enter, space, &number_str, length_str);
    if ((f[2] == 1 || (f[0] == 1 && f_enter == 0)) &&
        (f[3] == 0 || (f[3] == 1 && f_enter < 2)))
      printf("%s%d%c", space, number_str, 9);
    for (int i = 0; i < length_str; i++) {
      if ((f[5] == 1 || f[1] == 1 || f[4] == 1)) {
        if (str[i] >= 0 && str[i] < 32 && str[i] != 9 && str[i] != 10) {
          str[i] = str[i] + 64;
          printf("^");
        }
        if (str[i] < -96) {
          str[i] = str[i] + 192;
          printf("M-^");
        }
        if (str[i] == 127) {
          str[i] = str[i] - 64;
          printf("^");
        }
      }
      if (f[4] == 1 && str[i] == 9) {
        str[i] = 'I';
        printf("^");
      }
      if (f[3] == 0 || (f[3] == 1 && f_enter < 2)) {
        if (f[1] == 1 && i == length_str - 1 && !feof(f_pr) && str[i] == '\n')
          printf("$");
        printf("%c", str[i]);
      }
    }
    for (i = 0; i < 2000; i++) str[i] = '\0';
  }
  free(str);
}

void number_format(int f_n[6], char *str_n, int f_e, char space_n[6],
                   int *n_str, int l) {
  int sp_count = 5, i = 0, ns;
  ns = *n_str;
  for (i = 0; i < 6; i++) space_n[i] = '\0';
  i = 0;
  if (f_n[3] == 0 || (f_n[3] == 1 && f_e < 2)) {
    if (f_n[2] == 1) ns++;
    do {
      if (str_n[i] >= 32 && f_n[0] == 1 && f_e == 0) ns++;
      i++;
    } while (str_n[i - 1] < 32 && i < l);
  }
  if (ns >= 10) sp_count = 4;
  if (ns >= 100) sp_count = 3;
  if (ns >= 1000) sp_count = 2;
  if (ns >= 10000) sp_count = 1;
  if (ns >= 100000) sp_count = 0;
  for (int j = 0; j < 6; j++) space_n[j] = ' ';
  space_n[sp_count] = '\0';
  *n_str = ns;
}

int s21_strlen(char *str_c) {
  int l = 0, i = 0;
  while (i < 2000) {
    if (str_c[i] != 0) l++;
    i++;
  }
  return l;
}