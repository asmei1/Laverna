#include <stdlib.h>

#ifdef TEST
int hide_variable = 123;
#endif

struct DupaStrcut{
    int a;
    double b;
};

#define Def  123
//This is global variable
int globalna = Def;

/*!
*asdasdasdsada
*/
int main(int argc, char** argv)
{
    //int a = 5 + 10;
	int * a = (int*)malloc(2 * sizeof(int));

    //printf("Hello world");
    return 0;
}



//////
