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

int HashChainNode::HashFunction(int key){
    //Multiplication method
    double A = 0.6180339887;     //golden ratio
    double frac = key*A - floor(key*A);

    return floor(this->size*frac);
}

void HashChainNode::Rehashing(int size_orig){

    Node** newtable = new Node* [size]; // allocate memory for new table
    for (int i = 0; i < size; i++){     // initialization
        newtable[i] = 0;                // ensure every node in slots points to NULL
    }

    for (int i = 0; i < size_orig; i++){ //visit every node in the original table

        Node* curr_orig = table[i];
        Node* right_orig = NULL;    // on the right of current

        while(curr_orig != NULL){
            right_orig = curr_orig->next;

            int index = HashFunction(curr_orig->key);   // get index of slot in new table

            //push_front
            if (newtable[index] == NULL){   // if newtable[index] is empty
                newtable[index] = curr_orig;
                newtable[index]->next = 0;

            }
            else{   // if newtable[index] is not empty
                Node* next = newtable[index];
                newtable[index] = curr_orig;
                newtable[index]->next = next;

            }
            curr_orig = right_orig;
        }

    }
    delete [] table; // release memory of original table
    this->table = newtable; // point table of object to new table

}

void HashChainNode::TableDoubling(){
    int size_orig = size;
    size *= 2;              // size update
    Rehashing(size_orig);   // create new table with larger size

}

void HashChainNode::TableShrinking(){
    int size_orig = size;
    size /= 2;              // size update
    Rehashing(size_orig);   // create new table with smaller size
}