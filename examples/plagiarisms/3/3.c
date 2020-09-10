#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
int main()
{
    unsigned char kod[1000];
    unsigned char szyfr[1000];
    int i;
    int enigma;
    int q=0;
    printf("Podaj kod:\n");
    for(i=0; i<1000; i++)
    {
        q++;
        kod[i]=getchar();
        if(kod[i]=='\n')
        {
            kod[i]='\0';
            break;
        }
    }
    printf("Podaj enigme:\n");
    scanf("%d", &enigma);
    for(i=0; i<q-1; i++)
    {

        if(kod[i]==' ')
        {
          szyfr[i]=' ';
        }
        else if(islower(kod[i]))
        {
            szyfr[i]=(kod[i]+(enigma%26));
            if(szyfr[i]>122)
            {
                szyfr[i]=szyfr[i]-26;
            }
        }
        else if(isupper(kod[i]))
        {

            szyfr[i]=(kod[i] + (enigma%26));
            if(szyfr[i]>90)
            {
                szyfr[i] = szyfr[i]-26;
            }
        }
        printf("%c", szyfr[i]);
    }



    return 0;
}
