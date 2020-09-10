#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);
int multiply(const char* number1, const char* number2, char** result);
int validate(const char *number);
int compare(const char* number1, const char* number2);
char* reverse(const char * number);
char conv(int n);
int get_value(char c);
int trim(char* number);
int validate_expression(const char *expr);
int is_one_of(const char c, char* src);
int calculate(const char* expr, char **result);

int main(void){
  char *res;
  int error;

  char *expr=(char*)malloc(sizeof(char)*501);
  if(expr==NULL){
    printf("Failed to allocate memory");
    return 8;
  }
  printf("Podaj pierwsza rownanie: ");
  scanf("%500s", expr);
  while(getchar() != '\n');
  if(validate_expression(expr)!=0){
    printf("Incorrect input");
    free(expr);
    return 1;
  }
  error=calculate(expr, &res);
  if(error==3){
    printf("Failed to allocate memory");
    free(expr);
    return 8;
  }
  printf("%s", res);
  free(res);
  free(expr);
  return 0;
}

int trim(char* number){
if(number!=NULL){
  for(int i=(int)strlen(number)-1; i>0 ; i--){
    if(get_value(*(number+i)) == 0) *(number+i)='\0';
    else break;
  }
}
return 0;
}

char conv(int n){
  return '0'+n;
}

int subtract(const char* number1, const char* number2, char** result){
if(!number1 || !number2 || !result)
  return 1;

if(validate(number1)!=0 || validate(number2)!=0)
  return 2;
char *num1, *num2;
int neg=0;
int size;
size=(int)strlen(number1)>(int)strlen(number2)?(int)strlen(number1):(int)strlen(number2);
if(*number1=='-' && *number2!='-'){
  add(number1+1, number2, result);
  if(!*result)
    return 3;
  int len=(int)strlen(*result);
  *result=(char*)realloc(*result, sizeof(char)*(len+2));
  if(!(*result)) return 3;
  *result=reverse(*result);
  *(*result+len)='-';
  *(*result+len+1)='\0';
  *result=reverse(*result);
  return 0;
}
else if(*number2=='-' && *number1!='-'){
  return add(number1, number2+1, result);
}
else if(*number1=='-' && *number2=='-'){
  return add(number1, number2+1, result);;
}
else if(compare(number1,number2)==-1){
  num1=(char*)number2;
  num2=(char*)number1;
  neg=1;
}
else{
  num1=(char*)number1;
  num2=(char*)number2;
}
*result=(char*)malloc(sizeof(char)*(size+2));
if(!*result)
  return 3;
int temp, res=0, l1=(int)strlen(num1), l2=(int)strlen(num2);
for (int i=0; i<l2; i++){
      temp=get_value(*(num1+l1-1-i))-get_value(*(num2+l2-1-i))-res;
      if (temp<0){
          temp=temp+10;
          res=1;
      }
      else
          res=0;
      sprintf(*result+i, "%d", temp);
  }
  for (int i=l2; i<l1; i++){
      temp=get_value(*(num1+l1-1-i))-res;
      if (temp < 0){
          temp=temp+10;
          res=1;
      }
      else
          res=0;
      sprintf(*result+i, "%d", temp);
  }
trim(*result);
if(neg!=0){
  sprintf(*result+strlen(*result), "%c", '-');
}
*result=reverse(*result);
return 0;
}

int add(const char* number1, const char* number2, char** result){
if(!number1 || !number2 || !result)
  return 1;

if(validate(number1)!=0 || validate(number2)!=0)
  return 2;
int neg=0;
char *num1, *num2;
  int size;
  size=(int)strlen(number1)>(int)strlen(number2)?(int)strlen(number1):(int)strlen(number2);
if(*number1=='-' && *number2!='-'){
  return subtract(number2, number1+1, result);
}
else if(*number2=='-' && *number1!='-'){
  return subtract(number1, number2+1, result);
}
else if(*number1=='-' && *number2=='-'){
  num1=(char*)(number1+1);
  num2=(char*)(number2+1);
  neg=1;
}
else{
  num1=(char*)number1;
  num2=(char*)number2;
}
*result=(char*)malloc(sizeof(char)*(size+2));
if(!*result)
  return 3;
int temp, res=0, i=0, l1=(int)strlen(num1), l2=(int)strlen(num2);
while(1){
  temp=0;
  if(i<l1 && i<l2){
    temp=get_value(*(num1+l1-1-i))+get_value(*(num2+l2-1-i))+res;
  }
  else if(i<l2){
    temp=get_value(*(num2+l2-1-i))+res;
  }
  else if(i<l1){
    temp=get_value(*(num1+l1-1-i))+res;
  }
  if(temp>=10){
    res=temp/10;
    sprintf(*result+i, "%d", temp%10);
  }
  else if(i>=(l1<l2 ? l2 : l1)){
      if(temp!=0){
        sprintf(*result+i, "%d", temp);
      }
      if(res!=0){
        sprintf(*result+i, "%d", res);
      }
        i++;
        break;
    }
    else{
      res=0;
      sprintf(*result+i, "%d", temp);
    }
    i++;
  }
  if(neg!=0) sprintf(*result+strlen(*result), "%c", '-');
  *result=reverse(*result);
  return 0;
}
char* reverse(const char * number){
  if(!number) return NULL;

  int len=(int)strlen(number);
  char *n=(char*)number;
  for(int i=0; i<len/2; i++){
    char buff=*(n+len-1-i);
    *(n+len-1-i)=*(n+i);
    *(n+i)=buff;
  }
  return n;
}

int get_value(char c){
  return !c ? 0 : c-'0';
}

int validate(const char * number){
  if(!number) return -1;
  if((int)strlen(number)<1)
    return 2;
  int neg=0;
  if(*number=='0' && (int)strlen(number)>1)
    return 2;
  if(*number=='-' && (int)strlen(number)<2)
    return 2;
  else if(*number=='-')
    neg=1;
  for(int i=neg ? 1 : 0; i<(int)strlen(number); i++){
    if(*(number+i)<'0' || *(number+i)>'9')
      return 2;
  }
  return 0;
}

int compare(const char* number1, const char* number2){
  if(!number1 || !number2)
    return 2;

  if(validate(number1)!=0 || validate(number2)!=0)
    return 3;
  int l1,l2;
  l1=(int)strlen(number1);
  l2=(int)strlen(number2);
  if(*number1=='-' && *number2=='-'){
    if(l1>l2) return -1;
    if (l1<l2) return 1;
    for (int i=0; i<l1; i++) {
      if (*(number1+i)>*(number2+i)) return -1;
      else if (*(number1+i) < *(number2+i)) return 1;
    }
  }
  else if(*number1=='-' && *number2!='-')
    return -1;
  else if(*number1 != '-' && *number2 == '-')
    return 1;
  else{
    if(l1<l2)
    return -1;
    if (l1>l2)
      return 1;
    for(int i=0; i<l1; i++) {
      if(*(number1+i)<*(number2+i))
          return -1;
      else if(*(number1+i)>*(number2+i))
          return 1;
    }
  }
    return 0;
}

int multiply(const char* number1, const char* number2, char** result){
  if(!number1 || !number2 || !result)
  return 1;

  if(validate(number1)!=0 || validate(number2)!=0)
    return 2;
  int neg=0;
  char *num1, *num2;
  if(*number1=='-' && *number2!='-'){
    neg=1;
  }
  else if(*number2=='-' && *number1!='-'){
    neg=1;
  }
  else if(*number1=='-' && *number2=='-'){
    neg=0;
  }
  *result=(char*)calloc(sizeof(char),((int)strlen(number1) + (int)strlen(number2)+2));
  if(!*result)
    return 3;
  if(*number1=='0' ||*number2=='0'){
    **result='0';
    *(*result+1)='\0';
    return 0;
  }
  int l1,l2;
  l1 =*number1=='-' ? (int)strlen(number1)-1 : (int)strlen(number1);
  l2 =*number2=='-' ? (int)strlen(number2)-1 : (int)strlen(number2);
  num1=(char*)(*number1=='-' ? number1+1 : number1);
  num2=(char*)(*number2=='-' ? number2+1 : number2);
  int num1_p=0;
  int num2_p=0;
  **result=conv(0);
  for(int i=l1-1; i>=0 ; i--){
    int next=0;
    int val1=get_value(*(num1+i));
    num2_p=0;
    for(int j=l2-1; j>= 0; j--){
      int val2=get_value(*(num2+j));
      int prev=get_value(*(*result+num2_p+num1_p));
      int sum=val1*val2+prev+next;
      next=sum/10;
      *(*result+num1_p+ num2_p)=conv(sum%10);
      num2_p++;
    }
    if (next>0){
      *(*result+num1_p+num2_p)=conv(next);
    }
    num1_p++;
  }
  if(neg!=0){
    *(*result+strlen(*result))='-';
    *(*result+strlen(*result)+1)='\0';
  }
  else *(*result+strlen(*result))='\0';
  *result=reverse(*result);
  return 0;
}

int is_one_of(const char c, char* src){
  if(!src)
    return 0;

  for(int i=0; i<(int)strlen(src); i++){
    if(*(src+i)==c)
      return 1;
  }
  return 0;
}

int validate_expression(const char *expr){
  if(!expr)
    return 2;
  if(!isdigit(*expr) && *expr!='-')
    return 1;

  if(strlen(expr)>1 && *expr=='-' && !isdigit(*(expr+1)))
    return 1;
  for(int i=0; i<(int)strlen(expr); i++){
    if((is_one_of(*(expr+i), "*-+") && !isdigit(*(expr+i+1)) && *(expr+i+1)!='-') ||
      (!isdigit(*(expr+i)) && !is_one_of(*(expr+i), "*-+"))
    )
      return 1;
  }
  return 0;
}

int calculate(const char* expr, char **result){
  if(!expr || !result)
    return 1;

  if(validate_expression(expr)!=0)
    return 2;
  *result=(char*)malloc(sizeof(char)*(strlen(expr)+1));
  if(!*result)
    return 3;
  int end=0;
  char* sign=strpbrk(expr+1, "+-*");
  char sign_v;

  if(sign!=NULL){
    sign_v=*sign;

    int number_len=(int)(sign-expr);
    char* number=(char*)malloc(sizeof(char)*(number_len+1));
    strncpy(number, expr, number_len);
    *(number+number_len)='\0';
    strcpy(*result, number);
    *(*result+number_len)='\0';
    end+=number_len+1;
    free(number);
  }
  else{
    strcpy(*result, expr);
    *(*result+strlen(expr))='\0';
  }
  while(sign!=NULL){
    if(*(sign+1)=='-')
      sign=strpbrk(sign+2, "+-*");
    else
      sign=strpbrk(sign+1, "+-*");
    char* number;
    if(sign!=NULL){
      int number_len=(int)(sign-(expr+end));
      number=(char*)malloc(sizeof(char)*(number_len+1));
      strncpy(number, expr+end, number_len);
      *(number+number_len) = '\0';
      end+=number_len+1;
    }
    else{
      int number_len=(int)strlen(expr+end);
      number=(char*)malloc(sizeof(char)*(number_len+1));
      strncpy(number, expr+end, number_len);
      *(number+number_len)='\0';
      end+=number_len+1;
    }
    char* new_result;
    switch(sign_v){
         case '+':
          add(*result, number, &new_result);
          break;
         case '*':
          multiply(*result, number, &new_result);
          break;
         case '-':
          subtract(*result, number, &new_result);
          break;
      }
    if(*new_result!=0){
      free(*result);
      *result=new_result;
    }
    free(number);
    if(sign!=NULL){
      sign_v=*sign;
    }
  }
  return 0;
}

