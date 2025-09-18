#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
//eso esta muy duro profe :'(

int main(){
    int n;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;
    int arr[n];
    cout << "Ingrese los elementos:\n";
    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    bool hayDuplicados = false;
    cout << "Elementos duplicados: ";
    for(int i = 1; i < n; ++i) {
        if(arr[i] == arr[i-1]) {
            if(i == 1 || arr[i] != arr[i-2]) {
                cout << arr[i] << " ";
                hayDuplicados = true;
            }
        }
    }
    if(!hayDuplicados) {
        cout << "Ninguno";
    }
    cout << endl;
}