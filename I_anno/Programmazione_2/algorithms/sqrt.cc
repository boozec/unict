#include<iostream>

using namespace std;

double abs(double n) {
    if(n < 0) return -n;

    return n;
}


double sq(int n) {
    double x = n;
    double y = 1;
    while(x-y > 0.0000001) {
        x = (x+y)/2;
        y = n/x;
    }
    return x;
}

double sq2_n(double n, double a) {
    if(abs(a*a - n) <= 0.000001) {
        return a;
    }

    return sq2_n(n, (a+n/a)/2);
}

double sq2(int n) {
    return sq2_n(n, n/2);
}

int main() {
    cout << sq(81) << endl;
    cout << sq2(81) << endl;
    return 0;
}
