#include<iostream>
#include<fstream>
#include<string>
#include<queue>
using namespace std;

class Node//Node structure
{
	public:
		Node* Parent;
		Node* LeftChild;
		Node* RightChild;
		int data;
		Node():Parent(0),LeftChild(0),RightChild(0),data(-1){};
		Node(int number):Parent(0),LeftChild(0),RightChild(0),data(number){};
		void Insert(int data);
		Node* Search(int data);
		void Delete(Node* location);
};
Node* root = 0;//Binary Search Tree's root

void Node::Insert(int data){
	Node* NewParent = 0;//New node's parent
    Node* Place = 0;//Stor new node's place
    Node* InsertNode = new Node(data);
    Place = root;
    while(Place != NULL){     
    	NewParent = Place;
    	//Choose whether Place should go left or right
		if(data < Place->data) Place = Place->LeftChild;
    	else Place = Place->RightChild;
	}
    InsertNode->Parent = NewParent;//Set new node parent
    if(NewParent == NULL){//Whether new node is root
		root = InsertNode;
	}
	//if new node isn't root,set New parent's child
	else if(InsertNode->data < NewParent->data){
		NewParent->LeftChild = InsertNode;
	}
	else{
		NewParent->RightChild = InsertNode;
	}
}

Node* Node::Search(int data){
    Node* current = root;//Start from root
    while(current != NULL && data != current->data){
    	//Choose whether current should go left or right
        if(data < current->data){
			current = current->LeftChild;
        }
        else{
            current = current->RightChild;
        }
    }
    return current;
}

void Node::Delete(Node* location){
    Node* replace = location;//Deleted node's location
    if(replace->RightChild != NULL && replace->LeftChild != NULL){//Deleted node has right sub-tree and left sub-tree
    	replace = replace->RightChild;
    	while(replace->LeftChild != NULL) replace = replace->LeftChild;
    	location->data = replace->data;//Replace deleted node's data
    	if(replace->Parent->LeftChild == replace){
    		if(replace->RightChild != NULL) replace->Parent->LeftChild = replace->RightChild;
			else replace->Parent->LeftChild = NULL;
		}
    	else if(replace->Parent->RightChild == replace){
    		if(replace->RightChild != NULL) replace->Parent->RightChild = replace->RightChild;
			else replace->Parent->RightChild = NULL;
		}
	}
	else if(replace->LeftChild != NULL && replace->RightChild == NULL){//Deleted node doesn't have right sub-tree but has left sub-tree
		//Replace deleted node's with it's LeftChild
		replace = replace->LeftChild;
		if(location->Parent->LeftChild == location) location->Parent->LeftChild = replace;
    	else if(location->Parent->RightChild == location) location->Parent->RightChild = replace;
	}
	else if(replace->LeftChild == NULL && replace->RightChild != NULL){//Deleted node doesn't have left sub-tree but has right sub-tree
		//Replace deleted node's with it's RightChild
		replace = replace->RightChild;
		if(location->Parent->LeftChild == location) location->Parent->LeftChild = replace;
    	else if(location->Parent->RightChild == location) location->Parent->RightChild = replace;
	}
	else{//Deleted node is a leaf
		if(replace->Parent == NULL) location = 0;//Deleted node is root
		else{//Deleted node directly
			if(replace->Parent->LeftChild == replace) location->Parent->LeftChild = 0;
			else location->Parent->RightChild = 0;
		}
	}
}

void Preorder(Node* current){//Print BST in Prefix order
	if(current != NULL){
		//output order:current -> LeftChild -> RightChild
		ofstream out;
		out.open("output.txt",ios::app);
		cout<<current->data<<" ";
		out<<current->data<<" ";
		out.close();
		if(current->LeftChild != NULL) Preorder(current->LeftChild);
		if(current->RightChild != NULL) Preorder(current->RightChild);
	}
}

void Inorder(Node* current){//Print BST in Infix order
	if(current != NULL){
		//output order:LeftChild -> current -> RightChild
		if(current->LeftChild != NULL) Inorder(current->LeftChild);
		ofstream out;
		out.open("output.txt",ios::app);
		cout<<current->data<<" ";
		out<<current->data<<" ";
		out.close();
		if(current->RightChild != NULL) Inorder(current->RightChild);
	}
}

void Posorder(Node* current){//Print BST in Post order
	if(current != NULL){
		//output order:LeftChild -> RightChild -> current
		if(current->LeftChild != NULL) Posorder(current->LeftChild);
		if(current->RightChild != NULL) Posorder(current->RightChild);
		ofstream out;
		out.open("output.txt",ios::app);
		cout<<current->data<<" ";
		out<<current->data<<" ";
		out.close();
	}
}

void Levelorder(Node* current){//Print BST in Level order
	if(current != NULL){
		ofstream out;
		out.open("output.txt",ios::app);
		queue<Node*> q;
	    q.push(current);//Level order from root
	    while (!q.empty()){
	        current = q.front();
	        q.pop();
			cout <<current->data<<" ";
			out<<current->data<<" ";
	        if(current->LeftChild != NULL){//Check if there's a LeftChild
	            q.push(current->LeftChild);
	        }
	        if(current->RightChild != NULL){//Check if there's a RightChild
	            q.push(current->RightChild);
	        }
	    }
	    out.close();
	}
}

int main(){
	ifstream ifs;
	ofstream out;
	out.open("output.txt",ios::out);//Output File
	string FileName;
	cout<<"Enter file name: ";
	cin>>FileName;
	ifs.open(FileName);
	out<<"File name: "<<FileName<<"\n";
	out.close();
	//Check if the file exist
	if (!ifs.is_open()) {
        cout << "File doesn't exist.\n";
        return 1;//Exit failure
    }
    else{
    	//Load file
    	char move;//Strore movement like Insert,Delete,Search,Print and Exit
    	Node BST;
    	while(!ifs.eof()){
    		out.open("output.txt",ios::app);
    		cout<<"\n(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint 4 kinds of orders.\n(E)xit\n"<<endl;
    		out<<"\n(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint 4 kinds of orders.\n(E)xit\n"<<endl;
    		out.close();
    		ifs>>move;//input movement
    		if(move == 'i' || move == 'I'){
    			out.open("output.txt",ios::app);
    			cout<<"Insert:\n";
    			out<<"Insert:\n";
    			int number;
    			while(ifs>>number){
    				if(number == -1) break;
    				else{
    					if(BST.Search(number) == NULL){//Search if input number already exists
    						cout<<"Number "<<number<<" is inserted.\n";
    						out<<"Number "<<number<<" is inserted.\n";
    						BST.Insert(number);//If input number doesn't exist,insert it
						}
    					else{
    						cout<<"Error! Number "<<number<<" exists.\n";
    						out<<"Error! Number "<<number<<" exists.\n";
						}
					}
				}
				out.close();
			}
			else if(move == 'd' || move == 'D'){
				out.open("output.txt",ios::app);
				cout<<"Delete:\n";
				out<<"Delete:\n";
    			int number;
    			while(ifs>>number){
    				if(number == -1) break;
    				else{
    					if(BST.Search(number) != NULL){//Search if input number is exist
    						cout<<"Number "<<number<<" is deleted.\n";
    						out<<"Number "<<number<<" is deleted.\n";
    						BST.Delete(BST.Search(number));//If input number exists,delete it
						}
    					else{
    						cout<<"Number "<<number<<" is not exist.\n";
    						out<<"Number "<<number<<" is not exist.\n";
						}
					}
				}
				out.close();
			}
			else if(move == 's' || move == 'S'){
				out.open("output.txt",ios::app);
    			cout<<"Search:\n";
    			out<<"Search:\n";
    			int number;
    			while(ifs>>number){
    				if(number == -1) break;
    				else{
    					if(BST.Search(number) != NULL){//Search if input number is exist
    						cout<<"Bingo! "<<number<<" is found.\n";
    						out<<"Bingo! "<<number<<" is found.\n";
						}
    					else{
    						cout<<"Sorry! "<<number<<" is not found.\n";
    						out<<"Sorry! "<<number<<" is not found.\n";
						}
					}
				}
				out.close();
			}
			else if(move == 'p' || move == 'P'){
    			cout<<"Print:\n";
    			out.open("output.txt",ios::app);
    			out<<"Print:\n";
    			cout<<"The tree in prefix order: ";
    			out<<"The tree in prefix order: ";
    			out.close();
				Preorder(root);//Output BST in preorder
				cout<<endl;
				out.open("output.txt",ios::app);
				out<<endl;
				out.close();
    			cout<<"The tree in infix order: ";
    			out.open("output.txt",ios::app);
    			out<<"The tree in infix order: ";
    			out.close();
				Inorder(root);//Output BST in inorder
				cout<<endl;
				out.open("output.txt",ios::app);
				out<<endl;
				out.close();
    			cout<<"The tree in post order: ";
    			out.open("output.txt",ios::app);
    			out<<"The tree in post order: ";
    			out.close();
				Posorder(root);//Output BST in posorder
				cout<<endl;
				out.open("output.txt",ios::app);
				out<<endl;
				out.close();
    			cout<<"The tree in level order: ";
    			out.open("output.txt",ios::app);
    			out<<"The tree in level order: ";
    			out.close();
				Levelorder(root);//Output BST in levelorder
				cout<<endl;
				out.open("output.txt",ios::app);
				out<<endl;
				out.close();
			}
			else if(move == 'e' || move == 'E'){
				cout<<"Exit\n";
				out.open("output.txt",ios::app);
				out<<"Exit\n";
				out.close();
    			ifs.close();
    			return 0;//Exit program
			}
		}
		ifs.close();
		return 0;
	}
} 
