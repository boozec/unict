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

double cbrt2(int n) {
    int i = 1;
    while(i*i*i <= n)
        ++i;
    // precision
    
    --i;
    while(i*i*i < n)
        i+=0.000001;
    
    return i;
}

int main() {
    int i;
    cin >> i;
    cout << i << ' ' << cbrt(i) << endl;
    return 0;
}
