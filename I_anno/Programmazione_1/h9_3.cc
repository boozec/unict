#include <iostream>
#include <algorithm>

// Dato array V=NxM e uno grande W, trovare il numero di elementi presenti in W che sono compresi in ogni riga di V

int main() {
    std::cout << __cplusplus;
    const auto N = 4, M = 4, L = 3;
    int V[N][M] = {
        {3, 1, 5, 50},
        {5, 3, 1, 5},
        {8, 7, 4, 5},
        {4, 7, 4, 5},
    };

    int W[L] = {4, 50, 2};

    for(auto i = 0; i < N; ++i) {
        const auto range = std::minmax_element(std::begin(V[i]), std::end(V[i]));
        int count{0};
        for(auto const& j : W) {
            if(j >= *range.first && j <= *range.second)
                count++;
        }

        std::cout << count << std::endl;
    }


    return 0;
}
