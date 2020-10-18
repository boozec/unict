#include<iostream>
using namespace std;

template<int N, int M>
bool func(string (&A)[N][M], short w) {
    bool check{false};
    for(int i = 0; i < N; ++i) {
        bool counter{false};
        string str{""};
        string str2{""};
        for(int j = 0; j < M; ++j) {
            if(A[i][j].length() < w) {
                counter = false;
                continue;
            }

            if(!counter) {
                str = A[i][j].substr(0, w);
                
                counter = true;
                continue;
            } 

            str2 = A[i][j].substr(A[i][j].length()-w, w);

            if(str == str2) {
                check = true;
                break;
            } else {
                j--;
                counter = false;
            }
        }

        if(check) break;
    }

    return check;
}

int main() {
    string A[3][3] = {
        {"parola", "allorapar", "bla",},
        {"", "red", "red",},
        {"blue", "", "",},
    };
    cout << func(A, 3);
    return 0;
}
