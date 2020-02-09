#include<iostream>
#include<cmath>
#include<set>
#define DIM 10

using namespace std;

class A {
public:
	A(short m) : len{m} {
		srand(time(NULL));
		base = new char[len];
		for(int i = 0; i < len; ++i) {
			base[i] = rand()%('z'-'a'+1)+'a';
		}
	}

	~A() {
		delete base;
	}

	short getLen() {
		return len;
	}

	virtual string extract(short x) = 0;
	virtual void print(ostream& os) = 0;

protected:
	char get(short i) {
		return base[i];
	}

private:
	char* base;
	short len;
};

class B : public A {
public:
	B(short m, double p) : A{m} {
		for(int i = 0; i < m; ++i) {
			switch(get(i)) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				str+=get(i);
			}
		}
	}

	double foo(short s) {
		return sin(k+s)/log(s+1);
	}

	string extract(short x) override {
		string x2{""};
		short inserted{};
		set<char> chars_a;
		for(int i = 0; i < getLen(); ++i)
			chars_a.insert(get(i));

		while(inserted < x) {
			char r_char = rand()%('z'-'a'+1)+'a';
			if(chars_a.find(r_char) != chars_a.end()) {
				x2+=r_char;
				++inserted;
			}			
		}

		return x2;
	}

	void print(ostream& os) override {
		os << "B: base=[";
		for(int i = 0; i < getLen(); ++i) {
			os << get(i) << ' ';
		}
		os << "], str=" << str << ", k=" << k;
	}
	
private:
	string str;
	double k;
};

class C : public A {
public:
	C(short n, int k) : A{n}, y{k} {}

	double g(short w) {
		return sin(w+y);
	}

	string extract(short x) override {
		string x2{""};
		char* narr = new char[x];
		short counter_narr{};

		for(int i = 0; i < getLen(); ++i) {
			switch(get(i)) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				break;
			default:
				narr[counter_narr++] = get(i);
			}
		}
		for(int i = 0; i < x; ++i)
			x2+=narr[i];

		delete[] narr;

		return x2;
	}	

	void print(ostream& os) override {
		os << "C: base=[";
		for(int i = 0; i < getLen(); ++i) {
			os << get(i) << ' ';
		}
		os << "], y=" << y;
	}

	C operator++(int) {
		C temp{*this};
		
		y++;

		return temp;
	}
private:
	int y;
};

ostream& operator<<(ostream& os, A& a) {
	a.print(os);

	return os;
}

int main() {
	A *vett[DIM];

	double sum{};
	short i_c{-1};
	for(int i=0; i<DIM; i++) {
		short n=10+rand()%10;
		switch(rand()%2){
	  	case 0: {
	    	vett[i]= new C(n, rand()%20 + 1);
			auto cref = dynamic_cast<C*>(vett[i]);
			sum+=cref->g(5);
			i_c = i;
	    	break;
	  	}
		case 1: {
	   	 	vett[i]= new B(n, rand()/(double) RAND_MAX);
			auto bref = dynamic_cast<B*>(vett[i]);
			sum+=bref->foo(5);
	    	break;
		}
		}
    }

	for(int i=0; i<DIM; i++) 
		cout << *(vett[i]) << ", extract(3)=" << vett[i]->extract(3) <<  endl;

	cout << sum/DIM << endl;

	if(i_c >= 0) {
		cout << *vett[i_c] << endl;
		auto cref = dynamic_cast<C*>(vett[i_c]);
		(*cref)++;
		cout << *vett[i_c] << endl;
		

	}
	return 0;
}
