#include <iostream>
using namespace std;

template<int N, int M>
unique_ptr<string[]> func(string (&A)[N][M], short (&B)[N][M]) {
    auto arr = unique_ptr<string[]>(new string[N]);

    for(int i = 0; i < N; ++i) {
        short sum{0};
        string tmp{""};
        for(int j = 0; j < M; ++j) {
            sum+=B[i][j];
            tmp+=A[i][j];
        }

        arr[i] = tmp.length() >= sum ? tmp : "";
    }

    return arr;
}

int main() {
    string A[2][3] = {
        {"aab", "aA", "314"},
        {"1334", "5715", "__"},
    };

    short B[2][3] = {
        {2, 3, 0},
        {1, 15, 7}
    };
    
    auto x = func(A, B);

    for(int i = 0; i < 2; ++i)
        cout << x[i] << ' ';
    
    cout << endl;

    return 0;
}
