#include "types.h"
#include "stat.h"
#include "user.h"

// ms
int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf(1, "sleep n <= 1\n");
        exit();
    }
    int n = atoi(argv[1]);
    printf(1, "sleep n == %d \n", n);
    sleep(n);
    exit();
}