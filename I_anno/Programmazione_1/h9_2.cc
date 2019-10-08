#include <iostream>

// Array NxM e numero p. Stampare le medie per ogni colonna dispari dei valori x <= p

int main() {
    const short N = 4, M = 4;
    int p = 9;
    int A[N][M] = {
        {3, 1, 5, 5},
        {5, 3, 1, 5},
        {8, 7, 4, 5},
        {4, 7, 4, 5},
    };
    // Condizione necessaria per matrici in cui M != N
    short cond = (N < M) ? N : M;

    for(int i = 1; i < cond; i+=2) {
        int sum = 0, c = 0;
        for(int j = 0; j < M; ++j) {
            if(A[j][i] <= p) {
                sum += A[j][i];
                c++;
            }
        }

        if(c > 0) {
            std::cout << static_cast<float>(sum)/c << '\n';
        }
    }

    return 0;
}
