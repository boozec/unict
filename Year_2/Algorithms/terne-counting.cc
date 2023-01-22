#include <fstream>
#include <iostream>
#include <tuple>

using namespace std;
using tiii = tuple<int, int, int>;

void
countingsort(tiii* A, int n, ostream& out)
{
    int min = get<0>(A[0]);
    int max = get<0>(A[0]);

    for (int i = 1; i < n; ++i) {
        if (get<0>(A[i]) < min)
            min = get<0>(A[i]);
        if (get<0>(A[i]) > max)
            max = get<0>(A[i]);
    }

    int range = max - min + 1;

    int* freq = new int[range];
    tiii* C = new tiii[n];

    for (int i = 0; i < range; ++i)
        freq[i] = 0;

    for (int i = 0; i < n; ++i) {
        freq[get<0>(A[i]) - min]++;
    }
    for (int i = 1; i < range; ++i) {
        freq[i] += freq[i - 1];
    }

    out << "0 ";
    for (int i = 0; i < range - 1; ++i)
        out << freq[i] << ' ';

    for (int i = n - 1; i >= 0; --i) {
        C[freq[get<0>(A[i]) - min] - 1] = A[i];
        freq[get<0>(A[i]) - min]--;
    }

    for (int i = 0; i < n; ++i)
        out << "(" << get<0>(C[i]) / 10.0 << ' ' << get<1>(C[i]) / 10.0 << ' ' << get<2>(C[i]) / 10.0 << ") ";

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
    double x1, x2, x3;

    for (int i = 0; i < ts; ++i) {
        fin >> n;
        tiii* a = new tiii[n];
        for (int j = 0; j < n; ++j) {
            fin >> ch;
            x1 = stod(ch.substr(1, ch.length()));
            fin >> x2 >> ch;
            x3 = stod(ch.substr(0, ch.length() - 1));
            a[j] = { x1 * 10, x2 * 10, x3 * 10 };
        }

        countingsort(a, n, fout);
        delete[] a;
    }

    fin.close();
    fout.close();

    return 0;
}
