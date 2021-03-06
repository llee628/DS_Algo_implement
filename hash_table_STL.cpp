#include<iostream>
#include<vector>
#include<list>
#include<string>

using std::vector;
using std::list;
using std::string;
using std::cout;
using std::endl;

struct dict{
    string key; //key for name
    string value; // value for team
    dict():key(""), value(""){};
    dict(string Key, string Value):key(Key), value(Value){};
};

class HashChain{

private:
    int size;   //size of table
    int count;  //count of data

    vector<list<dict> > table;

    int PreHashing(string key_str);    //turn string_type_key to int_type_key
    int HashFunction(string key_str);    //using Division method

public:
    HashChain(){};
    HashChain(int m):size(m), count(0){
        table.resize(size);
    }

    void Insert(dict data);
    void Delete(string key);
    string Search(string key);
    void DisplayTable();


};

int HashChain::PreHashing(string key_str){
    int base = 9;    //choose randomly
    int key_int = 0;
    int p = 1;

    for (int i = (int)key_str.size()-1; i>=0; i-=1){
        key_int += key_str[i]*p;
        p *= base;

    }

    return key_int;
}

int HashChain::HashFunction(string key_str){
    int key_int = PreHashing(key_str);
    int hashcode = key_int % this->size;

    return hashcode;
}

void HashChain::Insert(dict data){
    /*
     * 1. get index from hashfunction
     * 2. insert data at the front of linked list
    **/

   int index = HashFunction(data.key);
   table[index].push_front(data);
}

string HashChain::Search(string key){
    /*
     * 1. get index from hashfunction
     * 2. traversal in linked list
    **/

   int index = HashFunction(key);
   for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); itr++){
       if ((*itr).key == key){
           return (*itr).value;
       }
   }

   return "...\nno such data";

}

void HashChain::Delete(string key){
    /*
     * 1. get index from hashfunction
     * 2. traversal in linked list
    **/

   int index = HashFunction(key);
   for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); itr++){
       if ((*itr).key == key){
           table[index].erase(itr);
       }
   }
}

void HashChain::DisplayTable(){

    for (int i = 0; i < table.size(); i+=1){
        cout<<"slot#"<<i<<": ";
        for(list<dict>::iterator itr = table[i].begin(); itr != table[i].end(); itr++){
            cout<<"("<<(*itr).key<<","<<(*itr).value<<") ";
        }
        cout<<endl;
    }
    cout<<endl;

}

int main(){
    HashChain hash(5);
    hash.Insert(dict("T-Mac","Magic"));
    hash.Insert(dict("Bryant","Lakers"));
    hash.Insert(dict("Webber","Kings"));
    hash.Insert(dict("Arenas", "Wizards"));
    hash.Insert(dict("Davis","Clippers"));
    hash.Insert(dict("Kidd","Nets"));
    hash.DisplayTable();

    cout << "T-Mac is in " << hash.Search("T-Mac") << ". " << endl;
    cout << "Arenas is in " << hash.Search("Arenas") << ". " << endl;

    hash.Delete("Kidd");
    hash.Delete("T-Mac");
    cout << "\nAfter deleing Kidd and T-Mac:\n";
    hash.DisplayTable();

    cout<< hash.Search("Kidd")<<endl;

    return 0;
}
