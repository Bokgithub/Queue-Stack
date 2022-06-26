#include "postfix_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions given in advance
read_info *read_eqs(char *file_name);
void free_eqs(read_info *rp);
bucket *init();
void destruct(bucket *q);
void print_bucket(bucket *q);
void strcat_wrap(char *str, char c);