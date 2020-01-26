#include<iostream>

using namespace std;

template<int N, int M>
bool func(int (&A)[N][M], double w, double v) {
    if(w > v) return false;

    for(int i = 0; i < M; ++i) {
        double sum{};
        for(int j = 0; j < N; ++j) {
            sum+=A[j][i];
        }

        double media = sum / static_cast<double>(N);

        if(media >= w && media <= v) return true;
    }

    return false;
}

int main() {
    int M[3][4] = {
        {1, 2, 3, 4},
        {1, 2, 3, 5,},
        {1, 2, 3, 6},
    };
    
    cout << func(M, 0.1, 0.2);

    return 0;
}
