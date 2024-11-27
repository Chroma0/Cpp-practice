#include"Transpose.h"
#include<iostream>
#include<time.h>
using namespace std;

void transpose::Transpose_Method_1(int matrix[][3],int row,int column,int line)
{
	int original_matrix[row][column];
	int transpose_matrix[column][row];
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			original_matrix[i][j]=0;
		}
	}
	for(int i=0;i<line;i++)
	{
		original_matrix[matrix[i][0]][matrix[i][1]]=matrix[i][2];
	}
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			if(original_matrix[i][j] != 0)
			{
				transpose_matrix[j][i]=original_matrix[i][j];
			}
			else
			{
				transpose_matrix[j][i]=0;
			}
		}
	}
	int transpose_line=0;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			if(transpose_matrix[j][i] != 0)
			{
				matrix[transpose_line][0]=j;
				matrix[transpose_line][1]=i;
				matrix[transpose_line][2]=transpose_matrix[j][i];
				transpose_line++;
			}
		}
	}
}

void transpose::Transpose_Method_2(int matrix[][3],int line)
{
	for(int i=0;i<line;i++)
	{
		int tmp=matrix[i][0];
		matrix[i][0]=matrix[i][1];
		matrix[i][1]=tmp;
	}
}
 
