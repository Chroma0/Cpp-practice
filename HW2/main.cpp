#include<iostream>
#include<fstream>
#include<cstring>
#include<stack> 
using namespace std;

string input[17];
int maze[17][17];
int mark[17][17];

class Item{
	public:
		int temp_x;
		int temp_y;
		int temp_dir;
		void temp(int x,int y,int dir){
			temp_x=x;
			temp_y=y;
			temp_dir=dir;
		}
};

int direction_x(int a){
	if(a==2 || a==3 || a==4){return 1;}
	else if(a==6 || a==7 || a==8){return -1;}
	else{return 0;}
}

int direction_y(int a){
	if(a==1 || a==2 || a==8){return 1;}
	else if(a==4 || a==5 || a==6){return -1;}
	else{return 0;}
}

void Path(const int m, const int p)
{ 	
	ofstream out;
	out.open("output.txt");
	int step=0;
	mark[1][0]=1;
	stack<Item> route;
	Item temp;
	temp.temp(1,0,1);
	route.push(temp);	
	while (!route.empty())
	{
		temp = route.top();
		route.pop();
		int i = temp.temp_x;
		int j = temp.temp_y;
		int d = temp.temp_dir;
		cout<<step<<":"<<i<<","<<j<<endl;
		out<<step<<":"<<i<<","<<j<<endl;
		step++;
		while (d < 9)
		{
			int g = i + direction_x(d);
			int h = j + direction_y(d);
			if(g <= 0) g=1;
			if(h <= 0) h=0; 
			if ((g == m-2) && (h == p-1) && maze[g][h]==0)
			{
				cout<<step<<":"<<g<<","<<h<<endl;
				out<<step<<":"<<g<<","<<h<<endl;
				cout<<"successfully escaped!!"<<endl;
				out<<"successfully escaped!!"<<endl;
				out.close();
				return;
			}
			if(maze[g][h]==0 && mark[g][h]==0)
			{
				cout<<step<<":"<<g<<","<<h<<endl;
				out<<step<<":"<<g<<","<<h<<endl;
				step++;
				mark[g][h] = 1;
				temp.temp_x = i;
				temp.temp_y = j;
				temp.temp_dir = d+1;
				route.push(temp);
				i = g;
				j = h;
				d = 1;
			}
			else d++;
		}
		if(i==1 && j==0)
		{
			cout<<"Failed to escape."<<endl;
			out<<"fail to escape."<<endl;
			out.close();
			return;
		}
	}
}

int main(){
	ifstream in;
	cout<<"enter filename :";
	string filename;
	cin>>filename;
	in.open(filename);
	for(int i=0;i<17;i++){
		in>>input[i];
	}
	in.close();
	for(int i=0;i<17;i++){
		for(int j=0;j<17;j++){
			maze[i][j]=stoi(input[i].substr(j,1));
		}
	}
	for(int i=0;i<17;i++){
		for(int j=0;j<17;j++){
			cout<<maze[i][j];
		}
		cout<<endl;
	}
	for(int i=0;i<17;i++){
		for(int j=0;j<17;j++){
			mark[i][j]=maze[i][j];
		}
	}
	Path(17,17);
	return 0;
} 
