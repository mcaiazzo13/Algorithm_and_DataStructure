#ifndef Hash_h
#define Hash_h
#include <iostream>
#include <string>
#include <iterator>
#include <list>
#include "RedBlack.h"
using namespace std;

// class Nodo Hash Table
class Hash{
private:
	int key;
	list<string> myList; // concatenamento
public:
	Hash(int key,string data);
	int getKey();
	void insertList(string data);
	string searchList(string data);
	void deleteList(string data);
	int sizeList();
	void stampaList();
	~Hash(){;}
};
// --------------------------------------------------------------------------- IMPLEMENTATION
// --------------------------------------------------------------------------- PUBLIC

 //---------------------------------------- costruttore
Hash::Hash(int key,string data){
	this->key = key;
	insertList(data);
  }
// ---------------------------------------- get key
int Hash::getKey(){
    return this->key;
  }
  //---------------------------------------- insert list
void Hash::insertList(string data){
	this->myList.push_back(data);
  }
  //---------------------------------------- search list
string Hash::searchList(string data){
	list<string>::iterator i;
	for(i=myList.begin();i!=myList.end();i++){
		if(*i == data){
			return "Presente";
		}
	}
	return "Non Presente";
  }
  //---------------------------------------- delete list
void Hash::deleteList(string data){
	this->myList.remove(data);
  }
  //---------------------------------------- stampa list
void Hash::stampaList(){
    list<string>::iterator it;
    for(it = this->myList.begin();it != this->myList.end();it++){
      cout << "Tupla : " << *it << endl;
    }
}
	//---------------------------------------- size list
int Hash::sizeList(){
	return (int)myList.size();
}

#endif /* Hash_h */
