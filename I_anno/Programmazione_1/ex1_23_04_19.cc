#include<iostream>
#define N 4
#define M 3

using namespace std;

double func(string (*S)[M], string s1, short k) {
    if(k < 1 || k > M) return -1;

    short counter{};
    short c_strings{};

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < k; ++j) {
            ++c_strings;
            if(S[i][j].length() > s1.length())
                ++counter;
        }
    }
    
    return static_cast<double>(counter*100/c_strings);
}

int main() {
    string A[N][M] = {
        {"red", "orange", "green"},
        {"red", "orange", "green"},
        {"red", "orange", "green"},
        {"red", "orange", "green"},
    };

    cout << func(&A[0], "pink", 2);
   
    return 0;
}
