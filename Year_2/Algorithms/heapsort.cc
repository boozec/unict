#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum class HeapType {
    Min,
    Max
};

template <typename H>
class Heap {
public:
    Heap(HeapType type, int n)
        : n_ { n + 1 }
        , type_ { type }
    {
        a_ = new H[n + 1];
        a_[0] = 0;
    }

    ~Heap()
    {
        delete[] a_;
    }

    void
    heapify(int i)
    {
        if (heapsize_ >= 1)
            count_++;

        int l = left(i);
        int r = right(i);
        int max = i;

        if (l <= heapsize_ && !compare(l, i))
            max = l;
        if (r <= heapsize_ && !compare(r, max))
            max = r;

        if (max != i) {
            swap(a_[i], a_[max]);
            heapify(max);
        }
    }

    void
    build(H aux[], int n)
    {
        a_ = aux;
        heapsize_ = n;

        for (int i = heapsize_ / 2; i > 0; --i) {
            heapify(i);
        }
    }

    H
    extract()
    {
        swap(a_[1], a_[heapsize_]);
        heapsize_--;
        heapify(1);

        return a_[heapsize_ + 1];
    }

    inline int
    left(int i)
    {
        return i << 1;
    }
    inline int
    right(int i)
    {
        return (i << 1) | 1;
    }

    void
    sort(ostream& out)
    {
        H* b = new H[heapsize_ + 1];

        int n = heapsize_;

        for (unsigned i = n; i > 0; --i) {
            b[i] = extract();
        }
        out << count_ << ' ';
        for (unsigned i = 1; i < n_; ++i) {
            out << b[i] << ' ';
        }
        out << endl;

        delete[] b;
    }

private:
    H* a_;
    int heapsize_ { 0 };
    int n_;
    HeapType type_;
    int
    compare(int i, int j)
    {
        return (type_ == HeapType::Min) ? a_[i] < a_[j] : a_[j] > a_[i];
    }
    int count_ { 0 };
};

int
main(int argc, char** argv)
{
    int n = (argc > 1) ? stoi(argv[1]) : 100;
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    string t;
    int m;

    for (int i = 0; i < n; ++i) {
        fin >> t >> m;

        if (t == "int") {
            Heap<int>* pq = new Heap<int>(HeapType::Max, m);
            int* k = new int[m + 1];

            k[0] = 0;
            for (int j = 1; j <= m; ++j) {
                fin >> k[j];
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "double") {
            Heap<double>* pq = new Heap<double>(HeapType::Max, m);
            double* k = new double[m + 1];

            k[0] = 0;
            for (int j = 1; j <= m; ++j) {
                fin >> k[j];
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "bool") {
            Heap<bool>* pq = new Heap<bool>(HeapType::Max, m);
            bool* k = new bool[m + 1];

            k[0] = 0;
            for (int j = 1; j <= m; ++j) {
                fin >> k[j];
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "char") {
            Heap<char>* pq = new Heap<char>(HeapType::Max, m);
            char* k = new char[m + 1];

            k[0] = 0;
            for (int j = 1; j <= m; ++j) {
                fin >> k[j];
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
