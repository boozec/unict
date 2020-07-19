#include<iostream>

using namespace std;

int pow(int b, int e) {
    if(e == 0) return 1;
    int a = b;
    int inc = b;
    for(int i = 0; i < e-1; ++i) {
        for(int j = 0; j < b-1; ++j) {
            a+=inc;
        }
        inc = a;
    }
    return a;
}

int mul(int b, int e) {
    if(e == 0) return 0;

    return b+mul(b, e-1);
}

int pow2(int b, int e) {
    if(e == 0) return 1;

    return mul(b, pow(b, e-1));
}

int main() {
    cout << pow(2, 5) << endl;
    cout << pow2(2, 5) << endl;
    return 0;
}
