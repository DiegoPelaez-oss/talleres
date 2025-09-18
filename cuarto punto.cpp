#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int main(){
    int array[6];
    for(int i = 0; i < 6; i++){
        cout << "Ingresa el valor " << i << ": ";
        cin >> array[i];
    }

    cout << "Elementos del array:\n";
    for(int i = 0; i < 6; i++){
        cout << array[i] << " ";
    }
}