#include <iostream>
#include <cctype>

using namespace std;

template<int N>
bool* func(string (&A)[N]) {
    bool* a2 = new bool[N];

    for(int i = 0; i < N; ++i) {
        bool is_pal = true;
        for(int j = 0, z = A[i].length()-1; j < z; ++j, --z ) {
            if(tolower(A[i].at(j)) != tolower(A[i].at(z))) {
                is_pal = false;
                break;
            }
        }
        a2[i] = is_pal;
    }

    return a2;
}

int main() {
    string t[] = {"oslo", "yam_a_may", "AnNa"};
    auto a = func(t);
    
    for(int i = 0; i < 3; ++i) {
        cout << a[i] << ' ';
    }

    return 0;
}
