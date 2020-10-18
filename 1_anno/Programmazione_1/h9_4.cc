#include <iostream>
#include <algorithm>

// Data matrice V di NxM, array A e numero w<M, trovare se c'è almeno una riga di V con almeno w elementi maggiori di ogni elemento di A

const auto N{4}, M{4}, k{3}, w{2};

bool row_alg(int V[N][M], int* A, int w) {
    // È ovvio che sia presente almeno 0 elementi, quindi non ha senso continuare
    if(w <= 0) return true;
    auto max_element_of_A = std::max_element(A,A+k);
    
    for(auto i = 0; i < N; ++i) {
        int counts = 0;
        for(auto j = 0; j < M; ++j) {
            if(V[i][j] > *max_element_of_A)
                counts++;

            if(counts == w)
                return true;
        }
    } 

    return false;
}

int main() {
    int V[N][M] = {
        {3, 59, 5, 54},
        {5, 3, 1, 5},
        {8, 7, 4, 5},
        {4, 7, 4, 5},
    };

    int A[k] = {4, 50, 2};

    std::cout << row_alg(V, A, w) << std::endl;

    return 0;
}
