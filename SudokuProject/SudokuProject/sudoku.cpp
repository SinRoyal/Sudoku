#include <iostream>
#include <string> 
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <algorithm> 
using namespace std;

int a[9][9]={0};

//判断是否符合数独条件 
bool judge(int i,int j,int number)
{
	int k;
	for (k=0;k<j;k++)//判断行 
    	if (a[i][k]==number)
            return false;
    for (k=0;k<i;k++)//判断列 
        if (a[k][j]==number)
            return false;
    int count=j%3+i%3*3;
    while (count--!=0)
        if (a[i-i%3+count/3][j-j%3+count%3]-number==0)//判断小九宫格 
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
		int p=(no+m)%9+1;//产生随机尝试序列，序列有一定的顺序 
		if(judge(i,j,p))
		{
			a[i][j]=p;
			int i_=i;
			int j_=j+1;
			if(j_==9)//如果一行填满了，则开始下一行 
				i_++,j_=0;
			if(sudoku(i_,j_))//递归 
				return true;	 
		} 
	}
	return false;//某一个点不符合条件就回溯 
} 

int main(int argc,char **argv)//main函数参数 
{
	ofstream fout("sudoku.txt",ios_base::trunc);//以文件形式输出，并且方式为覆盖 
	srand(time(0));//设置随机数种子 
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
			cout<<"输入有误，请重新输入。"<<endl;//输入的只能是数字 
			flag=1;//标记 
			break;
		} 
	}
	if(flag==0)
	{
		n=atoi(str.c_str());
	}
	if(n>1000000)
	{
		cout<<"输入的数字超出范围，请重新输入"<<endl;//N的范围为0~1000000 
	} 
	for(m=0;m<n;m++)
	{ 
		for(i=0;i<9;i++)
		{
			a[0][i]=i+1;//给第一行赋值1~9 
		}
		temp=a[0][0];//交换 
		a[0][0]=a[0][2];
		a[0][2]=temp; 
		random_shuffle(a[0]+1,a[0]+9);//产生第一行的随机数，并且第一个数被定为我的学号后两位相加整除9加上1，只有后八个随机 
	    sudoku(1,0);//填数从第二行第一个开始 
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
