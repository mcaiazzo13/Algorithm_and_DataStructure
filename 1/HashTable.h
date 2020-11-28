#ifndef HashTable_h
#define HashTable_h
#include "Hash.h"
#include "RedBlack.h"

// class Hash Table
class HashTable{
private:
	Hash **table;
	uint32_t hashFunction(int k);
	void insert(int key, string data);
	string search(int key,string data);
	void remove(int key,string data);
public:
	HashTable();
	void insertHash(int key, string data);
	void searchHash(int key, string data);
	void deleteHash(int key, string data);
	void stampa();
	~HashTable(){delete this->table;}
};
 //--------------------------------------------------------------------------- IMPLEMENTATION
 //--------------------------------------------------------------------------- PRIVATE
 
//----------------------------------------  hash function
 uint32_t HashTable::hashFunction(int k){
   const uint32_t knuth = 2654435769;
   const uint32_t y = k;
   return (y * knuth) >> (32 - 6);
 }
//---------------------------------------- insert private
 void HashTable::insert(int key, string data){
   int h = hashFunction(key);
   if(table[h] == nullptr){
	   table[h] = new Hash(key,data);
   }else{
	   table[h]->insertList(data); // inserisce il nodo nella lista concatenata
   }
 }
 //---------------------------------------- search private
 string HashTable::search(int key,string data){
	 int i = hashFunction(key);
	 while(table[i] != NULL && table[i]->getKey() != key)
	   i = hashFunction(i+1);
	 if(table[i] == NULL)
	   return "Non Presente";
	 else
	   return table[i]->searchList(data);
 }
 //---------------------------------------- delete private
 void HashTable::remove(int key,string data){
   int i = hashFunction(key);
	 while(table[i] != NULL && table[i]->getKey() != key)
	   i = hashFunction(i+1);
	 if(table[i] == NULL)
	   cout << "NULL"<<endl;
	 else{
		 // se ho solo un elemento posso eliminare direttamente la tupla
		if(table[i]->sizeList() == 1)
			table[i] = NULL;
		// se ci sono piu' elementi
		 else
			table[i]->deleteList(data);
	 }
 }
//--------------------------------------------------------------------------- IMPLEMENTATION
//--------------------------------------------------------------------------- PUBLIC

//---------------------------------------- costruttore
  HashTable::HashTable(){
    table = new Hash *[100];
    for(int i=0;i<100;i++)
      table[i] = nullptr;
  }
  //---------------------------------------- insert public
  void HashTable::insertHash(int key, string data){
    insert(key,data);
  }
  //---------------------------------------- search public
  void HashTable::searchHash(int key,string data){
      string x = search(key,data);
      cout << "Dato : " << x <<endl;
  }
  //----------------------------------------delete public
  void HashTable::deleteHash(int key,string data){
    remove(key,data);
  }
  //---------------------------------------- stampa
  void HashTable::stampa(){
    cout << "\n";
      int i;
      for(i=0;i<50;i++){
        if(this->table[i] != nullptr){
			cout << "key : " << this->table[i]->getKey() << " data : " <<endl;
			this->table[i]->stampaList();
			cout << "\n"<<endl;
        }
      }
    }
#endif /* HashTable_h */
