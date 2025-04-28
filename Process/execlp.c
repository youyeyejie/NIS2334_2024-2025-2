#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子进程中使用execlp执行date命令，显示当前日期和时间
        if (execlp("date", "date", NULL) == -1) {
            perror("execlp error in child");
            exit(EXIT_FAILURE);
        }
    } else {
        // 父进程等待子进程结束
        int status;
        pid_t wpid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process %d exited with status %d\n", wpid, WEXITSTATUS(status));
        }
        printf("Parent process %d continues.\n", getpid());
    }
    return 0;
}