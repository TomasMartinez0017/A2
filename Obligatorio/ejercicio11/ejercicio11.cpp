#include <iostream>
using namespace std;

int* arreglo;
int* resultado;

void sumarSinRestar(int n){
    int* acumulado = new int[n];
    acumulado[0] = arreglo[0];
    for(int i = 1; i < n; i++){
        acumulado[i] = acumulado[i-1] + arreglo[i];
    }

    int* acumuladoInverso = new int[n];
    acumuladoInverso[n-1] = arreglo[n-1];
    
    for(int i = n-2; i >=0;i--){
        acumuladoInverso[i] = acumuladoInverso[i+1] + arreglo[i];
    }
    
    resultado = new int[n];
    resultado[0] = acumuladoInverso[1];
    cout << resultado[0] << endl;
    resultado[n-1] = acumulado[n-2];
    for(int i = 1; i < n-1 ; i++){
        resultado[i] = acumulado[i-1] + acumuladoInverso[i+1];
        cout << resultado[i] << endl;
    }
    cout << resultado[n-1] << endl;
}

int main(){
    int n;
    cin >> n;
    arreglo = new int[n];
    for(int i = 0; i< n; i++){
        int elem;   
        cin >> elem;
        arreglo[i] = elem;
    }
    sumarSinRestar(n);
    return 0;
}
