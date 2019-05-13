#include<unistd.h>
#include<stdio.h>
int main()
{
    char buffer[128];
    int nread;
    nread=read(0,buffer,128);
    if(nread==-1)
        write(2,"a reader error has occurred\n",50);
    if(write(1,buffer,nread)!=nread)
        write(2,"a writer error has occurred\n",50);
    return 0;

}