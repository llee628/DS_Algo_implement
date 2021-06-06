#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iomanip>
#include <cmath>
#include "BinaryHeap.h"

using namespace std;

const int Max_Distance = 100;

class Graph_SP{
private:
    int num_vertex;
    vector<list<pair<int, int> > > AdjList;
    vector<int> edgeTo;
    vector<int> distTo;
    vector<bool> marked;

public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    };
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(vector<int> array);
    void PrintIntArray(int* array);

    void InitializeSingleSource(int Start);
    void Relax(int X, int Y, int weight);  // From X to Y

    void Dijkstra(int Start = 0);
    friend class BinaryHeap;

};

void Graph_SP::AddEdge(int from, int to, int weight){
    AdjList[from].push_back(make_pair(to,weight));
}

void Graph_SP::PrintDataArray(vector<int> array){
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<i;
    }
    cout<<endl;
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<array[i];
    }
    cout<<endl;
}

void Graph_SP::InitializeSingleSource(int Start){
    distTo.resize(num_vertex);
    edgeTo.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++){
        distTo[i] = Max_Distance;
        edgeTo[i] = -1;
    }
    distTo[Start] = 0;

}

void Graph_SP::Relax(int from, int to, int weight){

    if (distTo[to] > distTo[from] + weight){
        distTo[to] = distTo[from] + weight;
        edgeTo[to] = from;
    }

}

void Graph_SP::Dijkstra(int Start){

    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);    
    minQueue.BuildMinHeap(distTo);

    marked.resize(num_vertex, false);

    while(!minQueue.IsHeapEmpty()){
        int u = minQueue.ExtractMin();
        for (list<pair<int, int> >::iterator itr = AdjList[u].begin(); 
            itr != AdjList[u].end(); itr++){
            Relax(u, (*itr).first, (*itr).second);
            minQueue.DecreaseKey((*itr).first, distTo[(*itr).first]);
        }
    }
    cout<<"\nprint edgeTo:\n";
    PrintDataArray(edgeTo);
    cout<<"\nprint distTo:\n";
    PrintDataArray(distTo);

}

int main(){

    return 0;
}

