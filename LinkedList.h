typedef struct Node{
  int data;
  struct Node *next;
} Node;

typedef struct Lists{
  Node *list;
  struct Lists *next;
} Lists;

typedef  struct Number{
  char sign;
  Node *numbers;
  int count;
} Number;

typedef Node* List;
void initNumber(Number **N);

void push(List *L, int data);
void pushf(List *L, int data);
void displayList(List *L);
void displayListc(List *L);
int pop(List *L);
void displayNumbers(Number **L, int len);

void reverse(struct Node** head_ref);
void displayLists(Lists **L);

Node* reverseList(Node* head);
int addLists(Number **L, int L1, int L2, char sign);

int subLists(Number **L, int L1, int L2, char sign);

int isGreater(Number *L1, Number *L2);

int mulLists(Number **L, int L1, int L2, char sign);
int expoLists(Number **L, int L1, int L2, char sign);
void mulscalarList(Number *L, int num, Number **N);
int divLists(Number **L, int L1, int L2, char sign);
int modLists(Number **L, int L1, int L2, char sign);
