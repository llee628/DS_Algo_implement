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

void BinaryHeap::swap(struct HeapNode& p1, struct HeapNode& p2){

    struct HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}

int BinaryHeap::FindPosition(int node){

    int idx = 0;
    for (int i = 1; i < heap.size(); i++){
        if (heap[i].element == node){
            idx = i;
        }
    }
    
    return idx;
}

int BinaryHeap::Minimum(){
    return heap[1].element;
}

int BinaryHeap::ExtractMin(){

    if (IsHeapEmpty()){
        cout<<"error: heap is empty\n";
        exit(-1);
    }
    int min = heap[1].element;

    //delete the first element
    heap[1] = heap[heap.size()-1]; // replace first element with last element
    heap.erase(heap.begin() + heap.size()-1); // release the last element
    MinHeapify(1, (int)heap.size());

    return min;
}

void BinaryHeap::DecreaseKey(int node, int newKey){

    int index_node = FindPosition(node);

    if (newKey > heap[index_node].key){
        cout<<"new key is larger than current key\n";
        return;
    }
    heap[index_node].key = newKey;

    //sift up
    while (index_node > 1 && heap[GetParentNode(index_node)].key > heap[index_node].key){
        swap(heap[index_node], heap[GetParentNode(index_node)]);
        index_node = GetParentNode(index_node);
    }
}

void BinaryHeap::MinHeapInsert(int node, int key){

    heap.push_back(HeapNode(node,key));
    DecreaseKey(node, key);  //siftup if necessary
}
