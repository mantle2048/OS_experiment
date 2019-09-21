#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("进程创建失败\n");
	}
	else if(pid==0){
		printf("我是子进程1,ID: %d\n", getpid());
	}
	else{
		pid_t pid2; 
		pid2=fork(); 
		if(pid2<0){
			printf("创建进程失败\n");
		}
		else if(pid2==0){
			printf("我是子进程2,ID: %d  ", getpid());
		}
		else{
			printf("我是父进程,ID:%d  ",getpid()); 
			printf("我的子进程1的ID:%d  ",pid); 
			printf("我的子进程2的ID:%d\n",pid2);
		}
	}
	return 0;

}