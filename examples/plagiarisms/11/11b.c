#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct point_t {
  int x;
  int y;
};

int my_printf(char* format, ...);
int my_scanf(char* format, ...);

int print_i(int32_t arg);
int print_f(double arg);
int print_string(char* str);
int print_point(struct point_t p);
int get_digit_at(const int32_t, int);

int main(void) {

    double a;


    my_printf("Tekst zachety: ");

    my_scanf("%f ", &a);

    my_printf("%f", a);

  return 0;
}

int my_printf(char* format, ...){

  if(!format)
    return 0;

  int i = 0,
      count = 0;

  va_list valist;
  va_start(valist, format);

  while(*(format+i) != '\0'){
    if(*(format+i) == '%'){

      switch(*(format+i+1)){

        //string with \x0 as terminator
        case 's':
          count += print_string(va_arg(valist, char*));
        break;

        //int32_t
        case 'd':
          count += print_i(va_arg(valist, int32_t));
        break;

        //double
        case 'f':
          count += print_f(va_arg(valist, double));
        break;

        //point
        case 'p':
          count += print_point(va_arg(valist, struct point_t));
        break;


      }


      i += 2;
      continue;
    }
    else{
      putchar(*(format+i));
      count++;
    }

    i++;
  }

  va_end(valist);
  return count;
}

int my_scanf(char* format, ...){

  if(!format)
    return 0;

  int i = 0,
      count = 0;

  va_list valist;
  va_start(valist, format);

  while(*(format+i) != '\0'){
    if(*(format+i) == '%'){

      if(*(format+i+1) == 's'){
        char* string = va_arg(valist, char*);

        char c;
        int len = 0;

        while(isspace(c = getchar()));
        ungetc(c, stdin);

        while(1){
          c = getchar();

          if(c == ' ' || c == '\n')
            break;

          *(string+len++) = c;
        };

        *(string+len) = '\x0';
        count++;
      }

      if(*(format+i+1) == 'd'){
        int32_t* nr = va_arg(valist, int32_t*);

        char c;
        int is_valid = 1,
            is_read = 0; //is set only if some characters was valid

        *nr = 0;
        int is_neg = 0;

        while(isspace(c = getchar()));
        ungetc(c, stdin);

        while(1){
          c = getchar();

          if(c == ' ' || c == '\n' || (!isdigit(c) && is_read))
            break;

          if(c == '-' && *nr == 0){
            is_neg = 1;
            continue;
          }

          if(!isdigit(c))
            is_valid = 0;

          *nr *= 10;
          *nr += c - '0';
          is_read = 1;
        };

        if(is_neg)
          *nr *= -1;

        if(is_valid)
          count++;
      }

      if(*(format+i+1) == 'f'){
        double* nr = va_arg(valist, double*);

        char c;

        while(isspace(c = getchar()));
        ungetc(c, stdin);

        *nr = 0;
        int is_neg = 0, //is number negative
            f_point = 0, //is floating point matched
            r_pos = 1, //real part digit position
            is_valid = 1,
            is_read = 0; //is set only if some characters was valid

        while(1){
          c = getchar();

          if(c == ' ' || c == '\n' || (!isdigit(c) && is_read && c != '.'))
            break;

          if(c == '-' && *nr == 0){
            is_neg = 1;
            continue;
          }

          if(c == '.'){
            f_point = 1;
            continue;
          }

          if(!isdigit(c))
            is_valid = 0;

          if(!f_point){
            *nr *= 10;
            *nr += c - '0';
          }
          else{
            *nr += (c - '0')/pow(10, r_pos);
            r_pos++;
          }

          is_read = 1;
        };

        if(is_neg)
          *nr *= -1;

        if(is_valid)
          count++;
      }

      if(*(format+i+1) == 'p'){
        struct point_t* p = va_arg(valist, struct point_t*);
        int nr,
            is_valid = 1;

        char c;

        while(isspace(c = getchar()));

        nr = 0;
        int is_neg = 0;

        if(c != '(')
          is_valid = 0;

        while(1){
          c = getchar();

          if(c == ' ')
            break;

          if(c == '-' && nr == 0){
            is_neg = 1;
            continue;
          }

          if(!isdigit(c))
            is_valid = 0;

          nr *= 10;
          nr += c - '0';
        };

        if(is_neg)
          nr *= -1;

        if(is_valid){
          count++;
          p->x = nr;
        }

        nr = 0;
        is_neg = 0;

        while(1){
          c = getchar();

          if(c == ')')
            break;

          if(c == '-' && nr == 0){
            is_neg = 1;
            continue;
          }

          if(!isdigit(c))
            is_valid = 0;

          nr *= 10;
          nr += c - '0';
        };

        if(is_neg)
          nr *= -1;

        p->y = nr;

        if(c != ')')
          is_valid = 0;

        if(is_valid){
          count++;
        }
      }

      i += 2;
      continue;
    }

    i++;
  }

  va_end(valist);
  return count;
}

int print_i(int32_t arg){

  int32_t value = arg,
          count = 0;

  if(value == 0){
    putchar('0');
    count++;
  }

  if(value < 0){
    value *= -1;
    putchar('-');
    count++;
  }

  for(int i = 0; i < (int)log10(value)+1; i++){
    putchar('0' + get_digit_at(value, i+1));
    count++;
  }

  return count;
}

int print_f(double arg){

  int i_part, count = 0;

  if(arg < 0){
    i_part = ceil(arg);;
  }
  else{
    i_part = floor(arg);
  }

  double f_part = arg >= 0 ? arg - i_part : -1*(arg - i_part);

  count += print_i(i_part);

  putchar('.');
  count++;

  for(int i = 0; i < 5; i++){
    f_part *= 10;
    putchar('0' + (int)f_part%10);
    count++;
  }

  return count;
}

int print_string(char* str){

  int count = 0;

  if(str){
    int i = 0;

    while(*(str+i) != '\x0'){
      putchar(*(str+i));
      count++;
      i++;
    }
  }

  return count;
}

int print_point(struct point_t p){

  int count = 0;

  putchar('(');
  count++;

  count += print_i(p.x);

  putchar(' ');
  count++;

  count += print_i(p.y);

  putchar(')');
  count++;

  return count;
}

int get_digit_at(const int32_t nr, int pos){

  int len = log10(nr)+1;
  int32_t copy = nr;

  for(int i = 0; i < len - pos; i++){
    copy /= 10;
  }

  return copy%10;
}
