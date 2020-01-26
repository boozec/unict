#include<iostream>
#define N 3
#define M 4

using namespace std;

bool* func(string (*A)[M], short k, string s) {
    bool* arr = new bool[N];

    for(int i = 0; i < N; ++i) {
        short counter{};
        for(int j = 0; j < M; ++j) {
            if(A[i][j].find(s) != std::string::npos)
                ++counter;
        }

        arr[i] = (counter >= k);
    }
    
    return arr;
}

int main() {
    string Arr[N][M] = {
        {"Ciaone", "Come one va?", "We one", ""},
        {"Ciaoe", "Come va?", "We one", ""},
        {"Ciaone", "Come one va?", "We one", ""},
    };

    bool* v = func(Arr, 2, "one");
    for(int i = 0; i < N; ++i) cout << v[i] << ' ';

    return 0;
}
