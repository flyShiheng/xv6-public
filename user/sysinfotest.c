#include "types.h"
#include "stat.h"
#include "user.h"

struct SysInfo {
  uint mem_size;
  uint process_num;
} sinfo;

int main()
{

    sysinfo((int)&sinfo);
    printf(1, "sysinfo %d, %d\n", sinfo.mem_size, sinfo.process_num);
    exit();
}