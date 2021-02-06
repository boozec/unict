#include<iostream>

using namespace std;

int pow(int x, int y) {
    int a = 1;
    
    for(int i = 0; i < y; ++i)
        a*=x;
    
    return a;
}


int pow2(int x, int y) {
    if(y < 1) return 1;
    
    return x*pow(x, y-1);
}

int main() {
    cout << pow(2, 5) << endl;
    cout << pow2(2, 5) << endl;
    return 0;
}
