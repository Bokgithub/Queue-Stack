#include "postfix_module.h"

int main() {
  read_info *tmp;
  tmp = read_eqs("equations.txt");

  /////// Test region ///////

  for (int i = 0; i < tmp->num; i++) {
    printf("%s\t", tmp->infix_eqs[i]);
    printf("%d\n", (int)strlen(tmp->infix_eqs[i]));
  }
  printf("end\n");

  for (int i = 0; i < tmp->num; i++) {
      infix_to_postfix(tmp->postfix_eqs[i], tmp->infix_eqs[i]);
    printf("%s\n", tmp->postfix_eqs[i]);
  }

  for (int i = 0; i < tmp->num; i++)
    printf("\t\t\t\t%s = %d\n", tmp->postfix_eqs[i],
           calc_equation(tmp->postfix_eqs[i]));

  /////////////////////////////

  free_eqs(tmp);
  return 0;
}