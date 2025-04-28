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
    int fd = open(file, O_WRONLY);
    if(fd<0)
    {
        perror("open failed");
    }
    printf("open fifo.txt success! \n");
    char inFilename[] = "testfile/local.txt";
    int in = open(inFilename, O_RDWR, 0666);
    umask(0);
    ssize_t ret = mkfifo(file, 0777);
    if(ret < 0)
    {
        if(errno != EEXIST)
            perror("mkfifo failed.");
    }
    printf("mkfifo success.\n");
    char buf[BUFFER_SIZE];
    while((ret = read(in, buf, BUFFER_SIZE - 1)) > 0)
    {
        ret = write(fd, buf, strlen(buf));
        if(ret<0)
        {
            perror("write failed.\n");
        }
        printf("read from input and write to buffer: %s\n", buf);
        memset(buf, 0, sizeof(buf));
    }
    printf("read closed.\n");
    close(in);
    close(fd);
    return 0;
}