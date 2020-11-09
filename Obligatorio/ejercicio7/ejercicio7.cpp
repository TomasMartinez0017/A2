#include <iostream>
using namespace std;

int** matriz;
bool** esPositivo;

bool quedanNegativos(int filas, int columnas){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(matriz[i][j] < 0){
                return true;
            }
        }
    }
    return false;
}

bool esPositivoInicial(int posI, int posJ){
    return esPositivo[posI][posJ];
}

void actualizoPositivos(int filas, int columnas){
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if(matriz[i][j] > 0){
                esPositivo[i][j] = true;
            }
        }
        
    }
    
}

int minPases(int filas, int columnas){
    int cantPases = 0;
    while(quedanNegativos(filas, columnas)){
        for (int i = 0; i < filas; i++){
            for (int j = 0; j < columnas; j++){
                if(esPositivoInicial(i,j)){
                    if(i-1 >=0 && matriz[i-1][j] < 0){
                        matriz[i-1][j] = matriz[i-1][j] * -1;
                    }
                    if(i+1 < filas && matriz[i+1][j] < 0){
                        matriz[i+1][j] = matriz[i+1][j] * -1;
                    }
                    if(j-1 >= 0 && matriz[i][j-1] < 0){
                        matriz[i][j-1] =  matriz[i][j-1] * -1;
                    }
                    if(j+1 < columnas && matriz[i][j+1] < 0){
                        matriz[i][j+1] = matriz[i][j+1] * -1;
                    }
                }
            }  
        }
        cantPases++;
        actualizoPositivos(filas, columnas);
         
    }
    return cantPases;    
}

int main(){

    int cantFilas;
    int cantColumnas;
    cin>>cantFilas;
    cin>>cantColumnas;

    matriz = new int*[cantFilas];
    esPositivo = new bool*[cantFilas];
    for(int i = 0; i < cantFilas; i++){
        matriz[i] = new int[cantColumnas];
        esPositivo[i] = new bool[cantColumnas];
        for(int j = 0; j < cantColumnas; j++){
            matriz[i][j] = 0;
            esPositivo[i][j] = false;  
        }
    }

    int dato;
    for(int i = 0; i < cantFilas; i++){
        for(int j = 0; j < cantColumnas; j++){
            cin>>dato;
            matriz[i][j] = dato;
        }    
    }

    actualizoPositivos(cantFilas, cantColumnas);    

    int retorno = minPases(cantFilas, cantColumnas);

    cout<<retorno;

    return 0;

}