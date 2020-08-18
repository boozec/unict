#include<iostream>

using namespace std;

int cbrt(int n) {
    int i = 0;
    int j = n;
    int q = (i+j)/2;
    while(q*q*q != n) {
        q = (i+j)/2;
        if(q*q*q < n)
            i=q;
        else
            j=q;
    }
    return q;
}

int main() {
    int i;
    cin >> i;
    cout << i << ' ' << cbrt(i) << endl;
    return 0;
}
