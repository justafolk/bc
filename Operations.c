#include <stdio.h> 
#include <stdlib.h> 
#include "./LinkedList.h"
#include <limits.h>

int addLists(Number **L, int L1, int L2, char sign){


  List temp1 = L[L1]->numbers;
  List temp2 = L[L2]->numbers;

  Number *ret = (Number *) malloc(sizeof(Number));
  ret->numbers = (Node *) malloc(sizeof(Node));

  ret->numbers->data = INT_MIN;
  ret->numbers->next = 0;
  ret->sign = sign;
  ret->count = 0;

  int sum = 0;
  int carry = 0;

  while(temp1 != NULL && temp2 != NULL){
    sum = temp1->data + temp2->data + carry;
    push(&ret->numbers, sum%10);
    carry = sum / 10;
    ret->count++;

    temp1 = temp1->next;
    temp2 = temp2->next;

  }

  while(temp1 != NULL ){
    sum = temp1->data + carry;
    push(&ret->numbers, sum%10);
    carry = sum / 10;

    ret->count++;
    temp1 = temp1->next;
  }
  while(temp2 != NULL ){
    sum = temp2->data + carry;
    push(&ret->numbers, sum%10);
    carry = sum / 10;
    ret->count++;

    temp2 = temp2->next;
  }
  if( carry > 0){
    ret->count++;
    push(&ret->numbers, carry);
  }

  L[L2] = ret;

  return L2;
}

int subLists(Number **L, int L1, int L2, char sign){
  List temp1 = L[L1]->numbers;
  List temp2 = L[L2]->numbers;

  Number *ret = (Number *) malloc(sizeof(Number));
  ret->numbers = (Node *) malloc(sizeof(Node));

  ret->numbers->data = INT_MIN;
  ret->numbers->next = NULL;
  ret->sign = sign;
  ret->count = 0;

  int sum = 0;
  int carry = 0;
  int borrow = 0;

  while(temp1 != NULL && temp2 != NULL){

    if(temp1->data < temp2->data){
      sum = (((temp1->data+10)-borrow) + carry ) - temp2->data;
      borrow = 1;
    }
  else if (temp1->data == temp2->data && borrow){
      sum = (((temp1->data+10)-borrow) + carry ) - temp2->data;
      borrow = 1;

    }
  else{
      sum = (((temp1->data)-borrow) + carry ) - temp2->data;
      borrow = 0;
    }
    push(&ret->numbers, sum%10);
    carry = sum / 10;

    ret->count++;

    temp1 = temp1->next;
    temp2 = temp2->next;

  }

  while(temp1 != NULL ){
    if(temp1->data < borrow){
      sum =((temp1->data+10)-borrow)+carry;
      borrow = 1;
    } else{
      sum =((temp1->data)-borrow)+carry;
      borrow = 0;
    }
    push(&ret->numbers, sum%10);
    carry = sum / 10;

    ret->count++;
    temp1 = temp1->next;
  }

  while(temp2 != NULL ){

    if(temp2->data < borrow){
      sum = ((temp2->data+10)-borrow) + carry;
      borrow = 1;
    } else{
      sum = ((temp2->data)-borrow) + carry;
      borrow = 0;
    }
    push(&ret->numbers, sum%10);
    carry = sum / 10;
    ret->count++;

    temp2 = temp2->next;
    borrow = 1;
  }
  if( carry > 0){
    ret->count++;

    push(&ret->numbers, carry);
  }

  reverse(&ret->numbers);

  while(ret->numbers->next && ret->numbers->data == 0){

    ret->numbers = ret->numbers->next;
    ret->count--;
  }

  reverse(&ret->numbers);

  if(borrow)
    ret->sign = '-';

  L[L1] = ret;

  return L1;

}

void mulscalarList(Number *L, int num, Number **N){
  Node *sums = (*N)->numbers;
  Node *temp = L->numbers;
  int mul = 1;
  int carry = 0;
  (*N)->count = 0;

  while(temp){
    mul = (temp->data * num )+ carry;
    push(&sums, mul%10);

    carry = mul / 10;
    temp = temp->next;
    (*N)->count++;
  }

  while(carry){
    push(&(*N)->numbers, carry%10);
    carry = carry / 10;
    (*N)->count++;
  }

}



int mulLists(Number **L, int L1, int L2, char sign){


  Number *temp1 = L[L1];
  List temp2 = L[L2]->numbers;

  int inter = 0;
  int count = 0;

  Number *res = (Number *) malloc(sizeof(Number));
  res->numbers = NULL;
  pushf(&res->numbers, 0);

  res->count = 0;

  pushf(&res->numbers, 0);
  Node *templist = NULL;

  L[L1]= (Number *) malloc(sizeof(Number));
  L[L1]->count = 0;

  L[L2] = res;
  int k, i;
  i = 0;
  while(temp2){
    L[L1]->numbers = NULL;
    pushf(&L[L1]->numbers, 0);
    mulscalarList(temp1, temp2->data, &L[L1]);
    temp2 = temp2->next;
    k = 0;
    while(k<i){
      pushf(&(L[L1]->numbers), 0);
      k++;
    }
    i++;
    L[L2] = L[addLists(L, L1, L2, '+')];

  }
  L[L2]->numbers = L[L2]->numbers->next;
  L[L2]->sign = sign;

  return L2;

}


int divLists(Number **L, int L1, int L2, char sign){
  Number *temp1 = L[L1];
  Number *temp2 = L[L2];

  Node *temp1L = L[L1]->numbers;
  Node *temp2L = L[L2]->numbers;

  if (L[L2]->count == 1 && L[L2]->numbers->data == 0){
    int a = 0;
    printf("Zero Divide?");
    exit(1);
  }

  int topflag = -1;

  Number *dividend = (Number *) malloc(sizeof(Number));
  Number *res = (Number *) malloc(sizeof(Number));
  Node *divider = NULL;

  dividend->count = 0;
  dividend->numbers = NULL;


  reverse(&temp1L);
  reverse(&temp2L);

  L[L2]->numbers = temp2L;
  while(temp2L){
    pushf(&divider, temp2L->data);
    temp2L = temp2L->next;
  }

  Node *revtemp2L = L[L2]->numbers;
  temp2L = L[L2]->numbers; 
  int count = 0;
  int freepass = L[L2]->count+1;

  L[L2]->numbers = divider;

  res->numbers = NULL;
  res->sign = sign;
  res->count = 0;


  while (!(temp1->count == 1 && temp1L->data == 0) ){
    dividend->numbers = NULL;
    topflag = -1;

    if(!(temp2L && temp1L))
      break;

    while(temp2L && temp1L){
      if((topflag == -1 && temp1L->data < temp2L->data) )
         topflag = 0;
      if((topflag == -1 && temp1L->data > temp2L->data) )
        topflag = 1;

      pushf(&dividend->numbers, temp1L->data);
      dividend->count++;
      temp1L = temp1L->next;
      temp2L = temp2L->next;
      freepass--;
    }

    if (topflag == 0){
      dividend->count++;
      if (!temp1L){
        pushf(&res->numbers, 0);
        break;
      }
      freepass--;
      pushf(&dividend->numbers, temp1L->data);
      temp1L = temp1L->next; 
    }

    while (freepass < 0){
      pushf(&res->numbers, 0);
      res->count++;
      freepass++;
    }

    count = 0;

    L[L1]= dividend;
    topflag = 0;

    while( L[subLists(L, L1, L2, '+')]->sign != '-' ){
      divider = L[L1]->numbers;
      freepass = L[L1]->count+1;
      if (divider->data == 0 && !divider->next){
        topflag = 1;
      }
      count++;
    }

    while(count ){
      pushf(&res->numbers, count%10);
      res->count++;
      count = count / 10;
    }

    if((topflag == 1 && !temp1L) || !temp1L){
      break;
    }

    L[L1]->numbers = divider;

    if (topflag){
      L[L1]->numbers = temp1L;
      freepass = 1;

    } else{
      reverse(&L[L1]->numbers);
      divider = L[L1]->numbers;

      while(divider->next != NULL){
        divider = divider->next;
      }
      divider->next = temp1L;
    }
    temp1L = L[L1]->numbers;

    temp2L = revtemp2L;
  }

  L[L1] = res;
  return L1;
}


int modLists(Number **L, int L1, int L2, char sign){
  Number *temp1 = L[L1];
  Number *temp2 = L[L2];

  Node *temp1L = L[L1]->numbers;
  Node *temp2L = L[L2]->numbers;

  if (L[L2]->count == 1 && L[L2]->numbers->data == 0){
    int a = 0;
    printf("Zero Divide?");
    exit(1);
  }

  int topflag = -1;

  Number *dividend = (Number *) malloc(sizeof(Number));
  Number *res = (Number *) malloc(sizeof(Number));
  Node *divider = NULL;

  dividend->count = 0;
  dividend->numbers = NULL;


  reverse(&temp1L);
  reverse(&temp2L);

  L[L2]->numbers = temp2L;
  while(temp2L){
    pushf(&divider, temp2L->data);
    temp2L = temp2L->next;
  }

  Node *revtemp2L = L[L2]->numbers;
  temp2L = L[L2]->numbers; 
  int count = 0;
  int freepass = L[L2]->count+1;

  L[L2]->numbers = divider;

  res->numbers = NULL;
  res->sign = sign;
  res->count = 0;


  while (!(temp1->count == 1 && temp1L->data == 0) ){
    dividend->numbers = NULL;
    topflag = -1;

    if(!(temp2L && temp1L))
      break;
    while(temp2L && temp1L){
      if((temp1L->data < temp2L->data) && topflag == -1)
        topflag = 0;
      if((temp1L->data > temp2L->data) && topflag == -1)
        topflag = 1;

      pushf(&dividend->numbers, temp1L->data);
      dividend->count++;
      temp1L = temp1L->next;
      temp2L = temp2L->next;
      freepass--;
    }

    if (topflag == 0){
      dividend->count++;
      if (!temp1L){
        pushf(&res->numbers, 0);
        break;
      }
      freepass--;
      pushf(&dividend->numbers, temp1L->data);
      temp1L = temp1L->next; 
    }

    while (freepass < 0){
      pushf(&res->numbers, 0);
      res->count++;
      freepass++;
    }

    count = 0;

    L[L1]= dividend;
    topflag = 0;

    divider = L[L1]->numbers;
    while( L[subLists(L, L1, L2, '+')]->sign != '-' ){

      divider = L[L1]->numbers;

      freepass = L[L1]->count+1;

      if (divider->data == 0 && !divider->next){
        topflag = 1;
      }

      count++;
    }

    if (count == 0 && !temp1L){
      break;
    }


    while(count ){
      pushf(&res->numbers, count%10);
      res->count++;
      count = count / 10;
    }

    if((topflag == 1 && !temp1L) || !temp1L){
      break;
    }

    L[L1]->numbers = divider;

    if (topflag){
      L[L1]->numbers = temp1L;
      freepass = 1;

    }else{

      reverse(&L[L1]->numbers);
      divider = L[L1]->numbers;

      while(divider->next != NULL){
        divider = divider->next;
      }
      divider->next = temp1L;
    }
    temp1L = L[L1]->numbers;

    temp2L = revtemp2L;
  }

  L[L1]->numbers = divider;
  L[L1]->sign = sign;
  return L1;
}


