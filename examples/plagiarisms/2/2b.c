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


Example 1: 1.0
Example 2: 0.9944815567818762
Example 3: 0.05143861596817467
Example 3: 0.5982051993708947
Example 4: 0.1747920665387076
Example 6: 0.12965008518525453
Example 6: 0.11856664107988692

//liczby
Example 2 AB: 0.9944815567818762
Example 3 AB: 0.05143861596817467
Example 3 BA: 0.5982051993708947
Example 4 AB: 0.1747920665387076
Example 4 BA: 0.2507997440818938
Example 6 AB: 0.12965008518525453
Example 6 BA: 0.11856664107988692

//znaki
Example 2 AB: 0.9947997919916797
Example 3 AB: 0.04222520107238606
Example 3 BA: 0.6273458445040214
Example 4 AB: 0.8053949903660886
Example 4 BA: 0.8053949903660886
Example 6 AB: 0.1488296576917873
Example 6 BA: 0.10959274793667975

}
