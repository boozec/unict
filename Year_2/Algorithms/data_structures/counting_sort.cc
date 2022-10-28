#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

void
counting_sort(int* A, size_t n)
{
    int i, j;
    int max, min;
    int* freq;
    int* t;
    int range;

    max = A[0], min = A[0];
    t = new int[n];

    for (i = 1; i < n; ++i) {
        if (A[i] > max)
            max = A[i];

        if (A[i] < min)
            min = A[i];
    }

    range = (max - min) + 1;

    freq = new int[range];

    for (i = 0; i < range; ++i) {
        freq[i] = 0;
    }

    for (i = 0; i < n; ++i) {
        freq[A[i] - min] += 1;
    }
    for (i = 1; i < range; ++i) {
        freq[i] = freq[i] + freq[i - 1];
    }

    for (i = n - 1; i >= 0; --i) {
        t[freq[A[i] - min] - 1] = A[i];
        freq[A[i] - min]--;
    }

    for (i = 0; i < n; ++i)
        A[i] = t[i];

    delete[] freq;
    delete[] t;
}

int
main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string s;

    int* A = new int[1024];
    int n;
    char* token;

    for (int i = 0; i < 100; ++i) {
        getline(fin, s);
        n = 0;
        token = strtok((char*)s.c_str(), " ");
        while (token) {
            A[n++] = atoi(token);
            token = strtok(NULL, " ");
        }

        counting_sort(A, n);

        for (int i = 0; i < n - 1; ++i) {
            fout << A[i] << ' ';
        }
        fout << A[n - 1] << endl;
    }

    delete[] A;

    return 0;
}
