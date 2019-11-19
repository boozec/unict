#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<int N, int M>
bool func(int (&A)[N][M], short k, double x) {
    for(int i = 0; i < M; ++i) {
        vector<pair<int, int> > v;

        for(int j = 0; j < N-1; ++j) {
            v.push_back({A[j][i], A[j+1][i]});
        }
        
        int check_num = 0;

        for(auto const& i : v) {
            if(i.second == 0) continue;
            double elem = static_cast<double>(i.first) / static_cast<double>(i.second);

            if(elem < x)
                check_num++;
        }

        if(check_num == k)
            return true;
    }


    return false;
}

int main() {
    int A[4][3] = {
        {2, 3, 5},
        {10, 20, 10},
        {90, 19, 69},
        {10, 0, 0},
    };

    cout << func(A, 2, 0.005) << endl; // 0
    cout << func(A, 2, 1.0) << endl; // 1
    return 0;
}
