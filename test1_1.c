//	  1）在父进程中，fork返回新创建子进程的进程ID；
//    2）在子进程中，fork返回0；
//    3）如果出现错误，fork返回一个负值；
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t pid;//定义一个进程号变量pid
	pid=fork();//赋予一个进程号,pid就像一个指针，指向子进程的id号，如果当前是在父进程中，pid是儿子的id,如果当前是在儿子进程中，pid=0
	if(pid<0){
		printf("进程创建失败\n");
	}
	else if(pid==0){//pid 
		pid_t pid2; 
		pid2=fork(); 
		if(pid2<0){
			printf("进程创建失败\n");
		}
		else if(pid2==0 ){
			printf("我是子进程2,我的ID: %d\n",getpid());
		}
		else{
			waitpid(pid2);//等儿子执行完
			printf("我是子进程1,我的ID: %d  ",getpid());
			printf("我的子进程的ID: %d\n",pid2);
		}
	}
	else{
		waitpid(pid);
		printf("我是父进程,ID: %d  ",getpid());
		printf("我的子进程的ID: %d\n",pid);
		wait(0);
	}
}
