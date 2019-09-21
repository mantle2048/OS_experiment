//这是调用函数
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
int main(int argc,char*argv[])
{
	int j;
	char *cmd_name=argv[1];
	char **p=(char**)malloc(sizeof(char*)*(argc-1));
	if(argc<2){
		printf("你需要输入足够的参数\n");
		return 0;
	}
	for(j=0;j<argc-1;j++){
		p[j]=argv[j+1];
	}
	if(strcmp(cmd_name,"max")==0){
		execve("max",p,NULL);
	}
	else if(strcmp(cmd_name,"min")==0){
		execve("min",p,NULL);
	}
	else if(strcmp(cmd_name,"average")==0){
		execve("average",p,NULL);
	}
	else
		printf("no such function\n");
	free(p);
	return 1;
}