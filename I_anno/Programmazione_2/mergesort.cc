#include<iostream>

using namespace std;

void merge(int A[], int l, int q, int r) {
    int i = l;
    int j = q+1;
    int k = l;
    int B[r];

    while((i <= q) && (j <= r)) {
        if(A[i] <= A[j])
            B[k] = A[i++];
        else
            B[k] = A[j++];

        k++;
    }

    while(i <= q)
        B[k++] = A[i++];

    while(j <= r)
        B[k++] = A[j++];

    for(k = l; k <= r; ++k) 
        A[k] = B[k];
}

void mergesort(int A[], int l, int r) {
    if(l < r) {
        int q = (l+r)/2;
        mergesort(A, l, q);
        mergesort(A, q+1, r);
        merge(A, l, q, r);
    }
}


int main() {
    int a[] = {2, 4, 72, 100, 2, 12, 0, 0, 1, 23, 45, 12, 120, 3, 6};
    for(int i = 0; i < 15; ++i) {
        cout << a[i] << ' ';
    }
    cout << endl;
    mergesort(a, 0, 14);
    for(int i = 0; i < 15; ++i) {
        cout << a[i] << ' ';
    }

    return 0;
}
