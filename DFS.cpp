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
    void AddEdgeList(int from, int to);
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

    // int i = Start;
    // for (int j = 0; j < num_vertex; j++){
    //     if (marked[i] == 0){
    //         DFSVisit(i);
    //     }
    //     i = j;
    // }
    DFSVisit(Start);

    cout<<"marked: "<<endl;
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<i;
    }
    cout<<endl;
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<marked[i];
    }
    cout<<endl;

    cout<<"edgeTo: "<<endl;
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<i;
    }
    cout<<endl;
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<edgeTo[i];
    }
    cout<<endl;


}

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
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

int main(){
    Graph g2(8);
    //build graph
    g2.AddEdgeList(0, 1);g2.AddEdgeList(0, 2); 
    g2.AddEdgeList(1, 3);
    g2.AddEdgeList(2, 1);g2.AddEdgeList(2, 5);
    g2.AddEdgeList(3, 4);g2.AddEdgeList(3, 5);
    g2.AddEdgeList(5, 1);
    g2.AddEdgeList(6, 4);g2.AddEdgeList(6, 7);
    g2.AddEdgeList(7, 6);

    g2.DFS(0);

    Graph g1(9);
    g1.AddEdgeList(0, 1);
    g1.AddEdgeList(1, 0); g1.AddEdgeList(1, 2); g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 1); g1.AddEdgeList(2,5);
    g1.AddEdgeList(3,4);
    g1.AddEdgeList(4,1); g1.AddEdgeList(4,3); g1.AddEdgeList(4,5);
    g1.AddEdgeList(5,2); g1.AddEdgeList(5,4); g1.AddEdgeList(5,6); g1.AddEdgeList(5,8);
    g1.AddEdgeList(6,5); g1.AddEdgeList(6,7);
    g1.AddEdgeList(7,6);
    g1.AddEdgeList(8,5);
    g1.DFS(0);


    return 0;

}