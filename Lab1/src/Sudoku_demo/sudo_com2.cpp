#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
 
int sudoku[10][10];
int row[10][10];
int column[10][10];
int block[4][4][10];
int known[10][10];

void print(){
	
	ofstream data2;
	data2.open("outcome5.txt",ios::out);  
	cout<<"-----------------------"<<endl<<endl;
	for (int i=1;i<=9;i++){
		for (int j=1;j<=9;j++){
			cout<<sudoku[i][j];
			data2<<sudoku[i][j];
			if (j%3!=0) cout<<" ";
			else cout<<" | ";
		}
		cout<<endl;
		if (i%3!=0)cout<<endl;
		else  cout<<endl<<"-----------------------"<<endl<<endl;
	}
    
	data2.close();
}
void search(int x,int y){
	if (known[x][y]){
		search((9*x+y-9)/9+1,y%9+1);
	}
	else{
		if (x==10 && y==1) {
			print();
			exit(0);
		}
		else
		for (int i=1;i<=9;i++){
			if (row[x][i]==0 && column[y][i]==0 && block[(x-1)/3+1][(y-1)/3+1][i]==0){
				sudoku[x][y]=i;
				row[x][i]=1;
				column[y][i]=1;
				block[(x-1)/3+1][(y-1)/3+1][i]=1;
				search((9*x+y-9)/9+1,y%9+1);
				sudoku[x][y]=0;
				row[x][i]=0;
				column[y][i]=0;
				block[(x-1)/3+1][(y-1)/3+1][i]=0;
			}
		}
	}
}
 
 
int main(){
	ifstream data1;
    data1.open("test5.txt",ios::in);   //打开文件 
    
	char ch[81];
	for(int i=0;i<81;i++)
	{
		data1>>ch[i];
	}
	int k=0;
	for (int i=1;i<=9;i++)
	{
		for (int j=1;j<=9;j++)
		{
			sudoku[i][j]=int(ch[k]-'0');
			k++;
			if (sudoku[i][j]) known[i][j]=1;	
		}
	}
	
	for (int i=1;i<=9;i++){
		for (int j=1;j<=9;j++){
			if (sudoku[i][j]){
				row[i][sudoku[i][j]]=1;
				column[j][sudoku[i][j]]=1;
				block[(i-1)/3+1][(j-1)/3+1][sudoku[i][j]]=1;
			}
		}
	}
	search(1,1);
	data1.close();
	return 0;
}
