#include "types.h"
#include "stat.h"
#include "user.h"

char buff[1024];
char buffn[1024];

void xargs(int argc, char *argv[]) {
    int n, m;
    int len, buff_index = 0;
    int i = 1;
    m = 0;
    len = 0;
    char *buf[10];
    if (strcmp(argv[1], "-n") == 0) {
        len = atoi(argv[2]);
        i = 3;
    }

    while((n = read(0, buff+m, sizeof(buff)-m-1)) > 0) {
        m += n;
        buff[m] = '\0';
    }
    for (; i < argc; i++) {
        buf[buff_index] = argv[i];
        buff_index++;
    }

    if (len > 0) {
        i = 0;
        n = 0;
        while (i < m) {
            buffn[n] = buff[i];
            if ((buff[i] == '\\' && buff[i+1] == 'n' ) || n == len - 1) {
                if (n == len - 1) 
                    buffn[n+1] = '\0';
                else 
                    buffn[n] = '\0';
                n = 0;
                int p = fork();
                if (p == 0) {
                    buf[buff_index] = buffn;
                    exec(buf[0], (char**)&buf[0]);
                }
                wait();
                while (i < m && !(buff[i] == '\\' && buff[i+1] == 'n')) {
                    i++;
                }
                i+=2;
            } else {
                i++;
                n++;
            }
        }
    } else {
        buf[buff_index] = buff;
        exec(buf[0], (char**)&buf[0]);
        printf(1, "xargs: len=0 exec %s failed\n", argv[1]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(1, "xargs: parameters' num less 2\n");
        exit();
    }
    xargs(argc, argv);
    exit();
}

// echo Ss | xargs echo bye
// echo Ss | xargs -n 1 echo
// echo Ss\nsav\nabc | xargs -n 1 echo
