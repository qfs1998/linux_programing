#include<iostream>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int main()
{
    cout<<"this is the begin of father process"<<endl;

    int pid=fork();
    if(pid<0)
    {
        fprintf(stderr,"failed to fork a child process");
        exit(-1);
    }
    else if(pid==0)//child process
    {
         for(int i =0;i<100;++i)
         {
             cout<<i<<"  child process"<<endl;
         }
    }
    else
    {
        // for(int i=0;i<100;++i)
        // {
        //     cout<<i<<"  father process"<<endl;
        // }
        wait(NULL);
        cout<<"child process has completed"<<endl;
    }
    
    return 0;
}