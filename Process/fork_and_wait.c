#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    // 创建子进程
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子进程执行的代码
        printf("I'm the child process. My pid is %d\n", getpid());
        // 子进程执行一些简单任务，这里以打印1 - 5为例
        for (int i = 1; i <= 5; i++) {
            printf("Child: %d\n", i);
        }
        // 子进程执行完毕，正常退出
        exit(EXIT_SUCCESS);
    } else {
        // 父进程执行的代码
        printf("I'm the parent process. My pid is %d, and child pid is %d\n", getpid(), pid);
        // 父进程等待子进程结束
        int status;
        pid_t wpid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process %d exited with status %d\n", wpid, WEXITSTATUS(status));
        }
        // 父进程执行一些简单任务，这里以打印6 - 10为例
        for (int i = 6; i <= 10; i++) {
            printf("Parent: %d\n", i);
        }
    }
    return 0;
}