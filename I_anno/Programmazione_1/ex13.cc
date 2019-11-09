#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#define K2 2
#define N2 3
using namespace std;

template<int N, int K>
unique_ptr<double[]> func(int (&A)[K][N], int (&B)[N][K]) {
    auto arr = unique_ptr<double[]>(new double{K});
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
    int A[K2][N2] = {
        {3, 7, 10},
        {5, 12, 32},
    };
    int B[N2][K2] = {
        {12, 10},
        {15, 17},
        {8, 0},
    };
    auto x = func(A, B);

    for(int i = 0; i < K2; ++i)
        cout << x[i] << ' ';
    
    cout << endl;

    return 0;
}
