#include<iostream>

using namespace std;


class BST;
class BSTNode{
private:
	int key;
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;

public:
	BSTNode():left(0), right(0), parent(0), key(0){};
	BSTNode(int a):left(0), right(0), parent(0), key(a){};

	int GetKey(){return key;}

	friend class BST; //it is fine with putting this line either in private or public

};


class BST{
private:
	BSTNode* root;
	BSTNode* Leftmost(BSTNode* current);
	BSTNode* Successor(BSTNode* current);

public:
	BST():root(0){};

	BSTNode* search(int key);
	void insert(int key);
	void inorderPrint();
	void Levelorder();

};

BSTNode* BST::search(int key){
	BSTNode* current = root;

	while (current != NULL){
		if (key == current->key){
			return current;
		}
		else if (key > current->key){
			current = current->right;
		}
		else{
			current = current->left;
		}
	}

	return current;
}

void BST::insert(int key){
	BSTNode* current = root;
	BSTNode* current_parent = NULL;
	BSTNode* insert_node = new BSTNode(key);

	while(current != NULL){
		current_parent = current;

		if (insert_node->key < current->key){
			current = current->left;
		}
		else{
			current = current->right;
		}

		insert_node->parent = current_parent;

		if (current->parent == NULL){
			this->root = insert_node; //for the case that a BST is empty before insert
		}
		else if (insert_node->key < current_parent->key){
			current_parent->left = insert_node;
		}
		else{
			current_parent->right = insert_node;
		}

	}

}







