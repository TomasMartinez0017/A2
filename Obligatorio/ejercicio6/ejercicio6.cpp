#include <iostream>
using namespace std;
#define INF 99999

struct Nodo{
    int valor;
    int costo;
    Nodo* sig;
};

int tope;
Nodo** heap;
Nodo** listaAdy;

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
        if(heap[pos]->costo < heap[padre]->costo){
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
        if(heap[izq]->costo > heap[der]->costo){
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
        if(heap[min]->costo < heap[pos]->costo){
            swapNodos(min, pos);
            hundir(min);
        }
    }
}

void insertar(int vertice, int costo){
    Nodo* nuevo = new Nodo;
    nuevo->valor = vertice;
    nuevo->costo = costo;

    tope++;
    heap[tope] = nuevo;
    flotar(tope);
    
}

void desencolar(){
    heap[1] = heap[tope];
    tope--;
    hundir(1);
}

Nodo* minimo(){
    return heap[1];
}

bool* initVisitados(int cantV, int nodoOrigen){
    bool* retorno = new bool[cantV + 1];
    for(int i = 0; i < cantV+1; i++){
        retorno[i] = false;
    }
    retorno[nodoOrigen] = true;
    return retorno;
}

int* initCostos(int cantV, int nodoOrigen){
    int* retorno = new int[cantV + 1];
    for(int i = 0; i < cantV+1; i++){
        retorno[i] = INF;
    }
    retorno[nodoOrigen] = 0;
    return retorno;
}

int sumaDeCostos(int* costos, int cantV){
    int suma = 0;
    for(int i = 1; i < cantV+1; i++){
        if(costos[i] == INF){
            return -1;
        }
        suma+=costos[i];
    }
    return suma;
}

int prim(Nodo** listaAdy, int origen, int cantVertices){
    bool* visitados = initVisitados(cantVertices, origen);
    int* costos = initCostos(cantVertices, origen);
    insertar(origen, 0);
    while(tope>0){
        Nodo* min = minimo();
        desencolar();
        visitados[min->valor] = true;
        Nodo* adyacentes = listaAdy[min->valor];
        while(adyacentes != NULL){
            if(!visitados[adyacentes->valor]){
                if(costos[adyacentes->valor] > adyacentes->costo){
                    costos[adyacentes->valor] = adyacentes->costo;
                    insertar(adyacentes->valor, adyacentes->costo);
                }
            }
            adyacentes=adyacentes->sig;
        }
    }
    return sumaDeCostos(costos, cantVertices);
}

int main(){
    tope = 0;
    
    int cantVertices;
    int cantAristas;

    cin>>cantVertices;
    cin>>cantAristas;

    heap = new Nodo*[cantVertices+1];
    for(int i = 0; i < cantVertices+1; heap[i++]=NULL);

    listaAdy = new Nodo*[cantVertices + 1];
    for(int i = 0; i< cantVertices + 1; i++){
        listaAdy[i] = NULL;
    }

    for(int i = 0; i < cantAristas; i++){
        int origen;
        int destino;
        int costo;
        cin>>origen>>destino>>costo;

        Nodo* inserto1 = new Nodo;
        inserto1->valor = destino;
        inserto1->costo = costo;
        inserto1->sig = listaAdy[origen];
        listaAdy[origen] = inserto1;

        Nodo* inserto2 = new Nodo;
        inserto2->valor = origen;
        inserto2->costo = costo;
        inserto2->sig = listaAdy[destino];
        listaAdy[destino] = inserto2;

    }

    int suma = prim(listaAdy, 1, cantVertices);
    cout<<suma;

    return 0;
}
