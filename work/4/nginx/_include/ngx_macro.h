#ifndef __NGX_MACRO_H__
#define __NGX_MACRO_H__

#define PRNT_I(fmt, args...)   printf("[Info %s %d] "fmt "\n", __FUNCTION__, __LINE__, ##args)
#define PRNT_W(fmt, args...)   printf("[WARN %s %d] "fmt "\n", __FUNCTION__, __LINE__, ##args)
#define PRNT_A(fmt, args...)   printf("[ALERT %s %d] "fmt "\n", __FUNCTION__, __LINE__, ##args)
#define PRNT_E(fmt, args...)   printf("[ERR %s %d] "fmt "\n", __FUNCTION__, __LINE__, ##args)
#define PRNT_D(fmt, args...)   printf("[%s %d] "fmt "\n", __FUNCTION__, __LINE__, ##args)
#define PRNT_DD(fmt, args...)  printf("[%s %d] "fmt "\n", __FUNCTION__, __LINE__, ##args)
#define PRNT_DDD(fmt, args...) printf("[%s %d] "fmt "\n", __FUNCTION__, __LINE__, ##args)

#endif