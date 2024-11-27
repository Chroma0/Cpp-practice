#include<iostream>
#include<fstream>
#include<string>
#include<queue>
using namespace std;

class Node{
	public:
		int vertex1;
		int vertex2;
		int weight;
};

queue<Node> MST;
void prim(int graph[26][26],int startpoint){
	bool exist[26];
	bool visit[26];
	for(int i=0;i<26;i++){
		int count=0;
		for(int j=0;j<26;j++){
			if(graph[i][j] != 0){
				count++;
				break;
			}
		}
		if(count == 0){
			exist[i] = false;
			visit[i] = false;
		}
		else{
			exist[i] = true;
			visit[i] = false;
		}
	}
	Node new_edge;//Edge that found by prim's algorithm
	//Frist edge
	int new_edge_num=0;
	new_edge.vertex1 = new_edge.vertex2 = new_edge.weight = 0;
	for(int i=0;i<26;i++){
		if((graph[startpoint][i] != 0) && (new_edge_num == 0)){
			new_edge.vertex1 = startpoint;
			new_edge.vertex2 = i;
			new_edge.weight = graph[startpoint][i];
			new_edge_num++;
		}
		else if((graph[startpoint][i] != 0) && (graph[startpoint][i] < new_edge.weight)){
			new_edge.vertex1 = startpoint;
			new_edge.vertex2 = i;
			new_edge.weight = graph[startpoint][i];
		}
	}
	visit[startpoint] = visit[new_edge.vertex2] = true;
	graph[startpoint][new_edge.vertex2] = graph[new_edge.vertex2][startpoint] = 0;
	MST.push(new_edge);
	//Other edge
	int exist_num=0,visit_num=0;
	for(int i =0 ;i<26;i++){
		if(exist[i] == 1) exist_num++;
		if(visit[i] == 1) visit_num++;
	}
	while(exist_num != visit_num){
		new_edge_num = 0;
		for(int i=0;i<26;i++){
			if(visit[i] == true){
				for(int j=0;j<26;j++){
					if((graph[i][j] != 0) && (new_edge_num == 0) && (visit[j] == false)){
						new_edge.vertex1 = i;
						new_edge.vertex2 = j;
						new_edge.weight = graph[i][j];
						new_edge_num++;
					}
					else if((graph[i][j] != 0) && (graph[i][j] < new_edge.weight) && (visit[j] == false)){
						new_edge.vertex1 = i;
						new_edge.vertex2 = j;
						new_edge.weight = graph[i][j];
					}
				}
			}
		}
		visit[new_edge.vertex2] = true;
		graph[new_edge.vertex1][new_edge.vertex2] = graph[new_edge.vertex2][new_edge.vertex1] = 0;
		MST.push(new_edge);
		exist_num=0;
		visit_num=0;
		for(int i =0 ;i<26;i++){
			if(exist[i] == 1) exist_num++;
			if(visit[i] == 1) visit_num++;
		}	
	}
	Node out[MST.size()];
	int out_size=MST.size();
	for(int i=0;i<out_size;i++){
		out[i]=MST.front();
		MST.pop();
	}
	//Sort output in ascending order according to the weight
	for(int i=0;i<out_size-1;i++){
		for(int j=i+1;j<out_size;j++){
			if(out[i].weight > out[j].weight){
				Node swap=out[i];
				out[i]=out[j];
				out[j]=swap;
			}
		}
	}
	//Output file
	ofstream fout;
	fout.open("output_p.txt",ios::out);
	for(int i=0;i<out_size;i++){
		//Output in ascending order according to alphabetical order.
		if(out[i].vertex1 < out[i].vertex2){
			cout<<(char)(out[i].vertex1 + 97)<<" "<<(char)(out[i].vertex2 + 97)<<" "<<out[i].weight<<endl;
			fout<<(char)(out[i].vertex1 + 97)<<" "<<(char)(out[i].vertex2 + 97)<<" "<<out[i].weight<<endl;
		}
		else {
			cout<<(char)(out[i].vertex2 + 97)<<" "<<(char)(out[i].vertex1 + 97)<<" "<<out[i].weight<<endl;
			fout<<(char)(out[i].vertex2 + 97)<<" "<<(char)(out[i].vertex1 + 97)<<" "<<out[i].weight<<endl;
		}
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
    		graph[(int)(vertex2)-97][(int)(vertex1)-97] = weight;
		}
		ifs>>startPoint;
		ifs.close();
		prim(graph,(int)(startPoint)-97);
		return 0;
	}
} 
