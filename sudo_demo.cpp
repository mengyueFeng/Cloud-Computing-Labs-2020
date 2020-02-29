#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <cstring>
#include <fstream>

using namespace std;
 
int sudoku[10][10];
int problem[10][10];//���ɵ����� 
int row[10][10];//�� 
int column[10][10];//�� 
int block[4][4][10];
int known[10][10];
int f=0;
int cnt=0;

void init(){//��ʼ��Ϊ1 //�����ѡ����
	for (int i=1;i<=9;i++){
		for (int j=1;j<=9;j++){
			if (sudoku[i][j]){
				row[i][sudoku[i][j]]=1;
				column[j][sudoku[i][j]]=1;
				block[(i-1)/3+1][(j-1)/3+1][sudoku[i][j]]=1;
			}
		}
	}
}
void print(int sudoku[][10]){
	ofstream data2;
    data2.open("test5.txt",ios::out);   //���ļ� 
	cout<<"-----------------------"<<endl<<endl;
	for (int i=1;i<=9;i++){
		for (int j=1;j<=9;j++){
			if (sudoku[i][j]){
				cout<<sudoku[i][j];
				data2<<sudoku[i][j];
			}
			else 
			{ 
			    cout<<"0";
			    data2<<"0";
			}
			if (j%3!=0) cout<<" ";
			else cout<<" | ";
		}
		cout<<endl;
		if (i%3!=0)  cout<<endl;
		else       
		cout<<endl<<"-----------------------"<<endl<<endl;
		
	}
    
    data2.close();
}
void search(int x,int y){
	if (f) return;
	if (known[x][y]){//known��0��Ϊ���֣� ��������һ����Ԫ�� 
		search((9*x+y-9)/9+1,y%9+1);//����������[1,2],[1,3]...[1,9],[2,1]... 
	}
	else{
		if (x==10 && y==1) {//���������е������Ϸ�
			f=1;//���Ϊ1 
			cnt++;
		}
		for (int j=1;j<40;j++){
			int i=rand()%9+1;//����1-9֮����������
			if (row[x][i]==0 && column[y][i]==0 && block[(x-1)/3+1][(y-1)/3+1][i]==0)//�жϴ����Ƿ�Ϸ� 
			{
				sudoku[x][y]=i;
				row[x][i]=1;
				column[y][i]=1;
				block[(x-1)/3+1][(y-1)/3+1][i]=1;
				search((9*x+y-9)/9+1,y%9+1);//����������[1,2],[1,3]...[1,9],[2,1]...
				if (!f){//f=0��δ�������е��� 
					sudoku[x][y]=0;
					row[x][i]=0;
					column[y][i]=0;
					block[(x-1)/3+1][(y-1)/3+1][i]=0;
				}
			}
		}
	}
}
void search2(int x,int y){
	if (x!=10 && known[x][y]){//knownΪ����,��δ�������е��� 
		search2((9*x+y-9)/9+1,y%9+1);//����������[1,2],[1,3]...[1,9],[2,1]...
	}
	else{
		if (x==10 && y==1){//���������е������Ϸ�
			cnt++;
		}
		else
		for (int i=1;i<=9;i++){
			if (row[x][i]==0 && column[y][i]==0 && block[(x-1)/3+1][(y-1)/3+1][i]==0)//�жϴ����Ƿ�Ϸ� 
			{
				sudoku[x][y]=i;
				row[x][i]=1;
				column[y][i]=1;
				block[(x-1)/3+1][(y-1)/3+1][i]=1;
				search2((9*x+y-9)/9+1,y%9+1);
				sudoku[x][y]=0;
				row[x][i]=0;
				column[y][i]=0;
				block[(x-1)/3+1][(y-1)/3+1][i]=0;
			}
		}
	}
}
 
int main(){
	srand(time(0));
	search(1,1);
	int sum=0;
	int sudoku2[10][10]={0};
	for (int i=1;i<=9;i++){
		for (int j=1;j<=9;j++){
			problem[i][j]=sudoku2[i][j]=sudoku[i][j];
		}
	}
	cnt=0;
	while (cnt!=1){
		for (int i=1;i<=9;i++){
			for (int j=1;j<=9;j++){
				known[i][j]=1;
			}
		}
		sum=0;
		while (sum<50){
			int x=rand()%9+1;//�������1-9 
			int y=rand()%9+1;
			if (known[x][y]==0) continue;//0:�հ� 
			else {
				sum++;
				known[x][y]=0;
			}
		}
		for (int i=1;i<=9;i++){
			for (int j=1;j<=9;j++){
				if (known[i][j]==0) sudoku[i][j]=problem[i][j]=0; 
			}
		}
		cnt=0;
		f=0;
		memset(row,0,sizeof(row));//��ʼ��Ϊ0 
		memset(column,0,sizeof(column));
		memset(block,0,sizeof(block));
		init();//��ʼ��Ϊ1
		search2(1,1);//�ӣ�1,1����ʼ����
		for (int i=1;i<=9;i++){
			for (int j=1;j<=9;j++){
				sudoku[i][j]=sudoku2[i][j];
				if (cnt!=1) problem[i][j]=sudoku2[i][j];
			}
		}
	}
	print(problem);
	return 0;
}
