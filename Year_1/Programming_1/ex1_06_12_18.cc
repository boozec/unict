#include<iostream>

using namespace std;

template<int N>
bool func(int (&A)[N][N], double w) {
    int sumDiagonale{};
    for(int i = 0; i < N; ++i) sumDiagonale+=A[i][i];

    for(int i = 0; i < N; ++i) {
        int sumCol{};
        for(int j = 0; j < N; ++j) {
            sumCol+=A[j][i];
        }

        if(static_cast<double>(sumCol/sumDiagonale) > w)
            return true;
    }
    

    return false;
}

int main() {
    int A[4][4] = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
    };

    cout << func(A, 4.5);
    
    return 0;
}
