#include<iostream>
#include<vector>

#define n 3

using namespace std;

bool func(char (*A)[n]) {
    bool check{false};
    char str[n];

    for(int i = 0; i < n; ++i) {
        str[i] = A[i][i];
    }

    short n_check{0};
    for(int i = 0; i < n; ++i) {
        short index{0};
        for(int j = 0; j < n; ++j) {
            if(A[j][i] != str[index++]) {
                break;
            }
            ++n_check;
        }
        if(n_check == n) {
            check = true;
            break;
        }
    }

    return check;
}


int main() {
    char A[3][3] = {
        {'a', 'b', 'c'},
        {'b', 'b', 'c'},
        {'c', 'b', 'c'},
    };

    cout << func(&A[0]);

    return 0;
}
