#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

int main(int argc,char* argv[]){
	
      if(argc < 2){
         cout << "Inserire file input.txt" <<endl;
         exit(1);
      }

	   ifstream File_I(argv[1]);
   	int vertex,link,wormhole;
	
   	File_I >> vertex;
   	File_I >> link;
   	File_I >> wormhole;
  	 
   	cout << "vertex :" << vertex << " link :" << link << " wormhole :" << wormhole <<endl;

   	if(vertex < 2 || vertex > 1000){
   	   cout << "You have too many VERTEX or too few :  " << vertex <<endl;
   	   exit(1);
   	}
   	else if(link < 1 || link > 10000){
   	   cout << "You have too many LINK or too few : " << link <<endl;
   	   exit(1);
   	}
   	else if(wormhole < 2 || wormhole > vertex){
   	   cout << "You have too many WORMHOLE or too few : " << wormhole <<endl;
   	   exit(1);
   	}

   	Grafo Galaxy(vertex,wormhole);
   	// second line : system 1 , system 2 , weight
   	int node1,node2,weight,i;
	// inserimento di tutti i nodi nella galassia
	for(i=0;i<=vertex;i++){
		Galaxy.insertNodo(new Nodo(i));
	}
	// inserimento di tutti i link e i pesi
   	for(i=0;i<=link;i++){
		File_I >> node1;
		File_I >> node2;
		File_I >> weight;
		Galaxy.getNodo(node1)->insertLink(Galaxy.getNodo(node2), weight);
		Galaxy.getNodo(node2)->insertLink(Galaxy.getNodo(node1), weight);
   	}
	
	// viaggio intergalattico
	Galaxy.viaggiaWormhole(Galaxy.getNodo(1),Galaxy.getNodo(2));
	
	return 0;
};


