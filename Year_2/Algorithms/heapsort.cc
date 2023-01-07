#include <fstream>
#include <iostream>

using namespace std;

enum class HeapType {
    MAX,
    MIN,
};

template <class T>
class heap {
public:
    heap(HeapType type, int size)
        : _type(type)
        , _n { size }
    {
        _heapsize = 0;

        a = new T[size + 1];
    }

    heap(HeapType type, T* arr, int size)
        : _type(type)
        , _n { size + 1 }
    {
        _heapsize = size - 1;

        a = new T[size + 1];

        for (int i = 1; i < _n; ++i) {
            a[i] = arr[i - 1];
        }

        build(_heapsize);
    }

    void
    swap(unsigned x, unsigned y)
    {
        auto t = a[x];
        a[x] = a[y];
        a[y] = t;
    }

    heap<T>*
    insert(T key)
    {
        if (_heapsize == _n - 1)
            return this;

        a[++_heapsize] = key;

        unsigned i = _heapsize;
        while (i > 1 && compare(i >> 1, i)) {
            swap(i, i >> 1);
            i >>= 1;
        }

        return this;
    }

    void
    heapify(int i)
    {
        _heapify_count++;
        int l = i << 1;
        int r = l | 1;

        int max = i;
        if (l <= _heapsize && compare(l, max) < 0)
            max = l;
        if (r <= _heapsize && compare(r, max) < 0)
            max = r;

        if (max != i) {
            swap(i, max);
            heapify(max);
        }
    }

    void
    build(int n)
    {
        for (unsigned i = n / 2; i > 0; --i) {
            heapify(i);
        }
    }

    T
    extract()
    {
        swap(1, _heapsize);
        --_heapsize;
        heapify(1);
        return *(a + _heapsize + 1);
    }

    void
    heapsort(ofstream& fout)
    {
        T* b = new T[_heapsize];

        _heapify_count = 0;
        int n = _heapsize;
        for (unsigned i = 0; i < n; ++i) {
            b[i] = extract();
        }
        fout << _heapify_count << ' ';
        for (unsigned i = 0; i < n; ++i) {
            fout << b[i] << ' ';
        }
        fout << endl;

        delete[] b;
    }

    ~heap()
    {
        delete[] a;
    }

    int
    compare(unsigned x, unsigned y)
    {
        return _type == HeapType::MIN ? a[x] - a[y] : a[y] - a[x];
    }

private:
    HeapType _type;
    int _n;
    int _heapsize;
    T* a;
    unsigned _heapify_count = 0;
};

int
main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    string type;
    int n;

    for (int i = 0; i < 3; ++i) {
        fin >> type >> n;

        if (type == "int") {

            int k;

            heap<int>* h = new heap<int>(HeapType::MIN, n * 10);
            for (int j = 0; j < n; ++j) {
                fin >> k;
                h->insert(k);
            }

            h->heapsort(fout);

            delete h;
        } else if (type == "char") {
            char* keys = new char[n];

            for (int j = 0; j < n; ++j) {
                fin >> keys[j];
            }

            heap<char>* h = new heap<char>(HeapType::MIN, keys, n + 1);

            h->heapsort(fout);

            delete h;
            delete[] keys;
        } else if (type == "bool") {
            bool* keys = new bool[n];

            for (int j = 0; j < n; ++j) {
                fin >> keys[j];
            }

            heap<bool>* h = new heap<bool>(HeapType::MIN, keys, n + 1);

            h->heapsort(fout);

            delete h;
            delete[] keys;
        } else if (type == "double") {
            double* keys = new double[n];

            for (int j = 0; j < n; ++j) {
                fin >> keys[j];
            }

            heap<double>* h = new heap<double>(HeapType::MIN, keys, n + 1);

            h->heapsort(fout);

            delete h;
            delete[] keys;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
