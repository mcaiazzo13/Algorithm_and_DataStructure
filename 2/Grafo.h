
#ifndef Grafo_h
#define Grafo_h
#include <iostream>
#include <iterator> // dijkstra
#include <vector>
#include <queue> // dijkstra
#include "Nodo.h"
class Grafo{
private:
	vector<Nodo *> galassia;
	int vertici;
	int wormhole;
public:
	Grafo(int vertici,int wormhole);
	void insertNodo(Nodo *nodo);
	Nodo* getNodo(int n);
	void viaggia(Nodo* start,Nodo* end,vector<int> &wormholeTrovati,vector<int>& distanza); // dijkstra
	void viaggiaWormhole(Nodo* start,Nodo*end);
	void recuperaPercorso(Nodo* end, int wormhole,vector<int>& path,bool verify);
	~Grafo(){;}
};
// ------------------------------------ IMPLEMENTAZIONE
// costruttore
Grafo::Grafo(int vertici,int wormhole){
	this->vertici = vertici;
	this->wormhole = wormhole;
}
// aggiunge nodo
void Grafo::insertNodo(Nodo *nodo){
	this->galassia.push_back(nodo);
}
// get nodo
Nodo* Grafo::getNodo(int n){
	return this->galassia.at(n);
}

// viaggia (dijkstra)
void Grafo::viaggia(Nodo *start,Nodo *end,vector<int> &wormholeTrovati,vector<int>& dist){
	// valore Nodo | chiave distanza
	priority_queue<pair <Nodo *,int> > coda;
	int i;
	for(i=0;i<this->vertici+1;i++){
		dist.push_back(99);
		getNodo(i)->setP(nullptr);
	}
	coda.push(make_pair(start,0));
	dist.at(start->getInfo()) = 0;
	
	Nodo *u;
	Nodo *v;
	int w = 0;
	while(!coda.empty()){
		u = coda.top().first; // prendo il nodo in testa
		coda.pop(); // estraggo il nodo
		// ora devo scorrere tutta la lista di ADJ di u
		list<pair<Nodo *,int> >::iterator itr;
		for(itr = u->getAdjBegin();itr != u->getAdjEnd();itr++){
			v = (*itr).first; // nodo v
			w = (*itr).second; // peso dell'arco di v
			
			// se trovo un wormhole inseriscilo in un vettore
			if(v->getInfo() >= this->vertici-this->wormhole+1 && v->getInfo() < this->vertici+1){
				if(wormholeTrovati.size() == 0){
					wormholeTrovati.push_back(v->getInfo());
				}else{
					vector<int>::iterator it;
					it = find(wormholeTrovati.begin(),wormholeTrovati.end(),v->getInfo());
					// se non è uguale allora non l'ho trovato e quindi lo inserisco
					if(*it != v->getInfo()){
						wormholeTrovati.push_back(v->getInfo());
					}
				}
			}
			// relax
			if(dist.at(v->getInfo()) > dist.at(u->getInfo())+w){
				dist.at(v->getInfo()) = dist.at(u->getInfo())+w;
				v->setP(u);
				coda.push(make_pair(v,dist.at(v->getInfo())));
			}
		}
	}
}

// recupera percorso start -> wormhole più vicino | end -> wormhole più vicino
void Grafo::recuperaPercorso(Nodo* end, int wormhole,vector<int>& path,bool verify){
	Nodo* ptr = getNodo(wormhole); // primo wormhole trovato
	if(verify == true){
		while(ptr != end){ //  fino al wormhole
			path.push_back(ptr->getInfo());
			ptr = ptr->getP();
		}
		path.push_back(end->getInfo());
	}else{
		while(ptr != nullptr){
			path.push_back(ptr->getInfo());
			ptr = ptr->getP();
		}
		reverse(path.begin(),path.end());
	}
}


// viaggi wormhole
void Grafo::viaggiaWormhole(Nodo* start, Nodo* end){
	
	vector<int> wormholeTrovati;
	vector<int> dist;
	// step 1
	viaggia(start,end,wormholeTrovati,dist);
	
	// stampa percorso senza wormhole
	int costoP = dist.at(2);
	cout << "Percorso NO wormhole costo : " << costoP<<endl;
	Nodo* ptr;
	ptr = end;
	vector<int> temp;
	while(ptr != nullptr){
		temp.push_back(ptr->getInfo());
		ptr = ptr->getP();
	}
	reverse(temp.begin(),temp.end());
	for(int i=0;i<temp.size();i++)
		cout << temp.at(i) << " ";
	cout << endl;
	temp.clear();
	
	// step 2
	int wormhole1 = 0,costoP1 = 0;
	vector<int> percorsoW1;
	if(wormholeTrovati.size() != 0){
		wormhole1 = wormholeTrovati.front(); // primo wormhole trovato
		recuperaPercorso(start,wormhole1,percorsoW1,false); // recupera percorso da start -> wormhole1
		costoP1 = dist.at(wormhole1);
	
		wormholeTrovati.clear();
		dist.clear();
	
		// step 3
		viaggia(end,start,wormholeTrovati,dist);

		// step 4
		int wormhole2 = 0;
		if(wormholeTrovati.size() != 0){
			// HO MODIFICATO QUESTA STRINGA. ERRORE DI DISTRAZIONE. IL PRIMO WORMHOLE TROVATO SI TROVA IN FRONT NON IN BACK.
			// wormhole2 = wormholeTrovati.back();  --> SBAGLIATO !! ESEGUO UN PUSH_BACK() QUINDI DEVO ESTRARRE L'ELEMENTO FRONT

			wormhole2 = wormholeTrovati.front(); // primo wormhole trovato
		}
	
		// step 5
		vector<int> percorsoW2;
		int costoP2 = 0;
		if(wormhole1 != wormhole2 && wormhole2 != 0){ // posso usare questo wormhole e calcolare il percorso
			// devo usare il percorso S -> w1 ^ w2 -> D
			
			recuperaPercorso(end, wormhole2, percorsoW2,true);
			costoP2 = dist.at(wormhole2);

			cout << "Percorso CON wormhole costo : " << costoP2+costoP1+1 <<endl;
			for(int i=0;i<percorsoW1.size();i++){
				cout << percorsoW1.at(i) << " ";
			}
			cout << " ^ ";
			for(int i=0;i<percorsoW2.size();i++){
				cout << percorsoW2.at(i)<< " ";
			}
			cout << endl;
			
			// confronto tra i percorsi possibili
			if(costoP1+costoP2+1 >= costoP)
				cout << "Intraprendere il viaggio SENZA wormhole." << endl;
			else
				cout << "IPERSPAZIO. Intraprendere il viaggio CON WORMHOLE" << endl;
	
		}else
			cout << "Non c'è un percorso veloce con Wormhole.\nMotivo : i wormhole trovati da S->w1 e D->w2 sono uguali \noppure dalla DESTINAZIONE non è raggiungibile un wormhole." << endl;
		}else
			cout << "Non è possibile raggiungere un wormhole da START." << endl;
}
#endif /* Grafo_h */
