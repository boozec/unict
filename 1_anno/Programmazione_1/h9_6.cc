#include <iostream>
#include <algorithm>

int main() {
    const auto N{4}, M{4}, s{50}, z{2};
    int V[N][M] = {
        {3, 1, 5, 50},
        {5, 3, 1, 5},
        {8, 7, 4, 5},
        {4, 7, 4, 5},
    };

    int W[M] = {0};

    for(auto i = 0; i < N; ++i) {
        bool finish{false};
        for(auto j = 0, index = 0; j < M-1; ++j, ++index) {
            int sum{0};
            for(auto zz = index; zz < index+z; ++zz) {
                sum+=V[i][zz];
                if(sum >= s) {
                    W[i] = 1;
                    finish = true;
                    break;
                }
            }
            if(finish) break;
        }
    }

    for(auto i = 0; i < N; ++i)
        std::cout << W[i] << ' ';

    return 0;
}
