#include <iostream>
using namespace std;
#define INF 99999

int** grafo;

bool* initVisitados(int cantV) {
    bool* ret = new bool[cantV+1];
    for(int i=1; i<=cantV; i++){
        ret[i] = false;
    }
    return ret;
}

int* initCostos(int origen, int cantV){
    int* ret = new int[cantV+1];
    for(int i=1; i<=cantV; i++){
        ret[i] = i == origen ? 0 : INF;
    }
    return ret;
}

int* initVengo(int cantV){
    int* ret = new int[cantV+1];
    for(int i=1; i<=cantV; i++){
        ret[i] = -1;
    }
    return ret;
}

int verticesDesconocidoDeMenorCosto(bool* vistados, int* costos, int cantV) {
    int menorVerticeNoConocido = -1;
    int menorCosto = INF;
    for(int i=1; i<=cantV; i++) {
        if(!vistados[i] && costos[i] < menorCosto) {
            menorVerticeNoConocido = i;
            menorCosto = costos[i];
        }
    }
    return menorVerticeNoConocido;
}

void imprimirCosto(int* costos, int cantVertices){
    for(int i = 1; i <= cantVertices; i++){
        if(costos[i] == 0 || costos[i] == INF){
            cout<<-1<<endl;
        }
        else{
        cout<<costos[i]<<endl;
        }
    }
}       
    
void dijkstra(int origen, int cantVertices) {
    bool* visitados = initVisitados(cantVertices);
    int* costos = initCostos(origen, cantVertices);
    int* vengo = initVengo(cantVertices);

    for(int i=1; i<=cantVertices; i++) {
        int v = verticesDesconocidoDeMenorCosto(visitados, costos, cantVertices);
        if(v != -1) {
            visitados[v] = true;
            for(int w=1; w<=cantVertices; w++) {
                if(grafo[v][w] != INF) {
                    if(costos[w] > costos[v] + grafo[v][w]) {
                        costos[w] = costos[v] + grafo[v][w];
                        vengo[w] = v;
                    }
                }
            }
        }
    }
    imprimirCosto(costos, cantVertices);
}

int main(){

    int cantVertices;
    cin>>cantVertices;

    int cantAristas;
    cin>>cantAristas;


    grafo = new int*[cantVertices + 1];
    for(int i = 0; i < cantVertices + 1; i++){
        grafo[i] = new int[cantVertices + 1];
    }

    for(int i = 0; i < cantVertices + 1; i++){
        for(int j = 0; j < cantVertices + 1; j++){
            grafo[i][j] = INF;
        }
    }

    for(int i = 0; i < cantAristas; i++){
        int vertice1;
        int vertice2;
        int costo;
        cin >> vertice1 >> vertice2 >> costo;
        grafo[vertice1][vertice2] = costo;   
    }

    int verticesConsulta;
    cin>>verticesConsulta;

    for(int i = 1; i < cantVertices + 1; i++){
        dijkstra(i, cantVertices);
    }

    return 0;
}