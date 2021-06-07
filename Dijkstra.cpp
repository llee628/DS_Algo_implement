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
    Graph_SP g9(6);
    g9.AddEdge(0, 1, 8);g9.AddEdge(0, 5, 1);
    g9.AddEdge(1, 0, 3);g9.AddEdge(1, 2, 1);
    g9.AddEdge(2, 0, 5);g9.AddEdge(2, 3, 2);g9.AddEdge(2, 4, 2);
    g9.AddEdge(3, 1, 4);g9.AddEdge(3, 2, 6);g9.AddEdge(3, 4, 7);g9.AddEdge(3, 5, 3);
    g9.AddEdge(5, 3, 2);g9.AddEdge(5, 4, 8);
    g9.Dijkstra(0);

    Graph_SP g1(7);
    g1.AddEdge(0, 1, 2); g1.AddEdge(0, 2, 1);
    g1.AddEdge(1, 2, 5); g1.AddEdge(1, 3, 11); g1.AddEdge(1, 4, 3);
    g1.AddEdge(2, 5, 15);
    g1.AddEdge(3, 4, 2);
    g1.AddEdge(4, 2, 1); g1.AddEdge(4, 5, 4); g1.AddEdge(4, 6, 5);
    g1.AddEdge(6, 3, 1); g1.AddEdge(6, 5, 1);
    g1.Dijkstra(0);

    return 0;
}

