#include<iostream>
#include<vector>
#include<string>
#include<math.h>

using std::vector;
using std::string;
using std::cout;
using std::endl;

struct Node{
    int key;        //number
    string value;   //genre
    Node* next;

    Node():key(0), value(""), next(0){};
    Node(int Key, string Value):key(Key), value(Value), next(0){};
    Node(Node const &data):key(data.key), value(data.value), next(data.next){};
};

class HashChainNode{

private:
    int size;
    int count;
    Node** table;   //hashtable

    int HashFunction(int key);  //Multiplication method
    void TableDoubling();
    void TableShrinking();
    void Rehashing(int size_orig);

public:
    HashChainNode(){};
    HashChainNode(int m):size(m), count(0){
        table = new Node* [size];       // allocate the first dimmension of table
        for (int i = 0; i < size; i++){ // initialization 
            table[i] = 0;               // ensure every slot points to NULL
        }
    }
    ~HashChainNode();

    void Insert(Node data);     // consider TableDoubling()
    void Delete(int key);       // consider TableShrinking()
    string Search(int key);
    void DisplayTable();

};