//������Сֵ����
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int j;
	double temp;
	double *p=(double*)malloc(sizeof(double)*(argc-1));
	if(argc<2){
		printf("����Ҫ�����㹻�Ĳ���\n");
		return 0;
	}
	for(j=0;j<argc-1;j++){
		p[j]=atof(argv[j+1]);
	}
	temp=p[0];
	for(j=1;j<argc-1;j++){
		if(p[j]<temp)
			temp=p[j];
	}
	printf("��Сֵ��: %f\n",temp);
	free(p);
	return 1;


}


