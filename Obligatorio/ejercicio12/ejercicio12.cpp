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

int main(){
    
    /*
    int m;
    int n;
    cin>>m>>n;

    cout<<m<<endl;
    cout<<n<<endl;
    */
    
    char** matriz = new char*[5];
    for(int i = 0; i < 5; i++){
        matriz[i] = new char[5];
    }
    
    matriz[0][0] = 'P';
    matriz[0][1] = 'P';
    matriz[0][2] = 'C';
    matriz[0][3] = 'P';
    matriz[0][4] = 'C';
    matriz[1][0] = 'C';
    matriz[1][1] = 'C';
    matriz[1][2] = 'C';
    matriz[1][3] = 'P';
    matriz[1][4] = 'P';
    matriz[2][0] = 'C';
    matriz[2][1] = 'P';
    matriz[2][2] = 'C';
    matriz[2][3] = 'C';
    matriz[2][4] = 'C';
    matriz[3][0] = 'C';
    matriz[3][1] = 'C';
    matriz[3][2] = 'B';
    matriz[3][3] = 'P';
    matriz[3][4] = 'C';
    matriz[4][0] = 'P';
    matriz[4][1] = 'C';
    matriz[4][2] = 'C';
    matriz[4][3] = 'C';
    matriz[4][4] = 'C';
    
    int xBedelia = 3;
    int yBedelia = 2;
    
    /*
    for(int i = 0; i < m; i++){
        cout<<"Entre primer for"<<endl;
        for(int j = 0; j < n; j++){
            cout<<"Entre segundo for"<<endl;
            char casilla;
            cin>>casilla;
            cout<<casilla<<endl;
            matriz[i][j] = casilla;
            if(casilla == 'B'){
                xBedelia = i;
                yBedelia = j;
            }
        }
    }
    */
    /*
    int p;
    cin>>p;
    */
    
    bool** recorrido = new bool*[5];
    for(int i = 0; i < 5; i++){
        recorrido[i] = new bool[5];
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            recorrido[i][j] = false;
        }
    }
    /*
    for(int i = 0; i<p; i++){
        int xo;
        int yo;
        int xd;
        int yd;
        cin>>xo>>yo>>xd>>yd;
        int mejorNroMov = 9999999;
        
        facultadBT(xo-1, yo-1, xd-1, yd-1, matriz, recorrido, 0, mejorNroMov, xBedelia - 1, yBedelia - 1, m, n);

        cout<<mejorNroMov<<endl;
    }
    */

    int mejorNroMov = 9999999;
    facultadBT(0, 2, 3, 4, matriz, recorrido, 0, mejorNroMov, xBedelia, yBedelia, 5, 5);
    cout<<mejorNroMov<<endl;

    return 0;
}