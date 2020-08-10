#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //env
#include <string.h>

#include "ngx_macro.h"
#include "ngx_global.h"

void ngx_init_setproctitle(void)
{
    for(int i=0;environ[i]; i++)
        g_environlen += strlen(environ[i])+1;
    
    gp_envmem = new char[g_environlen];
    memset(gp_envmem, 0, g_environlen);
    
    char *ptmp = gp_envmem;
    
    for(int i=0;environ[i]; i++)
    {
        size_t size = strlen(environ[i])+1;
        strcpy(ptmp, environ[i]); //把原环境变量内容拷贝到新地方【新内存】
        environ[i] = ptmp;        //然后还要让新环境变量指向这段新内存
        ptmp += size;
    }
    return;
}

void ngx_setproctitle(const char *title)
{
    size_t ititlelen = strlen(title);
    
    size_t e_argvlen = 0;     //e表示局部变量吧
    for(int i = 0; g_os_argv[i]; i++)  
        e_argvlen += strlen(g_os_argv[i]) + 1;
    
    size_t esy = e_argvlen + g_environlen;
    if(ititlelen >= esy)
    {
        PRNT_E("invalid title length");
        return;
    }
    
    char *ptmp = g_os_argv[0];
    memset(ptmp, 0, e_argvlen);
    strcpy(ptmp, title);
    ptmp[ititlelen]=0;
    
    g_os_argv[1] = NULL;
    return;
}
