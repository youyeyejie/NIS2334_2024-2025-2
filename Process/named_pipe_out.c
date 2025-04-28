#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 128

int main()
{
    char *file = "testfile/fifo.txt";
    int fd = open(file, O_RDONLY);
    if(fd<0)
    {
        perror("open failed");
    }
    printf("open fifo.txt success! \n");
    umask(0);
    ssize_t ret = mkfifo(file, 0777);
    if(ret < 0)
    {
        if(errno != EEXIST)
            perror("mkfifo failed.");
    }
    printf("mkfifo success.\n");
    char buf[BUFFER_SIZE];
    char outFilename[] = "testfile/target.txt";
    int out = open(outFilename, O_CREAT | O_TRUNC | O_RDWR, 0666);
    while(1)
    {
        sleep(1);
        memset(buf, 0, sizeof(buf));
        ret = read(fd, buf, BUFFER_SIZE-1);
        if(ret<0)
        {
            perror("read failed.\n");
        }
        else if(ret==0)
        {
            printf("write closed.\n");
            return -1;
        }
        else
        {
            write(out, buf, strlen(buf));
            printf("read from buffer and write to output: %s\n", buf);
        }
    }
    close(out);
    close(fd);
    return 0;
}