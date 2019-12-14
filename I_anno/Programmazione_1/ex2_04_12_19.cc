#include <iostream>
#include <string>

using namespace std;

template<int N>
bool func(string (&Q)[N][N], string s) {
    short n_presents[2] = {0};
    for(int i = 0; i < N; ++i) {
        if(Q[i][i].find(s) != std::string::npos)
            n_presents[0]++;
    }
    
    for(int i = 0, j = N-1; i < N; ++i, --j) {
        cout << Q[j][i].find(s) << endl;
        if(Q[j][i].find(s) != std::string::npos)
            n_presents[1]++;
    }

    return n_presents[0] > n_presents[1];
}

int main() {
    string a1[3][3] = {
        {"ciaoneXX", "fra", "zio"},
        {"oh, ma che", "eXXh", "sta cosa?"},
        {"greg", "no", "foXXrse"}
    };
    
    string a2[3][3] = {
        {"ciaoneXX", "fra", "ziYYo"},
        {"oh, ma che", "eXXYYh", "sta cosa?"},
        {"gregYY", "no", "foXrse"}
    };

    cout << func(a1, "XX") << ' ' << func(a2, "YY") << endl;

    return 0;
}
