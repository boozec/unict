#include<iostream>
#define N 3
#define M 4
using namespace std;

float* func(int** Q, float a, float b) {
    float* arr = new float[M];

    int a_i = static_cast<int>(a);
    int b_i = static_cast<int>(b);

    for(int i = 0; i < M; ++i) {
        short counter{};
        float sum{};
        for(int j = 0; j < N; ++j) {
            if(Q[j][i]) {
                if(Q[j][i] >= a_i && Q[j][i] <= b_i) {
                    ++counter;
                    sum += Q[j][i];
                }
            }
        }

        arr[i] = (sum / static_cast<float>(counter));
    }

    return arr;
}

int main() {
    int** A = new int*[N];
    for(int i = 0; i < N; ++i) {
        A[i] = new int[M];
        for(int j = 0; j < M; ++j)
            A[i][j] = 24;
    }

    float* arr = func(A, 1.0, 33.0);    
    
    for(int j = 0; j < M; ++j)
        cout << arr[j] << ' ';

    delete[] A;
    delete arr;

    return 0;
}
