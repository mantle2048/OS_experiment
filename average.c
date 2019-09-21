//这是最大值函数
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
	int j;
	float sum=0;
	double *p=(double*)malloc(sizeof(double)*(argc-1));
	if(argc<2){
		printf("你需要输入足够的参数\n");
		return 0;
	}
	for(j=0;j<argc-1;j++){
		p[j]=atof(argv[j+1]);
		sum+=p[j];
	}
	printf("%f\n",sum/(argc-1));
	return 1;
}


