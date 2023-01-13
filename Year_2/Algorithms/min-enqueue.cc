#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

template <class H>
class MinHeap {
public:
    MinHeap<H>*
    enqueue(H key)
    {
        if (_size == _n)
            return this;
        ++_size;
        _A[_size] = key;

        int i = _size;
        int j = i / 2;

        while (i > 1 && _A[i] < _A[j]) {
            swap(i, j);
            i = j;
            j /= 2;
        }

        return this;
    }

    size_t
    left(int i)
    {
        return i * 2;
    }
    size_t
    right(int i)
    {
        return i * 2 + 1;
    }

    ~MinHeap()
    {
        delete _A;
    }

    MinHeap(H* A, int size, ostream& out)
        : _n(size + 1)
    {
        _A = new H[_n];
        for (int i = 0; i < size; ++i) {
            enqueue(A[i]);
        }

        for (int i = 1; i <= size; ++i) {
            out << _A[i] << ' ';
        }
        out << endl;
    }

    void
    swap(int x, int y)
    {
        auto t = _A[x];
        _A[x] = _A[y];
        _A[y] = t;
    }

private:
    H* _A;
    size_t _size;
    size_t _n;
};

int
main(int argc, char** argv)
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string t;
    int n, j;

    for (int i = 0; i < atoi(argv[1]); ++i) {
        fin >> t;
        fin >> n;

        if (t == "bool") {
            bool* arr = new bool[n];
            for (j = 0; j < n; ++j)
                fin >> arr[j];

            MinHeap<bool>* mh = new MinHeap<bool>(arr, n, fout);

            delete mh;
        } else if (t == "double") {
            double* arr = new double[n];
            for (j = 0; j < n; ++j)
                fin >> arr[j];

            MinHeap<double>* mh = new MinHeap<double>(arr, n, fout);

            delete mh;
        } else if (t == "char") {
            char* arr = new char[n];
            for (j = 0; j < n; ++j)
                fin >> arr[j];

            MinHeap<char>* mh = new MinHeap<char>(arr, n, fout);

            delete mh;
        } else if (t == "int") {
            int* arr = new int[n];
            for (j = 0; j < n; ++j)
                fin >> arr[j];

            MinHeap<int>* mh = new MinHeap<int>(arr, n, fout);

            delete mh;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
