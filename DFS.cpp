#include <iostream>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

class Graph{
private:
    int num_vertex;
    vector<list<int> > AdjList;     // Adjacent list
    int* marked;
    int* edgeTo;

public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize adjacent list
        AdjList.resize(num_vertex);
    };
    void DFS(int Start);
    void DFSVisit(int vertex);
};

void Graph::DFS(int Start){
    marked = new int[num_vertex];   // Assign address
    edgeTo = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++){
        marked[i] = 0;
        edgeTo[i] = -1;
    }

    int i = Start;
    for (int j = 0; j < num_vertex; j++){
        if (marked[i] == 0){
            DFSVisit(i);
        }
        i = j;
    }
}

void Graph::DFSVisit(int vertex){
    marked[vertex] = 1;
    for (list<int>::iterator itr = AdjList[vertex].begin(); itr != AdjList[vertex].end(); itr++){
        if (marked[*itr] == 0){ // means vertex *itr is not visited
            edgeTo[*itr] = vertex;
            DFSVisit(*itr);
        }
    }
}