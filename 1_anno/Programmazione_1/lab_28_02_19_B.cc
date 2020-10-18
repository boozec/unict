#include<iostream>
#include<cstdlib>
#include<cmath>
#define DIM 50
using namespace std;

class A {
public:
	A(short m, char c) : len{m} {
		ptr = new char[len];
		srand(time(NULL));
		for(int i = 0; i < m; ++i) {
			ptr[i] = static_cast<char>(rand()%(c-'a'+1) + 'a');
		}
	}
	A(const A& a) = default;
	~A() {
		delete ptr;
	}

	virtual string elab(short a, char c) = 0;
	virtual void print(ostream& o) = 0;
	short getLen() {
		return len;
	}

	char& operator[](int i) {
		return ptr[i];
	}

protected:
	char get(short i) {
		if(i > len)
			return ptr[0];

		return ptr[i];
	}

private:
	char* ptr;
	short len;
};

class B : public A {
public:
	B(short m, double y, char c) : A{m, c}, x{y} {}
	double foo(short s) {
		return sin(x+s)/log(x+s);
	}

	string elab(short a, char c) {
		string st{};
		for(int i = 0; i < getLen(); ++i) {
			auto ch = get(i);
			if(abs(ch-c) <= a) {
				st+=ch;
			}
		}

		return st;
	}

	void print(ostream& os) {
		os << "B ptr=[";
		for(int i = 0; i < getLen(); ++i) 
			os << get(i) << ' ';

		os << "], x=" << x << ", elab(5, z)=" << elab(5, 'z');
	}

private:
	double x;
};

template<typename T>
class C : public A {
public:
	C(short n, double k, char c) : A{n, c} {
		if(typeid(T) == typeid(short))
			y = static_cast<int>(100*k);
		else
			y = k;
	}

	string elab(short a, char c) {
		string st{};
		if(getLen() >= a) {
			if(a >= 1) {
				for(int i = 0; i < getLen(); st+=c, ++i);
			}
		} else {
			for(int i = 0; i < getLen(); st += get(i++));
		}

		return st;
	}

	double g(short w) {
		return sin(w+y);
	}
	
	void print(ostream& os) {
		os << "C<" << typeid(T).name() << "> ptr=[";
		for(int i = 0; i < getLen(); ++i) 
			os << get(i) << ' ';

		os << "], y=" << y << ", elab(5, z)=" << elab(5, 'z');
	}
private:
	T y;
};

ostream& operator<<(ostream& os, A& a) {
	a.print(os);

	return os;
}

int main() {
	srand(time(NULL));

	A *vett[DIM];
	short cb{}, cc{};
	double sumb{}, sumc{};

	for(int i=0; i<DIM; i++) {
  		short n=1+rand()%10;
    	switch(rand()%3) {
      	case 0: 
		{
        	vett[i]= new B(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
			auto temp = dynamic_cast<B&>(*(vett[i]));
			sumb+=temp.foo(5);
			++cb;
			break;
      	}
		case 1:
			vett[i]= new C<double>(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
			break;
      	case 2:
		{
			vett[i]= new C<short>(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
			auto temp = dynamic_cast<C<short>&>(*(vett[i]));
			sumc+=temp.g(5);
			++cc;
		}
      	}
	}

	for(int i=0; i<DIM; i++) {
		cout << *vett[i] << endl;
	}

	cout << "avg(foo(5))=" << sumb/cb << " "; 
	cout << "avg(g(5))=" << sumc/cc << endl; 

	cout << endl;
	cout << *vett[0] << endl;
	(*vett[0])[0] = '$';
	cout << *vett[0] << endl;
	return 0;
}
