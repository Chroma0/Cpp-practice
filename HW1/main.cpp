#include<iostream>
#include<fstream>
#include<windows.h>
#include"Transpose.h"
using namespace std;

double time1=0,time2=0;
double counts=0;
LARGE_INTEGER Freq;
LARGE_INTEGER START;
LARGE_INTEGER END;

int main (){
	ifstream ifs;
	ofstream ofs;
	transpose method;
	int column,row;
	int line;//檔案行數 
	string tmp;
	ifs.open("p1.in"); 
	while(getline(ifs,tmp))
	{
        line++;//計算檔案行數 
    }
    ifs.close();
    ifs.open("p1.in");
    int matrix[line-1][3];
    int matrix1[line-1][3];
    int matrix2[line-1][3];
    //讀取檔案內容 
	for(int i=0;i<line;i++)
	{
		if(i==0)
		{
			ifs>>row>>column;
		}
		else
		{
			ifs>>matrix[i-1][0]>>matrix[i-1][1]>>matrix[i-1][2];
		}
	}
	for(int i=0;i<line-1;i++)
	{
		matrix1[i][0]=matrix[i][0];
		matrix1[i][1]=matrix[i][1];
		matrix1[i][2]=matrix[i][2];
	}
	for(int i=0;i<line-1;i++)
	{
		matrix2[i][0]=matrix[i][0];
		matrix2[i][1]=matrix[i][1];
		matrix2[i][2]=matrix[i][2];
	}
	ifs.close();
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&START);//開始計時 
	method.Transpose_Method_1(matrix1,row,column,line-1);
	QueryPerformanceCounter(&END);//停止計時 
	time1=(double)(END.QuadPart - START.QuadPart)/(double)Freq.QuadPart*1000;
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&START);//開始計時 
	method.Transpose_Method_2(matrix2,line-1);
	QueryPerformanceCounter(&END);//停止計時 
	time2=(double)(END.QuadPart - START.QuadPart)/(double)Freq.QuadPart*1000;
	ofs.open("p1.out");
	//寫入檔案 
	for(int i=0;i<line-1;i++){
		ofs<<"("<<matrix[i][0]<<", "<<matrix[i][1]<<", "<<matrix[i][2]<<")"<<" becomes "<<"("<<matrix1[i][0]<<", "<<matrix1[i][1]<<", "<<matrix[i][2]<<") in the transpose"<<endl;
	}
	ofs<<time1<<"\n"<<time2<<endl;
	ofs.close();
	return 0;
} 
