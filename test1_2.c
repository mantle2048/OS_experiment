#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("���̴���ʧ��\n");
	}
	else if(pid==0){
		printf("�����ӽ���1,ID: %d\n", getpid());
	}
	else{
		pid_t pid2; 
		pid2=fork(); 
		if(pid2<0){
			printf("��������ʧ��\n");
		}
		else if(pid2==0){
			printf("�����ӽ���2,ID: %d  ", getpid());
		}
		else{
			printf("���Ǹ�����,ID:%d  ",getpid()); 
			printf("�ҵ��ӽ���1��ID:%d  ",pid); 
			printf("�ҵ��ӽ���2��ID:%d\n",pid2);
		}
	}
	return 0;

}