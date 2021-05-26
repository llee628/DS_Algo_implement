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

HashChainNode::~HashChainNode(){
    /**
     * Visit every node in table
     * and release the memory of each node
     */
    for (int i = 0; i < size; i++){

        Node* current = table[i];    
        while (current != NULL){
            Node* previous = current;
            current = current->next;
            delete previous;
            previous = 0;
        } 
    }
    delete [] table;
}

void HashChainNode::Insert(Node data){
    count += 1;
    if (count > size){      // consider load factor
        TableDoubling();    // if n/m > 1, then double the size of table
    }

    int index = HashFunction(data.key);
    Node* newNode = new Node(data);     // create new node to store data

    //push_front
    if (table[index] == NULL){
        table[index] = newNode;
    }
    else{
        Node* next = table[index];
        table[index] = newNode;
        newNode->next = next;
    }
}

void HashChainNode::Delete(int key){

    int index = HashFunction(key);
    Node* current = table[index];
    Node* previous = NULL;

    while (current != NULL && current->key != key){
        previous = current;
        current = current->next;
    }

    /**
     * traversal in list, 3 cases:
     * 1. data not found
     * 2. data found at first node
     * 3. data found at other position
     */

    if (current == NULL){
        cout<< "data not found.\n\n";
        return;
    }
    else{
        if (previous == NULL){
            table[index] = current->next;
        }
        else {
            previous->next = current->next;
        }
        delete current;
        current = 0;
    }

    count -= 1;
    if (count < size/4){
        TableShrinking();   // if n/m < 4, then shrink the table
    }
}

string HashChainNode::Search(int key){

    int index = HashFunction(key);
    Node* current = table[index];

    while(current != NULL){
        if (current->key == key){
            return current->value;
        }
        current = current->next;
    }
    return "...\nno such data";
}

void HashChainNode::DisplayTable(){

    for (int i = 0; i < size; i++){
        cout<< "slot#" <<i<<": ";
        Node* current = table[i];
        while (current != NULL){
            cout <<"("<<current->key<<","<<current->value<<") ";
            current = current->next;
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){

    HashChainNode hash(2);
    hash.Insert(Node(12,"post rock"));
    hash.Insert(Node(592,"shoegaze"));
    cout << "After inserting key(12),key(592):\n";
    hash.DisplayTable();

    hash.Insert(Node(6594,"blues"));        // evoke TableDoubling()
    cout << "After inserting key(6594), evoke TableDoubling():\n";
    hash.DisplayTable();

    hash.Insert(Node(7,"folk"));
    cout << "After inserting key(7):\n";
    hash.DisplayTable();
    hash.Insert(Node(123596,"hiphop"));     // evoke TableDoubling()
    cout << "After inserting key(123596), evoke TableDoubling():\n";
    hash.DisplayTable();

    hash.Insert(Node(93,"soul"));
    hash.Insert(Node(2288,"indie"));
    hash.Insert(Node(793,"jazz"));
    cout << "After inserting key(93),key(2288),key(793):\n";
    hash.DisplayTable();

    hash.Insert(Node(8491,"electro"));      // evoke TableDoubling()
    cout << "After inserting key(8491), evoke TableDoubling():\n";
    hash.DisplayTable();

    hash.Insert(Node(323359,"pop"));
    cout << "After inserting key(323359):\n";
    hash.DisplayTable();

    cout << "Searching: genre(8491) is " << hash.Search(8491) << ".\n\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(7);
    cout << "After deleting key(7):\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(592);
    cout << "After deleting key(592):\n";
    hash.DisplayTable();

    cout << "Want to  delete key(592) again:\n";
    hash.Delete(592);

    hash.Delete(123596);
    hash.Delete(323359);
    hash.Delete(793);
    hash.Delete(93);
    cout << "After deleting key(123596),key(323359),key(793),key(93):\n";
    hash.DisplayTable();

    hash.Delete(6594);      // evoke TableShrinking()
    cout << "After deleting key(6594), evoke TableShrinking():\n";
    hash.DisplayTable();


    return 0;
}

