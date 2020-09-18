#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main ()
{
    char tablica[1002];
    int i=0,len,kod;

    printf("Podaj tekst:\n");
    fgets(tablica,1002,stdin);
    len=(unsigned)strlen(tablica)-1;
    printf("Podaj znak kodowy:\n");
    scanf("%d",&kod);
    if(kod>26)
        kod=kod%26;

    for ( i = 0; i < len; i++)
    {
        if(isalpha(tablica[i]))
        {
            if(islower(tablica[i]))
            {
                tablica[i]=toupper(tablica[i]);
                 tablica[i]+=kod;
                if(tablica[i]>90)
                    tablica[i]-=26;

                tablica[i]=tolower(tablica[i]);
                continue;
            }
                if(tablica[i]==' ')
                    continue;

                tablica[i]+=kod;
                if(tablica[i]>90)
                    tablica[i]-=26;
        }
    }
    for ( i = 0; i < len; i++)
    {
        printf("%c",tablica[i]);
    }

}
