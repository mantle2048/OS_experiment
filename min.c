//这是最小值函数
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
		printf("你需要输入足够的参数\n");
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
	printf("最小值是: %f\n",temp);
	free(p);
	return 1;


}


