#include <iostream>
#include <climits>
using namespace std;

bool esPosicionValida(int x, int y, char** matriz, int filas, int columnas){
    return x < filas && x >= 0 && y < columnas && y >= 0 && matriz[x][y] != 'P';
}

bool pase(int x, int y, bool** recorrido){
    return recorrido[x][y] == true;
}

void probarCasilla(int x, int y, bool** recorrido){
    recorrido[x][y] = true;
}

bool llegueDestino(int xCandidato, int yCandidato, int xDestino, int yDestino){
    return xCandidato == xDestino && yCandidato == yDestino;
}

bool pasePorBedelia(int xB, int yB, bool** recorrido){
    return recorrido[xB][yB] == true;
}

void retiroCasilla(int xC, int yC, bool** recorrido){
    recorrido[xC][yC] = false;
}

void facultadBT(int xCandidato, int yCandidato, int xDestino, int yDestino, char** matriz, bool** recorrido, int nroMov, int& mejorNroMov, int xBedelia, int yBedelia, int filas, int columnas){
    if(nroMov < mejorNroMov){ //#PODA
        if(esPosicionValida(xCandidato, yCandidato, matriz, filas, columnas) && !pase(xCandidato, yCandidato, recorrido)) {
            probarCasilla(xCandidato, yCandidato, recorrido);

            if(llegueDestino(xCandidato, yCandidato, xDestino, yDestino) && (nroMov < mejorNroMov)){ //&& pasePorBedelia(xBedelia, yBedelia, recorrido) {

                mejorNroMov = nroMov;
            }
            else{

                int dFilas[4] = {1, 0, -1, 0};
                int dColumnas[4] = {0, 1, 0, -1};

                for(int i = 0; i < 4; i++){
                    
                    facultadBT(xCandidato + dFilas[i], yCandidato + dColumnas[i], xDestino, yDestino, matriz, recorrido, nroMov + 1, mejorNroMov, xBedelia, yBedelia, filas, columnas);
                }
            }
            retiroCasilla(xCandidato, yCandidato, recorrido);
        }
    }
}
void imprimirMatriz(char** matriz, int m, int n){
    for (int i = 0; i < m; i++){
        for(int j= 0; j< n;j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }   
}
int main(){
    int columnas;
    int filas;
    cin>>columnas;
    cin>>filas;
    
    char** matriz = new char*[filas];
    for(int i = 0; i < filas; i++){
        matriz[i] = new char[columnas];
    }

    int xBedelia;
    int yBedelia;
    
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            char casilla;
            cin>>casilla;
            matriz[i][j] = casilla;
            if(casilla == 'B'){
                xBedelia = i;
                yBedelia = j;
            }
        }
    }

    int p;
    cin>>p;
    
    bool** recorrido = new bool*[filas];
    for(int i = 0; i < filas; i++){
        recorrido[i] = new bool[columnas];
        for(int j = 0; j < columnas; j++){
            recorrido[i][j] = false;
        }
    }

    for(int i = 0; i<p; i++){
        int columnaOrigen;
        int filaOrigen;
        int columnaDestino;
        int filaDestino;

        cin>>columnaOrigen>>filaOrigen>>columnaDestino>>filaDestino;

        int mejorNroMov1 = INT_MAX;
        int mejorNroMov2 = INT_MAX;
        facultadBT(filaOrigen-1, columnaOrigen-1, xBedelia, yBedelia, matriz, recorrido, 1, mejorNroMov2,  xBedelia, yBedelia, filas, columnas);
        facultadBT(xBedelia, yBedelia, filaDestino-1, columnaDestino-1, matriz, recorrido, 0, mejorNroMov1,  xBedelia, yBedelia, filas, columnas);
        
        if(mejorNroMov2 == INT_MAX){
            mejorNroMov2 = 0;
        }
        if(mejorNroMov1 == INT_MAX){
            mejorNroMov1 = 0;
        }

        if(mejorNroMov1 == 0){
            mejorNroMov2 = 0;
        }
        if(mejorNroMov2 == 0){
            mejorNroMov1 = 0;
        }

        cout<<mejorNroMov2 + mejorNroMov1<<endl;
    }
    return 0;
}