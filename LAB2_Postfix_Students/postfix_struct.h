typedef struct _read {
  int num; // number of infix equations
  char **infix_eqs;
  char **postfix_eqs;
} read_info;

typedef struct _node {
  char tok;
  struct _node *next;
} node;

typedef struct _bucket {
  int len;
  struct _node *head;
  struct _node *tail;
} bucket;

typedef struct _postfix_partition {
  bucket *queue;
  bucket *stack;
} postfix_part;