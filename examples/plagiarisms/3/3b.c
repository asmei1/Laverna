#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
int main()
{

    unsigned char s[1000];
    unsigned char kodzik[1000];
    int i,szyfr;
    int k=0;
    printf("Podaj tekst do zaszyfrowania:\n");
    for(i=0; i<1000; i++)
    {
        k++;
        kodzik[i]=getchar();
        if(kodzik[i]=='\n')
        {
            kodzik[i]='\0';
            break;
        }
    }
    printf("Podaj opcje szyfru:\n");
    scanf("%d", &szyfr);
    for(i=0; i<k-1; i++)
    {
        if(kodzik[i]==' ')
        {
          s[i]=' ';
        }
        else if(isupper(kodzik[i]))
        {
            s[i]=(kodzik[i] + (szyfr%26));
            if(s[i]>90)
            {
                s[i] = s[i]-26;
            }
        }
        else if(islower(kodzik[i]))
        {
            s[i]=(kodzik[i]+(szyfr%26));
            if(s[i]>122)
            {
                s[i]=s[i]-26;
            }
        }
        
        printf("%c", s[i]);
    }
return 0;
}


