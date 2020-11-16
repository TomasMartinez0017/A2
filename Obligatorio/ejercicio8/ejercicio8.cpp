#include <iostream>
using namespace std;
#define INF 99999

struct NodoLista{
    int dato;
    NodoLista* sig;
};

class Cola{
    public:
    NodoLista* cola;
    Cola(){
        cola = NULL;
    }
	void encolar(int elemento){
		NodoLista* nuevo = new NodoLista;
		nuevo->dato = elemento;
		nuevo->sig = NULL;
		if(cola == NULL){
			cola = nuevo;
		}
		else{
			NodoLista* iter = cola;
			while(iter->sig != NULL){
				iter = iter->sig;
			}
			iter->sig = nuevo;
		}
	}
	int desencolar(){
		int retorno = cola->dato;
		NodoLista* borro = cola;
		cola = cola->sig;
		delete borro;
        return retorno;
	}
    bool estaVacia(){
        return cola == NULL;
    }
};

bool** matriz;

int obtenerNoVisitado(bool* visitados, int cantVertices){
    for(int i = 1; i < cantVertices + 1; i++){
        if(!visitados[i]){
            return i;
        }
    }
    return -1;
}


bool esConexo(int v, int cantVertices, int verticeQuitado){
    bool *vis = new bool[cantVertices + 1];
    for (int i = 0; i < cantVertices + 1; vis[i++] = false);
    Cola* cola = new Cola();
    cola->encolar(v);
    vis[v] = true;
    vis[verticeQuitado] = true;
    while(!cola->estaVacia()){
        int vertice = cola->desencolar();
        for(int i = 1; i < cantVertices + 1; i++){
            if(i!=verticeQuitado && !vis[i] && matriz[vertice][i]){
                vis[i] = true;
                cola->encolar(i);
            }
        }

    }
    int verticeNoVisitado = obtenerNoVisitado(vis, cantVertices);
    if (verticeNoVisitado != -1){
        return false;
    }
    else{
        return true;
    }

}

void puntosDeArticulacion(int cantVertices){
    for(int i = 1; i < cantVertices + 1; i++){
        if(i==1){
            if(!esConexo(2, cantVertices, i)){
                cout<<i<<endl;;
            }
        }
        else{
            if(!esConexo(1, cantVertices, i)){
                cout<<i<<endl;;
            }
        }
    }
}

int main(){
    int cantV;
    int cantA;

    cin>>cantV;
    cin>>cantA;

    matriz = new bool*[cantV + 1];
    for(int i = 0; i < cantV + 1; i++){
        matriz[i] = new bool[cantV + 1];
        for(int j = 0; j < cantV + 1; j++){
            matriz[i][j] = false;
        }
    }

    for(int i = 0; i < cantA; i++){
        int v1;
        int v2;
        cin>>v1;
        cin>>v2;
        matriz[v1][v2] = true;
        matriz[v2][v1] = true;
    }

    puntosDeArticulacion(cantV);

    return 0;
}