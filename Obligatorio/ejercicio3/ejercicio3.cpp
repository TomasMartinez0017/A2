#include <iostream>
using namespace std;
#include <string>

struct Nodo{
    int valor;
    Nodo* sig;
};

int tope;
Nodo** heap;

int posPadre(int pos){
    return pos/2;
}

int posHijoIzq(int pos){
    return pos*2;
}

int posHijoDer(int pos){
    return pos*2 + 1;
}

void swapNodos(int pos1, int pos2){
    Nodo* aux = heap[pos1];
    heap[pos1] = heap[pos2];
    heap[pos2] = aux;
}

void flotar(int pos){
    int padre = posPadre(pos);
    if(pos>1 && pos <= tope){
        if(heap[pos]->valor < heap[padre]->valor){
            swapNodos(pos, padre);
            flotar(padre);
        }
    }
}

bool esHoja(int pos){
    return posHijoIzq(pos) > tope;
}

int posMinimo(int izq, int der){
    if(der > tope){
        return izq;
    }
    else{
        if(heap[izq]->valor > heap[der]->valor){
            return der;
        }
        else{
            return izq;
        }
    }
}

void hundir(int pos){
    if(!esHoja(pos)){
        int hijoDer = posHijoDer(pos);
        int hijoIzq = posHijoIzq(pos);
        int min = posMinimo(hijoIzq, hijoDer);
        if(heap[min]->valor < heap[pos]->valor){
            swapNodos(min, pos);
            hundir(min);
        }
    }
}

void insertar(Nodo* nuevo){
    if(nuevo!=NULL){
        tope++;
        heap[tope] = nuevo;
        flotar(tope);
    }
    
}

void desencolar(){
    heap[1] = heap[tope];
    tope--;
    hundir(1);
}

Nodo* minimo(){
    return heap[1];
}

int main(){

    int k;
    cin>>k;
    tope=0;
    heap = new Nodo*[k+1];
    for(int i = 0; i < k+1; heap[i++]=NULL);

    for(int i = 0; i < k; i++){
        int cantElem;
        cin>>cantElem;
        Nodo* principio;
        Nodo* ultimo;
        for(int j = 0; j < cantElem; j++){
            Nodo* nuevo = new Nodo;
            int dato;
            cin>>dato;
            nuevo->valor = dato;
            if(j==0){
                principio = nuevo;
            }
            else{
                ultimo->sig = nuevo;
            }
            nuevo->sig = NULL;
            ultimo = nuevo;
            
        }
        insertar(principio);
    }

    while(tope!=0){
        Nodo* min = minimo();
        cout<<min->valor<<endl;
        desencolar();
        insertar(min->sig);
    }
    
    return 0;
}