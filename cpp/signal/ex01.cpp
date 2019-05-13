#include<signal.h>
#include<sys/unistd.h>
#include<stdio.h>
#include<iostream>
using namespace std;

static void sigHandle(int sig)
{
    //if(sig==SIGINT)
    //{

        //ctrl+c to int 
        //cout<<"process is been Int"<<endl;
        printf("process is been Int\n");
    //}

}
 

int main(int argc, char const *argv[])
{
    

    signal(SIGINT,sigHandle);
        for(int i=0;;++i)
    {
        cout<<i<<'\n';
        sleep(1);
    }
    return 0;
}
