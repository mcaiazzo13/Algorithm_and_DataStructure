
#ifndef Nodo_h
#define Nodo_h
#include <iostream>
#include <list>
using namespace std;

class Nodo{
private:
	list<pair <Nodo *,int> > *adj;
	int info;
	Nodo* p;
public:
	Nodo(int info);
	int getInfo();
	void setP(Nodo* p);
	Nodo* getP();
	void insertLink(Nodo *nodo, int peso);
	void deleteLink(Nodo *nodo);
	void insertWormholeLink(Nodo *nodo);
	list<pair<Nodo*, int> >::iterator getAdjBegin();
	list<pair<Nodo*, int> >::iterator getAdjEnd();
	~Nodo() {delete this->adj;}
};
// -------------------------------------- IMPLEMENTAZIONE
// costruttore
Nodo::Nodo(int info){
	this->info = info;
	this->p = nullptr;
	adj = new list<pair <Nodo *,int> >;
}
// get Info
int Nodo::getInfo(){
	return this->info;
}
// set P
void Nodo::setP(Nodo *p){
	this->p = p;
}
// get P
Nodo* Nodo::getP(){
	return this->p;
}
// get nodo adj begin
list<pair<Nodo *,int> >::iterator Nodo::getAdjBegin(){
	list<pair <Nodo *,int> >::iterator itr;
	itr = this->adj->begin();
	return itr;
}
// get nodo adj end
list<pair<Nodo *,int> >::iterator Nodo::getAdjEnd(){
	list<pair <Nodo *,int> >::iterator itr;
	itr = this->adj->end();
	return itr;
}
// inserimento link
void Nodo::insertLink(Nodo *nodo,int peso){
	this->adj->push_back(make_pair(nodo,peso));
}
// elimina link (utile solo per eliminare l'arco wormhole)
void Nodo::deleteLink(Nodo *nodo){
	list<pair<Nodo *,int> >::iterator itr;
	for(itr = adj->begin();itr != adj->end();itr++)
		if((*itr).first->getInfo() == nodo->getInfo()+1 && (*itr).second == 1)
			this->adj->erase(itr);
}
// insert wormhole link
void Nodo::insertWormholeLink(Nodo *nodo){
	insertLink(nodo,1);
}
#endif /* Nodo_h */
