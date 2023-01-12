#include <fstream>
#include <iostream>

using namespace std;

template <class H>
class min_heap {
public:
    inline int
    compare(unsigned a, unsigned b)
    {
        return arr_[a] - arr_[b];
    }

    void
    swap(unsigned i, unsigned j)
    {
        auto t = arr_[i];
        arr_[i] = arr_[j];
        arr_[j] = t;
    }

    min_heap<H>*
    enqueue(H key)
    {
        if (heapsize_ == length_)
            return this;

        arr_[++heapsize_] = key;

        unsigned i = heapsize_;

        while (i > 1 && compare(i >> 1, i) > 0) {
            swap(i, i >> 1);
            i >>= 1;
        }

        return this;
    }

    void
    show(ostream& out)
    {
        out << count_ << ' ';
        for (unsigned i = 1; i <= heapsize_; ++i) {
            out << arr_[i] << ' ';
        }
        out << endl;
    }

    void
    heapify(unsigned i)
    {
        if (heapsize_ < 1)
            return;

        count_++;
        auto l = i << 1;
        auto r = l | 1;

        auto min = i;

        if (l <= heapsize_ && compare(l, min) < 0)
            min = l;
        if (r <= heapsize_ && compare(r, min) < 0)
            min = r;

        if (min != i) {
            swap(i, min);
            heapify(min);
        }
    }

    H
    extract()
    {
        if (heapsize_ < 1)
            return 0;

        swap(1, heapsize_);
        --heapsize_;
        heapify(1);
        return arr_[heapsize_ + 1];
    }

    ~min_heap()
    {
        delete arr_;
    }

    min_heap()
        : heapsize_ { 0 }
    {
        length_ = 200;
        arr_ = new H[length_];
    }

private:
    H* arr_;
    unsigned length_ { 0 };
    unsigned heapsize_ { 0 };
    unsigned count_ { 0 };
};

template <typename H>
void
parse(min_heap<H>* heap, char typ, ifstream& fin, short act_nums)
{
    string s;
    string v;
    for (unsigned i = 0; i < act_nums; ++i) {
        fin >> s;
        if (s.at(1) == 'x') {
            heap->extract();
        } else {
            v = s.substr(2, s.length());

            if (typ == 'i')
                heap->enqueue(stoi(v));
            else if (typ == 'd')
                heap->enqueue(stod(v));
            else if (typ == 'b')
                heap->enqueue(v == "1" ? true : false);
            else if (typ == 'c')
                heap->enqueue(v[0]);
        }
    }
}

int
main(int argc, char** argv)
{
    int n = (argc > 1) ? atoi(argv[1]) : 100;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string typ;
    short actions;

    for (int i = 0; i < n; ++i) {
        fin >> typ;
        fin >> actions;

        if (typ == "int") {
            min_heap<int>* mh = new min_heap<int>();

            parse(mh, 'i', fin, actions);

            mh->show(fout);
            delete mh;
        } else if (typ == "double") {
            min_heap<double>* mh = new min_heap<double>();

            parse(mh, 'd', fin, actions);

            mh->show(fout);
            delete mh;
        } else if (typ == "bool") {
            min_heap<bool>* mh = new min_heap<bool>();

            parse(mh, 'b', fin, actions);

            mh->show(fout);
            delete mh;
        } else if (typ == "char") {
            min_heap<char>* mh = new min_heap<char>();

            parse(mh, 'c', fin, actions);

            mh->show(fout);
            delete mh;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
