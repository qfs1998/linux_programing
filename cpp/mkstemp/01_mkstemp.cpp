#include<stdlib.h>
#include<iostream>
#include<sys/unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdio.h>
//#include <fcntl.h>

using namespace std;
int main(int argc, char const *argv[])
{
    
    struct stat buf;
    if(stat("hello",&buf)==-1)
    {
        fprintf(stderr,"failed to return a stat of file\n");
        exit(-1);
    }
    cout<<"link num: "<<buf.st_nlink<<endl;
    
    link("hello","fuck");
    //refresh the data of buf
    if(stat("hello",&buf)==-1)
    {
        fprintf(stderr,"failed to return a stat of file\n");
        exit(-1);
    }

    cout<<"link num: "<<buf.st_nlink<<endl;
    //5 seconds
    //usleep  10^-3 seconds
    sleep(2);




    //delete the link 
    //only if st_nlink==0 and there are not any processes open the file ,
    //the function unlink(const char *) can delete the file
    //link != file
    /*       每一个文件，都可以通过一个struct stat的结构体来获得文件信息，其中一个成员st_nlink代表文件的链接数。

       当通过shell的touch命令或者在程序中open一个带有O_CREAT的不存在的文件时，文件的链接数为1。

       通常open一个已存在的文件不会影响文件的链接数。open的作用只是使调用进程与文件之间建立一种访问关系，即open之后返回fd，调用进程可以通过fd来read 、write 、 ftruncate等等一系列对文件的操作。
       close()就是消除这种调用进程与文件之间的访问关系。自然，不会影响文件的链接数。在调用close时，内核会检查打开该文件的进程数，如果此数为0，进一步检查文件的链接数，如果这个数也为0，那么就删除文件内容。

       link函数创建一个新目录项，并且增加一个链接数。
       unlink函数删除目录项，并且减少一个链接数。如果链接数达到0并且没有任何进程打开该文件，该文件内容才被真正删除。如果在unlilnk之前没有close，那么依旧可以访问文件内容。
  
       综上所诉，真正影响链接数的操作是link、unlink以及open的创建。
       删除文件内容的真正含义是文件的链接数为0，而这个操作的本质完成者是unlink。close能够实施删除文件内容的操作，必定是因为在close之前有一个unlink操作。
       */
    unlink("fuck");
    cout<<"already unlink"<<endl;


    cout<<"mkstemp"<<endl;
    char  temp_file_name[]="tempXXXXXX";
    int fd=mkstemp(temp_file_name);
    //we need to delete a temp file when we don't need it anymore
    //always do like this
    //only delete the link but the file is still open by our process
    //only when we call the function close(int fd),
    //the file will actually be deleted !
    //sleep(10);

    unlink(temp_file_name);
    size_t num=100;
    size_t write_num=write(fd,"this is a text wrriten into a temp file\nAnd 5 seconds later the file will be deleted\n",100000);
    char readbuf[100];
    lseek(fd,0,SEEK_SET);
    int read_num=read(fd,readbuf,write_num);
    cout<<write_num<<endl;
    cout<<read_num<<endl;
    printf("%s",readbuf);
    //sleep(5);

    close(fd);
    return 0;
}
