#ifndef RedBlack_h
#define RedBlack_h
#include "Nodo.h"
#include "HashTable.h"
#include <iostream>
#include <string>
using namespace std;

// class Red Black
class RB{
private:
  Nodo* root; // tree radix
  Nodo* nil; //  NIL node
  void rightRotate(Nodo *nodo);
  void leftRotate(Nodo *nodo);
  void insertNode(Nodo *node,int key,string data);
  void fixUp(Nodo *nodo);
  void transplant(Nodo *x,Nodo *y);
  Nodo* searching(Nodo* x,int k1);
  void inOrder(Nodo* nodo);
public:
  RB();
  Nodo* search(int k1);
  void searchRow(int k1,int k2,string data);
  void deleteRow(int k1,int k2,string data);
  void insert(int k1,int k2,string data);
  void visit();
	~RB(){delete this->root; delete this->nil;}
};
//--------------------------------------------------------------------------- IMPLEMENTATION
//--------------------------------------------------------------------------- PUBLIC
// ---------------------------------------- costruttore
RB::RB(){
    this->nil = new Nodo(-1,black,nullptr,nullptr,nullptr);
    root = nil;
    nil->setPx(root);
  }
  //---------------------------------------- search key Tree
  Nodo* RB::search(int k1){
    Nodo *aux = searching(this->root,k1);
    return aux; // red black node
  }
  //---------------------------------------- search row
  void RB::searchRow(int k1,int k2,string data){
    Nodo *aux = searching(this->root,k1);
    aux->searchHashTable(k2,data);
  }
  //---------------------------------------- delete row
  void RB::deleteRow(int k1,int k2,string data){
    Nodo *aux = searching(this->root,k1);
    aux->deleteHashTable(k2,data);
  }
  //---------------------------------------- insert row
  void RB::insert(int key, int key2,string data){
    Nodo *aux = new Nodo(key,red,this->nil,this->nil,this->nil);
    Nodo *verify = search(key);
    if(verify == this->nil){
      this->insertNode(aux,key2,data);
      this->fixUp(aux);
    }
    else{
      verify->insertHashTable(key2,data);
    }
  }
  void RB::visit(){
    this->inOrder(this->root);
  }
  //--------------------------------------------------------------------------- IMPLEMENTATION
  //--------------------------------------------------------------------------- PRIVATE
  
  //---------------------------------------- right rotate
  void RB::rightRotate(Nodo *nodo){
    Nodo *app = nodo->getSx();
    nodo->setSx(app->getDx());
    if(app->getDx() != this->nil)
        app->getDx()->setPx(nodo);
    app->setPx(nodo->getPx());
    if(nodo->getPx() == this->nil)
        this->root = app;
    else if (nodo == nodo->getPx()->getSx())
        nodo->getPx()->setSx(app);
         else
            nodo->getPx()->setDx(app);
    app->setDx(nodo);
    nodo->setPx(app);
  }
  //---------------------------------------- left rotate
   void RB::leftRotate(Nodo *nodo){
    Nodo *app = nodo->getDx();
    nodo->setDx(app->getSx());
    if(app->getSx() != this->nil)
        app->getSx()->setPx(nodo);
    app->setPx(nodo->getPx());
    if(nodo->getPx() == this->nil)
        this->root = app;
    else if (nodo == nodo->getPx()->getSx())
        nodo->getPx()->setSx(app);
         else
            nodo->getPx()->setDx(app);
    app->setSx(nodo);
    nodo->setPx(app);
  }
  //---------------------------------------- allocazione nodo
  void RB::insertNode(Nodo *node,int key,string data){
    Nodo *y = this->nil;
    Nodo *x = this->root;
    while(x != nil){
      y = x;
      if(node->getKey() < x->getKey())
         x = x->getSx();
      else
        x = x->getDx();
    }
    node->setPx(y);
    if(y == this->nil)
      this->root = node;
    else if(node->getKey() < y->getKey())
      y->setSx(node);
    else
      y->setDx(node);
    // insertimento in hash table
    node->insertHashTable(key,data);
  }
  //---------------------------------------- fix up
  void RB::fixUp(Nodo *nodo){
    while( (nodo != this->root) && (nodo->getPx()->matchColor(red))){
        if(nodo->getPx() == nodo->getPx()->getPx()->getSx()){
            Nodo* app = nodo->getPx()->getPx()->getDx();
            if(app->matchColor(red)){
                nodo->getPx()->setColor(black);
                app->setColor(black);
                nodo->getPx()->getPx()->setColor(red);
                nodo = nodo->getPx()->getPx();
            }
            else{
                if(nodo == nodo->getPx()->getDx()){
                    nodo = nodo->getPx();
                    this->leftRotate(nodo);
                }
                nodo->getPx()->setColor(black);
                nodo->getPx()->getPx()->setColor(red);
                this->rightRotate(nodo->getPx()->getPx());
            }
        }
        else{
            Nodo* app = nodo->getPx()->getPx()->getSx();
            if(app->matchColor(red)){
                nodo->getPx()->setColor(black);
                app->setColor(black);
                nodo->getPx()->getPx()->setColor(red);
                nodo = nodo->getPx()->getPx();
            }
            else{
                 if(nodo == nodo->getPx()->getSx()){
                    nodo = nodo->getPx();
                    this->rightRotate(nodo);
                }
                nodo->getPx()->setColor(black);
                nodo->getPx()->getPx()->setColor(red);
                this->leftRotate(nodo->getPx()->getPx());
            }
        }
    }
    this->root->setColor(black);
  }

  //---------------------------------------- transplant
  void RB::transplant(Nodo *x,Nodo *y){
    if(x->getPx() == this->nil)
      this->root = y;
    else if(x == x->getPx()->getSx())
      x->getPx()->setSx(y);
    else
      x->getPx()->setDx(y);
    y->setPx(x->getPx());
  }
  //---------------------------------------- ricerca nodo RB
  Nodo* RB::searching(Nodo* x,int k1){
   while(x != this->nil && x->getKey() != k1){
    if(k1 < x->getKey())
      x = x->getSx();
    else
      x = x->getDx();
   }
   return x;
  }
  //---------------------------------------- visita inorder
  void RB::inOrder(Nodo* nodo){
  if( nodo != this->nil ){
        inOrder(nodo->getSx());
		cout<< "nodo : " << nodo->getKey() << " colore : " << nodo->getColor() << " padre : " << nodo->getPx()->getKey()<<endl;
        nodo->stampaHashTable();
        inOrder(nodo->getDx());
    }
  }
#endif /* RedBlack_h */

/* questo e' per cambiare il colore dell'output ma xcode e' stupido
	  cout << "\033[31m" << "nodo : " << nodo->getKey() << " colore : " << nodo->getColor() << " padre : " << nodo->getPx()->getKey() << "\033[0m"<<endl;*/
