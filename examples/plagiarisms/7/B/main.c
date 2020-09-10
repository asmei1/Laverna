#include <stdio.h>
#include <stdlib.h>
#include "comparators.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(){
    int x;

        printf("Enter data type: ");
    int xx=scanf("%d", &x);
    if (xx!=1){ printf("Incorrect input"); return 1; }
    else if (x>2 || x <0){ printf("Incorrect input data"); return 2; }

    int size;
    printf("Enter array size: ");
    xx = scanf("%d", &size);
    if (xx!=1){ printf("Incorrect input"); return 1; }
    else if (size < 1){ printf("Incorrect input data"); return 2; }

    if (x==0){
        int* intArray = (int*)malloc(sizeof(int) * size);
        if(intArray==NULL){ printf("Failed to allocate memory"); return 8; }

        printf("Enter ints: \n");
        for (int i=0; i<size; i++){
            xx = scanf("%d", intArray + i);
            if (xx != 1){ printf("Incorrect input"); free(intArray); return 1;}
        }
        sort(intArray, size, sizeof(int), comp_int);

        for (int i=0; i<size; i++){ printf("%d ", *(intArray + i)); }
        free(intArray);
    }
    else if(x == 1){
        double* Array=(double*)malloc(sizeof(double) * size);
        if (Array==NULL){ printf("Failed to allocate memory"); return 8; }

            printf("Enter doubles: \n");
        for (int i=0; i<size; i++){
            xx = scanf("%lf", Array +i);
            if (xx != 1){ printf("Incorrect input"); free(Array); return 1;}
        }
        sort(Array, size, sizeof(double), comp_double);
        for (int i=0; i<size; i++){ printf("%lf ", *(Array + i));}
        free(Array);
    }
    else if (x==2){
        point* pointArray=(point*)malloc(sizeof(point) * size);
        if (pointArray==NULL){ printf("Failed to allocate memory"); return 8;}

            printf("Enter points: \n");
        for (int i=0; i<size; i++){
            xx = scanf("%lf", &(pointArray +i)->x);
            if (xx!=1){printf("Incorrect input"); free(pointArray); return 1;}
            xx = scanf("%lf", &(pointArray +i)->y);
            if (xx!=1){ printf("Incorrect input"); free(pointArray); return 1;}
        }

        sort(pointArray, size, sizeof(point), comp_point);
        for (int i=0; i<size; i++){
            printf("%lf ", (pointArray +i)->x);
            printf("%lf\n", (pointArray +i)->y);
        }
        free(pointArray);
    }
return 0;
}
