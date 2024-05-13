#include "s21_grep.h"

int param_form(int ar_c, char **ar_v, char pr[100], char v[100][2000]) {
  int rez = 0, nn = 0, f_optind = 0, a_rgc = ar_c + 1;
  char *short_options = "e:ivclnhsf:o0";
  char **a_rgv = (char **)malloc((ar_c + 1) * sizeof(char *));
  for (int i = 0; i < ar_c; i++) {
    a_rgv[i] = (char *)malloc(sizeof(char) * (strlen(ar_v[i]) + 1));
    strcpy(a_rgv[i], ar_v[i]);
  }
  a_rgv[a_rgc - 1] = (char *)malloc(sizeof(char) * (3));
  strcpy(a_rgv[a_rgc - 1], "-0");
  do {
    rez = getopt(a_rgc, a_rgv, short_options);
    if (rez == -1) {
      if (f_optind == 0) {
        pr[nn] = 'x';
        strcpy(v[nn], a_rgv[optind]);
        nn++;
        f_optind++;

      } else {
        pr[nn] = 'y';
        strcpy(v[nn], a_rgv[optind]);
        nn++;
      }
      deleting_line(a_rgc, a_rgv);
      a_rgc--;
    } else {
      if (rez == 'e' || rez == 'f') {
        pr[nn] = rez;
        strcpy(v[nn], optarg);
        f_optind++;
        nn++;
      }
      if (rez == 'i' || rez == 'v' || rez == 'c' || rez == 'l' || rez == 'n' ||
          rez == 'h' || rez == 's' || rez == 'o') {
        pr[nn] = rez;
        nn++;
      }
    }
  } while (optind < a_rgc);
  for (int i = 0; i <= ar_c; i++)
    if (a_rgv[i] != NULL) free(a_rgv[i]);
  if (a_rgv != NULL) free(a_rgv);
  return nn;
}

void deleting_line(int ac, char **a_v) {
  for (int i = 2; i < ac; i++) {
    a_v[i - 1] = realloc(a_v[i - 1], strlen(a_v[i]) + 1);
    strcpy(a_v[i - 1], a_v[i]);
  }
}

int file_form(char pr[100], int nn, char file_n[100][1000], char v[100][2000]) {
  int ff = 0;
  for (int i = 0; i < nn; i++)
    if (pr[i] == 'y') {
      strcpy(file_n[ff], v[i]);
      ff++;
    }

  return ff;
}

void modication_param(char pr[100], int modpr[11], int nn) {
  for (int j = 0; j < 11; j++) modpr[j] = 0;
  for (int i = 0; i < nn; i++) {
    if (pr[i] == 'i') modpr[0] = 1;
    if (pr[i] == 'v') modpr[1] = 1;
    if (pr[i] == 'h') modpr[2] = 1;
    if (pr[i] == 'c') modpr[3] = 1;
    if (pr[i] == 'n') modpr[4] = 1;
    if (pr[i] == 'l') modpr[5] = 1;
    if (pr[i] == 'o') modpr[6] = 1;
    if (pr[i] == 's') modpr[7] = 1;
    if (pr[i] == 'f') modpr[8] = 1;
    if (pr[i] == 'e') modpr[9] = 1;
    if (pr[i] == 'y') modpr[10] = 1;
  }
}

int sampl_form(char pr, char s_mpl[300][2000], int s_n, int *err, char *v) {
  FILE *fp;
  char str[2000];
  char *estr;
  int e = *err;

  if ((pr == 'e' || pr == 'x') && v != NULL) {
    strcpy(s_mpl[s_n], v);
    s_n++;
  }
  if ((fp = fopen(v, "r")) && pr == 'f') {
    while (!feof(fp)) {
      estr = fgets(str, 2000, fp);
      if (estr != 0) {
        strcpy(s_mpl[s_n], str);
        if (s_mpl[s_n][strlen(s_mpl[s_n]) - 1] == '\n')
          s_mpl[s_n][strlen(s_mpl[s_n]) - 1] = '\0';
        s_n++;
      }
    }
    fclose(fp);
  } else if (pr == 'f') {
    fprintf(stderr, "grep: %s: No such file or directory\n", v);
    e++;
    *err = e;
  }
  return s_n;
}

int analysis(FILE *fpr, char s_mpl[300][2000], int s_n, int count_f,
             int modpr[11], char *file_n) {
  int count_c = 0, count_s = 0;
  char str[2000] = {'\0'};
  while (!feof(fpr)) {
    count_s++;
    if (fgets(str, 2000 - 1, fpr) != 0) {
      int flag = 0, fc = 0, fi = 0, co = 0;
      for (int j = 0; j < s_n; j++) {
        fc = 0;
        fi = 0;
        fc = s21_strstr(str, s_mpl[j]);
        fi = s21_strcasestr(str, s_mpl[j]);
        if (modpr[0] == 1) fc = 0;
        if (modpr[0] == 0) fi = 0;
        if (fc != 0 && modpr[1] == 0 && modpr[0] == 0) flag++;
        if (fc == 0 && modpr[1] == 1 && modpr[0] == 0) flag++;
        if (fi != 0 && modpr[1] == 0 && modpr[0] == 1) flag++;
        if (fi == 0 && modpr[1] == 1 && modpr[0] == 1) flag++;
        if (modpr[5] == 0 && modpr[3] == 0 && modpr[6] == 1 && modpr[1] == 0 &&
            flag > 0) {
          if (modpr[2] == 0 && count_f > 1 && co == 0) printf("%s:", file_n);
          if (modpr[4] == 1 && co == 0) printf("%d:", count_s);
          co++;
          for (int i = 0; i < fc + fi; i++) printf("%s\n", s_mpl[j]);
        }
      }
      if (flag > 0) {
        count_c++;
        if (modpr[5] == 0 && modpr[3] == 0 && modpr[6] == 0) {
          if (modpr[2] == 0 && count_f > 1) printf("%s:", file_n);
          if (modpr[4] == 1) printf("%d:", count_s);
          if (modpr[6] == 0) printf("%s", str);
          if (str[strlen(str) - 1] != '\n') printf("\n");
        }
      }
    }
  }
  if (modpr[3] == 1) {
    if (modpr[2] == 0 && count_f > 1) printf("%s:", file_n);
    if (modpr[5] == 1 && count_c > 0) count_c = 1;
    printf("%d\n", count_c);
  }
  if (str[strlen(str) - 1] != '\n') count_c = -count_c;
  return count_c;
}

int s21_strstr(char *str1, char *str2) {
  int count = 0;
  if (str2 != NULL) {
    int i = 0, j = 0, f = 0;
    for (i = 0; i < (int)strlen(str1); i++) {
      j = 0;
      f = 0;
      while (j < (int)strlen(str2) && (i + j) < (int)strlen(str1)) {
        if (str1[i + j] == str2[j]) f++;
        j++;
      }
      if (f == j) count++;
    }
  }
  if (str1 == NULL && str2 == NULL) count = 1;
  return count;
}

int s21_strcasestr(char *str1, char *str2) {
  int count = 0;
  if (str2 != NULL) {
    int i = 0, j = 0, f = 0;
    for (i = 0; i < (int)strlen(str1); i++) {
      j = 0;
      f = 0;
      while (j < (int)strlen(str2) && (i + j) < (int)strlen(str1)) {
        if (str1[i + j] == str2[j])
          f++;
        else if ((str1[i + j] == str2[j] - 32) && str2[j] >= 'a' &&
                 str2[j] <= 'z')
          f++;
        else if ((str1[i + j] == str2[j] + 32) && str2[j] <= 'Z' &&
                 str2[j] >= 'A')
          f++;
        j++;
      }
      if (f == j) count++;
    }
  }
  if (str1 == NULL && str2 == NULL) count = 1;
  return count;
}
