#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    cout << "Encuentra la mediana de la matriz: \n";
    int n[5] = {1, 3, 8, 7, 9};
    // Mostrar el arreglo
    for(int i = 0; i < 5; i++){
        cout << n[i] << " ";
    }
    cout << endl;

    // Ordenar el arreglo (por si acaso no está ordenado)
    sort(n, n + 5);

    // Calcular la mediana
    double mediana;
    int tam = 5;
    if (tam % 2 == 1) {
        mediana = n[tam / 2];
    } else {
        mediana = (n[tam / 2 - 1] + n[tam / 2]) / 2.0;
    }

    cout << "La mediana del arreglo es: " << mediana << endl;
    return 0;
}