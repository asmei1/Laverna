#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

int* count_words(const char *filename, int *err_code, int N, ...);

int main(int argc, char** argv) 
{
  if(argc < 3){
    printf("Not enough arguments");
    return 9;
  }
  int err = 0;
  int* a = count_words(*(argv+1), &err, argc-2, *(argv+2),*(argv+3),*(argv+4),*(argv+5),*(argv+6),*(argv+7),*(argv+8),*(argv+9),*(argv+10),*(argv+11),*(argv+12),*(argv+13),*(argv+14),*(argv+15),*(argv+16));
  
  if(err == 2){
    printf("Couldn't open file");
    return 4;
  }
  if(err == 3){
    printf("Failed to allocate memory");
    return 8;
  }
  
  for(int i = 0; i < argc-2; i++){
    printf("%d\n",*(a+i));
  }
  
  free(a);

  return 0;
}

int* count_words(const char *filename, int *err_code, int N, ...){

  if(!filename || N<1){
    if(err_code) *err_code = 1;
    return NULL;
  }
  FILE *fp;

  fp = fopen(filename,"r");
  if(!fp){ 
    if(err_code) *err_code = 2;
    return NULL;
  }

  int *tab = (int*)malloc(sizeof(int)*N);
  if(!tab) {
    if(err_code) *err_code = 3;
    fclose(fp);
    return NULL;
  }

  char c = 0;
  int j = 0;
  va_list varg;
  va_start(varg, N);

  for(int i = 0; i <N; i++) {
      *(tab+i) = 0;
      char *a =  va_arg(varg, char*);
      while(fscanf(fp,"%c",&c) != EOF) {
        if(c == *(a+j)) j++;
        else{

          fseek(fp,-1,SEEK_CUR);
          while(fscanf(fp,"%c",&c) != EOF){
            if(c <'A' || (c >'Z' && c <'a') || c >'z'){
              j = 0;
              break;
            }
          }
          continue;
        }
        if(*(a+j) == '\0' && j == (int)strlen(a)){
          if((int)strlen(a) == 1) {
            fseek(fp,-2,SEEK_CUR);
            fscanf(fp,"%c",&c);
            if(((c >= 'A' && c <='Z') || (c >= 'a' && c <='z'))){
              j = 0;
              fseek(fp,1,SEEK_CUR);
              continue;
            }
            fseek(fp,1,SEEK_CUR);
            fscanf(fp,"%c",&c);
            if(((c >= 'a' && c <='z') || (c >= 'A' && c <='Z'))){
              j = 0;
              continue;
            }
            j = 0;
            *(tab+i)+=1;
          }
          else {
            fseek(fp,-2,SEEK_CUR);
            fscanf(fp,"%c",&c);
            if(c != *(a+j-2)) {
              j = 0;
              fseek(fp,1,SEEK_CUR);
              continue;
            }
            fseek(fp,1,SEEK_CUR);
            fscanf(fp,"%c",&c);
            if(((c >= 'A' && c <='Z') || (c >= 'a' && c<='z'))){
              j = 0;
              continue;
            }
            j = 0;
            *(tab+i)+=1;
          }
        }
    }
    fseek(fp,0,SEEK_SET);
  }
  va_end(varg);
  fclose(fp);
  if(err_code) *err_code = 0;
  return tab;
}
