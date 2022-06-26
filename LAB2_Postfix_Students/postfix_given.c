#include "postfix_given.h"

read_info *read_eqs(char *file_name) {

  FILE *fp = fopen(file_name, "r");
  read_info *e_info = malloc(sizeof(read_info));

  fscanf(fp, "%d", &(e_info->num));

  e_info->infix_eqs = malloc(e_info->num * sizeof(char *));
  e_info->postfix_eqs = malloc(e_info->num * sizeof(char *));

  int eq_len;
  char str_buf[100];
  for (int i = 0; i < e_info->num; i++) {
    fscanf(fp, "%s", str_buf);
    eq_len = strlen(str_buf);
    e_info->infix_eqs[i] = malloc((eq_len+1) * sizeof(char));
    e_info->postfix_eqs[i] = calloc((eq_len+1), sizeof(char));
    strcpy(e_info->infix_eqs[i], str_buf);
  }

  fclose(fp);

  return e_info;
}

void free_eqs(read_info *rp) {
  for (int i = 0; i < rp->num; i++) {
    free(rp->infix_eqs[i]);
    free(rp->postfix_eqs[i]);
  }
  free(rp->infix_eqs);
  free(rp->postfix_eqs);
  free(rp);
}

bucket *init() {
  bucket *bk = malloc(sizeof(bucket));
  bk->head = NULL;
  bk->tail = NULL;
  bk->len = 0;
  return bk;
}

void destruct(bucket *q) {
  node *tmp = q->head;
  while(tmp != NULL) {
    node *tmp_next = tmp->next;
    free(tmp);
    tmp = tmp->next;
  }
  free(q);
}

void print_bucket(bucket *q) {
node *tmp = q->head;
  while (tmp != NULL) {
    printf("%c ", tmp->tok);
    tmp = tmp->next;
  }
  printf("\n");
}