#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<int N>
bool func(int (&A)[N][N], double w) {
    vector<int> l;
    for(int i = N-1, j = 0; j < N; --i, j++) {
        l.push_back(A[i][j]);
    }

    auto min_max = minmax_element(begin(l), end(l));

    return (static_cast<double>(*min_max.first)/static_cast<double>(*min_max.second)) <= w;
}

int main() {
    int A[3][3] = {
        {1, 2, 3,},
        {67, 10, 56},
        {10, 0, 1},
    };

    cout << func(A, 0.2) << endl; // False
    cout << func(A, 0.4) << endl; // True

    return 0;
}
