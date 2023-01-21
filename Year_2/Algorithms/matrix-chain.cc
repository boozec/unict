#include <fstream>
#include <iostream>
#include <vector>
#define INF 9999999

using namespace std;

using pii = pair<int, int>;

int
matrix_chain_multiply(vector<pii> a)
{
    int n = a.size();
    int i, d, k;

    int** m = new int*[n];

    for (i = 0; i < n; ++i)
        m[i] = new int[n];

    for (i = 0; i < n; ++i)
        m[i][i] = 0;

    for (d = 1; d < n; ++d) {
        for (i = 1; i < n - d; ++i) {
            int j = d + i;
            m[i][j] = INF;

            for (k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + a[i - 1].first * a[k].first * a[j].first;
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    int result = m[1][n - 1];

    for (i = 0; i < n; ++i)
        delete[] m[i];

    delete[] m;

    return result;
}

int
main(int argc, char** argv)
{
    int ts = (argc > 1) ? stoi(argv[1]) : 100;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string ch;

    for (int i = 0; i < ts; ++i) {
        vector<pii> v;
        int n, x1, x2 {};
        fin >> n;

        for (int j = 0; j < n; ++j) {
            fin >> ch;
            auto x = ch.find('x');
            x1 = stoi(ch.substr(1, x - 1));
            x2 = stoi(ch.substr(x + 1, ch.length() - 1));
            v.push_back({ x1, x2 });
        }
        v.push_back({ x2, 0 });
        fout << matrix_chain_multiply(v) << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
