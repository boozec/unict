
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
class Coda {
public:
    Coda() : _head{nullptr}, _tail{nullptr} {}
    ~Coda() {

    }
    Coda<T>* enqueue(T val) {
        if(!_head) {
            _head = new node<T>{val, nullptr};
            _tail = _head;
        } else {
            _tail->next() = new node<T>{val, nullptr};
            _tail = _tail->next();
        }

        return this;
    }
    node<T>* dequeue() {
        if(!_head) return nullptr;
        node<T>* elem = _head;
        delete _head;
        _head = elem->next();

        return elem;
    }

    bool is_empty() { return _head == nullptr; }
private:
    node<T>* _head;
    node<T>* _tail;
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
            Coda<bool>* queue = new Coda<bool>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    queue->enqueue(s.at(1) - '0');
                } else {
                    queue->dequeue();
                }
            }
            while(!queue->is_empty())
                out << queue->dequeue()->key() << ' ';
            out << endl;
            break;
        }
        case 'd': {
            Coda<double>* queue = new Coda<double>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    queue->enqueue(stod(s.substr(1, s.length()-1)));
                } else {
                    queue->dequeue();
                }
            }
            while(!queue->is_empty())
                out << queue->dequeue()->key() << ' ';
            out << endl;
            break;
        }
        case 'c': {
            Coda<char>* queue = new Coda<char>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    queue->enqueue(s.at(1));
                } else {
                    queue->dequeue();
                }
            }
            while(!queue->is_empty())
                out << queue->dequeue()->key() << ' ';
            out << endl;
            break;
        }
        case 'i': {
            Coda<int>* queue = new Coda<int>{};
            in >> n;
            string s;
            for(int i = 0; i < n; ++i) {
                in >> s;
                if(s.at(0) == 'i') {
                    queue->enqueue(stoi(s.substr(1, s.length()-1)));
                } else {
                    queue->dequeue();
                }
            }
            while(!queue->is_empty())
                out << queue->dequeue()->key() << ' ';
            out << endl;
            break;
        }
        }
    }
    in.close();
    out.close();
    return 0;
}

