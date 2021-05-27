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