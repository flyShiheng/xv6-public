#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int pipefd[2];
    int p;
    pipe(pipefd);

    p = fork();
    if (p < 0) {
        exit();
    }
    if (p == 0) {
        char buff[10];
        read(pipefd[0], buff, 10);
        printf(1, "child\n");
        write(pipefd[1], "child", 5);
        close(pipefd[0]);
        close(pipefd[1]);
        exit();
    }
    char buff[10];
    write(pipefd[1], "father", 6);
    wait();
    read(pipefd[0], buff, 10);
    printf(1, "father\n");
    close(pipefd[0]);
    close(pipefd[1]);
    exit();
}
