#include <iostream>

using namespace std;

template<int N, int M>
short func(int (&A)[N][M], double d1, double d2, short s) {
    short result{0};

    for(int i = 0; i < M; ++i) {
        short temp_result{0};
        for(int j = 0; j < N-1; ++j) {
            if(temp_result >= s)
                continue;

            double div = static_cast<double>(A[j][i]) / static_cast<double>(A[j+1][i]);
            if(div >= d1 && div <= d2)
                temp_result++;
        }

        if(temp_result >= s)
            result++;
    }

    return result;
}

int main() {
    int a1[5][2] = {
        {15, 100},
        {15, 100},
        {10, 100},
        {10, 10},
        {10, 30},
    };  

    cout << func(a1, 0.3, 1.9, 2) << endl;

    return 0;
}
