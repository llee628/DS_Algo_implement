#include<iostream>
#include<queue>

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
	BSTNode* inorder_Successor(BSTNode* current);

public:
	BST():root(0){};

	BSTNode* search(int key);
	void insert(int key);
	void Delete(int key);
	void inorderPrint();
	void Levelorder();

};

BSTNode* BST::Leftmost(BSTNode* current){
	if (current == NULL){
		return current;
	}
	while (current->left != NULL){
		current = current->left;
	}
	return current;
}

BSTNode* BST::inorder_Successor(BSTNode* current){
	if (current == NULL){
		return current;
	}

	if (current->right != NULL){
		return Leftmost(current->right);
	}

	// for the case that right child is NULL
	BSTNode* successor = current->parent;
	while(successor != NULL && current == successor->right){
		current = successor;
		successor = successor->parent;
	}
	return successor;
}

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
	//cout<<"i am in"<<endl;
	BSTNode* current = root;
	BSTNode* current_parent = NULL;
	BSTNode* insert_node = new BSTNode(key);

	while(current != NULL){
		current_parent = current;

		if (insert_node->key < current->key){
			current = current->left;
		}
		else if(insert_node->key > current->key){
			current = current->right;
		}
		else{
			return;
		}
	}

	insert_node->parent = current_parent;

	if (current_parent == NULL){
		this->root = insert_node; //for the case that a BST is empty before insert
	}
	else if (insert_node->key < current_parent->key){
		current_parent->left = insert_node;
	}
	else{
		current_parent->right = insert_node;
	}
}

void BST::Delete(int key){

	//Still need approve
	//now can not deal with the case that when root has no child or one child

	BSTNode* delete_node = search(key);
	//check if key is in the BST
	if (delete_node == NULL){
		cout<<"data not found."<<endl;
		return;
	}

	//case1: leaf
	if (delete_node->left == NULL && delete_node->right == NULL){
		BSTNode* parent = delete_node->parent;
		if (delete_node == parent->left){
			parent->left = NULL;
			return;
		}
		else{
			parent->right = NULL;
			return;
		}
	}

	//case2: one child
	if (delete_node->left == NULL || delete_node->right == NULL){
		BSTNode* parent = delete_node->parent;
		if (delete_node == parent->left){
			if (delete_node->left != NULL){
				parent->left = delete_node->left;
				delete_node->left->parent = parent;
				return;
			}
			else{
				parent->left = delete_node->right;
				delete_node->right->parent = parent;
				return;
			}
		}
		else{
			if (delete_node->left != NULL){
				parent->right = delete_node->left;
				delete_node->left->parent = parent;
				return;
			}
			else{
				parent->right = delete_node->right;
				delete_node->right->parent = parent;
				return;
			}
		}
	}

	//case 3: two children
	if (delete_node->left != NULL && delete_node->right != NULL){
		BSTNode* successor = inorder_Successor(delete_node);
		BSTNode* parent = successor->parent;

		delete_node->key = successor->key;
		if (parent->left == successor){
			parent->left = NULL;
			return;
		}
		else{
			parent->right = NULL;
			return;
		}

	}
}

void BST::inorderPrint(){
	//cout<<"i am in"<<endl;

	if (root == NULL){
		//cout<<"i am in"<<endl;
		return;
	}

	BSTNode* current = Leftmost(root);
	while (current != NULL){
		cout<<current->key<<" ";
		current = inorder_Successor(current);
	}
}

void BST::Levelorder(){
	if (this->root == NULL){
		return;
	}

	queue<BSTNode* > q;
	q.push(this->root);

	while(!q.empty()){
		BSTNode* current = q.front();
		q.pop();
		cout<<current->key<<" ";

		if (current->left != NULL){
			q.push(current->left);
		}

		if (current->right != NULL){
			q.push(current->right);
		}

	}
}



int main(){
	BST T1;

	T1.insert(8);
	T1.insert(1000);
	T1.insert(2);
	T1.insert(513);

	cout<<"Inorder:"<<endl;
	T1.inorderPrint();
	cout<<endl;
	cout<<"Levelorder:"<<endl;
	T1.Levelorder();
	cout<<endl;

	T1.Delete(8);
	cout<<"Inorder:"<<endl;
	T1.inorderPrint();
	cout<<endl;
	cout<<"Levelorder:"<<endl;
	T1.Levelorder();
	cout<<endl;

	T1.Delete(512);
	T1.Delete(513);
	T1.Delete(1000); //run time error
	cout<<"Inorder:"<<endl;
	T1.inorderPrint();
	cout<<endl;
	cout<<"Levelorder:"<<endl;
	T1.Levelorder();
	cout<<endl;


	return 0;

}







