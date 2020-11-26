#include <iostream>
#include <climits>
using namespace std;

bool esPosicionValida(int x, int y, char** matriz, int filas, int columnas){
    if(x>=filas || y>=columnas || x<0 || y<0 || matriz[x][y] == 'P'){ //Revisar >=
        return false;
    }
    return true;
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

        if(esPosicionValida(xCandidato, yCandidato, matriz, filas, columnas) && !pase(xCandidato, yCandidato, recorrido)){

            probarCasilla(xCandidato, yCandidato, recorrido);

            if(llegueDestino(xCandidato, yCandidato, xDestino, yDestino) && pasePorBedelia(xBedelia, yBedelia, recorrido) && (nroMov < mejorNroMov)){

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
    for (int i = 0; i < n; i++){
        for(int j= 0; j< m;j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    
}
int main(){
    int m;
    int n;
    cin>>m>>n;
    
    char** matriz = new char*[n];
    for(int i = 0; i < n; i++){
        matriz[i] = new char[m];
    }

    int xBedelia;
    int yBedelia;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char casilla;
            cin>>casilla;
            matriz[i][j] = casilla;
            if(casilla == 'B'){
                xBedelia = j;
                yBedelia = i;
            }
        }
    }
    imprimirMatriz(matriz, m ,n);
    int p;
    cin>>p;
    
    bool** recorrido = new bool*[n];
    for(int i = 0; i < n; i++){
        recorrido[i] = new bool[m];
        for(int j = 0; j < 5; j++){
            recorrido[i][j] = false;
        }
    }
    
    for(int i = 0; i<p; i++){
        int xo;
        int yo;
        int xd;
        int yd;
        cin>>xo>>yo>>xd>>yd;
        int mejorNroMov = INT_MAX;
        
        facultadBT(yo-1, xo-1, yd-1, xd-1, matriz, recorrido, 0, mejorNroMov, xBedelia - 1, yBedelia - 1, n, m);
        if(mejorNroMov == INT_MAX) 
            mejorNroMov = 0;
        cout<<mejorNroMov<<endl;
    }
    return 0;
}