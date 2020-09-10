#include "comparators.h"
#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int sort(void* ptr, int length, int size, int(*comp)(const void*, const void*)){
    if(ptr==NULL || length<1 || size<1 || comp==NULL) return 1;

    for (int i=0; i<length -1; i++){
        for (int j=0; j<length -i-1; j++){
            void* ptr1 = ((unsigned char*)ptr + (j *size));
            void* ptr2 = ((unsigned char*)ptr + ((j + 1) * size));
            if (comp(ptr1, ptr2) > 0){
                swap(ptr1, ptr2, size);
    }}}
return 0;
}

int comp_int(const void* ptr1, const void* ptr2){
    if (ptr1==NULL || ptr2==NULL) return 0;
    int* p1 = (int*)ptr1;
    int* p2 = (int*)ptr2;

    if (*p1 > *p2) return 1;
    else if(*p1 < *p2) return -1;
    else return 0;
}

int comp_double(const void* ptr1, const void* ptr2){
    if (ptr1==NULL || ptr2==NULL) return 0;
    double* p1 = (double*)ptr1;
    double* p2 = (double*)ptr2;

    if (*p1 > *p2) return 1;
    else if (*p1 < *p2) return -1;
    else return 0;
}

int comp_point(const void* ptr1, const void* ptr2){
    if (ptr1==NULL || ptr2==NULL) return 0;
    point* p1 = (point*)ptr1;
    point* p2 = (point*)ptr2;

    if (p1->x > p2->x) return 1;
    else if (p1->x<p2->x) return -1;
    else{
        if (p1->y > p2->y) return 1;
        else if (p1->y < p2->y) return -1;
        else return 0;
}}

void swap(void* a, void* b, int len){
    unsigned char* p = a, * q = b, tmp;
    for (int i = 0; i != len; ++i){
        tmp = *(p + i);
        *(p + i) = *(q + i);
        *(q + i) = tmp;
}}
