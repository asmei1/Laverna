#include <stdlib.h>

#ifdef TEST
int hide_variable = 123;
#endif

//This is global variable
int globalna = 5;

/*!
*asdasdasdsada
*/
int main(int argc, char** argv)
{
    //int a = 5 + 10;
	int * a = (int*)malloc(2 * sizeof(int));

    int c = a[1];
	int b = *(a + 1);
    //printf("Hello world");
    return 0;
}