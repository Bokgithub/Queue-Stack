#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix_given.h"

#define CHAR_TO_INT(x) x - '0'
#define INT_TO_CHAR(x) x + '0'

// TODO: stack functions
void push(bucket *q, char tok);
char pop(bucket *q);

// TODO: linked queue
void enqueue(bucket *q, char tok);
char dequeue(bucket *q);

// TODO: infix to postfix
void infix_to_postfix(char* postfix, char* infix);

// TODO: postfix solver
postfix_part *partition_num_op(char *eq);
void calc_one_chunk(postfix_part *part);
int calc_equation(char *equation);
int compare(char inp);
/////// Add your functions
// ex. int get_priority(char op);