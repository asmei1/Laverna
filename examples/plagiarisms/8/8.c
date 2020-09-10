#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

int* count_words(const char *filename, int *err_code, int N, ...);
int main(int argc, char** argv) {
  if(argc < 3) {
    printf("Not enough arguments");
    return 9;
  }
  int err;
  int* counts = count_words(*(argv+1), &err, argc-2, *(argv+2),*(argv+3),*(argv+4),*(argv+5),*(argv+6),*(argv+7),*(argv+8),*(argv+9),*(argv+10),*(argv+11),*(argv+12),*(argv+13),*(argv+14),*(argv+15),*(argv+16),*(argv+17));
  if(err == 2) {
    printf("Couldn't open file");
    return 4;
  }
  if(err == 3){
    printf("Failed to allocate memory");
    return 8;
  }
  for(int i = 0; i < argc-2; i++){
    printf("%d\n",*(counts+i));
  }
  free(counts);

  return 0;
}

int* count_words(const char *filename, int *err_code, int N, ...){
  if(filename == NULL || N < 1) {
      if(err_code)
        *err_code = 1;
      return NULL;
    }

    FILE *f = fopen(filename,"r");
    if(f == NULL) {
        if(err_code)
          *err_code = 2;
        return NULL;
    }
    
    int *tab = (int*)malloc(sizeof(int)*N);
    if(tab == NULL) {
        if(err_code) 
          *err_code = 3;
        fclose(f);
        return NULL;
    }

    char letter = 0;
    int j = 0;
    va_list valist;
    va_start(valist, N);
    for(int i = 0; i <N; i++) {
        *(tab+i) = 0;
        char *word =  va_arg(valist, char*);
        while(fscanf(f,"%c",&letter) != EOF) {
            if(letter == *(word+j))
                j++;
            else {
                fseek(f,-1,SEEK_CUR);
                while(fscanf(f,"%c",&letter) != EOF) {
                  if(letter <'A' || (letter >'Z' && letter <'a') || letter >'z') {
                    j = 0;
                    break;
                  }
                }
                continue;
            }
            if(*(word+j) == '\0' && j == (int)strlen(word)) {
              if((int)strlen(word) == 1) {
                  fseek(f,-2,SEEK_CUR);
                  fscanf(f,"%c",&letter);
                  if(((letter >= 'a' && letter <='z') || (letter >= 'A' && letter <='Z'))){
                    j = 0;
                    fseek(f,1,SEEK_CUR);
                    continue;
                  }
                  fseek(f,1,SEEK_CUR);
                  fscanf(f,"%c",&letter);
                  if(((letter >= 'a' && letter <='z') || (letter >= 'A' && letter <='Z'))){
                    j = 0;
                    continue;
                  }
                  j = 0;
                  *(tab+i)+=1;
              }
              else {
                  fseek(f,-2,SEEK_CUR);
                  fscanf(f,"%c",&letter);
                  if(letter != *(word+j-2)) {
                    j = 0;
                    fseek(f,1,SEEK_CUR);
                    continue;
                  }
                  fseek(f,1,SEEK_CUR);
                  fscanf(f,"%c",&letter);
                  if(((letter >= 'a' && letter <='z') || (letter >= 'A' && letter <='Z'))){
                    j = 0;
                    continue;
                  }
                  j = 0;
                  *(tab+i)+=1;
              }
            }
        }
        fseek(f,0,SEEK_SET);
    }
  va_end(valist);
  fclose(f);
  if(err_code)
    *err_code = 0;
  return tab;
}
