#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>
using namespace std;
int main()
{
	int fd=0;
	fd=open("./t.txt",O_CREAT|O_RDWR);
	if(fd==-1)
		cout<<"open failed"<<endl;
	char a[]="hello world";
	int num=write(fd,(void *)a,strlen(a));
	cout<<"write_num"<<num<<endl;
	//cout<<strlen(a)<<endl;
	lseek(fd,0,SEEK_SET);
	char b[strlen(a)];
	int num1=read(fd,b,strlen(a));
	cout<<"read_num"<<num1<<endl;

	for(int i=0;i<strlen(a);++i)
		cout<<b[i];
	cout<<endl;
	return 0;
}
