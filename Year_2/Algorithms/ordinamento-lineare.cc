#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

template <typename T>
void
counting_sort(T* A, size_t n, ofstream& fout, int incr, bool is_char = false)
{
    int i, j;
    int max, min;
    int* freq;
    int* t;
    int range;

    for (i = 0; i < n; ++i) {
        A[i] = A[i] * incr;
    }

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
        freq[static_cast<int>(A[i] - min)] += 1;
    }
    for (i = 1; i < range; ++i) {
        freq[i] = freq[i] + freq[i - 1];
    }
    fout << "0 ";
    for (i = 0; i < range - 1; ++i) {
        fout << freq[i] << ' ';
    }

    for (i = n - 1; i >= 0; --i) {
        t[freq[static_cast<int>(A[i] - min)] - 1] = A[i];
        freq[static_cast<int>(A[i] - min)]--;
    }

    for (i = 0; i < n; ++i) {
        A[i] = t[i];
        if (is_char) {
            fout << (char)A[i] << ' ';
        } else {
            fout << A[i] / incr << ' ';
        }
    }
    fout << endl;

    delete[] freq;
    delete[] t;
}

int
main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string type;
    int N;

    for (int i = 0; i < 100; ++i) {
        fin >> type;
        fin >> N;

        if (type == "double") {
            double* a = new double[N];

            for (int j = 0; j < N; ++j) {
                fin >> a[j];
            }

            counting_sort(a, N, fout, 10);

            delete[] a;
        } else if (type == "char") {
            char* a = new char[N];

            for (int j = 0; j < N; ++j) {
                fin >> a[j];
            }

            counting_sort(a, N, fout, 1, true);
            delete[] a;
        } else {
            int* a = new int[N];

            for (int j = 0; j < N; ++j) {
                fin >> a[j];
            }

            counting_sort(a, N, fout, 1);
            delete[] a;
        }
    }

    return 0;
}
