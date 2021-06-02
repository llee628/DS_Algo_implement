#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iomanip>

using namespace std;

class Graph{
private:
    int num_vertex;
    vector<list<int> > AdjList;     // Adjacent list
    int* marked;
    int* edgeTo;
    int* distTo;

public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        //initialize adjacent list
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void BFS(int Start);
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}

