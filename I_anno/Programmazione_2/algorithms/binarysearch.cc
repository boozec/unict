#include<iostream>

using namespace std;

bool bs(int a[], int i, int j, int x) {
    if(j<i) return false;
    int mid = i+(j-i)/2;
    if(a[mid] == x)
        return true;
    if(a[mid] > x)
        return bs(a, i, mid-1, x);
    return bs(a, mid+1, j, x);
}

bool bs2(int a[], int i, int j, int x) {
    while(i <= j) {
        int mid = i+(j-i)/2;
        if(a[mid] == x) return true;
        if(a[mid] < x)
            i = mid+1;
        else
            j = mid-1;
    }
    return false;
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int i = 0; i < 12; ++i)
        cout << i << ' '<<bs(a, 0, 9, i) << ' ' << bs2(a, 0, 9, i) << endl;
    return 0;
}

