#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

int create_leading_word_cross(const char *first, const char *second, char ***result){

  if(!first || !second || !result)
    return -1;

  int first_common_pos = 0;
  int crossed_row = 0;
  int rows = (int)strlen(first);
  int cols = (int)strlen(second);

  //Validate first word
  for(int i = 0; i < rows; i++){

    if(!isalpha(*(first+i)) || islower(*(first+i))){
      *result = NULL;
      return -1;
    }

  }

  //Validate second word
  for(int i = 0; i < cols; i++){

    if(!isalpha(*(second+i)) || islower(*(second+i))){
      *result = NULL;
      return -1;
    }

  }


  //Find common letter and save this position
  int found = 0;
  for(int i = 0; i < cols; i++){

    for(int j = 0; j < rows; j++){

      if(*(first+j) == *(second+i)){
        first_common_pos = i;
        crossed_row = j;
        found = 1;
        break;
      }
    }

    if(found)
      break;
  }

  if(!found){
    *result = NULL;
    return -2;
  }

  *result = (char**)malloc(sizeof(char*)*(rows+1));

  if(!*result)
    return -3;

  for(int i = 0; i < rows; i++){

    if( i == crossed_row){
      *(*result+i) = (char*)malloc(sizeof(char)*(cols+1));
    }
    else{
      *(*result+i) = (char*)malloc(sizeof(char)*(first_common_pos+2));
    }

    if(!*(*result+i)){

      for(int j = 0; j < i; j++)
        free(*(*result+j));

      free(*result);
      *result = NULL;
      return -3;
    }
      
  }

  *(*result+rows) = NULL;

  for(int i = 0; i < rows; i++){

    for(int j = 0; j < cols; j++){

      if(i != crossed_row && j < first_common_pos){
        *(*(*result+i)+j) = ' ';
      }
      else if(i == crossed_row){
        *(*(*result+i)+j) = *(second+j);
      }
      else if(i != crossed_row && j == first_common_pos){
        *(*(*result+i)+j) = *(first+i);
      }
      
    }

    if(i == crossed_row){
        *(*(*result+i)+cols) = '\0';
    }
    else{
      *(*(*result+i)+first_common_pos+1) = '\0';
    }
  }

  return crossed_row;
}

int create_double_leading_word_cross(
    const char *first, const char *second, const char *third, const char *fourth,
    char ***result, char ***first_cross, char ***second_cross){

      if(!first || !second || !third || !fourth || 
      !result || !first_cross || !second_cross)
        return 1;

      int err1, err2;

      err1 = create_leading_word_cross(second, first, first_cross);

      if(err1 == -1){
        *result = NULL;
        return 1;
      }

      if(err1 == -2){
        *result = NULL;
        return 2;
      }

      if(err1 == -3){
         *result = NULL;
         return 3;
      }

      err2 = create_leading_word_cross(fourth, third, second_cross);

      if(err2 == -1){
        destroy(*first_cross);
        *result = NULL;
        *first_cross = NULL;
        return 1;
      }

      if(err2 == -2){
        destroy(*first_cross);
        *result = NULL;
        *first_cross = NULL;
        return 2;
      }

      if(err2 == -3){
        destroy(*first_cross);
        *result = NULL;
        *first_cross = NULL;
        return 3;
      }

      int l4_after_common = strlen(fourth)-err2;
      int l2_after_common = strlen(second)-err1;
      int max_len = l4_after_common > l2_after_common ? l4_after_common : l2_after_common; 

      int offset = (err1 > err2 ? err1 : err2);

      int height = offset + max_len + 1;
      
      int first_i = 0, second_i = 0;
      *result = (char**)malloc(sizeof(char*)*height);

      if(!*result){
        destroy(*first_cross);
        destroy(*second_cross);

        *first_cross = NULL;
        *second_cross = NULL;
        return 3;
      }

      first_i = 0;
      second_i = 0;

      //Count leading crosses heights

      int first_height = 0;
      int second_height = 0;

      for(int i = 0; *(*first_cross+i); i++){
        first_height++;
      }

      for(int i = 0; *(*second_cross+i); i++){
        second_height++;
      }

      //Combine two crosses into one

      int diff = err1-err2;
      int spaces;

      for(int i = 0; i < height; i++){

         if(diff < 0 && i < abs(diff)){
           spaces = strlen(*(*first_cross+err1))+3;

          *(*result+i) = malloc(sizeof(char)*(spaces+strlen(*(*second_cross+second_i))+1));

          if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);

            *first_cross = NULL;
            *second_cross = NULL;
            *result = NULL;
            return 3;
          }

           for(int j = 0; j < spaces; j++){
             *(*(*result+i)+j) = ' ';
           }
           
           for(int j = 0; j < (int)strlen(*(*second_cross+second_i)); j++){
             *(*(*result+i)+spaces+j) = *(*(*second_cross+second_i)+j);
           }
           
           *(*(*result+i)+spaces+strlen(*(*second_cross+second_i))) = '\0';
           second_i++;
         }
         else if(diff > 0 && i < diff){
           *(*result+i) = malloc(sizeof(char)*(strlen(*(*first_cross+first_i))+1));

           if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);

            *first_cross = NULL;
            *second_cross = NULL;
            *result = NULL;
            return 3;
          }
           
           strcpy(*(*result+i), *(*first_cross+first_i));
           
           *(*(*result+i)+strlen(*(*first_cross+first_i))) = '\0';
           first_i++;
         }
         else if( i >= abs(diff) && (first_i < first_height && second_i < second_height)){
           spaces = strlen(*(*first_cross+err1))-strlen(*(*first_cross+first_i))+3;

           int size = strlen(*(*first_cross+first_i))+strlen(*(*second_cross+second_i))+spaces;

           *(*result+i) = malloc(sizeof(char)*(size+1));

           if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);

            *first_cross = NULL;
            *second_cross = NULL;
            *result = NULL;
            return 3;
          }
           
           strcpy(*(*result+i), *(*first_cross+first_i));

           for(int j = 0; j < spaces; j++){
             *(*(*result+i)+strlen(*(*first_cross+first_i))+j) = ' ';
           }

           for(int j = 0; j < (int)strlen(*(*second_cross+second_i)); j++){
             *(*(*result+i)+strlen(*(*first_cross+first_i))+spaces+j) = *(*(*second_cross+second_i)+j);
           }

           *(*(*result+i)+size) = '\0';

           first_i++;
           second_i++;
         }
         else if( first_i < first_height){

           *(*result+i) = malloc(sizeof(char)*(strlen(*(*first_cross+first_i))+1));

           if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);

            *first_cross = NULL;
            *second_cross = NULL;
            *result = NULL;
            return 3;
          }
           
           strcpy(*(*result+i), *(*first_cross+first_i));
           
           *(*(*result+i)+strlen(*(*first_cross+first_i))) = '\0';
           first_i++;
         }
         else if( second_i < second_height){
           
           spaces = strlen(*(*first_cross+err1))+3;

          *(*result+i) = malloc(sizeof(char)*(spaces+strlen(*(*second_cross+second_i))+1));

          if(!*(*result+i)){
            destroy(*first_cross);
            destroy(*second_cross);
            destroy(*result);

            *first_cross = NULL;
            *second_cross = NULL;
            *result = NULL;

            return 3;
          }

           for(int j = 0; j < spaces; j++){
             *(*(*result+i)+j) = ' ';
           }

           for(int j = 0; j < (int)strlen(*(*second_cross+second_i)); j++){
             *(*(*result+i)+spaces+j) = *(*(*second_cross+second_i)+j);
           }
           
           *(*(*result+i)+spaces+strlen(*(*second_cross+second_i))) = '\0';
           second_i++;
         }
      }

      *(*result+height-1) = NULL;

      return 0;
    }

void destroy(char **words){

  if(words){

    int i = 0;

    while(*(words+i)){
      free(*(words+i));
      i++;
    }

    free(words);
  }
}
