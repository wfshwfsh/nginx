

#include <stdio.h>
#include <stdlib.h>  //malloc,exit
#include <unistd.h>  //fork
#include <signal.h>

int test()
{
    static int i=0;
    printf("i = %d \n", i);
    i++;
    if(i%2 == 0)
        return 0;
    else
        return 1;
}

int main(int argc, char *const *argv)
{
    
    //fork();  //一般fork都会成功所以不判断返回值了,我们假定成功
    //fork();

    ((test()&&test())||(test()&&test()));
    // => 邏輯 && 前面若為0 => 後面不執行
    // => 邏輯 || 前面若為1 => 後面不執行
    
    ((fork() && fork()) || (fork() && fork()));
    printf("每个实际用户ID的最大进程数=%ld\n",sysconf(_SC_CHILD_MAX));

    
    
    //for(;;)
    //{        
    //    sleep(1); //休息1秒
    //    printf("休息1秒，进程id=%d!\n",getpid());
    //}
    printf("再见了!\n");
    return 0;
}


