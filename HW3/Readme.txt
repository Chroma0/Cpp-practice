class Node : Binary Search Tree node.

void Node::Insert(int data) : Input an integer.If data already exists,ignore it,else insert it.

Node* Node::Search(int data) : Input an integer.Search if data exists in binary search tree.

void Node::Delete(Node* location) : Input an integer.If data exists in binary search tree,delete it,else ignore it.

void Preorder(Node* current) : Input pointer of binary search tree's root.Print binary search tree in prefix order.

void Inorder(Node* current) : Input pointer of binary search tree's root.Print binary search tree in infix order.

void Posorder(Node* current) : Input pointer of binary search tree's root.Print binary search tree in post order.

void Levelorder(Node* current) : Input pointer of binary search tree's root.Print binary search tree in level order.

int main() : Program starting point.