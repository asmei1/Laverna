#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(void) {

  char **result, **first, **second;
  char *word1 = malloc(sizeof(char)*11);

  if(!word1){
    printf("Failed to allocate memory");
    return 8;
  }
  char *word2 = malloc(sizeof(char)*11);
  if(!word2){
    printf("Failed to allocate memory");
    free(word1);
    return 8;
  }
  
  char *word3 = malloc(sizeof(char)*11);
  if(!word3){
    printf("Failed to allocate memory");
    free(word1);
    free(word2);
    return 8;
  }

  char *word4 = malloc(sizeof(char)*11);
  if(!word4){
    printf("Failed to allocate memory");
    free(word1);
    free(word2);
    free(word3);
    return 8;
  }
  int err;
  int i = 0;

  printf("Podaj slowa: ");

  scanf("%10s %10s %10s %10s", word1, word2, word3, word4);

  err = create_double_leading_word_cross(word1, word2, word3, word4, &result, &first, &second);

  if(err == 1){
    printf("Incorrect input");
    free(word1);
    free(word2);
    free(word3);
    free(word4);
    return 1;
  }
  else if(err == 2){
    printf("Unable to make two crosses");

    free(word1);
    free(word2);
    free(word3);
    free(word4);

    return 0;
  }
  else if(err == 3){
    printf("Failed to allocate memory");

    free(word1);
    free(word2);
    free(word3);
    free(word4);
    
    return 8;
  }

  i = 0;
  while(*(first+i)){
    printf("%s\n", *(first+i));
    i++;
  }

  printf("\n");

  i = 0;
  while(*(second+i)){
    printf("%s\n", *(second+i));
    i++;
  }

  printf("\n");

  i = 0;
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
