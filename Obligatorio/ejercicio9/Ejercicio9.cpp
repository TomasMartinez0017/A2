#include <iostream>
using namespace std;

struct tripleta{
    int inicio;
    int fin;
    int altura;

    tripleta(){
        inicio = 0;
        fin = 0;
        altura = 0;
    }
};
struct tupla{
    int inicio;
    int altura;
    tupla(){
        inicio = 0;
        altura = 0;
    }
};

struct nodoTupla{
    tupla* par;
    int cantidadElementos;
    int capacidad;
    nodoTupla(int cap){
        capacidad = cap;
        cantidadElementos = 0;
        par = new tupla[cap];
    }
};
tripleta* edificios;

nodoTupla* conversor(int posicion){
    nodoTupla* retorno = new nodoTupla(2);
    retorno->par[0].inicio = edificios[posicion].inicio;
    retorno->par[0].altura = edificios[posicion].altura;
    retorno->par[1].inicio = edificios[posicion].fin;
    retorno->par[1].altura = 0;
    retorno->cantidadElementos = 2;
    return retorno;
}
void agregar(nodoTupla* &nt,tupla t){
    if(nt->par[nt->cantidadElementos - 1].altura != t.altura){
        if(nt->par[nt->cantidadElementos - 1].inicio == t.inicio && nt->par[nt->cantidadElementos-1].altura < t.altura){
            nt->par[nt->cantidadElementos - 1].altura = t.altura;
        }else{
            nt->par[nt->cantidadElementos++] = t;
        }
    }
}

nodoTupla* merge(nodoTupla* izquierda, nodoTupla* derecha){
    nodoTupla* retorno = new nodoTupla(izquierda->cantidadElementos + derecha->cantidadElementos);
    int i = 0;
    int j = 0;
    int h1 = 0;
    int h2 = 0;
    while(i < izquierda->cantidadElementos  && j < derecha->cantidadElementos){
        int minimo = 0;
        if(izquierda->par[i].inicio > derecha->par[j].inicio){
            minimo = derecha->par[j].inicio;
            h2 = derecha->par[j++].altura;
        }else if(izquierda->par[i].inicio < derecha->par[j].inicio){
            minimo = izquierda->par[i].inicio;
            h1 = izquierda->par[i++].altura;
        }else{
            minimo = izquierda->par[i].inicio;
            h2 = derecha->par[j++].altura;
            h1 = izquierda->par[i++].altura;
        }
        tupla par = tupla();
        par.inicio = minimo;
        par.altura = h1 > h2 ? h1 : h2;
        agregar(retorno, par);
    }
    while(i < izquierda->cantidadElementos){
        agregar(retorno,izquierda->par[i++]);
    }
    while(j < derecha->cantidadElementos){
        agregar(retorno,derecha->par[j++]);
    }

    return retorno;
}

nodoTupla* siluetas(int desde, int hasta){
    if(desde == hasta){
        return conversor(desde);
    }

    int mitad = (hasta + desde) / 2;

    nodoTupla* izquierda = siluetas(desde, mitad);
    nodoTupla* derecha = siluetas(mitad+1, hasta);

    return merge(izquierda, derecha);
}


void imprimir(nodoTupla* nt){
    for(int i = 0; i<nt->cantidadElementos;i++){
        cout << nt->par[i].inicio << " " << nt->par[i].altura << endl;
    }
}

int main(){
    int n;
    cin >> n;
    edificios =new tripleta[n];
    for(int i=0; i<n;i++){
        int ini,fi,altu;
        cin >> ini >> fi >> altu;
        tripleta sombra = tripleta();
        sombra.inicio = ini;
        sombra.fin = fi;
        sombra.altura = altu;
        edificios[i] = sombra;
    }

    nodoTupla* sombras = siluetas(0,n-1);
    imprimir(sombras);
    return 0;
}