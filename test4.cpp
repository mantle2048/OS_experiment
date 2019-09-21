//����SSTF���̵����㷨����Ŀ��û��ָ�����������ж���
#include<iostream>
#include<stdlib.h>
#define MAX 100
using namespace std;

int direction=0;//0��ʾ��С����ķ���1��ʾ����С�ķ���
int SCAN(int *p,int n,int begin){
	int min,dis=0,next=0,sum=0;//disΪ���ʸ�������Ҫ�ƶ��ľ��룬nextΪ��һ��Ҫ���ʵ�����
	int i,j;
	bool flag;//�����ж��Ƿ�ı䷽��
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
			begin=p[next];//�´��ƶ�����ʼλ��
			cout<<p[next]<<" ";//�����������˳��
			dis=p[i];
			p[i]=p[next];
			p[next]=dis;
		}
	}
	return sum;
}

int SSTF(int *p,int n,int begin){
	int min,dis=0,next=0,sum=0;//disΪ���ʸ�������Ҫ�ƶ��ľ��룬nextΪ��һ��Ҫ���ʵ�����
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
		begin=p[next]; //�����´��Ʊ۵���ʼλ��
		cout<<"��һ���ŵ���: "<<p[next]<<" "; //��Ӧ��������Ĺ���
		cout<<"�ƶ����룺 "<<min<<endl;
		if(next==i)
		    continue;
		dis=p[i];		//���Ѿ����ȵķ�����ǰ
		p[i]=p[next];
		p[next]=dis;
	}
	return sum;
}

int  main(){
    int n;
	cout<<"1.SCAN "<<"2.SSTF "<<"0.EXIT "<<endl;
	cout<<"��ѡ���û��㷨: ";
	cin>>n;
	do{
	    if(n==0)
	    return 0;
	    if(n!=1&&n!=2)
	    {
	        cout<<"��ʱû�������Ĺ���"<<endl;
	        cout<<"��ѡ���û��㷨: ";
	        continue;
	    }
	    int order,length,begin,i=0,Sum=0;
    	int *p=new int[MAX];
    	cout<<"�����Ʊ۵ĳ�ʼλ��: ";
    	cin>>begin;
    	cout<<"������ŵ����г���: ";
    	cin>>length;
    	cout<<"������������: ";
    	while(length--){
    	    cin>>order;
    		p[i++]=order;
    	}
    	cout<<endl;
	    switch(n){
    		case 1:{
    		    Sum=SCAN(p,i,begin);
    		    cout<<"�Ʊ۵�����: "<<Sum<<endl;
    		    cout<<"��ѡ���û��㷨: ";
    		    break;}
    		case 2:{
    		    Sum=SSTF(p,i,begin);
    		    cout<<"�Ʊ۵�����: "<<Sum<<endl;
    		    cout<<"��ѡ���û��㷨: ";
    		    break;}
    		}
	}while(cin>>n);
	return 0;
}
