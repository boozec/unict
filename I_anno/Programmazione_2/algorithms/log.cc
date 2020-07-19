#include<iostream>

using namespace std;

double log(double n) {
    if(n <= 2) return 1.0;
    return 1.0 + log(n/2);
}

int log2(double n) {
    int a = 1;

    while(n > 2) {
        n /= 2;
        ++a;
    }

    return a;
}

int main() {
    for(int i = 0; i < 25; ++i)
        cout << i << ' ' << log(i) << ' ' << log2(i) << endl;
    return 0;
}
