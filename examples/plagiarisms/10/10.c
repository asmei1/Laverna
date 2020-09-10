#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int create_leading_word_cross(const char *first, const char *second, char ***result);
int create_double_leading_word_cross(const char *first, const char *second, const char *third, const char *fourth, char ***result, char ***first_cross, char ***second_cross);
void destroy(char **words);

int main(void){

  char **result, **first, **second;
  char *word1=malloc(sizeof(char)*11);

  if(!word1){
    printf("Failed to allocate memory");
    return 8;
  }
  char *word2=malloc(sizeof(char)*11);
  if(!word2){
    printf("Failed to allocate memory");
    free(word1);
    return 8;
  }

  char *word3=malloc(sizeof(char)*11);
  if(!word3){
    printf("Failed to allocate memory");
    free(word1);
    free(word2);
    return 8;
  }

  char *word4=malloc(sizeof(char)*11);
  if(!word4){
    printf("Failed to allocate memory");
    free(word1);
    free(word2);
    free(word3);
    return 8;
  }
  int error;
  int i=0;
  printf("Podaj slowa:");
  scanf("%10s %10s %10s %10s", word1, word2, word3, word4);
  error=create_double_leading_word_cross(word1, word2, word3, word4, &result, &first, &second);
  if(error==1){
    printf("Incorrect input");
    free(word1);
    free(word2);
    free(word3);
    free(word4);
    return 1;
  }
  else if(error==2){
    printf("Unable to make two crosses");
    free(word1);
    free(word2);
    free(word3);
    free(word4);
    return 0;
  }
  else if(error == 3){
    printf("Failed to allocate memory");
    free(word1);
    free(word2);
    free(word3);
    free(word4);
    return 8;
  }
  i=0;
  while(*(first+i)){
    printf("%s\n", *(first+i));
    i++;
  }
  printf("\n");
  i=0;
  while(*(second+i)){
    printf("%s\n", *(second+i));
    i++;
  }
  printf("\n");
  i=0;
  while(*(result+i)){
    printf("%s\n", *(result+i));
    i++;
  }
  destroy(first);
  destroy(second);
  destroy(result);
  free(word1);
  free(word2);
  free(word3);
  free(word4);
  return 0;
}

int create_leading_word_cross(const char *first, const char *second, char ***result){
  if(!first || !second || !result)
    return -1;

  int pos=0;
  int cross=0;
  int rows=(int)strlen(first);
  int cols=(int)strlen(second);
  for(int i=0; i<rows; i++){

    if(!isalpha(*(first+i)) || islower(*(first+i))){
      *result=NULL;
      return -1;
    }
  }
  for(int i = 0; i<cols; i++){
    if(!isalpha(*(second+i)) || islower(*(second+i))){
      *result = NULL;
      return -1;
    }
  }
  int flag=0;
  for(int i = 0; i<cols; i++){
    for(int j = 0; j<rows; j++){
      if(*(first+j)==*(second+i)){
        pos=i;
        cross=j;
        flag=1;
        break;
      }
    }
    if(flag!=0)
      break;
  }
  if(flag==0){
    *result=NULL;
    return -2;
  }
  *result=(char**)malloc(sizeof(char*)*(rows+1));
  if(!*result)
    return -3;
  for(int i=0; i<rows; i++){
    if(i==cross){
      *(*result+i)=(char*)malloc(sizeof(char)*(cols+1));
    }
    else{
      *(*result+i)=(char*)malloc(sizeof(char)*(pos+2));
    }
    if(!*(*result+i)){
      for(int j=0; j<i; j++)
        free(*(*result+j));
      free(*result);
      *result=NULL;
      return -3;
    }
  }
  *(*result+rows)=NULL;
  for(int i=0; i<rows; i++){

    for(int j=0; j<cols; j++){
      if(i!=cross && j<pos){
        *(*(*result+i)+j)=' ';
      }
      else if(i==cross){
        *(*(*result+i)+j)=*(second+j);
      }
      else if(i!=cross&& j==pos){
        *(*(*result+i)+j) = *(first+i);
      }
    }
    if(i==cross){
        *(*(*result+i)+cols)='\0';
    }
    else{
      *(*(*result+i)+pos+1)='\0';
    }
  }
  return cross;
}

int create_double_leading_word_cross(const char *first, const char *second, const char *third, const char *fourth, char ***result, char ***first_cross, char ***second_cross){
    if(!first || !second || !third || !fourth ||!result || !first_cross || !second_cross)
        return 1;

      int res1, res2;
      res1=create_leading_word_cross(second, first, first_cross);
      if(res1==-1){
        *result=NULL;
        return 1;
      }
      if(res1==-2){
        *result = NULL;
        return 2;
      }
      if(res1==-3){
         *result = NULL;
         return 3;
      }
      res2 = create_leading_word_cross(fourth, third, second_cross);
      if(res2==-1){
        destroy(*first_cross);
        *result=NULL;
        *first_cross=NULL;
        return 1;
      }
      if(res2==-2){
        destroy(*first_cross);
        *result=NULL;
        *first_cross=NULL;
        return 2;
      }
      if(res2==-3){
        destroy(*first_cross);
        *result=NULL;
        *first_cross=NULL;
        return 3;
      }
      int l4=strlen(fourth)-res2;
      int l2=strlen(second)-res1;
      int len=l4>l2 ? l4 : l2;
      int offset=(res1>res2 ? res1 : res2);
      int height=offset+len+1;
      int pos1=0, pos2=0;
      *result=(char**)malloc(sizeof(char*)*height);
      if(!*result){
        destroy(*first_cross);
        destroy(*second_cross);
        *first_cross=NULL;
        *second_cross=NULL;
        return 3;
      }
      pos1=0;
      pos2=0;
      int len1=0;
      int len2=0;
      for(int i=0; *(*first_cross+i); i++){
        len1++;
      }
      for(int i=0; *(*second_cross+i); i++){
        len2++;
      }
      int diff=res1-res2;
      int spaces;
      for(int i=0; i<height; i++){
         if(diff<0 && i<abs(diff)){
           spaces=strlen(*(*first_cross+res1))+3;
          *(*result+i)=malloc(sizeof(char)*(spaces+strlen(*(*second_cross+pos2))+1));
          if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);
            *first_cross=NULL;
            *second_cross=NULL;
            *result=NULL;
            return 3;
          }
           for(int j=0; j<spaces; j++){
             *(*(*result+i)+j)=' ';
           }
           for(int j=0; j<(int)strlen(*(*second_cross+pos2)); j++){
             *(*(*result+i)+spaces+j) = *(*(*second_cross+pos2)+j);
           }
           *(*(*result+i)+spaces+strlen(*(*second_cross+pos2)))='\0';
           pos2++;
         }
         else if(diff>0 && i<diff){
           *(*result+i)=malloc(sizeof(char)*(strlen(*(*first_cross+pos1))+1));
           if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);
            *first_cross=NULL;
            *second_cross=NULL;
            *result=NULL;
            return 3;
          }
           strcpy(*(*result+i), *(*first_cross+pos1));
           *(*(*result+i)+strlen(*(*first_cross+pos1)))='\0';
           pos1++;
         }
         else if(i>=abs(diff) && (pos1<len1&& pos2<len2)){
           spaces=strlen(*(*first_cross+res1))-strlen(*(*first_cross+pos1))+3;
           int size=strlen(*(*first_cross+pos1))+strlen(*(*second_cross+pos2))+spaces;
           *(*result+i)=malloc(sizeof(char)*(size+1));
           if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);
            *first_cross=NULL;
            *second_cross=NULL;
            *result=NULL;
            return 3;
          }
           strcpy(*(*result+i), *(*first_cross+pos1));
           for(int j=0; j<spaces; j++){
             *(*(*result+i)+strlen(*(*first_cross+pos1))+j)=' ';
           }
           for(int j=0; j<(int)strlen(*(*second_cross+pos2)); j++){
             *(*(*result+i)+strlen(*(*first_cross+pos1))+spaces+j)=*(*(*second_cross+pos2)+j);
           }
           *(*(*result+i)+size)='\0';
           pos1++;
           pos2++;
         }
         else if(pos1<len1){
           *(*result+i)=malloc(sizeof(char)*(strlen(*(*first_cross+pos1))+1));
           if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);
            *first_cross=NULL;
            *second_cross=NULL;
            *result=NULL;
            return 3;
          }
           strcpy(*(*result+i), *(*first_cross+pos1));
           *(*(*result+i)+strlen(*(*first_cross+pos1)))='\0';
           pos1++;
         }
         else if(pos2<len2){
           spaces=strlen(*(*first_cross+res1))+3;
          *(*result+i)=malloc(sizeof(char)*(spaces+strlen(*(*second_cross+pos2))+1));
          if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);
            *first_cross=NULL;
            *second_cross=NULL;
            *result=NULL;
            return 3;
          }
           for(int j=0; j<spaces; j++){
             *(*(*result+i)+j)=' ';
           }
           for(int j=0; j<(int)strlen(*(*second_cross+pos2)); j++){
             *(*(*result+i)+spaces+j) = *(*(*second_cross+pos2)+j);
           }
           *(*(*result+i)+spaces+strlen(*(*second_cross+pos2)))='\0';
           pos2++;
         }
      }
      *(*result+height-1)=NULL;
      return 0;
    }

void destroy(char **words){
  if(words!=NULL){
    int i=0;
    while(*(words+i)){
      free(*(words+i));
      i++;
    }
    free(words);
  }
}

