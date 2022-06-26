#include "postfix_module.h"
#include "ctype.h"


void enqueue(bucket* q, char tok) {
    // TODO: Enqueue the token in the linked queue
    node* make = malloc(sizeof(node)); //make��� ��带 ����� tok�� NULL�ּҰ��� �Ҵ�
    make->tok = tok;
    make->next = NULL;
    if (q->len == 0) //q�� len�� 0�� ���� tail�� node ��� make�� ����
    {
        q->tail = make;
        q->head = make;
    }
    else {
        q->tail->next = make; //q�� ������ ����, make�� tail �� ��忡 ��ġ�ϵ��� �ϰ�, tail�� make�� �����.
        q->tail = make;
    }
    q->len += 1;
}

char dequeue(bucket *q) {
    // TODO: Dequeue the token in the linked queue
    // Return: token char
    
    if (q->len == 0)
    {
        printf("queue is empty\n");
        return -1;
    }
    else if (q->len == 1)
    {
        int deq = q-> head->tok;
        q->head = NULL;
        q->tail = NULL;
        q->len -= 1;
        return deq;
    }
    else {
        int deq = q->head->tok;
        q->head = q->head->next;
        q->len -= 1;
        return deq;
    }

}




void push(bucket* q, char tok) {
    // TODO: Push the token in the linked stack
   
    node* make = malloc(sizeof(node)); //make��� ��带 ���� tok�Ҵ� next �ʱ�ȭ
    make->tok = tok;
    make->next = NULL;
    if (q->len == 0)
    {
        q->head = make; 
}
    else
        make->next = q->head; //make�� next�� ������ ù��° ���� �Ҵ��ϰ�
        q->head = make;  //ù��° ��带 make�� �����Ѵ�.
    q->len += 1; //q len�� �ϳ� ������Ŵ.

}

char pop(bucket *q) {
    // TODO: Pop the token in the linked queue
    // Return: token char
    
    if (q->len == 0)
    {
        printf("stack is empty");
        return -1;
    }
    char deq = q->head->tok;
    q->head = q->head->next;
    q->len -= 1;
    return deq;
    
}


int compare(char inp) 
{
    int ret = 0;
    switch (inp)
    {
    case '*' : //input�� �����Ǵ� ������ �������̸� 2
        ret = 2;
        break;
    case '/':
        ret = 2;
        break;
    case '+' : //input�� �����Ǵ� ���� �������̸� 1
        ret = 1;
        break;
    case '-':
        ret = 1;
        break;
    default: //�������� 0, �ڷ����� char������ ���ڷ� ǥ���� ���̶�� 0�� ��ȯ�ȴ�.
        ret = 0;

    }
    return ret;
}


void infix_to_postfix(char* postfix, char* infix) {

  int eq_len = strlen(infix);
  bucket *st = init();
  int num = 0;
  int brak = 0;
  for (int idx = 0; idx < eq_len; idx++) //infix�� ������� Ȯ���ϸ� ó��
  {
      
      if (compare(infix[idx])==0) //�Է°��� ���ڶ�� postfix�� �Է�
      {
          strcat_wrap(postfix, infix[idx]);
      }
      else
      { //���ڰ� �ƴ϶��
          if (st->len == 0) //st�� ���������, operator�� stack�� ����
          {
              push(st, infix[idx]);
          }
          else //stack�� �� ���������, stacknode�� stack�� head �����ͷ� �Ҵ���.
          {
              
              for (int stidx = st->len; stidx > 0; stidx--)
              {
                  if (compare(infix[idx]) > compare(st->head->tok)) //���ο� operator�� �켱������ ������ for���� Ż���Ͽ� stack�� operator ����.
                  {                 
                      break;
                  }
                  else {    //���ο� operator�� �켱������ ������ �켱 ������ �� ���� �ְ� ���� ������, tail���� ���� postfix�� ����.
                      strcat_wrap(postfix, pop(st));
                  }
                  
              }
              push(st, infix[idx]); //���ο� operator�� stack�� ����
          }

      } 

      
  }
  
  for (int stidx = st->len; stidx > 0; stidx--) //for ���� ������ stack�� ���� �����ڸ� ��� ���
  {
      strcat_wrap(postfix, pop(st));
  }

  destruct(st);
}


postfix_part *partition_num_op(char *eq) {
    // TODO: Initial partitioning of equation into stack and queue.
    postfix_part* part = malloc(sizeof(postfix_part));
    part->stack = init();
    part->queue = init();
    int op = 0;
    int idx = 0;


        while (compare(eq[idx])!=0) {
            push(part->stack, eq[idx]);
            idx++;
        }
        while (idx < strlen(eq)) {
            enqueue(part->queue, eq[idx]);
            idx++;
        }

    
    return part;
}

void calc_one_chunk(postfix_part *part) {
    // TODO: Pop two numbers, dequeue one operator, and solve
    // Use INT_TO_CHAR and CHAR_TO_INT to convert the datatype between two.
    char op = pop(part->stack);
    int num2 = CHAR_TO_INT(pop(part->stack));
    int num1 = CHAR_TO_INT(pop(part->stack));
    int num3;

    if (op == '+')
    {
        num3 = num1 + num2;
    }
    else if (op == '-')
    {
        num3 = num1 - num2;
    }
    else if (op == '*')
    {
        num3 = num1 * num2;
    }
    else if (op == '/')
    {
        num3 = num1 / num2;
    }
    push(part->stack, INT_TO_CHAR(num3));
}

int calc_equation(char *equation) {

    // TODO: Full equation solver. 
    // Utilize 'partition_num_op' and 'calc_one_chunk'.
    // Be aware to free pointers used in 'partition_num_op'. 
    // (You can use 'destruct' in postfix_given.h)
    
    postfix_part *part= partition_num_op(equation);
    int totalvalue;
    while (part->queue->len != 0)
    {
       
            char c = dequeue(part->queue);
            if (compare(c) == 0)
            {
                push(part->stack, c);                
            }
            else
            {
                push(part->stack, c);
                 calc_one_chunk(part);
            }
        
    }
    return CHAR_TO_INT(pop(part->stack));
    
}


// If you want to add your own function,
// please add declaration in 'postfix_module.h'




void strcat_wrap(char *str, char c) {
  char buf[2];
  buf[0] = c;
  buf[1] = '\0';

  strcat(str, buf);
}