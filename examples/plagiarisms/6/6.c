#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "tested_declarations.h"
#include "rdebug.h"
int add(const char* number1, const char* number2, char** result);
int subtract(const char* number1, const char* number2, char** result);
int validate(const char *number);
int compare(const char* number1, const char* number2);
int isNegative(const char *number);
void zero_delete(char *number);
void addChar(char *a,char c);
int multiply(const char* number1, const char* number2, char** result);
int validate_expression(const char *expr);
int calculate(const char* expr, char **result);

int main(void)
{
	int a;
	char *tab,*wynik;
	tab=(char*)malloc(sizeof(char)*501);
    if (tab==NULL){printf("Failed to allocate memory"); return 8;}
    printf("Podaj wyrazenie: ");
    a=scanf("%500s",tab);
    while(getchar()!='\n'){};
    a=calculate(tab, &wynik);
    if(a==2){free(tab); printf("Incorrect input"); return 1;}
    if(a==3){free(tab); printf("Failed to allocate memory"); return 8;}
    printf("%s",wynik);
    free(wynik);
    free(tab);
    return 0;
}
int validate(const char * number){
	if(number==NULL) return -1;
	int i=0,x=0,minus=0;
	char temp;
	x=strlen(number);
	if(*number=='-') minus=1;
	if(minus==1 && x==1) return 2;
	if(minus==0){if(*number<'0' || *number>=':') return 2;}
	
	if(x>1 && *(number+i)=='0') return 2;
	for(i=0;i<x;i++){
		temp=*(number+i);
		if(i>0){
			if(temp<'0' || temp>=':') return 2;
		}
	}
	return 0;
}
int add(const char* number1, const char* number2, char** result){
    if(result==NULL || number1==NULL || number2==NULL) return 1;
    
    if(validate(number1)!=0 || validate(number2)!=0) return 2;
    int i=0;
    if(isNegative(number1)==0 && isNegative(number2)==1){
       return subtract(number1,number2+1,result);
    }
	else if(isNegative(number2)==0 && isNegative(number1)==1){
        return subtract(number2,number1+1,result);
    }
	else{
        if(isNegative(number2)==isNegative(number1)){
            int a=0,b=0,c=0,rest=0,x1=0,x2=0,sizeFin=0,j=0,bN=0,lenghtFinal=0,ismo=0;
            const char *ptr;

            x1=strlen(number1);
            x2=strlen(number2);
            sizeFin=(x1>x2)?x2:x1;
            j=(x1>x2)?x1:x2;
            if( number1-1!=NULL && *(number1-1)=='-'){
                ismo++;
            }else if( number2-1!=NULL && *(number2-1)=='-'){
                ismo++;
            }
            *result=(char*)calloc(j+2+ismo,sizeof(char));
            if(*result==NULL) return 3;
            if(isNegative(number1)==1 && isNegative(number2)==1){
                number1++;
                number2++;
                bN=1;
            }
            ptr=(x1>x2)?number1:number2;
            if((*result+j)!=NULL){
                *(*result+j)='\0';
            }

            for(i=1;i<=sizeFin;i++){

                if((number1+x1-i)!=NULL && (number2+x2-i)!=NULL && (result+j-i)!=NULL){

                    if(i<=x1){
                        a=*(number1+x1-i)-'0';
                    }
                    if(i<=x2){
                        b=*(number2+x2-i)-'0';
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
            if(bN==1){
                addChar(*result,'-');
            }
        }
    }

    return 0;
}
int subtract(const char* number1, const char* number2, char** result){
    if(result==NULL || number1==NULL || number2==NULL) return 1;
    
    if(validate(number1)==2 || validate(number2)==2) return 2;
    
    int a=0,b=0,c=0,rest=0,x1=0,x2=0,sizeFin=0,i=0,j=0,negative=0,g;
    const char *ptr,*temp;
    if(isNegative(number2)==1 && isNegative(number1)==0){
        return add(number1,number2+1,result);
    }
	else if(isNegative(number2)==0 && isNegative(number1)==1){
        g=add(number2,number1+1,result);
        if(g==0)addChar(*result,'-');
        return g;
    }
	else if(isNegative(number1)==1 && isNegative(number2)==1){
       return add(number1,number2+1,result);
    }else{
        if(compare(number1,number2)==-1){
            temp=number2;
            number2=number1;
            number1=temp;
            negative=1;
        }
        x1=strlen(number1);
        x2=strlen(number2);
        sizeFin=(x1>x2)?x2:x1;
        j=(x1>x2)?x1:x2;
        int ismo=0;
        if( number1-1!=NULL && *(number1-1)=='-'){
            ismo++;
        }else if( number2-1!=NULL && *(number2-1)=='-'){
            ismo++;
        }
        *result=calloc(j+2+ismo,sizeof(char));
        if(*result==NULL) return 3;
        ptr=(x1>x2)?number1:number2;

        *(*result+j)='\0';
        for(i=1;i<=x2;i++){
            if((number1+x1-i)!=NULL && (number2+x2-i)!=NULL && (result+j-i)!=NULL){
                if(i<=x1){
                    a=*(number1+x1-i)-'0';
                }
                if(i<=x2){
                    b=*(number2+x2-i)-'0';
                }
                c=a-b-rest;
                if(c<0){
                    c+=10;
                    rest=1;
                }
				else rest=0;
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
                }
				else rest=0;
                if(i<=j){
                    *(*result+j-i)=c+'0';
                }
            }
        }
    }
    zero_delete(*result);
    if(negative==1) addChar(*result,'-');
    return 0;
}
void addChar(char *a,char c){
    int i;
    i=strlen(a)+1;
    while((a+i)!=NULL && i>0){
        if(a+i-1!=NULL){
            *(a+i)=*(a+i-1);
        }
        i--;
    }
    i=0;
    while(isdigit(*(a+i)) || *(a+i)=='-'){
        i++;
        if(*(a+i)=='\0') break;
    }
    *(a+i)='\0';
    *a=c;
}
int isNegative(const char *number){
    if(*number=='-'){
        if(strlen(number)==1){
            return 0;
        }
		else return 1;       
    }
    return 0;
}
void zero_delete(char *number){
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
int compare(const char* number1, const char* number2){
    if (number1 == NULL || number2 == NULL) return 2;
    if (validate(number1)==2 || validate(number2)==2) return 3;
    unsigned char negative1 = 0, negative2 = 0;
    if(*(number1) == '-') negative1 = 1;
    if(*(number2) == '-') negative2 = 1;
    if (negative1 == 1 && negative2 == 0) return -1;
    else if (negative1 == 0 && negative2 == 1) return 1;
    if (strlen(number1) == strlen(number2))
    {
        int check = strcmp(number1, number2);
        if (check == 0) return 0;
        if (negative1 == 0 && negative2 == 0){
            if (check > 0) return 1;
            else return -1;
        }
        else
        {
            if (check > 0) return -1;
            else return 1;
        }
    }
    else if(strlen(number1) > strlen(number2)){
        if(negative1 == 1 && negative2 == 1) return -1;
        else if(negative1 == 1 && negative2 == 0) return -1;
        else return 1;
    }
    else{
        if (negative1 == 1 && negative2 == 1) return 1;
        else if (negative1 == 0 && negative2 == 1) return 1;
        else return -1;
    }
}
int multiply(const char* number1, const char* number2, char** result){
    if(result==NULL || number1==NULL || number2==NULL) return 1;
    if(validate(number1)==2 || validate(number2)==2) return 2;

    int x1,x2,rest=0,i=0,j=0,li=1,lj=1,pos=0,l1,l2,iloczyn,size;
    char *ptr,*front,*back,temp;
	x1=strlen(number1);
	x2=strlen(number2);
    if (*number1 == '0' || *number2 == '0'){
        *result = (char*)malloc(2*sizeof(char));
        if ((*result)==NULL) return 3;
        **result = '0';
        *(*result + 1) = '\0';
        return 0;}
    *result = (char*)calloc(sizeof(char),x1+x2+1);
    if ((*result)==NULL) return 3;
    memset(*result,'0',x1+x2);
    for (i=(x2-1); i>=0 && *(number2+i)!='-'; li++, --i){
        l1 = *(number2 + i) - '0';
        for (j=(x1-1);j>=0 && (*(number1 + j)!= '-'); j--, lj++)
        {
            l2 = *(number1 + j) - '0';
            rest = 0;
            iloczyn = l1 * l2;
            pos = lj + li - 1;
            if (i == x2 - 1 && j == x1 - 1){
                *(*result + pos - 1) = iloczyn % 10 + '0';;
                *(*result + pos) = iloczyn / 10 + '0';
            }
            else{
                rest = (*(*result + pos - 1) - '0') + iloczyn % 10;
                *(*result + pos - 1) = rest % 10 + '0';
                if(rest>=10) rest = rest / 10;
                else rest = 0;
                *(*result + pos) = (*(*result + pos) - '0')+ iloczyn / 10 + rest + '0';
            }
        }
        lj = 1;
    }
    ptr=strpbrk(*result+pos, "0");
    if(ptr){
        *ptr = '\0';
        if (*number1 == '-' && *number2 != '-' || *number1 != '-' && *number2 == '-'){
            *ptr = '-';
            *(ptr + 1) = '\0';
        }
    }
    size=strlen(*result);
    front = *result;
    back = (*result + size - 1);
    while(front<back){
        temp = *front;
        *front = *back;
        *back = temp;

        ++front;
        --back;
    }
    return 0;
}
int validate_expression(const char* expr){
    if (expr==NULL) return 2;
    if ((*expr != '-' && !isdigit(*expr)) || strspn(expr, "1234567890+-*") != strlen(expr)) return 1;
    char *tab;
    tab = strpbrk(expr, "-+*");
    while(tab != NULL){
        if(*(tab + 1) != '-' && !isdigit(*(tab + 1))) return 1;
        if(*(tab + 1) == '-'){
            if(*(tab + 2) == '-') return 1;
        }
        tab = strpbrk(tab + 1, "-+*");
    }
    return 0;
}
int calculate(const char* expr, char** result){
    if(expr==NULL || result==NULL) return 1;
    if(validate_expression(expr)!=0) return 2;
    char *num1,*num2,*str,*tab,*op;
    int c=0,x=0,len;
    if(strspn(expr, "-1234567890") == strlen(expr)){
        if(*expr == '-'){
            if (strspn(expr+1, "1234567890") == strlen(expr) - 1){
                *result = (char*)malloc(sizeof(char) * (strlen(expr) + 1));
                strcpy(*result, expr);
                return 0;
            }
        }
        if(strspn(expr, "1234567890") == strlen(expr)){
            *result = (char*)malloc(sizeof(char) * (strlen(expr) + 1));
            strcpy(*result, expr);
            return 0;
        }
    }
    num1=(char*)malloc(sizeof(char)*201);
    if (num1==NULL) return 3;
    num2=(char*)malloc(sizeof(char)*201);
    if (num2==NULL){free(num1); return 3;}

    tab=strpbrk(expr, "1234567890");
    len=strspn(tab, "1234567890");
    if(*expr=='-') len++;       
    strncpy(num1, expr, len);
    *(num1 + len) = '\0';
    op=strpbrk(tab, "+-*");
    do{
        *num2='\0';
        tab=strpbrk(tab+len, "1234567890");
        if(tab==NULL) break;
        len=strspn(tab, "1234567890");
        strncpy(num2,tab, len);
        *(num2+len)='\0';
        if (*op=='-'){
            if (*(op+1)=='-'){
                memmove(num2+1,num2,strlen(num2));
                *num2='-';
                *(num2+len+1)='\0';
            }
            c=subtract(num1,num2,result);
            if(c==3){free(num1); free(num2); return 3;}
        }
        else if (*op=='*'){
            if (*(op+1)=='-'){
                memmove(num2+1, num2, strlen(num2));
                *num2='-';
                *(num2+len+1) = '\0';
            }
            c=multiply(num1, num2, result);
            if(c==3){free(num1); free(num2); return 3;}     
        }
        else{
            if (*(op+1)=='-'){
                memmove(num2+1,num2,strlen(num2));
                *num2='-';
            *(num2+len+1) = '\0';
            }
            c=add(num1,num2,result);
            if(c==3){free(num1);free(num2); return 3;} 
        }
        if(*(tab+len)=='\0') break;
        if(x%2==0){
            str=(char*)realloc(num1,strlen(*result)+1);
            num1=str;
        }   
        else{
            num1=(char*)realloc(str,strlen(*result)+1);
            str=NULL;
        }
        *num1 = '\0';
        num1 = strcpy(num1, *result);
        free(*result);
        if (*(op+1)=='-') op=strpbrk(op+2,"+-*");
        else op=strpbrk(op+1,"+-*");
        x++;
    }while(1);
    free(num2);
    free(num1);
    return 0;
 }

