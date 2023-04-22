#include <stdio.h> 
#include <stdlib.h> 
#include "Operations.h"
#include "LinkedList.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "./infix.h"

int isnumeric(char s){

  if (s - '0' >= 0 && s - '0' <= 9){
    return 1;
  }
  return 0;
}


Number **L;

int main(){

  printf("bc 1.0\n");
  printf("Copyright 2023 COEP's Free Software Foundation ");
  printf("\nThis is free software with ABSOLUTELY NO WARRANTY.\n");


  while(1){
    List operators = (List) malloc(sizeof(Node));
    operators->data = INT_MIN;
    char* input;
    size_t size;
    int len;
    int i;
    int c;
    int index;
    List temp;
    input = NULL;
    size = 0;

    getline(&input, &size, stdin);
    if (!strcmp(input, "quit\n") )
      exit(0);
    len = strlen(input);
    i = 0;
    c = 1;
    RemoveSpaces(input);
    while(input[i] != '\0'){
      if (!isnumeric(input[i])){
        c++;
      }
      i++;
    }

    char infix[c*3];
    i = 0;
    L = (Number **) malloc(sizeof(Number *)*(c*4));
    index = 0;

    initNumber(&L[0]);
    temp = L[0]->numbers;

    if((input[0] == '+') || (input[0] == '-')){
      L[0]->sign = input[0];
      i++;
    } else{
      L[0]->sign = '+';
    }

    while(input[i]=='0'){i++;

      if(!isnumeric(input[i])){
        i--;
        break;
      }
    }
    c = 0;

    while(input[i] != '\n'){
      if(isnumeric(input[i])){
        pushf(&L[index]->numbers, input[i] - '0');
        L[index]->count ++;

      } else if (input[i] == '('){
        push(&operators, input[i]);
        if (input[i+1] == '+' || input[i+1] == '-' ){
          if(L[index]->sign == input[i+1])
            L[index]->sign = '+';
          else
            L[index]->sign = '-';
          i++;
        }

        while(input[i+1]=='0'){i++;}

      } else if (input[i] == ')'){
        push(&operators, '0'+c++);
        while(input[i] == ')'){
          push(&operators, input[i]);
          i++;
        }
        i--;
      } else{
        if (input[i-1] != ')'){
          push(&operators, '0'+c);
          c++;
        }
        push(&operators, input[i]);

        index++;

        initNumber(&L[index]);
        temp = L[index]->numbers;

        if((input[i+1] == '+') || (input[i+1] == '-') ){
          L[index]->sign = input[i+1];
          i++;
        } 

        while(input[i+1]=='0'){i++;}
        if(!isnumeric(input[i+1]) && input[i+1] != '(')
          i--;

      }
      i++;
    }

    if(input[i-1] != ')'){
      push(&operators, '0'+c);
    }

    i = 0;

    while(operators->next != NULL){
      infix[i] = operators->data;
      operators = operators->next;
      i++;
    }
    infix[i] = operators->data;
    infix[++i] = '\n';


    char postfix[250];

    infix_to_postfix(infix, postfix);


    int rest = eval_postfix(postfix, L);
    if( (L[rest]->sign != '+' ) && !(L[rest]->numbers->data == 0 && L[rest]->count == 1)){
      printf("%c", L[rest]->sign);
    }
    displayList(&L[rest]->numbers);

  }
}
