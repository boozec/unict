#include <iostream>

using namespace std;
/*
2 3 4 5
1 2 3 4
1 2 3 0

3 x 4

5 2 1 0
*/

template<int N, int M>
bool* func(unsigned int (&K)[N][M], double (&D)[M]) {
    bool* A = new bool[M];
    for(int i = 0; i < M; ++i) 
        A[i] = false;

    for(int i = 0; i < M; ++i) {
        int sum = 0;
        for(int j = 0; j < N; ++j) {
            sum+=K[j][i];
        }

        if(static_cast<double>(sum)/static_cast<double>(M) > D[i]) {
            A[i] = true;
        }
    }

    return A;
}

int main() {
    // TODO: test
    unsigned int A[3][4] = {
        {2, 3, 4, 5},
        {1, 2, 3, 4},
        {1, 2, 3, 0}
    };   

    double D[4] = {5., 2.2, 1.1, 0.50};

    auto a = func(A, D);
    for(int i = 0; i < 4; ++i) 
        cout << a[i] << ' ';

    cout << endl;
    
    unsigned int A2[3][4] = {
        {2, 3, 4, 5},
        {1, 2, 0, 4},
        {1, 2, 0, 0}
    };   

    double D2[4] = {5., 2.2, 15.1, 18.50};

    auto a2 = func(A2, D2);
    for(int i = 0; i < 4; ++i) 
        cout << a2[i] << ' ';

    cout << endl;

    return 0;
}
