#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#ifndef endl
#define endl "\n"
#endif

using namespace std;

//structure of each node of the tree node
struct Node{
	Node* left;
	int data;
	Node* right;
};

//function to create node;
Node* createNode(int data);

//function to insert node into BST
Node* insert(Node* root, int data);

//function for pre-order traversal
void preOrder(Node* root);

//function for post-order traversal
void inOrder(Node* root);

//function for post-order traversal
void postOrder(Node* root);

//function for level order traversal
void levelOrder(Node* root);
void levelOrderRecursive(queue<Node*> queue);

//double order traversal
void doubleOrder(Node* root);

//triple order traversal
void tripleOrder(Node* root);

//search operation in BST
bool search(Node* root, int target);

//min element
int min(Node* root);
// max element
int max(Node* root);

//function to delete a node from a BST
void deleteNode(Node* root, int data);

int main(int argc, char const *argv[]){
	/* code */
	Node* root = NULL;
	/*
		Although root is not going to change after the first insert
	*/
	root = insert(root, 9);
	root = insert(root, 10);
	root = insert(root, 3);
	root = insert(root, 7);
	root = insert(root, 19);
	root = insert(root, 31);
	root = insert(root, 1);
	root = insert(root, 12);
	root = insert(root, 0);
	root = insert(root, 5);
	root = insert(root, 2);
	root = insert(root, 17);
	root = insert(root, 13);
	root = insert(root, 4);
	root = insert(root, 11);
	root = insert(root, 6);
	cout << "pre-order traversal: ";
	preOrder(root);
	cout << endl;
	cout << "in-order traversal: ";
	inOrder(root);
	cout << endl;
	cout << "post-order traversal: ";
	postOrder(root);
	cout << endl;
	cout << "level-order traversal: ";
	levelOrder(root);
	cout << endl;
	// cout << "level Order (Recursive) traversal: ";
	// queue<Node*> queue;
	// queue.push(root);
	// levelOrderRecursive(queue);
	// cout << endl;
	// cout << "double-order traversal: ";
	// doubleOrder(root);
	// cout << endl;
	// cout << "triple-order traversal: ";
	// tripleOrder(root);
	// cout << endl;
	cout << "min element = " << min(root) << endl;
	cout << "max element = " << max(root) << endl;
	int target, data, choice;
	while (true) {
		/* code */
		cout << "choose opteration\n 1.search\n 2.delete :\n";
		cin>>choice;
		switch (choice) {
			case 1: cout << "enter target to search in tree" << endl;
							cin>>target;
							if(search(root, target))
								cout << target << " is present in tree" << endl;
							else
								cout << target << " is not present in tree" << endl;
							break;
			case 2: cout << "level-order traversal before deletion : ";
							levelOrder(root);
							cout << endl;
							cout << "enter the node->data to delete it must be a in tree:\n";
							cin >> data;
							deleteNode(root, data);
							cout << "level-order traversal after deletion : ";
							levelOrder(root);
							cout << endl;
							break;
			default: cout << "invalid choice !\n";
		}
	}
	return 0;
}
Node* createNode(int data){
	Node* node = new Node();
	node->left = nullptr;
	node->data =  data;
	node->right = nullptr;
	return node;
}
Node* insert(Node* root, int data){
	//when BST is empty and to reach the
	if(!root) {
		Node* node = createNode(data);
		return node;
	}
	if (data < root->data )
	{
		root->left = insert(root->left, data);

	}else{
		root->right = insert(root->right, data);
	}
	return root;
}
/*--binary search tree

			  root
			   |
			   9
			/    \
		 3     10
	 /   \    \
  1 	 7    19
 / \  /   /   \
0  2 5	  12 	31
 	  / \	 /	\
   4  6 11	17
     	  		/
     	  	13


*/
void deleteNode(Node* root, int data){
	if(!root){
		cout << "there is no such node ! \n";
		return;
	}
	if(data < root->data ){
		deleteNode(root->left, data);
	}else if(data > root->data){
		deleteNode(root->right, data);
	}else{
		/*there will be three scenrios
		1. Node with no children
		2. Node with only one children
			Now there will be two cases
			either node will have
			i). left children or
			ii). right
		3. Node with two children
		So lets deal with them ...cheers
		*/
		if(root->left == NULL and root->right == NULL){
			root->data = 0;
			root->left = root->right = NULL;
			return;
		}
		else if (root->right == NULL){
			//more than one ancestors
			Node* tmp = root->left;
			// if right of left of root does not exist
			if(!tmp->right){
				root->data = tmp->data;
				root->left = tmp->left;
				tmp = NULL;
				return;
			}
			else {
				while(tmp->right != NULL){
					tmp = tmp->right;
				}
				swap(root->data, tmp->data);
				deleteNode(tmp, tmp->data);
				return;
			}
		}
		else if (root->left == NULL){
			//more than one ancestors
			Node* tmp = root->right;
			// if left of right of root does not exist
			if(!tmp->left){
				root->data = tmp->data;
				root->right = tmp->right;
				tmp = NULL;
				return;
			}
			else {
				while(tmp->left != NULL){
					tmp = tmp->left;
				}
				swap(root->data, tmp->data);
				deleteNode(tmp, tmp->data);
				return;
			}
		}
		else {
			//means node that has to be delete has two children
			Node* tmp = root->right;
			while(tmp->left != NULL){
				tmp = tmp->left;
			}
			swap(root->data, tmp->data);
			deleteNode(tmp, tmp->data);
			return;
		}
	}
	return;
}
bool search(Node* root, int target){
		if (!root) {
			/* code */
			return false;
		}
		if (root->data == target) {
			/* code */
			return true;
		}
		if (target < root->data) {
			/* code */
			return search(root->left, target);
		}else{
			return search(root->right, target);
		}
}


void preOrder(Node* root){
	if (!root)
		return;
	cout<< root->data <<" ";
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(Node* root){
	if (!root){
		return;
	}
	inOrder(root->left);
	cout<< root->data <<" ";
	inOrder(root->right);
}

void postOrder(Node* root){
	if (!root){
		return;
	}
	postOrder(root->left);
	postOrder(root->right);
	cout<< root->data <<" ";
}

void levelOrder(Node* root){
	if(!root)
		return;
	// store root node into queue
	queue<Node*> queue;
	queue.push(root);
	/*
		pop each node from the queue and push the child node (if not null) into
		the queue, keep doing this untill queue is empty.
	*/
	while(!queue.empty()){
		Node* node = queue.front();
		if(node->left != NULL)
			queue.push(node->left);
		if(node->right != NULL)
			queue.push(node->right);
		cout << node->data << " ";
		queue.pop();
	}
}

void levelOrderRecursive(queue<Node*> queue){
	if(queue.empty())
		return;
	Node* node = queue.front();
	cout << node->data << " ";
	if(node->left != NULL)
		queue.push(node->left);
	if(node->right != NULL)
		queue.push(node->right);
	queue.pop();
	levelOrderRecursive(queue);
}



int min(Node* root){
	if(!(root->left))
		return root->data;
	return min(root->left);
}

int max(Node* root){
	if(!(root->right))
		return root->data;
	return max(root->right);
}

void doubleOrder(Node* root){
	if(!root)
		return;
	cout << root->data <<" ";
	doubleOrder(root->left);
	cout << root->data << " ";
	doubleOrder(root->right);
}
//triple order traversal
void tripleOrder(Node* root){
	if(!root)
		return;
	cout << root->data << " ";
	tripleOrder(root->left);
	cout << root->data << " ";
	tripleOrder(root->right);
	cout << root->data << " ";
}
