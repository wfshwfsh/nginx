#ifndef __NGX_FUNC_H__
#define __NGX_FUNC_H__

//函数声明
void myconf();    
#define  MYVER  "1.2"
void Rtrim(char *string);
void Ltrim(char *string);

void ngx_init_setproctitle(void);
void ngx_setproctitle(const char *title);

#endif  