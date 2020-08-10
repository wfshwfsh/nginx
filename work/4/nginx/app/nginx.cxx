
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "ngx_macro.h"
#include "ngx_c_conf.h"  //和配置文件处理相关的类,名字带c_表示和类有关
#include "ngx_signal.h"
#include "ngx_func.h"    //各种函数声明

//和设置标题有关的全局量
char **g_os_argv;            //原始命令行参数数组,在main中会被赋值
char *gp_envmem = NULL;      //指向自己分配的env环境变量的内存
int  g_environlen = 0;       //环境变量所占内存大小

void test1__argv_env(int argc, char *const *argv, bool log_on)
{
    g_os_argv = (char **) argv;
    
    if(log_on)
    {
        for(int i=0; i<argc; i++)
            PRNT_DDD("g_os_argv[%d] = %p, %s", i, g_os_argv[i], g_os_argv[i]);
        
        for (int i=0; environ[i]; i++) 
            PRNT_DDD("environ[%d] = %p, %s", i, environ[i], environ[i]);
    }
    //修改進程名--- 先把环境变量搬家
    ngx_init_setproctitle();
    ngx_setproctitle("nginx: master process");
    
    if(log_on)
    {
        for(int i=0; i<argc; i++)
            if(g_os_argv[i])
                PRNT_DDD("g_os_argv[%d] = %p, %s", i, g_os_argv[i], g_os_argv[i]);
            else
                break;
        
        for (int i=0; environ[i]; i++) 
        {
            PRNT_DDD("environ[%d] = %p, %s", i, environ[i], environ[i]);
        }
    }
}

void test2__get_conf_params(void)
{
    CConfig *p_config = CConfig::GetInstance();

    //read for nginx.conf
    if(!p_config->Load("nginx.conf"))
    {
        PRNT_E("load conf failed");
        exit(1);
    }

    //DBG for read CONF items
    for(int i=0; p_config->m_ConfigItemList[i]!=NULL; i++)
    {
        PRNT_I("%s: %s"
            , p_config->m_ConfigItemList[i]->ItemName
            , p_config->m_ConfigItemList[i]->ItemContent);
    }
    
    delete(p_config);
}

int main(int argc, char *const *argv)
{
    test1__argv_env(argc, argv, false);
    test2__get_conf_params();
    
    for(int i=0;;i++)
    {
        sleep(1);
    }
    
    return 0;
}


