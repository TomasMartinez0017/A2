#include <iostream>
using namespace std;
#include <string>

struct Nodo{
    string valor;
    Nodo* sig;
};


unsigned int funcHash(string& key){
    unsigned int hashVal = 0;
    for(int i = 0; i < key.length(); i++){
        hashVal = 37 * hashVal + key[i];
    }
    return hashVal;
}

void insertar(string elemento, Nodo**& hash, int largo){
    int pos = funcHash(elemento)%largo;
    Nodo* nuevo = new Nodo;
    nuevo->valor = elemento;
    nuevo->sig = NULL;
    Nodo* principio = hash[pos];
    if(principio==NULL){
        hash[pos] = nuevo;
    }
    else{
        hash[pos] = nuevo;
        nuevo->sig = principio;
    }
}

int existe(string elemento, Nodo**& hash, int largo){
    int pos = funcHash(elemento)%largo;
    Nodo* principio = hash[pos];
    while(principio!=NULL){
        if(principio->valor == elemento){
            return 1;
        }
        else{
            principio = principio->sig;
        }
    }
    return 0;
}

int main(){

    int n;
    cin>>n;
    int largo = n*2;
    Nodo** tablaHash = new Nodo*[largo];
    for(int i = 0; i < largo; tablaHash[i++] = NULL);

    for(int i = 0; i < n; i++){
        string palabra;
        cin>>palabra;
        insertar(palabra, tablaHash, largo);
    }

    int m;
    cin>>m;
    for(int i = 0; i < m; i++){
        string palabraTest;
        cin>>palabraTest;
        cout<<existe(palabraTest, tablaHash, largo)<<endl;
    }
    return 0;
}