// main file
#include <iostream>
#include <string>
#include <fstream>
#include "RedBlack.h"
#include "HashTable.h"
using namespace std;

RB mytree;
//----------------------- carica informazioni
void carica(string line){
  string num1;
  string num2;
  string alfa;
  int index[2];
  int j,i;
  i=j=0;
  for(int k=0;k<line.length();k++){
      if(line[k] == ':'){
        index[j] = k;
        j++;
      }
    }
    num1 = line.substr(0,index[0]);
    num2 = line.substr(index[0]+1,index[1]-1);
    alfa = line.substr(index[1]+1,line.length());
	
	// risolve problema 
	string cha = "\r";
	if(alfa[alfa.length()-1] == cha[0]){
		for (unsigned int i = 0; i < cha.length(); ++i){
			alfa.erase (remove(alfa.begin(), alfa.end(), cha[i]), alfa.end());
		 }
	}
	
    int k1 = std::stoi(num1,nullptr,10);
    int k2 = std::stoi(num2,nullptr,10);
    mytree.insert(k1,k2,alfa);
}
//--------------------------------------------------------------------------- MAIN
int main(int argc,char *argv[]){
  string alfa;
  ifstream in("input2.txt");
  string unused;
    while (getline(in, unused)){
      alfa = unused;
      carica(alfa);
    }
    mytree.visit();

    // menu
    int scelta;
    int k1,k2;
    string data;
  do{
    cout << "\n 1.Inserisci Tupla \n 2.Cerca Tupla \n 3.Elimina Tupla \n 4.Stampa RB-HT \n 5.Esci" << endl;
    cin >> scelta;
      switch(scelta){
        case 1:
        cout << "Inserire Chiave RB : "; cin >> k1;
        cout << "Inserire Chiave HT : "; cin >> k2;
        cout << "Inserire tupla : "; cin >> data;
        mytree.insert(k1,k2,data);
          break;
        case 2:
        cout << "Inserire Chiave RB : "; cin >> k1;
        cout << "Inserire Chiave HT : "; cin >> k2;
        cout << "Inserire tupla : "; cin >> data;
        mytree.searchRow(k1,k2,data);
          break;
        case 3:
        cout << "Inserire Chiave RB : "; cin >> k1;
        cout << "Inserire Chiave HT : "; cin >> k2;
        cout << "Inserire tupla : "; cin >> data;
        mytree.deleteRow(k1,k2,data);
          break;
        case 4:
         mytree.visit();
          break;
        case 5:
        cout << "esci" << endl;
          break;
        default:
        cout << "riprova"<<endl;
          break;
      }
    }while(scelta != 5);

  return 0;
}
