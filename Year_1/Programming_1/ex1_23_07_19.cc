#include<iostream>

using namespace std;

template<int N, int M>
bool func(double (&D)[N][M], int a) {
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N-1; ++j) {
            if(static_cast<int>(D[j][i]+D[j+1][i]) == a) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    double A[3][4] = {
        {40.2, 10, 10.2, 1},
        {40.2, 10, 10.2, 1},
        {40.2, 10, 10.2, 1},
    };

    cout << func(A, 20);
    
    return 0;
}
