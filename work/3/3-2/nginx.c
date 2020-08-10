#include <stdio.h>
#include <unistd.h>
#include "signal.h"

int main(int argc, char *const *argv)
{
    printf("非常高兴，大家和老师一起学习《linux c++通讯架构实战》\n");
#if 1//CASE 2
    pid_t pid;
    
    pid = fork();
    if(pid<0)
    {
        printf("fork failed \n");
    }
    else if(pid == 0)
    {
        //child
        setsid();
        for(;;)
        {
            sleep(1); //休息1秒
            printf("子进程休息1秒\n");
        }
        return 0;
    }
    else
    {
        //parents
        for(;;)
        {
            sleep(1); //休息1秒
            printf("父进程休息1秒\n");
        }
        return 0;
    }
#else//CASE 1
    signal(SIGHUP, SIG_IGN);
    for(;;)
    {
        sleep(1); //休息1秒
        printf("休息1秒\n");
    }
#endif
    printf("程序退出，再见!\n");
    return 0;
}


