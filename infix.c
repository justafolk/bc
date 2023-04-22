
#include <ctype.h>
#include <stdio.h>
#include "./LinkedList.h"
#include "./Operations.h"

char s[250];
int top = -1; 

void RemoveSpaces(char* source) {
  char* i = source;
  char* j = source;
  while(*j != 0) {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}

void pushStack(char elem) { 
  s[++top] = elem;
}

char popStack() { 
  return (s[top--]);
}

int pr(char elem) { 
  switch (elem) {
    case '#':
      return 0;
    case '(':
      return 1;
    case '+':
    case '-':
      return 2;
    case '*':
    case '/':
    case '%':
      return 3;
  }
}

void infix_to_postfix(char *infix, char *postfix) {
  char ch, elem;
  int i = 0, k = 0;

  RemoveSpaces(infix);
  pushStack('#');

  while ((ch = infix[i++]) != '\n') {
    if (ch == '(')
      pushStack(ch);
    else if (isalnum(ch))
        postfix[k++] = ch;
      else if (ch == ')') {
          while (s[top] != '(')
            postfix[k++] = popStack();
          elem = popStack(); 
        } else { 
          while (pr(s[top]) >= pr(ch))
            postfix[k++] = popStack();
          pushStack(ch);
        }
  }

  while (s[top] != '#') 
    postfix[k++] = popStack();

  postfix[k] = 0; 
}



void solve(int op1, int op2, char ch, Number **L){
  switch(ch) {
    case '+' : 
      pushStack(addLists(L, op1, op2, L[op1]->sign));
      break;
    case '-' : 
      if (L[op1]->count > L[op2]->count ) {
        pushStack(subLists(L, op1, op2, L[op1]->sign));

      } 
      else if (L[op1]->count < L[op2]->count ) {
        pushStack(subLists(L, op2, op1, '-'));

      } else{
        if(isGreater(L[op1], L[op2] )){
          pushStack(subLists(L, op1, op2, L[op1]->sign));
        } else{
          pushStack(subLists(L, op2, op1, '-'));
        }
      }

      break;
    case '*' : 
      if (L[op1]->sign == L[op2]->sign)
        pushStack(mulLists(L, op1, op2,'+'));
      else
        pushStack(mulLists(L, op1, op2, '-'));
      break;
    case '/' : 
      if ( ( (L[op1]->count == L[op2]->count) && isGreater(L[op2], L[op1])) || L[op1]->count < L[op2]->count){

        L[op1]->count = 1;
        L[op1]->numbers->data = 0;
        L[op1]->numbers->next = NULL;
        pushStack(op1);
        break;
      }
      if (L[op1]->sign == L[op2]->sign)
        pushStack(divLists(L, op1, op2,'+'));
      else
        pushStack(divLists(L, op1, op2, '-'));
      break;
    case '%':
      if (L[op1]->sign == L[op2]->sign)
        pushStack(modLists(L, op1, op2,'+'));
      else
        pushStack(modLists(L, op1, op2, '-'));
      break;
 //  case '^':
 //    if (L[op1]->sign == L[op2]->sign)
 //      pushStack(expoLists(L, op1, op2,'+'));
 //    else
 //      pushStack(expoLists(L, op1, op2, '-'));
 //    break;
  }


}

int eval_postfix(char *postfix, Number **L) {
  char ch;
  int i = 0, op1, op2;
  while((ch = postfix[i++]) != 0) {
    if(isdigit(ch)) 
      pushStack(ch-'0'); 
    else {        
        op2 = popStack();
        op1 = popStack();

        if((ch == '+') && (L[op1]->sign == L[op2]->sign )){
          solve(op1, op2, '+', L);
        } else if((ch == '+') && (L[op1]->sign != L[op2]->sign) ){
            if (L[op1]->sign == '-')
              solve(op2, op1, '-', L);
            else  
              solve(op1, op2, '-', L);

        } else if((ch == '-') && (L[op1]->sign !=  L[op2]->sign )){
          solve(op1, op2, '+', L);
        } else {
          solve(op1, op2, ch, L);
        }

      }
  }

  reverse(&L[s[top]]->numbers);
  return s[top];
}

