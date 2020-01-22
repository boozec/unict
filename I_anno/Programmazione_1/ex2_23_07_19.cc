#include<iostream>

using namespace std;

template<int N>
bool func(string (&Q)[N][N]) {
    string stringaL = Q[0][0];
    string stringaC = Q[0][0];
    for(int i = 0; i < N; ++i) {
        if(Q[i][i].length() > stringaL.length())
            stringaL = Q[i][i];
        else if(Q[i][i].length() < stringaC.length())
            stringaC = Q[i][i];
    }

    short vocaliL{};
    short vocaliC{}; 

    for(auto& c : stringaL) {
        c = tolower(c);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            ++vocaliL;
    }
    
    for(auto& c : stringaC) {
        c = tolower(c);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            ++vocaliC;
    }
    
    return vocaliL < vocaliC;
}

int main() {
    string A[3][3] = {
        {"lllll", "bb", "cc"},
        {"AAA", "e", "cc"},
        {"AAA", "bb", "cc"},
    };

    cout << func(A);
    
    return 0;
}
