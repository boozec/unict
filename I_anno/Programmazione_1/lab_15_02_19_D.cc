#include<iostream>
#include<stdexcept>
#define DIM 50

using namespace std;

class A {
public:
	A(short m, short k) : len{m} {
		ptr = new int[len];
		srand(time(NULL));
		
		for(int i = 0; i < len; ++i) {
			ptr[i] = rand()%k + 1;
		}
	}

	~A() {
		delete ptr;
	}

	virtual double const f() = 0;
	void print(ostream& os) {
		os << typeid(*this).name() << ", ptr=[ ";
		for(int i = 0; i < len; ++i)
			os << ptr[i] << ' ';

		os << "]";
	}

	int get(short i) {
		if(i >= len)
			throw out_of_range{"out of range"};

	 	return ptr[i];
	}

	short getLen() {
		return len;
	}

	int& operator[](int x){ 
		return ptr[x];
	}

	const int& operator[](int x) const { 
		return ptr[x];
	}
	
private:
	int* ptr;
	short len;

};

class B : public A {
public:
	B(short m, short k, double y) : A{m, k}, p{y} {}
	double const f() {
		int sum{};
		for(int i = 0; i < getLen(); ++i) {
			int t = get(i);

			if((t%2) == 0) {
				sum+=t;
			}
		}

		if(sum == 0)
			return 0;

		return static_cast<double>(sum/p);
	}

	void print(ostream& os) {
		A::print(os);
		os << ", p=" << p;
	}
private:
	double p;
};

class C : public A {
public:
	C(short n, short k, char c) : A{n, k}, x{c} {}

	double const f() {
		int sum{};
		short c{};
		for(int i = 0; i < getLen(); ++i) {
			int t = get(i);

			if((t%2) == 1) {
				sum+=t;
				++c;
			}
		}

		if(c == 0)
			return 0;

		return static_cast<double>(sum/c);
	}

	string const g(char c) {
		string t{""};
		t+=x;
		t+=c;

		return t;
	}

	void print(ostream& os) {
		A::print(os);
		os << ", x=" << x;
	}
private:
	char x;
};

ostream& operator<<(ostream& os, A& a) {
	a.print(os);

	return os;
}

int main() {
	srand(111222333);
    A *vett[DIM];

	string conc{""};
    for(int i=0; i<DIM; i++){
		short n=1+rand()%10;
		short m = 1+rand()%15;
		if(rand()%2==0)
	 	 	vett[i]= new B(n, m, rand()/(double) RAND_MAX+0.05);
		else {
	  		vett[i]= new C(n, m, (char) (rand()%('z' - 'a' + 1) + 'a'));
			auto cpnt = dynamic_cast<C*>(vett[i]);
			conc+=cpnt->g('h');
		}
	}

	double sum{};
    for(int i = 0; i < DIM; i++) {
		auto fval = vett[i]->f();
		cout << i << ") " << *(vett[i]) << ", f()=" << fval << endl; 
		sum+=fval;
	}
	
	cout << "PUNTO 2:\n\tavg(f())=" << sum/DIM << ", g('h')=" << conc << endl;
	cout << "PUNTO 3:\n";
	cout << (*(vett[0])).get(0) << endl;
	(*(vett[0]))[0] = 24;
	cout << (*(vett[0])).get(0) << endl;

	
	return 0;
}
