#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {

private:
	vector<int> parent;
	int find(int p){
		//give a node, find its root
		int root = p;
		while(parent[root] >= 0){
			root = parent[root];
		}
		return root;
	}

public:
	DisjointSet(int N){
		vector<int> buf(N, -1);
		parent = buf;
	}

	bool isConnected(int p, int q){
		int root_p = find(p);
		int root_q = find(q);

		if (root_p == root_q){
			return true;
		}

		return false;
	}

	void connect(int p, int q){
		int i = find(p);
		int j = find(q);
		parent[i] = j;
	}
};

int main(){
	DisjointSet D_set(8);

	cout<<D_set.isConnected(0,1)<<endl; //false
	D_set.connect(0,1);
	D_set.connect(3,4);
	D_set.connect(0,4);
	D_set.connect(5,7);

	cout<<D_set.isConnected(0,1)<<endl; //true
	cout<<D_set.isConnected(1,3)<<endl; //true
	cout<<D_set.isConnected(0,4)<<endl; //true
	cout<<D_set.isConnected(5,7)<<endl; //true
	cout<<D_set.isConnected(0,7)<<endl; //false
	
	return 0;
}




