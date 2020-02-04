#include<iostream>
#include<cmath>
#define DIM 30

using namespace std;

class A {
protected:
	double* ptr;
	short len;

	void getPtr(ostream& os) {
		os << "ptr=[";
		for(int i = 0; i < len; ++i) { 
			os << ptr[i] << ' ';
		}

		os << "]";
	}
public:
	A(short n) : len{n} {
		srand(time(NULL));
		ptr = new double[n];
		for(int i = 0; i < n; ++i) {
			ptr[i] = (double) rand() / RAND_MAX;
		}
	}

	~A() {
		delete ptr;
	}
	virtual double foo(short a) const = 0;
	virtual void print(ostream& os) = 0;

	double operator[](int i) {
		return ptr[i];
	}
};

class B : public A {
public:
	B(short m, double s) : A{m}, alpha{s} {}
	double foo(short b) const {
		return static_cast<double>(log(1+extract(b)));
	}
	void print(ostream& os) {
		os << "B, ";
		getPtr(os);
		os << ", alpha=" << alpha;
	}

private:
	double alpha;
	double extract(short s) const {
		return (ptr[s%len]+alpha)/2;
	}

};

template<typename T>
class C;

template<>
class C<double> : public A {
public:
	C(short n) : A{n} {
		x = static_cast<double>(log(1+n));
	}

	double foo(short r) const {
		return g(r*x);
	}

	double g(double k) const {
		return 3*k;
	}

	void print(ostream& os) {
		os << "C<double> ";
		getPtr(os);
		os << ", x=" << x;
	}
private:
	short x;
};

template<>
class C<int> : public A {
public:
	C(short n) : A{n} {
		x = g(n);
	}

	double foo(short r) const {
		return g(r*x);
	}

	short g(short k) const {
		return 3*k;
	}

	void print(ostream& os) {
		os << "C<short> ";
		getPtr(os);
		os << ", x=" << x;
	}
private:
	short x;
};

ostream& operator<<(ostream& os, A& a) {
	a.print(os);

	return os;
}

int main() {
	srand(328832748);
	A* vett[DIM];
	double maxfoo{-11111111.0};
	double g_sum{};
	for(int i=0; i<DIM; i++) {
		short n=1+rand()%5;
		switch(rand()%3) {
			case 0: vett[i]= new B(n, n/100.0); break;
			case 1: {
				vett[i]= new C<double>(n);
				auto refC = dynamic_cast<C<double>*>(vett[i]);
				g_sum+=refC->g(5);
				break;
			}
			case 2: vett[i]= new C<int>(n);

		}

		double foo5 = vett[i]->foo(5);
		if(foo5 > maxfoo)
			maxfoo = foo5;
	}

	for(int i = 0; i < DIM; ++i) {
		cout << i+1 << ")" << *(vett[i]) << ", foo(5)=" << vett[i]->foo(5) << endl;
	}

	cout << "max(foo(5))=" << maxfoo << " sum(g(5))=" << g_sum << endl;
	cout << (*vett[2])[0] << endl;

	return 0;
}
