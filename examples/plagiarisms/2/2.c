#include <stdio.h>
#include <ctype.h>
#include <string.h>
char tab[1002];
int i=0,len,kod;
int main (void)
{
    printf("Podaj tekst:\n");
    fgets(tab,1002,stdin);
    len=(unsigned)strlen(tab)-1;
    printf("Podaj znak kodowy:\n");
    scanf("%d",&kod);
    if(kod>26)
        kod=kod%26;

    for ( i = 0; i < len; i++)
    {
        if(isalpha(tab[i]))
        {
            if(islower(tab[i]))
            {
                tab[i]=toupper(tab[i]);
                 tab[i]+=kod;
                if(tab[i]>90)
                    tab[i]-=26;

                tab[i]=tolower(tab[i]);
                continue;
            }
                if(tab[i]==' ')
                    continue;

                tab[i]+=kod;
                if(tab[i]>90)
                    tab[i]-=26;
        }
    }
    for ( i = 0; i < len; i++)
    {
        printf("%c",tab[i]);
    }
    

        
    
}