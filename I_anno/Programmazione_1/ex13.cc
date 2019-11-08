#include <iostream>
#include <algorithm>
#include <vector>
#define K 2
#define N 3
using namespace std;

double* func(int A[K][N], int B[N][K]) {
    double* arr = new double[K];
    for(int i = 0; i < K; ++i) {
        vector<int> t;
        int sum = 0;
        for(int j = 0; j < N; ++j) {
            t.push_back(B[j][i]);
            sum+=A[i][j];
        }
        
        double media = static_cast<double>(sum)/N;
        auto min_num = min_element(begin(t), end(t));
        arr[i] = media - *min_num;
    }

    return arr;
}

int main() {
    int A[K][N] = {
        {3, 7, 10},
        {5, 12, 32},
    };
    int B[N][K] = {
        {12, 10},
        {15, 17},
        {8, 0},
    };
    double* x = func(A, B);

    for(int i = 0; i < K; ++i)
        cout << x[i] << ' ';
    
    cout << endl;

    return 0;
}
