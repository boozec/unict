#include <iostream>
#include <cctype>

using namespace std;

template<int N, int M>
bool func(string (&A)[N][M], unsigned short k, unsigned short s) {
    for(int i = 0; i < N; ++i) {
        short string_num = 0;
        for(int j = 0; j < M; ++j) {
            short upper_chars = 0;
            for(auto const& c : A[i][j]) {
                if(isupper(c))
                    ++upper_chars;
            }

            if(upper_chars >= s)
                ++string_num;
        }

        if(string_num >= k) 
            return false;
    }   

    return true;
}

int main() {
    string A[2][3] = {
       {"suce", "oHh", "b"},
       {"111", "HAAa", "B"}
    };

    cout << func(A, 2, 1) << endl;
    return 0;
}
