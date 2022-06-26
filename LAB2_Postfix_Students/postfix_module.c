#include "postfix_module.h"
#include "ctype.h"


void enqueue(bucket* q, char tok) {
    // TODO: Enqueue the token in the linked queue
    node* make = malloc(sizeof(node)); //make라는 노드를 만들어 tok와 NULL주소값을 할당
    make->tok = tok;
    make->next = NULL;
    if (q->len == 0) //q의 len가 0일 때는 tail과 node 모두 make로 설정
    {
        q->tail = make;
        q->head = make;
    }
    else {
        q->tail->next = make; //q가 존재할 때는, make가 tail 뒷 노드에 위치하도록 하고, tail을 make로 만든다.
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
   
    node* make = malloc(sizeof(node)); //make라는 노드를 만들어서 tok할당 next 초기화
    make->tok = tok;
    make->next = NULL;
    if (q->len == 0)
    {
        q->head = make; 
}
    else
        make->next = q->head; //make의 next를 원래의 첫번째 노드로 할당하고
        q->head = make;  //첫번째 노드를 make로 설정한다.
    q->len += 1; //q len를 하나 증가시킴.

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
    case '*' : //input이 곱셈또는 나눗셈 연산자이면 2
        ret = 2;
        break;
    case '/':
        ret = 2;
        break;
    case '+' : //input이 덧셈또는 뺄셈 연산자이면 1
        ret = 1;
        break;
    case '-':
        ret = 1;
        break;
    default: //나머지는 0, 자료형이 char이지만 숫자로 표현된 값이라면 0이 반환된다.
        ret = 0;

    }
    return ret;
}


void infix_to_postfix(char* postfix, char* infix) {

  int eq_len = strlen(infix);
  bucket *st = init();
  int num = 0;
  int brak = 0;
  for (int idx = 0; idx < eq_len; idx++) //infix를 순서대로 확인하며 처리
  {
      
      if (compare(infix[idx])==0) //입력값이 숫자라면 postfix에 입력
      {
          strcat_wrap(postfix, infix[idx]);
      }
      else
      { //숫자가 아니라면
          if (st->len == 0) //st이 비어있으면, operator를 stack에 넣음
          {
              push(st, infix[idx]);
          }
          else //stack이 안 비어있으면, stacknode를 stack의 head 포인터로 할당함.
          {
              
              for (int stidx = st->len; stidx > 0; stidx--)
              {
                  if (compare(infix[idx]) > compare(st->head->tok)) //새로운 operator의 우선순위가 높으면 for문을 탈출하여 stack에 operator 넣음.
                  {                 
                      break;
                  }
                  else {    //새로운 operator의 우선순위가 낮으면 우선 순위가 더 낮은 애가 나올 때까지, tail값을 빼고 postfix에 넣음.
                      strcat_wrap(postfix, pop(st));
                  }
                  
              }
              push(st, infix[idx]); //새로운 operator를 stack에 넣음
          }

      } 

      
  }
  
  for (int stidx = st->len; stidx > 0; stidx--) //for 문이 끝나면 stack에 남은 연산자를 모두 출력
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