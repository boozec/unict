#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int
main(int argc, char** argv)
{
    int n = (argc > 1) ? atoi(argv[1]) : 100;
    unsigned i, j, bucketsize, bucketnum;
    double A { 0.61803 };
    string t;

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    for (i = 0; i < n; ++i) {
        fin >> t >> bucketsize >> bucketnum;

        int* h = new int[bucketsize];
        for (j = 0; j < bucketsize; ++j)
            h[j] = 0;

        if (t == "int") {
            int k;

            for (j = 0; j < bucketnum; ++j) {
                fin >> k;
                h[static_cast<int>(floor(bucketsize * fmod(k * A, 1)))]++;
            }
        } else if (t == "double") {
            double k;

            for (j = 0; j < bucketnum; ++j) {
                fin >> k;
                h[static_cast<int>(floor(bucketsize * fmod(k * A, 1)))]++;
            }
        } else if (t == "char") {
            char k;

            for (j = 0; j < bucketnum; ++j) {
                fin >> k;
                h[static_cast<int>(floor(bucketsize * fmod(k * A, 1)))]++;
            }
        } else if (t == "bool") {
            bool k;

            for (j = 0; j < bucketnum; ++j) {
                fin >> k;
                h[static_cast<int>(floor(bucketsize * fmod(k * A, 1)))]++;
            }
        }

        for (j = 0; j < bucketsize; ++j)
            fout << h[j] << ' ';

        fout << endl;

        delete[] h;
    }

    fin.close();
    fout.close();
    return 0;
}
