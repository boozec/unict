#include<iostream>
#include<cmath>
#include<typeinfo>

#define DIM 30

using namespace std;

class A {
public:
    A(short m, int a, int b) : len(m) {
        srand(time(NULL));
        vec = new int[m];
        
        for(int i = 0; i < m; ++i) {
            vec[i] = rand()%b + a;
        }
    }

    ~A() {
        delete vec;
    }

    virtual double foo(short a) = 0;
    short getLen() {
        return len;
    }

    virtual void print(ostream& o) = 0;

    int operator()(int i1, int i2) {
        if(i1 < 0) i1 = 0;
        if(i2 > len) i2 = len;

        int sum = 0;
        
        for(int i = i1; i < i2; ++i) {
            sum+=vec[i];
        }

        return sum;
    }
    
protected:
    int get(short i) {
        return vec[i];
    }
private:
    int* vec;
    short len;
};

class B : public A {
public:
    B(short m, int x, int y) : A(m, x, y) {
        srand(time(NULL));
        short rand_num = rand()%m;
        p = get(rand_num);
    }
    
    double foo(short a) {
        return static_cast<double>(prod(a)) / static_cast<double>(p);
    }

    void print(ostream& os) {
        os << "vec=[";
        for(int i = 0; i < getLen(); ++i) {
            os << get(i) << ' ';
        }
        os << "], p=" << p;
    }
protected:
    int prod(short s) {
        int index = s%getLen();
        int _prod = 1;
        for(int i = index; i < getLen(); ++i) {
            _prod *= get(i);
        }

        return _prod;
    }
private:
    int p;
};


template<class T> class C : public A {
public:
    C(short n, int a, int b) : A(n, a, b) {
        if(typeid(T) == typeid(short)) {
            x = n;
        } else {
            x = log(1+pow(sin(n), 2));
        }

    }
    
    double foo(short r) {
        return g(r);
    }

    T g(T k) {
        return 2*x*(k+1);
    }

    void print(ostream& os) {
        os << "vec=[";
        for(int i = 0; i < getLen(); ++i) {
            os << get(i) << ' ';
        }
        os << "], x=" << x;
    }
private:
    T x;
};

ostream& operator<<(ostream& os, A& a) {
    os << typeid(a).name() << ", ";
    a.print(os);
    return os;
}

int main() {
    srand (time(0)); 
    A* vett[DIM];
    double sum_cd = 0;
    short num_cd = 0;
    for(int i=0; i < DIM; ++i) {
        short n = 1+rand()%10;
        switch ( rand ()%3) {
        case 0:
            vett[i]= new B(n, rand()%5 + 1, rand()%10 + 5);
            break ;
        case 1: {
            vett[i]= new C<double>(n, rand()%5 + 1, rand()%10 + 5); 
            ++num_cd;
            C<double>& cc = dynamic_cast<C<double>& >(*(vett[i]));
            sum_cd += cc.g(5);
            
            break ;
        }
        case 2:
            vett[i]= new C<short>(n, rand()%5 + 1, rand()%10 + 5);
        }
    }

    double max_foo = -100000;

    for(int i = 0; i < DIM; ++i) {
        auto foo3 = vett[i]->foo(3);

        if(foo3 > max_foo) {
            max_foo = foo3;
        }
        cout << (*(vett[i])) << ", foo(3)=" << foo3 <<endl;
    }
    
    // max_foo => Valore maggiore calcolato per foo(3)
    // sum_cd / num_cd => media valori g(5) per C<Double> 
    
    cout << (*vett[0])(0, 2) << endl;

    return 0;
}
