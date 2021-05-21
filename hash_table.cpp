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
