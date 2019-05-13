#include<stdio.h>
#include<stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int argc, char const *argv[])
{
    FILE * fp;
    if(argc==1)
    {
        do_more(stdin);
    }
    else 
    {
        while(argc--)
        {
            if((fp=fopen(*++argv,"r"))!=NULL)
            {
                do_more(fp);
                fclose(fp);
            }
            else
            {
                exit(1);
            }
            
        }
    }
    return 0;
}

void do_more(FILE *f)
{
    char line[LINELEN];
    int num_of_line=0;
    int see_more(),reply;

    while(fgets(line,LINELEN,f))
    {
        if(num_of_line==PAGELEN)
        {
            reply=see_more();
            if(reply==0)
                break;
            num_of_line-=reply;

        }
        if(fputs(line,stdout)==EOF)
            exit(1);
        num_of_line++;
    }
    return ;
}

int see_more()
{
    int c;
    printf("\033[7m more?\033[m");

    while((c=getchar())!=EOF)
    {
        switch (c)
        {
            case 'q':
                return 0;
            case ' ':
                return PAGELEN;
            case '\n':
                return 1;
        }
    }
    return 0;
}