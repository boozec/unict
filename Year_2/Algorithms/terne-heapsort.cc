#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

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
        a_ = new tuple<H, H, H>[n + 1];
        a_[0] = { 0, 0, 0 };
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

        if (l <= heapsize_ && compare(l, max))
            max = l;
        if (r <= heapsize_ && compare(r, max))
            max = r;

        if (max != i) {
            swap(a_[i], a_[max]);
            heapify(max);
        }
    }

    void
    build(tuple<H, H, H> aux[], int n)
    {
        a_ = aux;
        heapsize_ = n;

        for (int i = heapsize_ / 2; i > 0; --i) {
            heapify(i);
        }
    }

    tuple<H, H, H>
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
        tuple<H, H, H>* b = new tuple<H, H, H>[heapsize_ + 1];

        int n = heapsize_;

        for (unsigned i = n; i > 0; --i) {
            b[i] = extract();
        }
        out << count_ << ' ';
        for (unsigned i = 1; i < n_; ++i) {
            out << "(" << get<0>(b[i]) << ' ' << get<1>(b[i]) << ' ' << get<2>(b[i]) << ")" << ' ';
        }
        out << endl;

        delete[] b;
    }

private:
    tuple<H, H, H>* a_;
    int heapsize_ { 0 };
    int n_;
    HeapType type_;

    bool
    compare(int i, int j)
    {
        auto ai1 = get<0>(a_[i]);
        auto ai2 = get<1>(a_[i]);
        auto ai3 = get<2>(a_[i]);
        auto aj1 = get<0>(a_[j]);
        auto aj2 = get<1>(a_[j]);
        auto aj3 = get<2>(a_[j]);
        return (type_ == HeapType::Max) ? ai1 > aj1 || (ai1 == aj1 && ai2 > aj2) || (ai1 == aj1 && ai2 == aj2 && ai3 > aj3)
                                        : ai1 < aj1 || (ai1 == aj1 && ai2 < aj2) || (ai1 == aj1 && ai2 == aj2 && ai3 < aj3);
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
    string ch;

    for (int i = 0; i < n; ++i) {
        fin >> t >> m;

        if (t == "int") {
            Heap<int>* pq = new Heap<int>(HeapType::Max, m);
            tuple<int, int, int>* k = new tuple<int, int, int>[m + 1];

            k[0] = { 0, 0, 0 };
            int x1, x2, x3;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = stoi(ch.substr(1, ch.length()));
                fin >> ch;
                x2 = stoi(ch);
                fin >> ch;
                x3 = stoi(ch.substr(0, ch.length() - 1));
                k[j] = { x1, x2, x3 };
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "double") {
            Heap<double>* pq = new Heap<double>(HeapType::Max, m);
            tuple<double, double, double>* k = new tuple<double, double, double>[m + 1];

            k[0] = { 0, 0, 0 };
            double x1, x2, x3;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = stod(ch.substr(1, ch.length()));
                fin >> ch;
                x2 = stod(ch);
                fin >> ch;
                x3 = stod(ch.substr(0, ch.length() - 1));
                k[j] = { x1, x2, x3 };
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "bool") {
            Heap<bool>* pq = new Heap<bool>(HeapType::Max, m);
            tuple<bool, bool, bool>* k = new tuple<bool, bool, bool>[m + 1];

            k[0] = { 0, 0, 0 };
            bool x1, x2, x3;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = stoi(ch.substr(1, ch.length()));
                fin >> ch;
                x2 = stoi(ch);
                fin >> ch;
                x3 = stoi(ch.substr(0, ch.length() - 1));
                k[j] = { x1, x2, x3 };
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "char") {
            Heap<char>* pq = new Heap<char>(HeapType::Max, m);
            tuple<char, char, char>* k = new tuple<char, char, char>[m + 1];

            k[0] = { 0, 0, 0 };
            char x1, x2, x3;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = ch[1];
                fin >> x2;
                fin >> ch;
                x3 = ch[0];
                k[j] = { x1, x2, x3 };
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
