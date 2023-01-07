#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

template <class H>
class MaxHeap {
public:
    void
    max_heapify(int i)
    {
        if (i > _size)
            return;

        size_t l = left(i);
        size_t r = right(i);
        size_t max = i;

        if (l <= _size && _A[l] > _A[i])
            max = l;
        if (r <= _size && _A[r] > _A[max])
            max = r;

        if (max != i) {
            swap(i, max);
            max_heapify(max);
        }
    }

    size_t
    left(int i)
    {
        return i << 1;
    }
    size_t
    right(int i)
    {
        return (i << 1) | 1;
    }

    ~MaxHeap()
    {
        delete _A;
    }

    MaxHeap(H* A, int size, ostream& out)
        : _size(size + 1)
    {
        _A = new H[_size + 1];
        for (int i = 1; i <= size; ++i) {
            _A[i] = A[i - 1];
        }

        for (int i = _size / 2; i > 0; --i)
            max_heapify(i);

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

    H
    extract_max()
    {
        swap(1, _size);
        --_size;
        max_heapify(1);

        return _A[_size + 1];
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

            MaxHeap<bool>* mh = new MaxHeap<bool>(arr, n, fout);

            delete mh;
        } else if (t == "double") {
            double* arr = new double[n];
            for (j = 0; j < n; ++j)
                fin >> arr[j];

            MaxHeap<double>* mh = new MaxHeap<double>(arr, n, fout);

            delete mh;
        } else if (t == "char") {
            char* arr = new char[n];
            for (j = 0; j < n; ++j)
                fin >> arr[j];

            MaxHeap<char>* mh = new MaxHeap<char>(arr, n, fout);

            delete mh;
        } else if (t == "int") {
            int* arr = new int[n];
            for (j = 0; j < n; ++j)
                fin >> arr[j];

            MaxHeap<int>* mh = new MaxHeap<int>(arr, n, fout);

            delete mh;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
