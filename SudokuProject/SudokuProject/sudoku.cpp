#include <iostream>
#include <string> 
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <algorithm> 
using namespace std;

int a[9][9]={0};

//�ж��Ƿ������������ 
bool judge(int i,int j,int number)
{
	int k;
	for (k=0;k<j;k++)//�ж��� 
    	if (a[i][k]==number)
            return false;
    for (k=0;k<i;k++)//�ж��� 
        if (a[k][j]==number)
            return false;
    int count=j%3+i%3*3;
    while (count--!=0)
        if (a[i-i%3+count/3][j-j%3+count%3]-number==0)//�ж�С�Ź��� 
            return false;
    return true;
}

bool sudoku(int i,int j)
{
	if(i=9) 
		return true;
	int no=rand()%9;
	int m;
	for(m=0;m<9;m++)
	{
		int p=(no+m)%9+1;//��������������У�������һ����˳�� 
		if(judge(i,j,p))
		{
			a[i][j]=p;
			int i_=i;
			int j_=j+1;
			if(j_==9)//���һ�������ˣ���ʼ��һ�� 
				i_++,j_=0;
			if(sudoku(i_,j_))//�ݹ� 
				return true;	 
		} 
	}
	return false;//ĳһ���㲻���������ͻ��� 
} 

int main(int argc,char **argv)//main�������� 
{
	ofstream fout("sudoku.txt",ios_base::trunc);//���ļ���ʽ��������ҷ�ʽΪ���� 
	srand(time(0));//������������� 
	std::string str; 
	int len,flag=0;
	int k; 
	int i,j,temp;
	int n=0,m;
	str=argv[2];
	len=str.length();
	for(k=0;k<len;k++)
	{
		if(str[k]<'0'||str[k]>'9')
		{
			cout<<"�����������������롣"<<endl;//�����ֻ�������� 
			flag=1;//��� 
			break;
		} 
	}
	if(flag==0)
	{
		n=atoi(str.c_str());
	}
	if(n>1000000)
	{
		cout<<"��������ֳ�����Χ������������"<<endl;//N�ķ�ΧΪ0~1000000 
	} 
	for(m=0;m<n;m++)
	{ 
		for(i=0;i<9;i++)
		{
			a[0][i]=i+1;//����һ�и�ֵ1~9 
		}
		temp=a[0][0];//���� 
		a[0][0]=a[0][2];
		a[0][2]=temp; 
		random_shuffle(a[0]+1,a[0]+9);//������һ�е�����������ҵ�һ��������Ϊ�ҵ�ѧ�ź���λ�������9����1��ֻ�к�˸���� 
	    sudoku(1,0);//�����ӵڶ��е�һ����ʼ 
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				fout<<a[i][j]<<" ";
			}
			fout<<endl;
		}
		fout<<endl; 
	}	
	return 0;
}
