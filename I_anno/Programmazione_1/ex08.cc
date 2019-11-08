#include <iostream>
#include <stdio.h>
#define N 3 
#define M 5

using namespace std;

bool func(int A[N][M], short k, short w) { 
    short counter = 0;
    for(int i = 0; i < M; ++i) {
        short t_counter = 0;
        for(int j = 1; j < N; ++j) {
            if(A[j][i] < A[j-1][i])
                break;
            else 
                ++t_counter;
        }

        if(t_counter >= k)
            ++counter;
    }

    return counter >= w;
}

int main() {
    int array[N][M] = {
        {5, 7, 9, 10, 5},
        {10, 2, 3, 4, 10},
        {16, 34, 21, 23, 1}
    };

    cout << func(array, 2, 1) << endl;

    return 0;
}
