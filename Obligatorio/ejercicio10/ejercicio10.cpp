#include <iostream>
using namespace std;


char* edificio;

/*
VERSION 1 (Re ineficiente)
void construccion(int K, int largo){
    bool* atendidos = new bool[largo];
    for(int i = 0; i < largo; atendidos[i++] = false);
    int indice = 0;
    for(int i = 0; i < largo; i++){
        if(edificio[i] == 'O'){
            if(i-K < 0){
                indice = 0;
            }    
            else{
                indice = i-K;
            }
            bool encontre = false;
            while(indice <= i+K && !encontre && indice < largo){
                if(edificio[indice] == 'C' && atendidos[indice] == false){
                    atendidos[indice] = true;
                    encontre = true;
                }
                indice++;    
            }
        }   
    }
    int cont = 0;
    for(int i = 0; i < largo; i++){
        if(atendidos[i] == true){
            cont ++;
        }
    }
    cout<<cont<<endl;
}
*/

int* operadores;
int* cuadrillas;
int largoOp;
int largoCuad;

void initVectores(int largo){
    int ops = 0;
    int cuads = 0;
    for(int i = 0; i < largo; i++){
        edificio[i] == 'C' ? cuads++ : ops++;
    }
    largoOp = ops;
    largoCuad = cuads;
    operadores = new int[largoOp];
    cuadrillas = new int[largoCuad];

    int indexOps = 0;
    int indexCuads = 0;

    for(int i = 0; i < largo; i++){
        edificio[i] == 'C' ? cuadrillas[indexCuads++] = i : operadores[indexOps++] = i;
    }
}

void construccion(int K, int largo){
    int atendidos = 0;
    int ops = 0;
    int cuads = 0;

    while(cuads<largoCuad && ops<largoOp){
        int distanciaActual = abs(operadores[ops] - cuadrillas[cuads]);
        if(distanciaActual <= K){
            atendidos++;
            ops++;
            cuads++;
        }
        else if(cuadrillas[cuads] < operadores[ops]){
            cuads++;
        }
        else{
            ops++;
        }
    }
    cout<<atendidos<<endl;
}

int main(){
    int P;
    cin>>P;
    for(int i = 0; i<P; i++){
        int K;
        cin>>K;
        int largo;
        cin>>largo;
        edificio = new char[largo];
        for(int j = 0; j < largo; j++){
            char dato;
            cin>>dato;
            edificio[j] = dato;
        }
        initVectores(largo);
        construccion(K, largo);
        delete[] edificio;

    }
}