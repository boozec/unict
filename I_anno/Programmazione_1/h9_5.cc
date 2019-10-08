#include <iostream>
#include <algorithm>
#include <map>

// Date due matrici e un numero p, stampare i valori che compaiono p volte dalla prima alla seconda matrice

int main() {
    const auto N{4}, M{4}, L{4}, Q{4}, p{4};
    int V[N][M] = {
        {3, 1, 5, 50},
        {5, 3, 1, 5},
        {8, 7, 4, 5},
        {4, 7, 4, 5},
    };

    int W[L][Q] = {
        {30, 3, 5, 50},
        {51, 25, 12, 5},
        {90, 12, 4, 5},
        {4, 6, 4, -3},
    };

    std::map<int, int> values;

    for(auto i = 0; i < N; ++i) {
        for(auto j = 0; j < M; ++j) {
            if(values.find(V[i][j]) == values.end())
                values.insert({V[i][j], 1});
            else
                values[V[i][j]] += 1;
        }
    }

    for(auto i = 0; i < L; ++i) {
        for(auto j = 0; j < Q; ++j) {
            auto elem = values.find(W[i][j]);
            if(elem != values.end()) {
                if(elem->second >= p) {
                    std::cout << W[i][j] << ' ';
                } else {
                    std::cout << "x ";
                }
            } else {
                std::cout << "x ";
            }
        }
        std::cout << '\n';
    }

    return 0;
}
