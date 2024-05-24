#include "types.h"
#include "stat.h"
#include "user.h"

int count = 0;

void proc(int parent_fd, int fdx) {
    count++;
    int n = 0;
    int index = 0;
    int arr[36] = {0};
    while (1) {
        read(parent_fd, &n, 4);
        if (n == 0) break;
        arr[index] = n;
        index++;
    }
    close(parent_fd);
    close(fdx);

    int pipefd[2];
    pipe(pipefd);
    int p;
    p = fork();
    if (p == 0) {
        if (count < 9) {
            proc(pipefd[0], pipefd[1]);
        }
        int n = 0;
        int index = 0;
        int arr[36] = {0};
        while (1) {
            read(pipefd[0], &n, 4);
            if (n == 0) break;
            arr[index] = n;
            index++;
        }
        printf(1, "primes %d\n", arr[0]);
        close(pipefd[0]);
        close(pipefd[1]);
        exit();
    }

    printf(1, "primes %d\n", arr[0]);
    for (int i = 1; i < index; ++i) {
        if (arr[i] % arr[0] != 0) {
            write(pipefd[1], &arr[i], 4);
        }
    }

    write(pipefd[1], &n, 4);
    wait();
    close(pipefd[0]);
    close(pipefd[1]);
    exit();
}

int main() {
    int pipefd[2];
    pipe(pipefd);
    int p;
    p = fork();
    if (p == 0) {
        proc(pipefd[0], pipefd[1]);
    }
    int n = 0;
    int index = 0;
    int arr[36] = {0};
    for (int i = 2; i < 36; ++i) {
        arr[index] = i;
        index = index + 1;
    }
    printf(1, "primes %d\n", arr[0]);
    for (int i = 1; i < index; ++i) {
        if (arr[i] % arr[0] != 0) {
            write(pipefd[1], &arr[i], 4);
        }
    }
    write(pipefd[1], &n, 4);
    close(pipefd[0]);
    close(pipefd[1]);
    wait();
    exit();
}