#include<iostream>
#include<stdexcept>
#include<cstdlib>
#include<cmath>
#define DIM 50

using namespace std;

class A {
public:
	A(short m) : len{m} {
		arr = new short[m];
		srand(time(NULL));
		for(int i = 0; i < m; ++i) {
			arr[i] = rand()%10+1;
		}
	}

	~A() {
		delete[] arr;
	}

	virtual double f(short a) = 0;	
	virtual void print(ostream& os) = 0;

	short getLen() {
		return len;
	}

protected:
	short get(short i) {
		if(i < 0 || i >= getLen())
			throw out_of_range{"out of arr' range"};

		return arr[i];
	}

private:
	short* arr;
	short len;
};

template<typename T>
class B : public A {
public:
	B(short m, char c) : A{m} {
		if(typeid(T) == typeid(char)) {
			x = c;
		} else if(typeid(T) == typeid(string)) {
			for(int i = 0; i < m; ++i) 
				x+=c;

		} else {
			// tipo non gestito
			throw bad_typeid{}; 
		}
	}
	
	double f(short a) override {
		double n = static_cast<double>(getLen() - a);
		double sum{};
		for(int i = a; i < getLen(); ++i) 
			sum+=get(i);
		
		return sum/n;
	}

	void print(ostream& os) override {
		os << "B<" << (typeid(T) == typeid(char) ? "char" : "string") << "> arr=[";
		for(int i = 0; i < getLen(); ++i)
			os << get(i) << ' ';
		os << "], x=" << x;
	}

	double foo(short s) {
		return log(s) + sin(f(s));
	}
private:
	T x;
};

class C : public A {
public:
	C(short n, int k) : A{n}, y{k} {}

	double f(short a) override {
		srand(time(NULL));
		short rand_elem = get(rand()%getLen());
		
		return static_cast<double>(a+y)/static_cast<double>(rand_elem);
	}

	double g(short w) {
		// sicuri che non debba convertire a double? qui sarà sempre 0, forse 1
		return static_cast<double>(sin(w+y));
	}

	void print(ostream& os) override {
		os << "C arr=[";
		for(int i = 0; i < getLen(); ++i)
			os << get(i) << ' ';
		os << "], y=" << y;
	}

	C& operator++() {
		++y;
		return *this;
	}
private:
	int y;
};

ostream& operator<<(ostream& os, A& a) {
	a.print(os);

	return os;
} 

int main() {
	srand(111222333);

	A *vett[DIM];

	double max_f3{-100000000.0};
	short c_count{};
	double gsum{};
	short i_to_p{-1};
	
	for(int i=0; i<DIM; i++) {
		short n=1+rand()%10;
		switch(rand()%3) {
		case 0: 
		{
			vett[i]= new C(n, rand()%10 + 1);
			i_to_p = i;
			auto cref = dynamic_cast<C&>(*(vett[i]));
			gsum+=cref.g(5);
			++c_count;
	    	break;
	  	}
		case 1:
	    	vett[i]= new B<string>(n, rand()%('z' - 'a' + 1) + 'a');
	    	break;
	  	case 2: 
	    	vett[i]= new B<char>(n, rand()%('z' - 'a' + 1) + 'a');
		}

		auto f3 = vett[i]->f(3);
		if(f3 > max_f3)
			max_f3 = f3;
    }

	for(int i = 0; i < DIM; ++i)
		cout << i+1 << ')' << *(vett[i]) << ", f(3)=" << vett[i]->f(3) << endl;

	cout << "max f(3)=" << max_f3;
	cout << " avg g(5)=" << (static_cast<double>(gsum/c_count)) << endl;
	if(i_to_p >= 0) {
		cout << *(vett[i_to_p]) << endl;
		auto cref = dynamic_cast<C*>(vett[i_to_p]);
		++(*cref);
		cout << *(vett[i_to_p]) << endl;
	}
	
	return 0;
}
