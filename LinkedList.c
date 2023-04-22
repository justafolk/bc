#include <stdio.h> 
#include <stdlib.h> 
#include "./Operations.h"
#include "./LinkedList.h"
#include <limits.h>

void push(List *L, int data){

  List temp = *L;
  if (temp->data == INT_MIN){
    temp->data = data;
    temp->next = NULL;
    return;

  }

  Node *newNode = (Node *) malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;

  while(temp->next != NULL){
    temp = temp->next;
  }

  temp->next = newNode;

}

void initNumber(Number **N){
  *N = (Number *) malloc(sizeof(Number ));
  (*N)->numbers = (Node *) malloc(sizeof(Node));
  (*N)->numbers = NULL;
  (*N)->count = 0;
  (*N)->sign = '+';

}
void pushf(List *L, int data){


  Node *newNode = (Node *) malloc(sizeof(Node));
  newNode->data = data;

  if(!(*L)){
    newNode->next = NULL;
    *L = newNode;
    return;
  }
  newNode->next = *L;
  *L = newNode;


}

void displayNumbers(Number **L, int len){
  int i = 0;

  while(i < len){
    printf("\nnumber %d: %c", i+1, L[i]->sign );
    displayList(&L[i]->numbers);
    i++;

  }
}

void displayListc(List *L){

  List temp = *L;

  printf("\n");

  while(temp != NULL){

    printf("%c",temp->data );
    temp = temp->next;
  }
  printf("\n");

}
void displayList(List *L){

  List temp = *L;


  while(temp != NULL){

    printf("%d",temp->data );
    temp = temp->next;
  }
  printf("\n");

}


int pop(List *L){
  List temp = *L;
  int det;

  while(temp->next->next != NULL){
    temp = temp->next;
  }
  det = temp->next->data;
  free(temp->next);
  temp->next = NULL;
  return det;
}

void reverse(List* head_ref)
{
  List prev = NULL;
  List current = *head_ref;
  List next = NULL;
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *head_ref = prev;
}



void displayLists(Lists **L){

  Lists *t = *L;
  List temp;
  while(t != NULL){

    temp = t->list;

    printf("\n");

    while(temp != NULL){

      printf("%d",temp->data );
      temp = temp->next;
    }
    printf("\n");
    t = t->next;
  }

}

int isGreater(Number *L1s, Number *L2s){

  Number *L1 = L1s;
  Number *L2 = L2s;

  reverse(&L1->numbers);
  reverse(&L2->numbers);

  Node *temp1 = L1->numbers;
  Node *temp2 = L2->numbers;


  while(temp1->next && temp2->next){
    if (temp1->data > temp2->data){
      reverse(&L1->numbers);
      reverse(&L2->numbers);
      return 1;
    }
    else if (temp1->data < temp2->data){
      reverse(&L1->numbers);
      reverse(&L2->numbers);
      return 0;
    }

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

      reverse(&L1->numbers);
      reverse(&L2->numbers);
  if (temp1->data > temp2->data)
    return 1;
  else 
    return 0;

  return -1;
}

