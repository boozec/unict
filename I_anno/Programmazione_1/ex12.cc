#include <iostream>
#include <vector>
#define N 3
using namespace std;

string* func(string a[N][N], short k, string s) {
    string* sn = new string[N];
    vector<string> l;

    // Diagonale secondaria
    for(int i = N-1, j = 0; i >= 0; --i, ++j) {
        l.push_back(a[i][j]);
    } 

    bool d2 = true;
    for(auto const& i : l) {
        if(i.length() < k || i.find(s) != 0) {
            d2 = false;
            break;
        }
    }

    if(d2) {
        for(int i = 0; i < N; ++i) {
            sn[i] = l.at(i);
        }
    } else {
        for(int i = 0; i < N; ++i) {
            sn[i] = a[i][i];
        }
    }

    return sn; 
}

int main() {
    string a[N][N] = {
        {"aab", "bbc", "4de"},
        {"xyb", "bbc", "yz3"},
        {"47x", "1y_", "23g"},
    };
    string* x = func(a, 1, "4");

    for(int i = 0; i < N; ++i)
        cout << x[i] << ' ';
    
    cout << endl;

    return 0;
}
