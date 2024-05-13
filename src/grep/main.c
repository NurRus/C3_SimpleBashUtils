
#include "s21_grep.h"

int main(int argc, char **argv) {
  int n = 0, f = 0, sn = 0, error = 0;
  char f_name[100][1000] = {'\0'}, sampl[300][2000] = {'\0'};

  char rezult[100] = {'\0'};
  char val[100][2000] = {'\0'};

  int modrez[11] = {0};

  n = param_form(argc, argv, rezult, val);

  f = file_form(rezult, n, f_name, val);

  modication_param(rezult, modrez, n);

  for (int i = 0; i < n; i++)
    if (sn < 300) sn = sampl_form(rezult[i], sampl, sn, &error, val[i]);

  if (error == 0 && f > 0) {
    int find = 0;
    for (int i = 0; i < f; i++) {
      FILE *fp;
      if ((fp = fopen(f_name[i], "r"))) {
        find = analysis(fp, sampl, sn, f, modrez, f_name[i]);
        if (modrez[5] == 1 && find != 0) printf("%s\n", f_name[i]);
        fclose(fp);
      } else if (modrez[7] == 0)
        fprintf(stderr, "grep: %s: No such file or directory\n", f_name[i]);
    }
  }

  return 0;
}
