#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template<int N>
bool func(int (&A)[N][N], double w) {
    vector<int> list;
    for(int i = 0, j = N-1; i < N; ++i, --j) 
        list.push_back(A[j][i]);

    auto minmax = minmax_element(begin(list), end(list));
    return (static_cast<double>(*minmax.first)/static_cast<double>(*minmax.second)) <= w;
}

int main() {
    int A[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };

    cout << func(A, 0.1);

    return 0;
}
