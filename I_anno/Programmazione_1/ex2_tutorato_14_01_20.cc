#include<iostream>

using namespace std;

template<int N, int M>
bool func(string (&A)[N][M], unsigned short k, unsigned short s) {
    for(int i = 0; i < N; ++i) {
        short count_s{};
        for(int j = 0; j < M; ++j) {
            short upper_cs{};
            for(auto const& c : A[i][j]) {
                if(isupper(c))
                    ++upper_cs;
            }
        
            if(upper_cs < s)
                ++count_s;
        }

        if(count_s >= k)
            return true;
    }
    
    return false;
}

int main() {
    string A[3][4] = {
        {"ProVA", "CiAone", "RAed"},
        {"IVVA", "CiAOO", "BLUE"},
        {"AA", "AA", "AA3#"},
    };

    cout << func(A, 3, 1);
        

    return 0;
}
