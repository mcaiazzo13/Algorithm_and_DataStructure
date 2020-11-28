#ifndef Nodo_h
#define Nodo_h
#include <iostream>
#include <string>
#include "HashTable.h"
using namespace std;
typedef enum color{black,red} Color;

// class Nodo Red Black
class Nodo{
private:
	int Key;
	Color color;
	Nodo* Dx;
	Nodo* Sx;
	Nodo* Px;
	HashTable table; // ogni nodo RedBlack ha un Hash Table associata
public:
	Nodo(int Key,Color color,Nodo *Sx,Nodo *Dx,Nodo *Px);
	void setKey(int k);
	void setColor(Color c);
	void setPx(Nodo* Px);
	void setSx(Nodo* Sx);
	void setDx(Nodo* Dx);
	int getKey();
	int getColor();
	Nodo* getSx();
	Nodo* getDx();
	Nodo* getPx();
	bool matchColor(Color c);
	void insertHashTable(int key,string data);
	void deleteHashTable(int key,string data);
	void searchHashTable(int key,string data);
	void stampaHashTable();
	~Nodo(){;}
};
//--------------------------------------------------------------------------- IMPLEMENTATION

//---------------------------------------- costruttore
Nodo::Nodo(int Key,Color color,Nodo *Sx,Nodo *Dx,Nodo *Px){
	this->Key = Key;
	this->color = color;
	this->Sx = Sx;
	this->Dx = Dx;
	this->Px = Px;
  }
  //----------------------------------------set chiave
void Nodo::setKey(int k){
    Key = k;
  }
  //---------------------------------------- set color
void Nodo::setColor(Color c){
    color = c;
  }
  //---------------------------------------- set Padre
void Nodo::setPx(Nodo* Px){
    this->Px = Px;
  }
  //----------------------------------------set Sx
  void Nodo::setSx(Nodo* Sx){
    this->Sx = Sx;
  }
  //---------------------------------------- set Dx
void Nodo::setDx(Nodo* Dx){
    this->Dx = Dx;
  }
  //---------------------------------------- ritorna key
int Nodo::getKey(){
    return Key;
  }
  //---------------------------------------- ritorna colore
int Nodo::getColor(){
    return this->color;
  }
  //---------------------------------------- ritorna Dx
  Nodo* Nodo::getDx(){
    return this->Dx;
  }
  //---------------------------------------- ritorna Sx
Nodo* Nodo::getSx(){
    return this->Sx;
  }
  //---------------------------------------- ritorna padre
Nodo* Nodo::getPx(){
    return this->Px;
  }
  //---------------------------------------- controlla se i colori sono uguali
bool Nodo::matchColor(Color c){
    bool result;
    (this->color == c) ? result = true : result = false;
    return result;
  }
  //---------------------------------------- inserisce dell'hash table
void Nodo::insertHashTable(int key,string data){
    table.insertHash(key,data);
  }
  //---------------------------------------- elimina nell'hash table
void Nodo::deleteHashTable(int key,string data){
    table.deleteHash(key,data);
  }
  //---------------------------------------- cerca nell'hash table
void Nodo::searchHashTable(int key, string data){
    table.searchHash(key,data);
  }
  //---------------------------------------- stampa hash table
void Nodo::stampaHashTable(){
    table.stampa();
  }
  #endif /* Nodo_h */
