#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void child_task(int num) {
    for (int i = 1; i <= 3; i++) {
        printf("Child %d: Task %d\n", num, i);
    }
    // exit(EXIT_SUCCESS);
}

int main() {
    pid_t pid1, pid2;
    // 创建第一个子进程
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork error for pid1");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        child_task(1);
    }
    // 创建第二个子进程
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork error for pid2");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        child_task(2);
    }
    // 父进程等待两个子进程结束
    int status1, status2;
    pid_t wpid1 = wait(&status1);
    pid_t wpid2 = wait(&status2);
    if (WIFEXITED(status1)) {
        printf("Child process %d exited with status %d\n", wpid1, WEXITSTATUS(status1));
    }
    if (WIFEXITED(status2)) {
        printf("Child process %d exited with status %d\n", wpid2, WEXITSTATUS(status2));
    }
    printf("Parent process finished waiting for children.\n");
    return 0;
}