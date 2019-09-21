
#include<iostream>
#include<vector>
using namespace std;

//这是FIFO
int f=0;
int r=0;
int miss=0;//记录缺页次数

void print_fifo(int *Q,int n){
    cout<<"当前队列为: ";
    if(f<=r){
        for(int i=f;i<=r;i++){
            if(Q[i]==-1)
            continue;
            cout<<Q[i]<<" ";
        }
    }
    else{
        for(int i=f;i<n;i++){
            if(Q[i]==-1)
            continue;
            cout<<Q[i]<<" ";
        }
        for(int i=0;i<=r;i++){
            if(Q[i]==-1)
            continue;
            cout<<Q[i]<<" ";
        }
    }
}
void FIFO()
{
	int n=0,len=0,page;
	int i,j;
	bool is_find=false;
	cout<<"分配页面数: ";
	cin>>n;
	int *Q=new int[n];
	cout<<"引用页面长度: ";
	cin>>len;
	cout<<"页面序列: ";
	for(i=0;i<n;i++){
		Q[i]=-1;
	}
	for(i=0;i<len;i++)
	{
		is_find=false;
		cin>>page;
		cout<<"输入: "<<page;
		for(j=0;j<n;j++){
			if(Q[j]==page){
				is_find=true;
				cout<<"命中"<<endl;
				break;
			}
		}
		if(is_find==false){
			cout<<"缺页"<<page<<endl;
			miss++;
			if((r+1)%n==f){
				f=(f+1)%n;
				Q[r]=page;
				r=(r+1)%n;
			}
			else{
				Q[r]=page;
				r=(r+1)%n;
			}
		}
		print_fifo(Q,n);
	}
	delete []Q;
	cout<<"缺页次数: "<<miss<<endl;
	cout<<"缺页率: "<<(miss*1.0)/len<<endl;
	return;
}

//这是LRU

typedef struct Node{
	struct Node *next;
	int data;
}Lnode;

typedef struct List{
	Lnode *f;
	Lnode *r;
	int length;
	int num;
}List;

List init_List(int n){
	List L;
	L.length=n;
	L.num=0;
	L.f=new Lnode[1];
	L.f->data=-1;
	L.f->next=NULL;
	L.r=L.f;
	return L;

}
bool is_full(List *L){
	if(L->num==L->length)
		return true;
	else
		return false;
}
Lnode* is_find(List *L,int page){
	Lnode *p=L->f->next,*q=L->f;
	while(p!=NULL){
		if(page==p->data)
			return q;
		q=p;
		p=p->next;		
	}
	return NULL;
}
void print(List *L){
	Lnode* m;
	Lnode* n;
	m=L->f;
	n=m->next;
	cout<<"当前队列为: ";
	while(n!=NULL){
		cout<<n->data<<" ";
		m=n;
		n=n->next;
	}
	cout<<"  ";
}

void insert(List* L,int page){
	if(L->f->next!=NULL){	
		Lnode *temp1=is_find(L,page);
		if(temp1!=NULL){//命中了
			if(temp1->next==L->r){
			    cout<<"命中"<<endl;
			    return;
			}
			Lnode *temp2=temp1->next;
			L->r->next=temp2;
			temp1->next=temp2->next;
			temp2->next=NULL;
			L->r=temp2;
			cout<<"命中"<<endl;
			return;
		}
		cout<<"缺页: "<<page<<endl;
		miss++;
	}
	else{
		cout<<"缺页: "<<page<<endl;
		miss++;
	}
	if(is_full(L)){
		Lnode *temp=L->f->next;
		L->f->next=temp->next;
		L->num--;
		delete []temp;
	}
	L->r->next=new Lnode[1];
	L->r=L->r->next;
	L->r->data=page;
	L->r->next=NULL;
	L->num++;
	return;
}
void LRU()
{
	int i;
	int n=0,len=0,page;
	List *L,P;
	cout<<"分配进程页面数: ";
	cin>>n;
	P=init_List(n);
	L=&P;
	cout<<"页面序列长度: ";
	cin>>len;
	cout<<"页面序列: ";
	for(i=0;i<len;i++){
		cin>>page;
		cout<<"输入: "<<page<<" ";
		insert(L,page);
		print(L);
	}
	cout<<"缺页次数: "<<miss<<endl;
	cout<<"缺页率: "<<(miss*1.0)/len<<endl;
	return;
}


int main(){
    int n;
	cout<<"1.FIFO "<<"2.LRU "<<"0.EXIT "<<endl;
	cout<<"请选择置换算法: ";
	cin>>n;
	do{
	    f=0;
        r=0;
        miss=0;//记录缺页次数
	    if(n==0)
	    return 0;
	    if(n!=1&&n!=2)
	    {
	        cout<<"暂时没有这样的功能"<<endl;
	        cout<<"请选择置换算法: ";
	        continue;
	    }
	    switch(n){
    		case 1:{
    		    FIFO();
    		    cout<<"请选择置换算法: ";
    		    break;}
    		case 2:{
    		    LRU();
    		    cout<<"请选择置换算法: ";
    		    break;}
    		}
	}while(cin>>n);
	return 0;
}


