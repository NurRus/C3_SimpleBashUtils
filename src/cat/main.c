
#include "s21_cat.h"

int main(int argc, char **argv) {
  int par_count = 0, file_count = 0;
  int parameters[100], flags[6];
  char file_name[100][2000];
  FILE *file_pr;

  for (int i = 0; i < 100; i++) parameters[i] = '0';

  file_count = file_formed(argc, argv, file_name);

  par_count = parameters_formed(argc, argv, parameters);

  filtr_parameters(parameters, par_count);

  flag_formed(parameters, flags, par_count);

  for (int i = 0; i < file_count; i++) {
    if ((file_pr = fopen(file_name[i], "r"))) {
      output(file_pr, flags);
      fclose(file_pr);
    } else
      fprintf(stderr, "cat: %s: No such file or directory\n", file_name[i]);
  }

  return 0;
}