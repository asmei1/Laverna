#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int trim(char* number){

if(number){

  //Doesn't check cipher at least position 
  for(int i = (int)strlen(number)-1; i > 0 ; i--){
    if(get_value(*(number+i)) == 0) *(number+i) = '\0';
    else break;
  }
}

return 0;
}

char int_to_char(int n){ //convert single cipher [0-9] to char
  return '0'+n;
}

int subtract(const char* number1, const char* number2, char** result){

if(!number1 || !number2 || !result)
  return 1;

if(!!validate(number1) || !!validate(number2))
  return 2;

char *n1, *n2;
int is_negative = 0;

int size = (int)strlen(number1) > (int)strlen(number2) ? (int)strlen(number1) : (int)strlen(number2);

if(*number1 == '-' && *number2 != '-'){
  add(number1+1, number2, result);

  if(!*result)
    return 3;

  int len = (int)strlen(*result);

  if(!(*result = (char*)realloc(*result, sizeof(char)*(len+2))))
    return 3;

  *result = reverse(*result);

  *(*result+len) = '-';
  *(*result+len+1) = '\0';

  *result = reverse(*result); 

  return 0;
}
else if(*number2 == '-' && *number1 != '-'){
  return add(number1, number2+1, result);
}
else if(*number1 == '-' && *number2 == '-'){
  return add(number1, number2+1, result);;
}
else if(compare(number1, number2) == -1){
  n1 = (char*)number2;
  n2 = (char*)number1;
  is_negative = 1;
}
else{
  
  n1 = (char*)number1;
  n2 = (char*)number2;
}

*result = (char*)malloc(sizeof(char)*(size+2));

if(!*result)
  return 3;

int current,
    next = 0,
    l1 = (int)strlen(n1),
    l2 = (int)strlen(n2);

for (int i = 0; i < l2; i++)  { 

      current = get_value(*(n1+l1-1-i))-get_value(*(n2+l2-1-i))- next; 
        
      if (current < 0){ 
          current = current + 10; 
          next = 1; 
      } 
      else
          next = 0; 

      sprintf(*result+i, "%d", current); 
  } 

  for (int i = l2; i < l1; i++) { 
      current = get_value(*(n1+l1-1-i)) - next; 
        
      if (current < 0){ 
          current = current + 10; 
          next = 1; 
      } 
      else
          next = 0; 

      sprintf(*result+i, "%d", current); 
  } 

trim(*result);

if(is_negative){
  sprintf(*result+strlen(*result), "%c", '-');
}

*result = reverse(*result);

return 0;
}

int add(const char* number1, const char* number2, char** result){

if(!number1 || !number2 || !result)
  return 1;

if(!!validate(number1) || !!validate(number2))
  return 2;

int negative_res = 0;
char *n1, *n2;

  int size = (int)strlen(number1) > (int)strlen(number2) ? (int)strlen(number1) : (int)strlen(number2);

if(*number1 == '-' && *number2 != '-'){
  return subtract(number2, number1+1, result);
}
else if(*number2 == '-' && *number1 != '-'){
  return subtract(number1, number2+1, result);
}
else if(*number1 == '-' && *number2 == '-'){
  n1 = (char*)(number1+1);
  n2 = (char*)(number2+1);
  negative_res = 1;
}
else{
  n1 = (char*)number1;
  n2 = (char*)number2;
}

*result = (char*)malloc(sizeof(char)*(size+2));

if(!*result)
  return 3;

int current,
    prev = 0,
    i = 0,
    l1 = (int)strlen(n1),
    l2 = (int)strlen(n2);

while(1){
  current = 0;

  if( i < l1 && i < l2){
    current = get_value(*(n1+l1-1-i)) + get_value(*(n2+l2-1-i)) + prev;
  }
  else if(i < l2){
    current = get_value(*(n2+l2-1-i)) + prev;
  }
  else if( i < l1) {
    current = get_value(*(n1+l1-1-i)) + prev;
  }

  if(current >= 10){
    prev = current/10;
    sprintf(*result+i, "%d", current%10);
  }
  else if(i >= (l1 < l2 ? l2 : l1)){

      if(current != 0){
        sprintf(*result+i, "%d", current);
      }

      if(prev != 0){
        sprintf(*result+i, "%d", prev);
      }

        i++;
        break;
    }
    else{
      prev = 0;
      sprintf(*result+i, "%d", current);
    }

    i++;
    
  } 

  if(negative_res)
    sprintf(*result+strlen(*result), "%c", '-');

  *result = reverse(*result);

  return 0;

}
char* reverse(const char * number){

  if(!number) return NULL;

  int len = (int)strlen(number);
  char *n = (char*)number;

  for(int i = 0; i < len/2; i++){
    char buff = *(n+len-1-i);
    *(n+len-1-i) = *(n+i);
    *(n+i) = buff;
  }

  return n;
}

int get_value(char c){
  return !c ? 0 : c - '0';
}

int validate(const char * number){

  if(!number) return -1;

  int is_negative = 0;

  if((int)strlen(number) < 1)
    return 2;

  if(*number == '0' && (int)strlen(number) > 1)
    return 2;
  
  if(*number == '-' && (int)strlen(number) < 2)
    return 2;
  else if(*number == '-')
    is_negative = 1;

  for(int i = is_negative ? 1 : 0; i < (int)strlen(number); i++){
    if(*(number+i) < '0' || *(number+i) > '9')
      return 2;
  }

  return 0;
} 

int compare(const char* number1, const char* number2){
  
  if(!number1 || !number2)
    return 2;

  if(!!validate(number1) || !!validate(number2))
    return 3;

  int l1 = (int)strlen(number1),
      l2 = (int)strlen(number2);

  if(*number1 == '-' && *number2 == '-'){
    if(l1 > l2)
    return -1;

    if (l1 < l2) 
      return 1; 

    for (int i=0; i<l1; i++) {
      if (*(number1+i) > *(number2+i)) 
          return -1; 
      else if (*(number1+i) < *(number2+i)) 
          return 1; 
    }
  }
  else if(*number1 == '-' && *number2 != '-')
    return -1;
  else if(*number1 != '-' && *number2 == '-')
    return 1;
  else{

    if(l1 < l2)
    return -1;

    if (l1 > l2) 
      return 1; 

    for (int i=0; i<l1; i++) {
      if (*(number1+i) < *(number2+i)) 
          return -1; 
      else if (*(number1+i) > *(number2+i)) 
          return 1; 
    }
  }
  
    return 0; 
}

int multiply(const char* number1, const char* number2, char** result){

  if(!number1 || !number2 || !result)
  return 1;

  if(!!validate(number1) || !!validate(number2))
    return 2;

  int negative_res = 0;
  char *n1, *n2;

  if(*number1 == '-' && *number2 != '-'){
    negative_res = 1;
  }
  else if(*number2 == '-' && *number1 != '-'){
    negative_res = 1;
  }
  else if(*number1 == '-' && *number2 == '-'){
    negative_res = 0;
  }

  *result = (char*)calloc(sizeof(char),((int)strlen(number1) + (int)strlen(number2)+2));

  if(!*result)
    return 3;

  if(*number1 == '0' || *number2 == '0'){
    **result = '0';
    *(*result+1) = '\0';
    return 0;
  }

  int l1 = *number1 == '-' ? (int)strlen(number1)-1 : (int)strlen(number1),
      l2 = *number2 == '-' ? (int)strlen(number2)-1 : (int)strlen(number2);

  n1 = (char*)(*number1 == '-' ? number1+1 : number1);
  n2 = (char*)(*number2 == '-' ? number2+1 : number2);

  //Will show current position in result
  int n1_i = 0;  
  int n2_i = 0; 

  **result =  int_to_char(0);

  for(int i = l1-1; i >= 0 ; i--){

    int next = 0; 
    int val1 = get_value(*(n1+i)); 

    n2_i = 0;  

    for(int j = l2-1; j >= 0; j--){
      
      int val2 = get_value(*(n2+j));
      int prev = get_value(*(*result+n2_i+n1_i));

      int sum = val1*val2 + prev + next; 
   
      next = sum/10; 

      // save calculated cipher at current position
      *(*result + n1_i + n2_i) = int_to_char(sum % 10); 

      n2_i++; 
    }

    if (next > 0){
      *(*result + n1_i + n2_i) = int_to_char(next);
    }  

    n1_i++; 
  }

  if(negative_res){
    *(*result+strlen(*result)) = '-';
    *(*result+strlen(*result)+1) = '\0';
  } 
  else
    *(*result+strlen(*result)) = '\0';

  *result = reverse(*result);

  return 0;
}

int is_one_of(const char c, char* src){

  if(!src)
    return 0;

  for(int i = 0; i < (int)strlen(src); i++){
    if(*(src+i) == c)
      return 1;
  }

  return 0;
}

int validate_expression(const char *expr){

  if(!expr)
    return 2;

  if(!isdigit(*expr) && *expr != '-')
    return 1;

  if(strlen(expr) > 1 && *expr == '-' && !isdigit(*(expr+1)))
    return 1;
  
  for(int i = 0; i < (int)strlen(expr); i++){

    
    if((is_one_of(*(expr+i), "*-+") && !isdigit(*(expr+i+1)) && *(expr+i+1) != '-') ||
      (!isdigit(*(expr+i)) && !is_one_of(*(expr+i), "*-+"))
    )
      return 1;
    
  }


  return 0;
}

int calculate(const char* expr, char **result){

  if(!expr || !result)
    return 1;

  if(!!validate_expression(expr))
    return 2;

  *result = (char*)malloc(sizeof(char)*(strlen(expr)+1));

  if(!*result)
    return 3;

  int last_i = 0;
  char* sign = strpbrk(expr+1, "+-*");
  char sign_c;
  
  if(sign){
    sign_c = *sign;
    
    int nr_len = (int)(sign-expr);
    char* number = (char*)malloc(sizeof(char)*(nr_len+1));

    strncpy(number, expr, nr_len);
    *(number+nr_len) = '\0';

    strcpy(*result, number);
    *(*result+nr_len) = '\0';

    last_i += nr_len+1;
    free(number);
  }
  else{
    strcpy(*result, expr);
    *(*result+strlen(expr)) = '\0';
  }
  

  while(sign){

    if(*(sign+1) == '-')
      sign =  strpbrk(sign+2, "+-*");
    else
      sign =  strpbrk(sign+1, "+-*");

    char* number;

    if(sign){
    
      int nr_len = (int)(sign-(expr+last_i));
      number = (char*)malloc(sizeof(char)*(nr_len+1));

      strncpy(number, expr+last_i, nr_len);
      *(number+nr_len) = '\0';

      last_i += nr_len+1;
    }
    else{

      int nr_len = (int)strlen(expr+last_i);
      number = (char*)malloc(sizeof(char)*(nr_len+1));

      strncpy(number, expr+last_i, nr_len);
      *(number+nr_len) = '\0';

      last_i += nr_len+1;

    }

    char* new_res;

    switch(sign_c){
         
         case '+':
          add(*result, number, &new_res);
          break;

         case '*':
          multiply(*result, number, &new_res);
          break;

         case '-':
          subtract(*result, number, &new_res);
          break;

      }

    if(*new_res){
      free(*result);
      *result = new_res;
    }

    free(number);

    if(sign){
      sign_c = *sign;
    }
      
  }

  return 0;
}
