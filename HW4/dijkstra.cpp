#include<iostream>
#include<fstream>
#include<string>
#include<queue>
using namespace std;

class shortestPath{
	public:
		char destination;
		int weight;
};

void dijkstra(int graph[26][26],int startpoint){
	bool exist[26];
	queue<shortestPath> output;
	for(int i=0;i<26;i++) exist[i]=false;
	for(int i=0;i<26;i++){
		for(int j =0;j<26;j++){
			if(graph[i][j] != 0){
				exist[i]=true;
				exist[j]=true;
			}
		}
	}
	shortestPath path;
	path.destination = (char)(startpoint+97);
	path.weight=0;
	output.push(path);
	//Dijkstra algorithm
	bool dij_visit[26];//Check whether it has been visited.
	int cost[26];//The shortest path from start point to the node.
	for(int i=0;i<26;i++){
		if(exist[i]==1) dij_visit[i]=false;
		else dij_visit[i]=true;
		cost[i]=0;
	}
	dij_visit[startpoint]=true;
	for(int i=0;i<26;i++){
		if(graph[startpoint][i] != 0) cost[i]=graph[startpoint][i];
	}
	while(true){
		int nextpoint;
		int point_exist=0;
		for(int i=0;i<26;i++){
			if(point_exist==0 && cost[i]!=0 && dij_visit[i] == false){
				nextpoint=i;
				point_exist++;
			}
			else if(cost[i]!=0 && cost[i]<cost[nextpoint] && dij_visit[i] == false) nextpoint=i;
		}
		for(int i=0;i<26;i++){
			if(graph[nextpoint][i] != 0){
				if(cost[i] == 0 && i != startpoint && dij_visit[i] == false) cost[i]=cost[nextpoint]+graph[nextpoint][i];
				else if(cost[i] != 0 && cost[i]>(cost[nextpoint]+graph[nextpoint][i]) && dij_visit[i] == false) cost[i]=cost[nextpoint]+graph[nextpoint][i];
			}
		}
		dij_visit[nextpoint] = true;
		int dij_visit_num=0;
		for(int i=0;i<26;i++){
			if(dij_visit[i] == false) dij_visit_num++;
		}
		if(dij_visit_num == 0) break;
	}
	for(int i=0;i<26;i++){
		if(cost[i] != 0){
			path.destination=(char)(i+97);
			path.weight=cost[i];
			output.push(path);
		}
	}
	shortestPath out[output.size()];
	int out_size=output.size();
	for(int i=0;i<out_size;i++){
		out[i]=output.front();
		output.pop();
	}
	//Sort output in ascending order according to the weight
	for(int i=0;i<out_size-1;i++){
		for(int j=i+1;j<out_size;j++){
			if(out[i].weight > out[j].weight){
				shortestPath swap=out[i];
				out[i]=out[j];
				out[j]=swap;
			}
		}
	}
	//Output file
	ofstream fout;
	fout.open("output_d.txt",ios::out);
	for(int i=0;i<out_size;i++){
		cout<<out[i].destination<<" "<<out[i].weight<<endl;
		fout<<out[i].destination<<" "<<out[i].weight<<endl;
	}
	fout.close();
	return;
}

int main(){
	ifstream ifs;
	string fileName;
	cout<<"Enter file name: ";
	cin>>fileName;
	ifs.open(fileName);
	if (!ifs.is_open()) {
        cout << "File doesn't exist.\n";
        return 1;//Exit failure
    }
    else{
    	int edge;
    	char startPoint;
    	//Load file
    	ifs>>edge;
    	int graph[26][26];
    	for(int i =0;i<26;i++){
    		for(int j=0;j<26;j++){
    			graph[i][j]=0;
			}
		}
    	for(int i = 0 ; i < edge ; i++){
    		char vertex1,vertex2;
			int weight;
    		ifs>>vertex1>>vertex2>>weight;
    		graph[(int)(vertex1)-97][(int)(vertex2)-97] = weight;
		}
		ifs>>startPoint;
		ifs.close();
		for(int i=0;i<26;i++){
			int count=0;
			for(int j=0;j<26;j++){
				if(graph[j][i] != 0){
					count++;
					break;
				}
			}
			//If no node is connected to it and it is not the start point,we can pretend the node isn't exist.
			if(count==0 && (i != (int)(startPoint)-97)){
				for(int j=0;j<26;j++){
					graph[i][j]=0;
				}
			}
		}
		dijkstra(graph,(int)(startPoint)-97);
		return 0;
	}
}
