#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include"format_type.h"
#include "tested_declarations.h"
#include "rdebug.h"

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};


int load(const char *filename, int ***ptr, enum save_format_t format);
int statistics_row(int **ptr, struct statistic_t **stats);
void destroy(int ***ptr);
void display(int **ptr);


int ilosctekstowa(const char *filename);
int wierszebinarne(const char *filename);




void display(int **ptr)
{
    if(ptr)
    {
        
        int i;
        for(i=0;*(ptr+i);i++)
        {
            int p;
            for(p=0;;p++)
            {
                if(*(*(ptr+i)+p)==-1)
                {
                    break;
                }
                printf("%d ",*(*(ptr+i)+p));
            }
            
            ///
            printf("\n");
        }
    }
}




void destroy(int ***ptr)
{
    if(ptr)
    {
        int i;
        for(i=0;;i++)
        {
            if(*(*ptr+i)==NULL)
            {
                break;
            }
            free(*(*ptr+i));
        }
        free(*ptr);
    }
}



int wierszebinarne(const char *filename)
{
    if(!filename)
    {
        return 1;
    }
    
    
    FILE*f;
    
    if((f=fopen(filename,"rb"))==NULL)
    {
        return 2;
    }
    int ui=0;
    
    
    if(feof(f))
    {
        fclose(f);
        return -1;
    }
    
    fread(&ui,sizeof(int),1,f);
    
    
    
    int nowalinia=0;
    while(1==1)
    {
        if(ui==-1)
        {
            nowalinia++;
        }
        if(feof(f))
        {
            break;
        }
        fread(&ui,sizeof(int),1,f);
        if(feof(f))
        {
            break;
        }
    }
    
    
    fclose(f);
    if(nowalinia==0)
    {
        return -1;
    }
    
    
    return nowalinia;
}


int ilosctekstowa(const char *filename)
{
    if(!filename)
    {
        return 1;
    }
    
    FILE*f;
    if((f=fopen(filename,"r"))==NULL)
    {
        return 2;
    }
    
    
    
    int ui=0;
    if(feof(f))
    {
        fclose(f);
        return -1;
    }
    
    
    if(fscanf(f,"%d",&ui)==0)
    {
        fclose(f);
        return -1;
    }
    
    int nowalinia=0;
    
    
    while(1==1)
    {
        if(ui==-1)
        {
            nowalinia=nowalinia+1;
        }
        
        if(feof(f))
        {
            break;
        }
        if(fscanf(f,"%d",&ui)==0)
        {
            fclose(f);
            return -1;
        }
        
        if(feof(f))
        {
            break;
        }
    }
    
    
    
    fclose(f);
    if(nowalinia==0)
    {
        return -1;
    }
    
    return nowalinia;
}

int load(const char *filename, int ***ptr, enum save_format_t format)
{
    if(!filename||!ptr||(format!=fmt_text&&format!=fmt_binary))
    {
        return 1;
    }
    
    

    if(format==fmt_text)
    {
        int io=ilosctekstowa(filename);
        if (io==-1)
        {
            return 3;
        }
        
        
        FILE*f;
        if((f=fopen(filename,"r"))==NULL)
        {
            return 2;
        }
        
        
        
        *ptr=(int**)calloc(io+1,sizeof(int*));
        if(*ptr==NULL)
        {
            fclose(f);
            return 4;
        }
        
        
        
        int i;
        for(i=0;i<io;i++)
        {
            *((*ptr+i))=(int*)calloc(1,sizeof(int));
            if(*((*ptr+i))==NULL)
            {
                int p;
                for(p=i-1;p>=0;p--)
                {
                    free(*((*ptr+p)));
                }
                
                free(*ptr);
                fclose(f);
                return 4;
            }
        }
        
        
        int *tymcz;
        int zlicz=1;
        
        for (i=0;i<io;i++)
        {
            int p;
            for(p=0;;p++)
            {
                tymcz=(int*)realloc(*((*ptr+i)),zlicz*sizeof(int));
                if(!tymcz)
                {
                    int k;
                    for(k=0;k<io;k++)
                    {
                        free(*((*ptr+k)));
                    }
                    free(*ptr);
                    fclose(f);
                    return 4;
                }
                
                zlicz++;
                int n=fscanf(f,"%d",tymcz+p);
                if(!n)
                {
                    int k;
                    for(k=0;k<io;k++)
                    {
                        free(*((*ptr+k)));
                    }
                    free(*ptr);
                    fclose(f);
                    return 3;
                }
                
                
                
                *((*ptr+i))=tymcz;
                if(*(tymcz+p)==-1||feof(f))
                {
                    break;
                }
            }
            zlicz=1;
        }
        fclose(f);
        
        
        *(*ptr+io)=NULL;
    }
    
    
    else if(format==fmt_binary)
    {
        int w=wierszebinarne(filename);
        if(w==-1)
        {
            return 3;
        }
        FILE*f;
        
        
        if((f=fopen(filename,"rb"))==NULL)
        {
            return 2;
        }
        
        *ptr=(int**)calloc(w+1,sizeof(int*));
        if(*ptr==NULL)
        {
            fclose(f);
            return 4;
        }
        
        
        
        int i;
        for (i=0;i<w;i++)
        {
            *((*ptr+i))=(int*)calloc(1,sizeof(int));
            if(*((*ptr+i))==NULL)
            {
                int p;
                for(p=i-1;p>=0;p--)
                {
                    free(*((*ptr+p)));
                }
                free(*ptr);
                fclose(f);
                return 4;
            }
        }
        
        
        int *tymcz;
        int zlicz=1;
        
        
        for(i=0;i<w;i++)
        {
            int p;
            for(p=0;;p++)
            {
                tymcz=(int*)realloc(*((*ptr+i)),zlicz*sizeof(int));
                if(!tymcz)
                {
                    
                    int k;
                    for(k=0;k<w;k++)
                    {
                        free(*((*ptr+k)));
                    }
                    free(*ptr);
                    fclose(f);
                    return 4;
                }
                
                zlicz++;
                
                if(fread(tymcz+p,sizeof(int),1,f)!=1)
                {
                    int k;
                    for(k=0;k<w;k++)
                    {
                        free(*((*ptr + k)));
                    }
                    
                    free(*ptr);
                    fclose(f);
                    return 3;
                }
                *((*ptr+i))=tymcz;
                if(*(tymcz+p)==-1||feof(f))
                {
                    break;
                }
            }
            zlicz=1;
        }
        
        fclose(f);
        *(*ptr+w)=NULL;
    }
    return 0;
}

int statistics_row(int **ptr, struct statistic_t **stats)
{
    if(!ptr||!stats)
    {
        return -1;
    }
    
    int i=0;
    
    
    
    for(;*(ptr+i);i++);
    
    *stats=(struct statistic_t*)malloc(sizeof(struct statistic_t)*i);
    if(*stats==NULL)
    {
        return -2;
    }
    
    
    int maximum=0,minimum=0,sum=0,p=0;
    float avg=0,summa=0;
    
    for(i=0;*(ptr+i);i++)
    {
        p=0;
        sum=0;
        summa=0;
        
        minimum=*(*(ptr+i)+p);
        maximum=*(*(ptr+i)+p);
        for(;;p++)
        {
            if(*(*(ptr+i)+p)==-1&&p==0)
            {
                (*stats+i)->min=-1;
                (*stats+i)->max=-1;
                (*stats+i)->avg=-1;
                (*stats+i)->range=-1;
                (*stats+i)->standard_deviation=-1;
                break;
            }
            
            if(*(*(ptr+i)+p)==-1)
            {
                break;
            }
            
            if(*(*(ptr+i)+p)>maximum)
            {
                maximum=*(*(ptr+i)+p);
            }
            if(*(*(ptr+i)+p)<minimum)
            {
                minimum=*(*(ptr+i)+p);
            }
            
            sum+=*(*(ptr+i)+p);
        }
        if(p==0)
        {
            continue;
        }
        avg=(float)sum/p;
        (*stats+i)->min=minimum;

        (*stats+i)->max=maximum;
        (*stats+i)->avg=avg;
        (*stats+i)->range=maximum-minimum;
        
        for(p=0;;p++)
        {
            if(*(*(ptr+i)+p)==-1&&p==0)
            {
                (*stats+i)->standard_deviation=-1;
                break;
            }
            
            if(*(*(ptr+i)+p)==-1)
            {
                break;
            }
            summa+=(float)pow(*(*(ptr+i)+p)-avg,2);
        }
        (*stats+i)->standard_deviation=(float)sqrt(summa/p);
    }
    return i;
}







int main(void)
{
    char*path=(char*)calloc(40,sizeof(char));
    if(!path)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    
    printf("Podaj nazw plik:");
    
    
    scanf("%39s", path);
    while(getchar()!='\n');
    
    
    int binarny=0;
    int tekstowy=0;
    int dlugosc=(int)strlen(path);
    
    

    if(*(path+dlugosc-1)=='t'&&*(path+dlugosc-2)=='x'&&*(path+dlugosc-3)=='t'&&*(path+dlugosc-4)=='.')
    {
        tekstowy=1;
    }
    else if(*(path+dlugosc-1)=='n'&&*(path+dlugosc-2)=='i'&&*(path+dlugosc-3)=='b'&&*(path+dlugosc-4)=='.')
    {
        binarny=1;
    }
    else
    {
        printf("Unsupported file format");
        free(path);
        return 7;
    }
    
    
    int**tablica;
    
    int n=load(path,&tablica,tekstowy>binarny?fmt_text:fmt_binary);
    if(n==2)
    {
        printf("Couldn't open file");
        free(path);
        return 4;
    }
    
    if(n==3)
    {
        printf("File corrupted");
        free(path);
        return 6;
    }
    
    if(n==4)
    {
        printf("Failed to allocate memory");
        free(path);
        return 8;
    }
    
    
    
    struct statistic_t *stats;
    n=statistics_row(tablica, &stats);
    if(n==-2)
    {
        printf("Failed to allocate memory");
        free(path);
        return 8;
    }
    
    int i;
    
    
    for(i=0;i<n;i++)
    {
        printf("%d %d %d %.2f %.2f\n",(stats+i)->min,(stats+i)->max,(stats+i)->range,(stats+i)->avg,(stats+i)->standard_deviation);
    }
    
    
    
    
    
    free(path);
    free(stats);
    destroy(&tablica);
    return 0;
}


