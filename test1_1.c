//	  1���ڸ������У�fork�����´����ӽ��̵Ľ���ID��
//    2�����ӽ����У�fork����0��
//    3��������ִ���fork����һ����ֵ��
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t pid;//����һ�����̺ű���pid
	pid=fork();//����һ�����̺�,pid����һ��ָ�룬ָ���ӽ��̵�id�ţ������ǰ���ڸ������У�pid�Ƕ��ӵ�id,�����ǰ���ڶ��ӽ����У�pid=0
	if(pid<0){
		printf("���̴���ʧ��\n");
	}
	else if(pid==0){//pid 
		pid_t pid2; 
		pid2=fork(); 
		if(pid2<0){
			printf("���̴���ʧ��\n");
		}
		else if(pid2==0 ){
			printf("�����ӽ���2,�ҵ�ID: %d\n",getpid());
		}
		else{
			waitpid(pid2);//�ȶ���ִ����
			printf("�����ӽ���1,�ҵ�ID: %d  ",getpid());
			printf("�ҵ��ӽ��̵�ID: %d\n",pid2);
		}
	}
	else{
		waitpid(pid);
		printf("���Ǹ�����,ID: %d  ",getpid());
		printf("�ҵ��ӽ��̵�ID: %d\n",pid);
		wait(0);
	}
}
