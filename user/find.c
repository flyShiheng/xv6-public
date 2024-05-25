#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char* fmtname(char *path) {
    char *p;
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;
    return p;
}

void find(char *path, char *file) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        printf(1, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        printf(1, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
    case T_FILE:
        if (strcmp(file, fmtname(path)) == 0)
            printf(1, "file: %s %d %d %d\n", path, st.type, st.ino, st.size);
        break;
    case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf(1, "find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
                printf(1, "find: cannot stat %s\n", buf);
                continue;
            }
            if (strcmp(de.name, ".") && strcmp(de.name, "..")) {
                find(buf, file);
            }
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if(argc < 3){
        printf(1, "find: please input file name\n");
        printf(1, "find dir destination\n");
        exit();
    }
    find(argv[1], argv[2]);
    exit();
}
