#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[])
{
    int mask, i;
    char *buf[10];
    if (argc < 3) {
        printf(1, "trace parameters num less 3\n");
        exit();
    }

    mask = atoi(argv[1]);
    trace(mask);
    
    for (i = 2; i < argc; i++) {
        buf[i-2] = argv[i];
    }
    exec(buf[0], (char**)&buf[0]);

    exit();
}