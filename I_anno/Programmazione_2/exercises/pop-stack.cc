#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class node {
public:
    node(T key, node<T>* next) : _key{key}, _next{next} {}
    node(T key) : _key{key}, _next{nullptr} {}
    const T& key() const { return _key; }
    T& key() { return _key; }
    const node<T>*& next() const { return _next; }
    node<T>*& next() { return _next; }
private:
    T _key;
    node<T>* _next;
};

template<class T>
class Pila {
public:
    Pila() : _head{nullptr}{}
    ~Pila() {

    }
    Pila<T>* push(T val) {
        if(!_head) {
            _head = new node<T>{val, nullptr};
        } else {
            _head = new node<T>{val, _head};
        }

        return this;
    }
    node<T>* pop() {
        if(!_head) return nullptr;
        node<T>* elem = _head;
        delete _head;
        _head = elem->next();

        return elem;
    }

    bool is_empty() { return _head == nullptr; }
private:
    node<T>* _head;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        string t;
        int n;
        in >> t;
        switch(t.at(0)) {
        case 'b': {
            Pila<bool>* stack = new Pila<bool>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    stack->push(s.at(1) - '0');
                } else {
                    stack->pop();
                }
            }
            while(!stack->is_empty())
                out << stack->pop()->key() << ' ';
            out << endl;
            break;
        }
        case 'd': {
            Pila<double>* stack = new Pila<double>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    stack->push(stod(s.substr(1, s.length()-1)));
                } else {
                    stack->pop();
                }
            }
            while(!stack->is_empty())
                out << stack->pop()->key() << ' ';
            out << endl;
            break;
        }
        case 'c': {
            Pila<char>* stack = new Pila<char>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    stack->push(s.at(1));
                } else {
                    stack->pop();
                }
            }
            while(!stack->is_empty())
                out << stack->pop()->key() << ' ';
            out << endl;
            break;
        }
        case 'i': {
            Pila<int>* stack = new Pila<int>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    stack->push(stoi(s.substr(1, s.length()-1)));
                } else {
                    stack->pop();
                }
            }
            while(!stack->is_empty())
                out << stack->pop()->key() << ' ';
            out << endl;
            break;
        }
        }
    }
    in.close();
    out.close();
    return 0;
}
