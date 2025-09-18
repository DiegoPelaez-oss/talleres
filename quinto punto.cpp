#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(){
    
    int orden[6] = {5, 3, 6, 2, 10, 1};
    int numerosOrdenados[6];
    cout << "Array original: \n";

    for(int i = 0; i < 6; i++){
        cout << orden[i] << ", ";
    }
    cout << "\n";

    for (int i = 0; i < 6; i++)
    {
        numerosOrdenados[i] = orden[i];
    }

    sort(numerosOrdenados, numerosOrdenados + 6);
    cout << "Array ordenado: \n";
    for (int i = 0; i < 6; i++)
    {
        cout << numerosOrdenados[i] << ", ";
    }
    

}
