#include <iostream>

using namespace std; 

template<int N, int M>
short* func(string (&S)[N][M], char (&C)[N], char (&D)[N]) {
    short* a = new short[N];

    for(int i = 0; i < N; ++i) {
        short counter = 0;
        for(auto const& rows_string : S[i]) {
            if(rows_string.length() > 2) {
                if(rows_string.at(0) == C[i]
                    && rows_string.at(rows_string.length()-1) == D[i])
                        ++counter;
            }
        }

        a[i] = counter;
    }    


    return a;
}

int main() {
    string t[3][3]{
        {"suca", "we", "soia"},
        {"omg", "ooohygodg", "onopg"},
        {"", "mii", ""},
    };

    char c[3] = {'s', 'o', 'a'};
    char d[3] = {'a', 'g', 'a'};

    short* n = func(t, c, d);

    for(int i = 0; i < 3; ++i) {
        cout << n[i] << ' ';
    }

    return 0;
}
