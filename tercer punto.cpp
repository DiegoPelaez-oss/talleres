#include <iostream>
#include <vector>

using namespace std;

int main() {

    int n [3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    cout << "Matriz original:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << n[i][j] << " ";
        }
        cout << endl;
    }
    cout << "matriz transpuesta:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << n[j][i] << " ";
        }
        cout << endl;
    }

}