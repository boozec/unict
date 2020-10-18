#include <iostream>

// Array NxM. Trovare media dei valori differenza tra gli elementi della diagonale principale e secondaria

int main() {
    const short N = 4, M = 3;
    int A[N][M] = {
        {3, 1, 5},
        {5, 3, 1},
        {8, 7, 4},
        {4, 7, 4},
    };

    int diff1 = A[0][0], diff2 = A[N-1][0];

    // Condizione necessaria per matrici in cui M != N
    short cond = (N < M) ? N : M;
    
    for(int i = 1, j = N-1, j2 = 1; i < cond; ++i, --j, ++j2) {
        diff1 -= A[i][i];
        diff2 -= A[j][j2];
    }

    std::cout << static_cast<float>((diff1+diff2)/2) << std::endl;

    return 0;
}
