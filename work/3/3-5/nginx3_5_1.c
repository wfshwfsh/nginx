#include <stdio.h>
#include <stdlib.h>  //malloc
#include <unistd.h>
#include <signal.h>

int is_signal_in_maskset(sigset_t *maskset, int sig)
{
	int ret;
	switch(sig){
		case SIGQUIT:
			if(sigismember(maskset, sig))
			{	printf("CAN NOT Catch signal QUIT now \n"); ret=1;}
			else
			{	printf("CAN Catch signal QUIT now \n"); ret=0;}
			break;
		case SIGHUP:
			if(sigismember(maskset, sig))
			{	printf("CAN NOT Catch signal SIGHUP now \n"); ret=1;}
			else
			{	printf("CAN Catch signal SIGHUP now \n"); ret=0;}
			break;
		default:
			printf("??? \n");
	}
	return ret;
}

//信号处理函数
void sig_quit(int signo)
{   
	printf("[%s] \n", __FUNCTION__);
    if(signal(SIGQUIT,SIG_DFL) == SIG_ERR)
    {
        printf("无法为SIGQUIT信号设置缺省处理(终止进程)!\n");
        exit(1);
    }
}

int main(int argc, char *const *argv)
{
    sigset_t new_mask, old_mask;
	if(SIG_ERR == signal(SIGQUIT, sig_quit))
	{
		printf("CAN NOT Catch signal QUIT now \n");
		exit(1);
	}

	sigemptyset(&new_mask);
	sigaddset(&new_mask, SIGQUIT);
	is_signal_in_maskset(&new_mask, SIGQUIT);
	is_signal_in_maskset(&new_mask, SIGHUP);
	if(sigprocmask(SIG_BLOCK, &new_mask, &old_mask)<0)
	{
		printf("sigprocmask(SIG_BLOCK) failed \n");
		exit(1);
	}
	else
		printf("sigprocmask(SIG_BLOCK) success \n");

	printf("=== beg to sleep 10 sec === \n");
	sleep(10);
	printf("=== end of sleep 10 sec === \n");


	if(sigprocmask(SIG_SETMASK, &old_mask, NULL)<0)
	{
		printf("sigprocmask(SIG_SETMASK) failed \n");
		exit(1);
	}
	else
		printf("sigprocmask(SIG_SETMASK) success \n");

	if(!is_signal_in_maskset(&old_mask, SIGQUIT))
	{
		printf("=== beg to sleep 10 sec , u can send SIGQUIT=== \n");
		int mysl = sleep(10);
		if(mysl>0)
			printf("sleep(10) still have %d sec \n", mysl);
	}

	printf("GoodBye\n");
    return 0;
}

