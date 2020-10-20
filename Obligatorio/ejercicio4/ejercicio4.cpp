#include<iostream>
using namespace std;

struct Nodo{
    int valor;
    int nivel;
};

struct NodoAdy{
    int dato;
    NodoAdy* sig;
};

Nodo** heap;
int tope = 0;

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
        if(heap[pos]->nivel < heap[padre]->nivel){
            swapNodos(pos, padre);
            flotar(padre);
        }
        else if (heap[pos]->nivel == heap[padre]->nivel){
            if(heap[pos]->valor < heap[padre]->valor){
                swapNodos(pos, padre);
                flotar(padre);
            }
        }
    }
}

bool esHoja(int pos){
    return posHijoIzq(pos) > tope;
}

int posMinimo(int izq, int der){
    if(heap[izq]->nivel > heap[der]->nivel){
        return der;
    }
    else if(heap[izq]->nivel < heap[der]->nivel){
        return izq;
    }
    else if(heap[izq]->nivel == heap[der]->nivel){
        if (heap[izq]->valor > heap[der]->valor){
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
        if(heap[min]->nivel < heap[pos]->nivel){
            swapNodos(min, pos);
            hundir(min);
        }
        else if(heap[min]->nivel == heap[pos]->nivel){
            if (heap[min]->valor < heap[pos]->valor){
                swapNodos(min, pos);
                hundir(min);
            }
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
    int cantVertices;
    int cantAristas;
    cin>>cantVertices;
    cin>>cantAristas;


    NodoAdy** listaAdy = new NodoAdy*[cantVertices+1];
    int* vecIncidentes = new int[cantVertices+1];
    heap = new Nodo*[cantVertices+1];

    for(int i = 0; i<cantVertices+1; i++){
        listaAdy[i] = NULL;
    }

    for(int i = 0; i < cantVertices + 1; i++){
        vecIncidentes[i] = 0;
        heap[i] = NULL;
    }


    
    for(int i = 0; i < cantAristas; i++){
        int vertice1;
        int vertice2;
        cin >> vertice1 >> vertice2;

        NodoAdy* nuevo = new NodoAdy;
        nuevo->dato = vertice2;
        nuevo->sig = listaAdy[vertice1];
        listaAdy[vertice1] = nuevo;
        vecIncidentes[vertice2]++;

    }

    //AGREGO EN EL HEAP TODOS LOS VERTICES DE INCIDENCIA CERO
    for(int i = 1; i <= cantVertices; i++){
        if(vecIncidentes[i] == 0){
            Nodo* nuevo = new Nodo;
            nuevo->nivel = 0;
            nuevo->valor = i;
            insertar(nuevo);
        }
    }
    while(tope!=0){
        Nodo* minimoHeap = minimo();
        desencolar();
        cout << minimoHeap->valor << endl;
        NodoAdy* ady = listaAdy[minimoHeap->valor];
        while(ady!=NULL){
            vecIncidentes[ady->dato]--;
            if(vecIncidentes[ady->dato]==0){
                Nodo* inserto = new Nodo;
                inserto->nivel = minimoHeap->nivel + 1;
                inserto->valor = ady->dato;
                insertar(inserto);
            }
            ady = ady->sig;
        }
    }
    
    return 0;
}