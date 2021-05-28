#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

struct HeapNode{
    int element;
    int key;
    HeapNode():element(0),key(0){};
    HeapNode(int node, int key):element(node), key(key){};

};

class BinaryHeap{
private:
    vector<HeapNode> heap;      //use an array to represent binary heap
    void swap(struct HeapNode& p1, struct HeapNode& p2);
    int FindPosition(int node);
    int GetParentNode(int node){return floor(node/2);}

public:
    BinaryHeap(){
        heap.resize(1);     // leave the position 0
    }
    BinaryHeap(int n){
        heap.resize(n+1);
    }
    bool IsHeapEmpty(){return (heap.size()<1);}

    //Min-Priority Queue
    void MinHeapify(int node, int length);
    void BuildMinHeap(vector<int> array);
    void DecreaseKey(int node, int newKey);
    void MinHeapInsert(int node, int key);
    int Minimum();
    int ExtractMin();


};

void BinaryHeap::MinHeapify(int node, int length){
    //sink

    int left = 2*node;          // left child
    int right = 2*node + 1;     // right child
    int smallest;

    if (left <= length && heap[left].key < heap[node].key){
        smallest = left;
    }
    else{
        smallest = node;
    }

    if (right <= length && heap[right].key < heap[smallest].key){
        smallest = right;
    }

    if (smallest != node){
        swap(heap[smallest], heap[node]);
        MinHeapify(smallest, length);   // Minheapify the new subtree
    }
}

void BinaryHeap::BuildMinHeap(vector<int> array){
    // put the information of array into heap [], and leave the heap[0]
    for (int i = 0; i < array.size(); i++){
        heap[i+1].element = i;
        heap[i+1].key = array[i];
    }
    for (int i = (int)heap.size()/2; i >= 1; i--){
        MinHeapify(i, (int)heap.size()-1); // -1 is because we leave heap[0] blank
    }
}
