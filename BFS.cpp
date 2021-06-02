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

void Graph::BFS(int Start){

    marked = new int[num_vertex];
    edgeTo = new int[num_vertex];
    distTo = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++){ // initialize the above three arrays
        marked[i] = 0;
        edgeTo[i] = -1;
        distTo[i] = num_vertex + 1;

    }

    queue<int> q;
    int i = Start;

    for (int j = 0; j < num_vertex; j++){
        if (marked[i] == 0){
            marked[i] = 1;
            distTo[i] = 0;
            edgeTo[i] = -1;
            q.push(i);
            while (!q.empty()){
                int u = q.front();
                for (list<int>::iterator itr = AdjList[u].begin();
                    itr != AdjList[u].end(); itr++){
                    
                    if (marked[*itr] == 0){
                        marked[*itr] = 1;
                        distTo[*itr] = distTo[u] + 1;
                        edgeTo[*itr] = u;
                        q.push(*itr);
                    }
                }
                q.pop();
            }
        }
        i = j;
    }

    // display arrays
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

    cout<<"distTo: "<<endl;
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<i;
    }
    cout<<endl;
    for (int i = 0; i < num_vertex; i++){
        cout<<setw(4)<<distTo[i];
    }
    cout<<endl;
}

int main(){
    //test case 1:
    cout<<"test case 1:"<<endl;
    Graph g1(9);

    g1.AddEdgeList(0, 1);g1.AddEdgeList(0, 2);g1.AddEdgeList(0, 3);
    g1.AddEdgeList(1, 0);g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 0);g1.AddEdgeList(2, 4);g1.AddEdgeList(2, 5);g1.AddEdgeList(2, 6);g1.AddEdgeList(2, 7);
    g1.AddEdgeList(3, 0);g1.AddEdgeList(3, 7);
    g1.AddEdgeList(4, 1);g1.AddEdgeList(4, 2);g1.AddEdgeList(4, 5);
    g1.AddEdgeList(5, 2);g1.AddEdgeList(5, 4);g1.AddEdgeList(5, 8);
    g1.AddEdgeList(6, 2);g1.AddEdgeList(6, 7);g1.AddEdgeList(6, 8);
    g1.AddEdgeList(7, 2);g1.AddEdgeList(7, 3);g1.AddEdgeList(7, 6);
    g1.AddEdgeList(8, 5);g1.AddEdgeList(8, 6);
    g1.BFS(0);

    //test case 2:
    cout<<"test case 2: "<<endl;
    Graph g2(9);

    g2.AddEdgeList(0, 1);
    g2.AddEdgeList(1, 0); g2.AddEdgeList(1, 2); g2.AddEdgeList(1, 4);
    g2.AddEdgeList(2, 1); g2.AddEdgeList(2, 5);
    g2.AddEdgeList(3, 4);
    g2.AddEdgeList(4, 1); g2.AddEdgeList(4, 3); g2.AddEdgeList(4, 5);
    g2.AddEdgeList(5, 2); g2.AddEdgeList(5, 4); g2.AddEdgeList(5, 6); g2.AddEdgeList(5, 8);
    g2.AddEdgeList(6, 5); g2.AddEdgeList(6, 7);
    g2.AddEdgeList(7, 6);
    g2.AddEdgeList(8, 5);
    g2.BFS(0);
    
}
