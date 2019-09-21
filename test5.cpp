#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<math.h>
#include<time.h>
#define m 2         //one block size
#define n 5         //max block per file
#define N 51
#define MAX 501
using namespace std;


typedef struct file
{
    int size;
    int logic_block[n];
    int father;
} file;

file disk[MAX];     

typedef struct index
{
    string name;
    int indexBlock;
} index_list;


index_list file_index[N];  

bool bitTable[MAX];


int file_size (double num)
{
    double temp=fmod(num,m);
    return temp==0?(int)num/m:(int)num/m+1;
}

int find_index(){
    for(int i=1;i<N;i++){
        if(file_index[i].indexBlock==-1){
            return i;
        }
    }
}
bool is_full_index(){
    int cnt=0;
    for(int i=1;i<N;i++){
        if(file_index[N].indexBlock!=-1)
            cnt++;
    }
    return cnt==(N-1)?true:false;
}
bool is_full_disk(){
    int cnt=0;
    for(int i=1;i<MAX;i++){
        if(bitTable[i]==true)
            cnt++;
    }
    return cnt==(MAX-1)?true:false;
}
void init ()
{
    for (int i = 1; i < MAX; i++)
    {
      disk[i].size = 0;
      disk[i].father= -1;
      for (int j = 0; j < n; j++)
      {
          disk[i].logic_block[j] = -1;

      }
      bitTable[i] = false;
    }
    for(int i=1; i<N; i++){
        file_index[i].name.clear();
        file_index[i].indexBlock=-1;
    }
}

//create 50 new file and store in disk
void create_file ()
{
    srand ((unsigned) time (NULL));
    for (int i = 1; i < N; i++)
    {
        file_index[i].name +=to_string(i);
        file_index[i].name +=".txt";
        for (int j = 1; j < MAX; j++)
        {
            if (bitTable[j] == false)
            {
                bitTable[j] = true;
                disk[j].father=i;
                file_index[i].indexBlock = j;
                break;
            }

        }
        int index = file_index[i].indexBlock;
        double f_size = (double) (rand () % 8)  + 2;   //ji suan size of file
        disk[index].size = file_size (f_size);
        for (int j = 0; j < disk[index].size; j++)
        {
            for (int k = 1; k < MAX; k++)
            {
                if (bitTable[k] == false)
                {
                    disk[index].logic_block[j] = k;
                    disk[k].father=i;
                    bitTable[k] = true;
                    break;
                }

            }
        }
    }
}



//delete odd file
void delete_odd ()
{
    for(int i=1;i<N;i++){
        string temp;
        int j=0;
        while(file_index[i].name[j]!='.'){
            temp+=file_index[i].name[j++];
        }
        int tmp=stoi(temp);
        if(tmp%2==1){
            file_index[i].name.clear();
            int index = file_index[i].indexBlock;
            file_index[i].indexBlock=-1;
            bitTable[index]=false;
            for(int k=0;k<disk[index].size;k++){
                disk[disk[index].logic_block[k]].father=-1;
                bitTable[disk[index].logic_block[k]]=false;
            }
            disk[index].size=0;
            disk[index].father=-1;
        }
        
    }
}
void creat_5_files(){
    if(is_full_disk())
        cout<<"��ǰ�����������������������"<<endl;
    double size[5]={7.0,5.0,2.0,9.0,3.5};
    for (int t = 0; t < 5; t++)
    {
        int i=find_index();
        file_index[i].name +=t+'A';
        file_index[i].name +=".txt";
        for (int j = 1; j < MAX; j++)
        {
            if (bitTable[j] == false)
            {
                bitTable[j] = true;
                disk[j].father=i;
                file_index[i].indexBlock = j;
                break;
            }

        }
        int index = file_index[i].indexBlock;
        double f_size =size[i];
        disk[index].size = file_size (f_size);
        for (int j = 0; j < disk[index].size; j++)
        {
            for (int k = 1; k < MAX; k++)
            {
                if (bitTable[k] == false)
                {
                    disk[index].logic_block[j] = k;
                    disk[k].father=i;
                    bitTable[k] = true;
                    break;
                }

            }
        }
        
    }
    /*for(int i=0;i<5;i++){
        int index=file_index[i].indexBlock;
        cout<<file_index[i].name<<"   "<<file_index[i].indexBlock<<"   ";
        for(int j=0;j<disk[index].size;j++){
            cout<<disk[index].logic_block[j]<<" ";
        }
        cout<<endl;
    }*/

}


        
void print(){
    cout<<"�ļ���\t"<<"�ļ���С "<<"������\t"<<"�����\t"<<endl;
    for(int i=1;i<N;i++){
    if(file_index[i].indexBlock!=-1){
        int index=file_index[i].indexBlock;
        cout<<file_index[i].name<<"\t"<<disk[file_index[i].indexBlock].size<<"\t"<<file_index[i].indexBlock<<"\t";
        for(int j=0;j<disk[index].size;j++){
            cout<<disk[index].logic_block[j]<<" ";
        }
        cout<<endl;
    }
}
}

void disk_print(){
    for(int i=1;i<MAX;i++){
        if(bitTable[i]==false){
            cout<<"_____\t";
            continue;
        }
        if(disk[i].size!=0){
            int father=disk[i].father;
            string temp;
            int j=0;
            while(file_index[father].name[j]!='.'){
                temp+=file_index[father].name[j++];
        }
            cout<<"idx_"<<temp<<"\t";
            continue;
        }
        int tmp=disk[i].father;
        cout<<file_index[tmp].name<<"\t";
        if(i%10==0)
            cout<<endl;
    }
}
int main ()
{
    init ();
    cout<<"����50���ļ�"<<endl;
    create_file ();
    print();
    disk_print();
    cout<<"==============================================================================================="<<endl;
    cout<<"ɾ�������ļ�"<<endl;
    delete_odd();
    disk_print();
    cout<<"==============================================================================================="<<endl;
    cout<<"����������ļ�"<<endl;
    creat_5_files();
    disk_print();
    cout<<"==============================================================================================="<<endl;
return 0;

}
/*��1��������� 2k-10k ���ļ� 50 �����ļ���Ϊ 1.txt��2.txt��������
50.txt�����������㷨�洢��ģ������С�
��2��ɾ������.txt��1.txt��3.txt��������49.txt���ļ�
��3���´��� 5 ���ļ���A.txt��B.txt��C.txt��D.txt��E.txt������С
Ϊ��7k��5k��2k��9k��3.5k�������루1����ͬ���㷨�洢
��ģ������С�
��4�������ļ� A.txt��B.txt��C.txt��D.txt��E.txt ���̿�洢״̬
�����п��������״̬*/