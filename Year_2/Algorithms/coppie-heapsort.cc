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
        a_ = new pair<H, H>[n + 1];
        a_[0] = { 0, 0 };
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
    build(pair<H, H> aux[], int n)
    {
        a_ = aux;
        heapsize_ = n;

        for (int i = heapsize_ / 2; i > 0; --i) {
            heapify(i);
        }
    }

    pair<H, H>
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
        pair<H, H>* b = new pair<H, H>[heapsize_ + 1];

        int n = heapsize_;

        for (unsigned i = n; i > 0; --i) {
            b[i] = extract();
        }
        out << count_ << ' ';
        for (unsigned i = 1; i < n_; ++i) {
            out << "(" << b[i].first << ' ' << b[i].second << ")" << ' ';
        }
        out << endl;

        delete[] b;
    }

private:
    pair<H, H>* a_;
    int heapsize_ { 0 };
    int n_;
    HeapType type_;

    bool
    compare(int i, int j)
    {
        return (type_ == HeapType::Max) ? a_[i].first > a_[j].first || (a_[i].first == a_[j].first && a_[i].second > a_[j].second)
                                        : a_[j].first > a_[i].first || (a_[j].first == a_[i].first && a_[j].second > a_[i].second);
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
            pair<int, int>* k = new pair<int, int>[m + 1];

            k[0] = { 0, 0 };
            int x1, x2;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = stoi(ch.substr(1, ch.length()));
                fin >> ch;
                x2 = stoi(ch.substr(0, ch.length() - 1));
                k[j] = { x1, x2 };
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "double") {
            Heap<double>* pq = new Heap<double>(HeapType::Max, m);
            pair<double, double>* k = new pair<double, double>[m + 1];

            k[0] = { 0, 0 };
            double x1, x2;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = stod(ch.substr(1, ch.length()));
                fin >> ch;
                x2 = stod(ch.substr(0, ch.length() - 1));
                k[j] = { x1, x2 };
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "bool") {
            Heap<bool>* pq = new Heap<bool>(HeapType::Max, m);
            pair<bool, bool>* k = new pair<bool, bool>[m + 1];

            k[0] = { 0, 0 };
            bool x1, x2;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = stoi(ch.substr(1, ch.length()));
                fin >> ch;
                x2 = stoi(ch.substr(0, ch.length() - 1));
                k[j] = { x1, x2 };
            }
            pq->build(k, m);

            pq->sort(fout);

            delete pq;
        } else if (t == "char") {
            Heap<char>* pq = new Heap<char>(HeapType::Max, m);
            pair<char, char>* k = new pair<char, char>[m + 1];

            k[0] = { 0, 0 };
            char x1, x2;
            for (int j = 1; j <= m; ++j) {
                fin >> ch;
                x1 = ch[1];
                fin >> ch;
                x2 = ch[0];
                k[j] = { x1, x2 };
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
