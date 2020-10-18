#include<stdio.h>
#include<stdlib.h>
#define HEAP_TYPE 0 // if 0 is max heap, else min heap

unsigned heapsize = 0;

int compare(int x, int y) {
    return (HEAP_TYPE) ? x < y : x > y;
}

void swap(int* a, int x, int y) {
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

void insert(int* a, int k) {
    a[++heapsize] = k;
    unsigned i = heapsize;

    while(i > 1 && compare(a[i>>1], a[i])) {
        swap(a, i, i >> 1);
        i >>= 1;
    }
}

void heapify(int* a, int n, int i) {
    int l = i << 1;
    int r = l | 1;

    int max = i;
    if(l <= n && compare(a[l], a[max])) max = l;
    if(r <= n && compare(a[r], a[max])) max = r;

    if(max != i) {
        swap(a, i, max);
        heapify(a, n, max);
    }
}

void build(int* a, int n) {
    for(unsigned i = n/2; i > 0; --i) {
        heapify(a, n, i);
    }
}

int extract(int* a) {
    swap(a, 1, heapsize);
    --heapsize;
    heapify(a, heapsize, 1);
    return *(a+heapsize+1);
}

int* heapsort(int* a, int n) {
    int* b = malloc(sizeof(int) * n);
    build(a, n);
    for(unsigned i = 0; i < n; ++i) {
        b[i] = extract(a);
;
    }

    return b;
}

void increase_key(int* a, int i, int k) {
    swap(a, i, k);
    while(i > 1 && compare(a[i>>1], a[i])) {
        swap(a, i, i >> 1);
        i >>= 1;
    }
}

int main() {
    heapsize = 6;
    int* a = malloc(sizeof(int) * 7);

    for(unsigned i = 1; i < 7; ++i)
        a[i] = i;
    build(a, 6);
    for(unsigned i = 1; i <= heapsize; ++i)
        printf("%d ", *(a+i));

    printf("\n");
    printf("max value = %d\n", extract(a));

    for(unsigned i = 1; i <= heapsize; ++i)
        printf("%d ", *(a+i));

    printf("\n");
    increase_key(a, 1, 4);
    for(unsigned i = 1; i <= heapsize; ++i)
        printf("%d ", *(a+i));
    printf("\n");
    int n = heapsize;
    int* b = heapsort(a, heapsize);

    printf("heapsort = ");
    for(unsigned i = 0; i < n; ++i)
        printf("%d ", *(b+i));
    free(b);
    free(a);
    return 0;
}
