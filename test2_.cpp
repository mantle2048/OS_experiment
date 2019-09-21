#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define q 1
#define clock 1//定义时钟周期为1
struct E
{
	char name; 
	int at;
	int st;
	int time_remaining;
	int wait_time;//等待时间
	int R;//响应比 R=(w+s)/s，其中R表示响应比，w表示已经等待的时间，s表示期待服务的时间
	int ft;//完成时间
	int ct;//周转时间
	double d_ct;//带权周转
}process[500];

queue<int> Q;
vector<char> list;//用来保存已经调度的序列
int cnt=0;//计时器
bool mark[500];//标识是否已经被执行结束
bool in_queue[500];//标识是否已经在等待队列里
//初始化
void init(E process[],int num){
	cnt=0;//计时器记得清零
	list.clear();
	for(int i=0;i<num;i++){
		process[i].name=0;process[i].at=0;process[i].st=0;process[i].ft=0;process[i].ct=0;process[i].d_ct=0.0;process[i].wait_time=0;process[i].R=0;	
		mark[i]=false;
		in_queue[i]=false;
		while(!Q.empty())
			Q.pop();
	}
}
//打印
void print(E process[],int num){
	double aver_ct=0,aver_d_ct=0;
	cout<<"进程  "<<"完成时间  "<<"周转时间 "<<"带权周转时间"<<endl;
	for(int i=0;i<num;i++){
		cout<<process[list[i]].name<<"\t"<<process[list[i]].ft<<"\t"<<process[list[i]].ct<<"\t"<<process[list[i]].d_ct<<endl;
		aver_ct+=process[list[i]].ct;
		aver_d_ct+=process[list[i]].d_ct;
	}
	cout<<"平均周转时间: "<<aver_ct/num<<" "<<"平均带权周转时间: "<<aver_d_ct/num<<endl;
}
//找一个最先到达的且未在等待队列里的进程
int  find(E process[],int num){
	int min=123123123;
	int choose=-1;
	for(int i=0;i<num;i++){
		if(process[i].at<=cnt && in_queue[i]==false){
			if(process[i].at<min){
				min=process[i].at;
				choose=i;
			}
		}
	}
	if(choose!=-1){
	in_queue[choose]=true;//放入队列
	return choose;
	}
	return -1;
}
//判断所有的进程是否已经结束
bool finish(E process[],int num){
	for(int i=0;i<num;i++){
		if(mark[i]==false)
			return false;
	}
	return true;
}

void FCFS(E process[],int num){
	while(!finish(process,num)){
		cout<<"当前时间为: "<<cnt<<endl;
		int temp=find(process,num);
		cout<<"已到达的进程:";
		while(temp!=-1){
			Q.push(temp);
			cout<<process[temp].name<<" ";
			temp=find(process,num);
		}
		int k=Q.front();
		mark[k]=true;
		list.push_back(k);
		Q.pop();
		cout<<"调度的进程为: "<<process[k].name<<endl;
		cout<<"------------------------------------------------"<<endl;
		cnt+=process[k].st;
		process[k].ft=cnt;
		process[k].ct=process[k].ft-process[k].at;
		process[k].d_ct=double(process[k].ct)/process[k].st;
	}
}

void PR(E process[],int num){
	int k=-1;
	while(!finish(process,num)){
		cout<<"当前时间为: "<<cnt<<endl;
		int temp=find(process,num);
		cout<<"已到达的进程: ";
		while(temp!=-1){
			Q.push(temp);
			cout<<process[Q.front()].name<<" ";
			temp=find(process,num);
		}
		if(mark[k]==false&&k!=-1)
		{
			Q.push(k);
		}
		k=Q.front();
		cout<<"调度的进程为: "<<process[k].name<<endl;
		process[k].time_remaining-=q;
		cnt+=q;
		cout<<"时间片执行完成,该进程剩余时间为: "<<process[k].time_remaining<<endl;
		cout<<"------------------------------------------------"<<endl;
		if(process[k].time_remaining==0){
			cout<<process[k].name<<" 进程已执行完"<<endl;
			cout<<"------------------------------------------------"<<endl;
			list.push_back(k);//按完成顺序采集
			mark[k]=true;
			process[k].ft=cnt;
			process[k].ct=process[k].ft-process[k].at;
			process[k].d_ct=double(process[k].ct)/process[k].st;
		}
		Q.pop();
	}
}

struct SJF_E_non
 {
 	int number;
 	int at;
 	int st;
 	bool operator <(const SJF_E_non &A)const {//重载<操作符,按照响应比从小到大排序，这样数组的队尾就是接下来要执行的进程
 		return st>A.st;
   }

 }; 

void SJF_non(E process[],int num){
		SJF_E_non SJF_queue[500];
		int size=0;
		for(int i=0;i<500;i++){
			SJF_queue[i].number=-1;
			SJF_queue[i].at=0;
			SJF_queue[i].st=0;
		}
	while(!finish(process,num)){
		cout<<"当前时间为: "<<cnt<<endl;
		int temp=find(process,num);
		while(temp!=-1){
			SJF_queue[size].number=temp;
			SJF_queue[size].at=process[temp].at;
			SJF_queue[size].st=process[temp].st;
			size++;
 			temp=find(process,num);
		}
		cout<<"已到达的进程: ";
		for(int i=0;i<size;i++){
			cout<<process[SJF_queue[i].number].name<<" ";
			cout<<"  服务时间  "<<SJF_queue[i].st<<"  ";
		}
		cout<<endl;
		sort(SJF_queue,SJF_queue+size);
		int k=SJF_queue[size-1].number;
		mark[k]=true;
		list.push_back(k);
		size--;
		cout<<"调度的进程为: "<<process[k].name<<endl;
		cout<<"------------------------------------------------"<<endl;
		cnt+=process[k].st;
		process[k].ft=cnt;
		process[k].ct=process[k].ft-process[k].at;
		process[k].d_ct=double(process[k].ct)/process[k].st;
	}
}

struct SJF_E_on
 {
 	int number;
 	int at;
 	int st;
 	int time_remaining;
 	bool operator <(const SJF_E_on &A)const {//重载<操作符,按照响应比从小到大排序，这样数组的队尾就是接下来要执行的进程
 	    if(time_remaining!=A.time_remaining)
 		    return time_remaining>A.time_remaining;
 		else
 		    return number>A.number;//两种方法，最后D和B的时间一样，先执行D的平均执行时间比较小一点，在这里我用的先按输入顺序排序，先执行B
   }

 }; 

void SJF_on(E process[],int num){
		SJF_E_on SJF_queue[500];
		int size=0;
		for(int i=0;i<500;i++){
			SJF_queue[i].number=-1;
			SJF_queue[i].at=0;
			SJF_queue[i].st=0;
			SJF_queue[i].time_remaining=0;
		}
	while(!finish(process,num)){
		cout<<"当前时间为: "<<cnt<<endl;
		int temp=find(process,num);
		while(temp!=-1){
			SJF_queue[size].number=temp;
			SJF_queue[size].at=process[temp].at;
			SJF_queue[size].st=process[temp].st;
			SJF_queue[size].time_remaining=process[temp].st;
			size++;
 			temp=find(process,num);
		}
		cout<<"已到达的进程: ";
		for(int i=0;i<size;i++){
			cout<<process[SJF_queue[i].number].name<<" ";
			cout<<"  剩余时间  "<<SJF_queue[i].time_remaining<<"  ";
		}
		cout<<endl;
		sort(SJF_queue,SJF_queue+size);
		int k=SJF_queue[size-1].number;
		cout<<"调度的进程为: "<<process[k].name<<endl;
		cout<<"------------------------------------------------"<<endl;
		SJF_queue[size-1].time_remaining-=clock;
		cnt+=clock;
		if(SJF_queue[size-1].time_remaining==0)
		{
			cout<<" 该进程已执行完"<<endl;
			mark[k]=true;
			list.push_back(k);
			size--;
			process[k].ft=cnt;
			process[k].ct=process[k].ft-process[k].at;
			process[k].d_ct=double(process[k].ct)/process[k].st;
		}

	}
}



struct HRN_E
 {
 	int number;
 	int wait_time;
 	int at;
 	double R;
 	bool operator <(const HRN_E &A)const {//重载<操作符,按照响应比从小到大排序，这样数组的队尾就是接下来要执行的进程
 		return R<A.R;
   }

 }; 

void HRN(E process[],int num){
		HRN_E HRN_queue[500];
		int size=0;
		for(int i=0;i<500;i++){
			HRN_queue[i].number=-1;
			HRN_queue[i].R=0;
		}
	while(!finish(process,num)){
		cout<<"当前时间为: "<<cnt<<endl;
		int temp=find(process,num);
		while(temp!=-1){
			HRN_queue[size].number=temp;
			HRN_queue[size].wait_time=cnt-process[temp].at;
			HRN_queue[size].at=process[temp].at;
			HRN_queue[size].R=(double)(HRN_queue[size].wait_time+process[temp].st)/process[temp].st;
			size++;
 			temp=find(process,num);
		}
		cout<<"已到达的进程: ";
		for(int i=0;i<size;i++){
			cout<<process[HRN_queue[i].number].name<<" ";
			cout<<"  响应比："<<HRN_queue[i].R<<"  ";
		}
		cout<<endl;
		sort(HRN_queue,HRN_queue+size);
		int k=HRN_queue[size-1].number;
		mark[k]=true;
		list.push_back(k);
		process[k].wait_time=HRN_queue[size-1].wait_time;
		process[k].R=HRN_queue[size-1].wait_time;
		size--;
		cout<<"调度的进程为: "<<process[k].name<<endl;
		cout<<"------------------------------------------------"<<endl;
		cnt+=process[k].st;
		for(int i=0;i<size;i++){
			HRN_queue[i].wait_time+=process[k].st;
			HRN_queue[i].R=(double)(HRN_queue[i].wait_time+process[HRN_queue[i].number].st)/process[HRN_queue[i].number].st;
		}
		process[k].ft=cnt;
		process[k].ct=process[k].ft-process[k].at;
		process[k].d_ct=double(process[k].ct)/process[k].st;
	}
}

void menu(int n){
	
	return;
}
int main(){
	int n;
	cout<<"1.FCFS "<<"2.PR "<<"3.SJF_non "<<"4.SJF_non "<<"5.HRN "<<"0.EXIT "<<endl;
	cout<<"请选择调度方法: ";
	cin>>n;
	do{
	    if(n==0)
	    return 0;
	    else if(n!=(1||2||3||4||5))
	    {
	        cout<<"暂时没有这样的功能"<<endl;
	        cout<<"请选择调度方法: ";
	        continue;
	    }
	    int num;//进程数
    	cout<<"请输入进程数: ";
    	cin>>num;
    	init(process,num);
    	cout<<"进程  "<<"到达时间  "<<"服务时间"<<endl;
    	for(int i=0;i<num;i++){
    		cin>>process[i].name>>process[i].at>>process[i].st;
    		process[i].time_remaining=process[i].st;
    	}
    	switch(n){
    		case 1:{
    		    cout<<"——————————————————————FCFS——————————————————————"<<endl;
    			FCFS(process,num);
    			print(process,num);
    	        cout<<"请选择调度方法: ";
    			break;
    		}
    		case 2:{
    		    cout<<"——————————————————————PR————————————————————————"<<endl;
    			PR(process,num);
    			print(process,num);
    	        cout<<"请选择调度方法: ";
    			break;
    		}
    		case 3:{
    		    cout<<"————————————————————SJF_non—————————————————————"<<endl;
    			SJF_non(process,num);
    			print(process,num);
    	        cout<<"请选择调度方法: ";
    			break;
    		}
    		case 4:{
    		    cout<<"————————————————————SJF_on——————————————————————"<<endl;
    			SJF_on(process,num);
    			print(process,num);
    	        cout<<"请选择调度方法: ";
    			break;
    		}
    		case 5:{
    		    cout<<"———————————————————————HRN——————————————————————"<<endl;
    			HRN(process,num);
    			print(process,num);
    	        cout<<"请选择调度方法: ";
    			break;
    		}
    	}
	}while(cin>>n);
	return 0;

}