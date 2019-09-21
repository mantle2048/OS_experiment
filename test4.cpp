//这是SSTF磁盘调度算法，题目中没有指明输入序列有多少
#include<iostream>
#include<stdlib.h>
#define MAX 100
using namespace std;

int direction=0;//0表示从小到大的方向，1表示东大到小的方向
int SCAN(int *p,int n,int begin){
	int min,dis=0,next=0,sum=0;//dis为访问该柱面需要移动的距离，next为下一个要访问的柱面
	int i,j;
	bool flag;//用于判断是否改变方向
	for(i=0;i<n;i++){
		min=MAX;
		flag=false;
		for(j=i;j<n;j++){
			if((direction&&(p[j]<begin))||(!direction&&(p[j]>begin))){
				dis=abs(p[j]-begin);
				if(dis<min){
					min=dis;
					next=j;
					flag=true;
				}
			}
		}
		if(!flag){
			direction=!direction;
			i--;
		}
		else{
			sum+=min;
			begin=p[next];//下次移动比起始位置
			cout<<p[next]<<" ";//输出磁盘请求顺序
			dis=p[i];
			p[i]=p[next];
			p[next]=dis;
		}
	}
	return sum;
}

int SSTF(int *p,int n,int begin){
	int min,dis=0,next=0,sum=0;//dis为访问该柱面需要移动的距离，next为下一个要访问的柱面
	int i,j;
	for(i=0;i<n;i++){
		min=123123123;
		for(j=i;j<n;j++){
			dis=abs(p[j]-begin);
			if(dis<min){
				min=dis;
				next=j;
			}
		}
		sum+=min;
		begin=p[next]; //更新下次移臂的起始位置
		cout<<"下一个磁道号: "<<p[next]<<" "; //响应磁盘请求的过程
		cout<<"移动距离： "<<min<<endl;
		if(next==i)
		    continue;
		dis=p[i];		//将已经调度的放在最前
		p[i]=p[next];
		p[next]=dis;
	}
	return sum;
}

int  main(){
    int n;
	cout<<"1.SCAN "<<"2.SSTF "<<"0.EXIT "<<endl;
	cout<<"请选择置换算法: ";
	cin>>n;
	do{
	    if(n==0)
	    return 0;
	    if(n!=1&&n!=2)
	    {
	        cout<<"暂时没有这样的功能"<<endl;
	        cout<<"请选择置换算法: ";
	        continue;
	    }
	    int order,length,begin,i=0,Sum=0;
    	int *p=new int[MAX];
    	cout<<"磁盘移臂的初始位置: ";
    	cin>>begin;
    	cout<<"请输入磁道序列长度: ";
    	cin>>length;
    	cout<<"磁盘请求序列: ";
    	while(length--){
    	    cin>>order;
    		p[i++]=order;
    	}
    	cout<<endl;
	    switch(n){
    		case 1:{
    		    Sum=SCAN(p,i,begin);
    		    cout<<"移臂的总量: "<<Sum<<endl;
    		    cout<<"请选择置换算法: ";
    		    break;}
    		case 2:{
    		    Sum=SSTF(p,i,begin);
    		    cout<<"移臂的总量: "<<Sum<<endl;
    		    cout<<"请选择置换算法: ";
    		    break;}
    		}
	}while(cin>>n);
	return 0;
}
