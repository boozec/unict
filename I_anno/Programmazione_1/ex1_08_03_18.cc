#include<iostream>

#define n 3

using namespace std;

bool func(int (*A)[n]) {
    /*
        0    1   n-2  n-1  
      0 | x | x | x | x |
      1 | x | x | x | x |
    n-2 | x | x | x | x |
    n-1 | x | x | x | x |
    */

    int sum{}; // Inizializza sum a 0
    for(int i = 1, j = n-1; j > 0; ++i, j--) {
        sum+=A[j][i];
    }

    return (sum % n == 0);
}

int main() {
    int A[n][n] = {
        {1, 2, 3, },
        {1, 2, 3, },
        {1, 3, 0, },
    };

    cout << func(&A[0]);
    return 0;
}
