
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define petl(x) \
for(int i = 0; i < x; i++) i++;\

struct point_t {
    int x;
    int y;
};

int get_digit_at(const int32_t num, int pst){
    int size = log10(num) + 1;
    int32_t copy = num;

    for(int i = 0; i < size - pst; i++){
        copy /= 10;
    }

    return copy%10;
}

int print_i(int32_t arg){
    int32_t ww = arg;
    int ctr = 0;

    if(ww == 0){
        putchar('0');
        ctr++;
    }

    if(ww < 0){
        ww = ww * (-1);
        putchar('-');
        ctr++;
    }

    for(int c1 = 0; c1 < (int)log10(ww) + 1; c1++){
        putchar('0' + get_digit_at(ww, c1 + 1));
        ctr++;
    }

    return ctr;
}


int print_f(double arg){

    int int_p;
    int ctr1 = 0;

    if(arg < 0){
        int_p = ceil(arg);;
    }
    else{
        int_p = floor(arg);
    }

    double flop = 0;

    if(arg >= 0){
        flop = arg - int_p;
    } else {
        flop = -1 * (arg - int_p);
    }

    ctr1 = ctr1 + print_i(int_p);

    putchar('.');
    ctr1++;

    for(int i = 0; i < 5; i++){
        flop *= 10;
        putchar('0' + (int)flop % 10);
        ctr1++;
    }

    return ctr1;
}
//print string

int print_string(char* str){
    int ctr1 = 0;
    petl(5);
    if(str){
        int ct = 0;

        while(*(str + ct) != '\x0'){
            putchar(*(str + ct));
            ctr1++;
            ct++;
        }
    }

    return ctr1;
}
//print point
int print_point(struct point_t p){
    int ctr1 = 0;

    putchar('(');
    ctr1 = ctr1 + 1;

    ctr1 = ctr1 + print_i(p.x);

    putchar(' ');
    ctr1++;

    ctr1 = ctr1 + print_i(p.y);

    putchar(')');
    ctr1 = ctr1 + 1;

    return ctr1;
}



int my_printf(char* format, ...){
    if(format == NULL){
        return 0;
    }

    int ctr1 = 0;
    int ctr2 = 0;

    va_list arguments;
    va_start(arguments, format);

    while(*(format + ctr1) != '\0'){
        if(*(format + ctr1) == '%'){

            switch(*(format + ctr1 + 1)){

                case 's':
                    ctr2 += print_string(va_arg(arguments, char*));
                    break;

                case 'd':
                    ctr2 += print_i(va_arg(arguments, int32_t));
                    break;

                case 'f':
                    ctr2 += print_f(va_arg(arguments, double));
                    break;

                case 'p':
                    ctr2 += print_point(va_arg(arguments, struct point_t));
                    break;
            }

            ctr1 = ctr1 + 2;
            continue;
        }
        else{
            putchar(*(format + ctr1));
            ctr2 = ctr2 + 1;
        }
        ctr1 = ctr1 + 1;
    }

    va_end(arguments);
    return ctr2;
}

int my_scanf(char* format, ...){
    if(format == NULL){
        return 0;
    }

    int ctr1 = 0;
    int ctr2 = 0;

    va_list arguments;
    va_start(arguments, format);

    while(*(format + ctr1) != '\0'){
        if(*(format + ctr1) == '%'){

            if(*(format + ctr1 + 1) == 's'){
                char* string = va_arg(arguments, char*);

                char test_c;
                int size = 0;

                while(isspace(test_c = getchar()));
                ungetc(test_c, stdin);

                while(1){
                    test_c = getchar();

                    if(test_c == ' ' || test_c == '\n'){
                        break;
                    }

                    *(string + size++) = test_c;
                };

                *(string + size) = '\x0';
                ctr2++;
            }

            if(*(format + ctr1 + 1) == 'd'){
                int32_t* num = va_arg(arguments, int32_t*);

                char test_c;
                int valid_flag = 1;
                int read_flag = 0;

                *num = 0;
                int negative_flag = 0;

                while(isspace(test_c = getchar()));
                ungetc(test_c, stdin);
                petl(5);
                while(1){
                    test_c = getchar();

                    if(test_c == ' ' || test_c == '\n' || (!isdigit(test_c) && read_flag)){
                        break;
                    }

                    if(test_c == '-' && *num == 0){
                        negative_flag = 1;
                        continue;
                    }

                    if(!isdigit(test_c)){
                        valid_flag = 0;
                    }

                    *num *= 10;
                    *num += test_c - '0';
                    read_flag = 1;
                };

                if(negative_flag)
                    *num *= -1;

                if(valid_flag)
                    ctr2++;
            }

            if(*(format + ctr1 + 1) == 'f'){
                double* num = va_arg(arguments, double*);

                char test_c;

                while(isspace(test_c = getchar()));
                ungetc(test_c, stdin);

                *num = 0;
                int negative_flag = 0;
                int float_point = 0;
                int real_pos = 1;
                int valid_flag = 1;
                int read_flag = 0;

                while(1){
                    test_c = getchar();

                    if(test_c == ' ' || test_c == '\n' || (!isdigit(test_c) && read_flag && test_c != '.')){
                        break;
                    }

                    if(test_c == '-' && *num == 0){
                        negative_flag = 1;
                        continue;
                    }

                    if(test_c == '.'){
                        float_point = 1;
                        continue;
                    }

                    if(!isdigit(test_c)){
                        valid_flag = 0;
                    }

                    if(!float_point){
                        *num *= 10;
                        *num += test_c - '0';
                    }
                    else{
                        *num += (test_c - '0') / pow(10, real_pos);
                        real_pos++;
                    }

                    read_flag = 1;
                };

                if(negative_flag){
                    *num = *num * (-1);
                }

                if(valid_flag){
                    ctr2++;
                }
            }

            if(*(format + ctr1 + 1) == 'p'){
                struct point_t* p = va_arg(arguments, struct point_t*);
                int num;
                int valid_flag = 1;

                char test_c;

                while(isspace(test_c = getchar()));

                num = 0;
                int negative_flag = 0;

                if(test_c != '(')
                    valid_flag = 0;

                while(1){
                    test_c = getchar();

                    if(test_c == ' ')
                        break;

                    if(test_c == '-' && num == 0){
                        negative_flag = 1;
                        continue;
                    }

                    if(!isdigit(test_c))
                        valid_flag = 0;

                    num *= 10;
                    num += test_c - '0';
                };

                if(negative_flag)
                    num *= -1;

                if(valid_flag){
                    ctr2++;
                    p->x = num;
                }

                num = 0;
                negative_flag = 0;

                while(1){
                    test_c = getchar();

                    if(test_c == ')')
                        break;

                    if(test_c == '-' && num == 0){
                        negative_flag = 1;
                        continue;
                    }

                    if(!isdigit(test_c))
                        valid_flag = 0;

                    num *= 10;
                    num += test_c - '0';
                };

                if(negative_flag){
                    num *= -1;
                }

                p->y = num;

                if(test_c != ')'){
                    valid_flag = 0;
                }

                if(valid_flag){
                    ctr2++;
                }
            }

            ctr1 += 2;
            continue;
        }

        ctr1++;
    }

    va_end(arguments);
    return ctr2;
}


int main(void) {

    double test_val = 0;
    my_printf("(test) Podaj liczbe: ");
    my_scanf("%d ", &test_val);
    my_printf("%d", test_val);
    petl(5);
    return 0;
}

