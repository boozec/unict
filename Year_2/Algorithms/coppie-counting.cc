#include <fstream>
#include <iostream>

using namespace std;
using pii = pair<int, int>;

void
countingsort(pii* A, int n, ostream& out)
{
    int min = A[0].first;
    int max = A[0].first;

    for (int i = 1; i < n; ++i) {
        if (A[i].first < min)
            min = A[i].first;
        if (A[i].first > max)
            max = A[i].first;
    }

    int range = max - min + 1;

    int* freq = new int[range];
    pii* C = new pii[n];

    for (int i = 0; i < range; ++i)
        freq[i] = 0;

    for (int i = 0; i < n; ++i) {
        freq[A[i].first - min]++;
    }
    for (int i = 1; i < range; ++i) {
        freq[i] += freq[i - 1];
    }

    out << "0 ";
    for (int i = 0; i < range - 1; ++i)
        out << freq[i] << ' ';

    for (int i = n - 1; i >= 0; --i) {
        C[freq[A[i].first - min] - 1] = A[i];
        freq[A[i].first - min]--;
    }

    for (int i = 0; i < n; ++i)
        out << "(" << C[i].first / 10.0 << ' ' << C[i].second / 10.0 << ") ";

    out << endl;
    delete[] C;
    delete[] freq;
}

int
main(int argc, char** argv)
{
    int ts = (argc > 1) ? stoi(argv[1]) : 100;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string ch;
    int n;
    double x1, x2;

    for (int i = 0; i < ts; ++i) {
        fin >> n;
        pii* a = new pii[n];
        for (int j = 0; j < n; ++j) {
            fin >> ch;
            x1 = stod(ch.substr(1, ch.length()));
            fin >> ch;
            x2 = stod(ch.substr(0, ch.length() - 1));
            a[j] = { x1 * 10, x2 * 10 };
        }

        countingsort(a, n, fout);
        delete[] a;
    }

    fin.close();
    fout.close();

    return 0;
}
