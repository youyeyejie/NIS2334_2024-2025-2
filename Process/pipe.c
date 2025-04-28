#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 10

int main()
{
    int fds[2];
    char buf[BUFFER_SIZE];
    // for (int i=0; i<BUFFER_SIZE; i++) buf[i]='0';
    //临时数组，用于存放通信的消息
    if(pipe(fds) < 0)
    {
        perror("pipe");
        return 1;
    }
    char inFilename[] = "testfile/local.txt";
    char outFilename[] = "testfile/target.txt";
    int in = open(inFilename, O_RDWR, 0666);
    int out = open(outFilename, O_CREAT | O_TRUNC | O_RDWR, 0666);
    //fflush(stdout);
    ssize_t length;
    pid_t pid = fork();
    if(pid == 0)
    {
        //子进程只写，关闭读出端
        printf("child process %d\n", getpid());
        close(fds[0]);
        while((length = read(in, buf, BUFFER_SIZE - 1)) > 0)
        {
            printf("child process %d read \"%s\" from file\n", getpid(), buf);
            write(fds[1],buf,strlen(buf)+1);
            printf("child process %d write \"%s\" to pipe\n", getpid(), buf);
            //将buf的内容写入管道
            memset(buf, 0, sizeof(buf));
        }
        close(fds[1]);
    }
    else
    {
        //父进程只读，关闭写入端
        printf("parent process %d\n", getpid());
        close(fds[1]);
        //从管道里读数据，放入buf
        while((length = read(fds[0],buf,BUFFER_SIZE)) > 0)
        {
            printf("parent process %d read \"%s\" from pipe\n", getpid(), buf);
            write(out, buf, strlen(buf));
            printf("parent process %d write \"%s\" to file\n", getpid(), buf);
            memset(buf, 0, sizeof(buf));
        }
        close(fds[0]);
    }
    return 0;
}