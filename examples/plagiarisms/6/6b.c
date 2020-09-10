#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "tested_declarations.h"
#include "rdebug.h"
#define PI 3.14159265
int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);
int multiply(const char* number1, const char* number2, char** result);
int calculate(const char* expr, char **result);
int validate_expression(const char *expr);

int compare(const char* number1, const char* number2);
int validate(const char *expr);
int isNegative(const char *number);
int injectNumber(const char *output,char *input);
void removeLeadingZero(char *number);
void addChar(char *a,char c);


int main()
{
    char *expresion,*result;
    int d=0;
    expresion=calloc(501, sizeof(char));
    if(expresion == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("enter expresion");
    scanf("%s",expresion);
    if(validate_expression(expresion)!=0){
        printf("Incorrect input");
        free(expresion);
        return 1;
    }
    d=calculate(expresion,&result);
    if(d==3){
        printf("Failed to allocate memory");
        free(expresion);
        return 8;
    }
    printf("%s",result);
    free(expresion);
    free(result);
    return 0;
}
int subtract(const char* number1, const char* number2, char** result){
    if(number1==NULL || number2==NULL || result==NULL){
        return 1;
    }
    if(validate(number1)==2 || validate(number2)==2){
        return 2;
    }
    int a=0,b=0,c=0,rest=0,size1=0,size2=0,sizeFin=0,i=0,j=0, negative=0;
    const char *ptr,*temp;
    if(isNegative(number2) == 1 && isNegative(number1) == 0){

        return add(number1,number2+1,result);

    }else if(isNegative(number2) == 0 && isNegative(number1) == 1){

        int g=add(number2,number1+1,result);
        if(g==0)addChar(*result,'-');

        return g;

    }else if(isNegative(number1)==1 && isNegative(number2)==1){

       return add(number1,number2+1,result);

    }else{

        if(compare(number1,number2) == -1){
            temp=number2;
            number2=number1;
            number1=temp;
            negative=1;
        }
        size1=strlen(number1);
        size2=strlen(number2);
        sizeFin=(size1>size2)?size2:size1;
        j=(size1>size2)?size1:size2;
        int ismo=0;
        if( number1-1!=NULL && *(number1-1)=='-'){
            ismo++;
        }else if( number2-1!=NULL && *(number2-1)=='-'){
            ismo++;
        }
        *result=calloc(j+2+ismo,sizeof(char));
        if(*result==NULL){
            return 3;
        }
        ptr=(size1>size2)?number1:number2;

        *(*result+j)='\0';
        for(i=1;i<=size2;i++){
            if((number1+size1-i)!=NULL && (number2+size2-i)!=NULL && (result+j-i)!=NULL){

                if(i<=size1){
                    a=*(number1+size1-i)-'0';
                }
                if(i<=size2){
                    b=*(number2+size2-i)-'0';
                }
                c=a-b-rest;
                if(c<0){
                    c+=10;
                    rest=1;
                }else{
                    rest=0;
                }
                if(i<=j){
                    *(*result+j-i)=c+'0';
                }
            }
        }
        for(i=sizeFin+1;i<=j;i++){
            for(i=sizeFin+1;i<=j;i++){
                a=*(ptr+j-i)-'0';
                c=a-rest;
                if(c<0){
                    rest=1;
                    c+=10;
                }else{
                    rest=0;
                }
                if(i<=j){
                    *(*result+j-i)=c+'0';
                }
            }
        }
    }
    removeLeadingZero(*result);

    if(negative==1){
       addChar(*result,'-');
    }

    return 0;
}
//#################################################################
int add(const char* number1, const char* number2, char** result){
    if(number1==NULL || number2==NULL || result==NULL){
        return 1;
    }
    if(validate(number1)!=0 || validate(number2)!=0){
        return 2;
    }
    int i=0;
    if(isNegative(number1)==0 && isNegative(number2)==1){

       return subtract(number1,number2+1,result);

    }else if(isNegative(number2)==0 && isNegative(number1)==1){

        return subtract(number2,number1+1,result);

    }else{
        if(isNegative(number1)==isNegative(number2)){

            int a=0,b=0,c=0,rest=0,size1=0,size2=0,sizeFin=0,j=0,bothNegative=0,lenghtFinal=0,ismo=0;
            const char *ptr;

            size1=strlen(number1);
            size2=strlen(number2);
            sizeFin=(size1>size2)?size2:size1;
            j=(size1>size2)?size1:size2;
            if( number1-1!=NULL && *(number1-1)=='-'){
                ismo++;
            }else if( number2-1!=NULL && *(number2-1)=='-'){
                ismo++;
            }
            *result=(char*)calloc(j+2+ismo,sizeof(char));
            if(*result==NULL){
                return 3;
            }

            if(isNegative(number1)==1 && isNegative(number2)==1){
                number1++;
                number2++;
                bothNegative=1;
            }
            ptr=(size1>size2)?number1:number2;
            if((*result+j)!=NULL){
                *(*result+j)='\0';
            }

            for(i=1;i<=sizeFin;i++){

                if((number1+size1-i)!=NULL && (number2+size2-i)!=NULL && (result+j-i)!=NULL){

                    if(i<=size1){
                        a=*(number1+size1-i)-'0';
                    }
                    if(i<=size2){
                        b=*(number2+size2-i)-'0';
                    }

                    c=rest;
                    lenghtFinal++;
                    if(a+'0'!='-'){
                        c+=a;
                    }

                    if(b+'0'!='-'){
                        c+=b;
                    }

                    if(c>=10){
                        rest=c/10;
                        c=c%10;
                    }else{
                        rest=0;
                    }
                   if(i<=j){
                       if( (*result+j-i)!=NULL ){
                            *(*result+j-i)=c+'0';
                       }
                    }
                }
            }

             for(i=sizeFin+1;i<=j;i++){
                a=*(ptr+j-i)-'0';
                c=a+rest;
                if(c>=10){
                    rest=c/10;
                    c=c%10;
                }else{
                    rest=0;
                }
                lenghtFinal++;
                if(i<=j){
                    if((*result+j-i)!=NULL ){
                        *(*result+j-i)=c+'0';
                    }
                }
             }

            if(rest==1){
                addChar(*result,'1');
                lenghtFinal++;
            }
            *(*result+lenghtFinal)='\0';

            if(isNegative(number1)){
                **result='-';
            }
            if(bothNegative==1){
                addChar(*result,'-');
            }
        }
    }

    return 0;
}
int multiply(const char* number1, const char* number2, char** result){

    if(number1==NULL || number2==NULL || result==NULL){
        return 1;
    }

    if(validate(number1)!=0 || validate(number2)!=0){
        return 2;
    }

    int size1=0,size2=0,k=0,sizeRes=0,res=0,resSum=0,i=0,j=0,a=0,b=0,c=0,d=0,h=0,g=0,g1=0;
    size1 = strlen(number1);
    size2 = strlen(number2);
    if(compare("0",number1)==0 ||compare("0",number2)==0){
        *result = calloc(2, sizeof(char));
        if(*result == NULL){
            return 3;
        }
        *(*result) = '0';
        *(*result + 1) = '\0';
        return 0;
    }
    if(isNegative(number1)!=isNegative(number2)){
        k = 1;
    }else{
        if(isNegative(number1)==1){
            g = 1;
        }
    }
    if(isNegative(number2)==1 && isNegative(number1)==0  ){
        number2++;
        size2--;
        g1++;
    }
    sizeRes = size1 + size2;
    *result = calloc(sizeRes + 1 + k, sizeof(char));
    if(*result == NULL){
        return 3;
    }
    for(i = 0; i < sizeRes;i++){
        *(*result + i)='0';
    }

    for(i = size1 ; i >= 1+g; i--){
        for(j = size2 ; j >= 1+g; j--){

            if(*(number1 + i - 1)=='-' || *(number2 + j - 1)=='-'){
                continue;
            }
            if(i-1>=0 && i-1<size1){
                a = *(number1 + i-1) - '0';
            }
            if(j-1>=0 && j-1<size2){
                b = *(number2 + j-1) - '0';
            }
            c=a*b + res;

            if(c >= 10){
                res = c/10;
                c = c % 10;
            }else{
                res = 0;
            }
            d = *(*result + i + j-1)-'0';

            h = d + c + resSum;
            if(h >= 10){
                resSum = 1;
                h = h%10;
            }else{
                resSum = 0;
            } //printf("[%d]%d ",i + j-1,h);
            //printf(" res = %d",resSum);
            *(*result + i + j-1)= h + '0';
        }
         //printf("[%d]%d",i+j-1,resSum+res);
        if(resSum!=0 || res!=0){
            (*(*result+i+j-1))+=resSum+res;
            res=0;
            resSum=0;
            //printf("%d ",resSum+res);
        }
        //printf("\n");
    }
    if(resSum!=0){
        *(*result)+=resSum+res+'0';
    }else{
        while(*(*result+i)=='\0'){
            i++;
        }
        while(j+i<=sizeRes){
            *(*result+j)=*(*result+j+i);
            j++;
        }
    }
    *(*result + sizeRes) = '\0';
    removeLeadingZero(*result);
    if(k==1){
        addChar(*result,'-');
    }
    if(g1==0){
        number2++;
    }
    return 0;
}
//#################################################################
int calculate(const char* expr, char **result){
    if(expr == NULL || result == NULL){
        return 1;
    }
    if(validate_expression(expr)!=0){
        return 2;
    }
    int i=0,d=0;
    *result=calloc(strlen(expr)+1,sizeof(char));
    if(*result==NULL){
        return 3;
    }
    char *temp, *temp2, znak;
    temp=calloc(strlen(expr)+1,sizeof(char));
    if(temp==NULL){
        free(*result);
        return 3;
    }
    temp2=calloc(strlen(expr)+1,sizeof(char));
    if(temp2==NULL){
        free(*result);
        free(temp);
        return 3;
    }
    i=injectNumber(expr,*result);

    while(*(expr+i)!='\0'){
        znak=*(expr+i);
        i+=injectNumber(expr+i+1,temp)+1;
        strcpy(temp2,*result);
        free(*result);
        switch(znak){
            case '+':{
                d=add(temp2,temp,result);
                break;
            }
            case '-':{
                d=subtract(temp2,temp,result);
                break;
            }
            case '*':{
                d=multiply(temp2,temp,result);
                break;
            }
        }
        if(d==3){
            free(*result);
            free(temp2);
            free(temp);
            return 3;
        }
    }
    free(temp);
    free(temp2);
    return 0;
}
//#################################################################
int validate_expression(const char *expr){
    if(expr==NULL){
        return 2;
    }
    if(*expr!='-' && !isdigit(*expr)){
        return 1;
    }
    if(strlen(expr)==0){
        return 1;
    }
    if(strspn(expr,"0123456789-*+")!=strlen(expr)){
        return 1;
    }
    const char *n;
    n=strpbrk(expr,"0123456789-");

    do{
        n=strpbrk(n,"+-*");
        if(n==NULL){
            break;
        }
        if(*(n+1)=='\0'){
            return 1;
        }
        if(*n == '-' && ( *(n + 1)!='-' && !isdigit(*(n + 1)))){
            return 1;
        }
        if( *(n+1)=='-'){
            if( !isdigit(*(n + 2))){
                return 1;
            }
            n=strpbrk(n+2,"0123456789");
        }else{
            if( !isdigit(*(n + 1))){

                return 1;
            }
             n=strpbrk(n+1,"0123456789");
        }


    }while(n!=NULL);





    return 0;
}

void addChar(char *a,char c){
    int i=strlen(a)+1;
    //int io=i;
    while((a+i)!=NULL && i>0){
        if(a+i-1!=NULL){
            *(a+i)=*(a+i-1);
        }
        i--;
    }
    i=0;
    while(isdigit(*(a+i)) || *(a+i)=='-'){
        i++;
        if(*(a+i)=='\0'){
            break;
        }
    }
    *(a+i)='\0';
    *a=c;
}

int validate(const char * number){
    if(number==NULL){
        return -1;
    }
    int j=0,size=strlen(number);
    if(strlen(number)==0){
        return 2;
    }
    if(size>1 && *number=='0'){
        return 2;
    }
    if(*number=='-'){
        if(size==1){
            return 2;
        }else{
            j++;
        }
    }
    for(;j<=size && *(number+j)!='\0' &&(number+j)!=NULL; j++){
        if(*(number+j)>':'-1 || *(number+j)<'0'){
            return 2;
        }
    }

    return 0;
}
int compare(const char* number1, const char* number2){
    if(number1==NULL || number2==NULL){
        return 2;
    }
    if(validate(number1)==2 || validate(number2)==2){
        return 3;
    }
    if(isNegative(number1)>isNegative(number2)){
        return -1;
    }else if(isNegative(number1)<isNegative(number2)){
        return 1;
    }
    if(strlen(number1)>strlen(number2)){
        return 1;
    }else if(strlen(number1)<strlen(number2)){
        return -1;
    }
    int i=0;
    while(*(number1+i)!='\0' && *(number2+i)!='\0'){
        if(*(number1+i)!=*(number2+i)){
            if(*(number1+i)>*(number2+i)){
                if(isNegative(number1)){
                    return -1;
                }else{
                    return 1;
                }
            }else{
                if(isNegative(number1)){
                    return 1;
                }else{
                    return -1;
                }
            }
        }
        i++;
    }


    return 0;
}
int isNegative(const char *number){
    if(*number=='-'){
        if(strlen(number)==1){
            return 0;
        }else{
            return 1;
        }
    }
    return 0;
}
void removeLeadingZero(char *number){
    if(number!=NULL){
        int i=0,j=0;
        while(*(number+i)=='0' && strlen(number+i)!=1){
            i++;
        }
        while(*(number+j)!='\0'){
            *(number+j)=*(number+j+i);
            if(*(number+j)=='\0'){
                break;
            }
            j++;
        }
    }
}
int injectNumber(const char *input,char *output){
    if(input==NULL || output==NULL){
        return -1;
    }
    if(validate_expression(input)!=0){
        return -1;
    }
    int i=0;
    if(*(input)=='-'){
        *(output)='-';
        i++;
    }
    while( isdigit(*(input+i)) ){
        *(output+i)=*(input+i);
        i++;
    }
    *(output+i)='\0';
    return i;
}

