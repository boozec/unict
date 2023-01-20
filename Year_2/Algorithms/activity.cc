#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pi;

int
find(int j, int* w, int* o, int* p)
{
    int c { 0 };
    while (j > 0) {
        if (w[j] + o[p[j]] > o[j - 1]) {
            c += w[j];
            j = p[j];
        } else {
            j--;
        }
    }

    return c;
}

int
activity(vector<pi> A)
{
    int n = A.size() + 1;
    int* p = new int[n];
    int* w = new int[n];
    int* o = new int[n];
    int i, j;

    o[0] = w[0] = p[0] = 0;

    for (i = 1; i < n; ++i) {
        p[i] = 0;
        w[i] = A[i - 1].second - A[i - 1].first;
    }

    for (i = n - 1; i > 0; --i) {
        for (j = 1; j < n; ++j)
            if (A[j - 1].second <= A[i - 1].first)
                p[i]++;
    }

    for (i = 1; i < n; ++i) {
        o[i] = max(w[i] + o[p[i]], o[i - 1]);
    }

    int res = find(n - 1, w, o, p);

    delete[] p;
    delete[] w;
    delete[] o;

    return res;
}

int
main(int argc, char** argv)
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int ts = (argc > 1) ? stoi(argv[1]) : 100;
    int n;

    for (int i = 0; i < ts; ++i) {
        fin >> n;
        string ch;
        int s;
        int e;
        vector<pi> a;

        for (int j = 0; j < n; ++j) {
            fin >> ch;
            s = stoi(ch.substr(1, ch.length()));
            fin >> ch;
            e = stoi(ch.substr(0, ch.length() - 1));
            a.push_back({ s, e });
        }

        sort(a.begin(), a.end(), [](pi const& x, pi const& y) {
            return x.second < y.second;
        });

        fout << activity(a) << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
