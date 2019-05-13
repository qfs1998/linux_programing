#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#define BUFFERSIZE 4096 
void oops(char* s1,char *s2)
{
    fprintf(stderr,"Error: %s",s1);
    perror(s2);
    exit(1);
}
int main(int argc, char const *argv[])
{
    if(argc!=3)
    // {
    //     printf("source and destination\n");
    //     exit(1);
    // }
    {
        fprintf(stderr,"source and destination");
        exit(1);
    }
    int in_fd=open(*(argv+1),O_RDONLY);
    if(in_fd==-1)
    {
        printf("source open failed\n");
        exit(1);
    }
    int copy_to_fd=creat(*(argv+2),0644);
    char buffer[BUFFERSIZE];
    int n_chars;
    while((n_chars=read(in_fd,buffer,BUFFERSIZE))>0)
    {
        if(write(copy_to_fd,buffer,n_chars)!=n_chars)
        {
            printf("write error\n");
            exit(1);
        }

        printf("read  %d\n",n_chars);
    }
    if(n_chars==-1)
    {
        printf("read error\n");
        exit(1 );
    }
    if(close(in_fd)==-1||close(copy_to_fd)==-1)
    {
        printf ("closed file error\n");
        exit(1);
    }
    return 0;
}
