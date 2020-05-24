#include<iostream>

using namespace std;

template<typename T>
struct node {
    T value;
    node<T>* next;
};

template<class T>
class stack {
public:
    stack() : _head{nullptr} {}

    ~stack() {
        auto iter = _head;
        while(iter) {
            delete iter;
            iter = iter->next;
        }
    }

    stack<T>* push(T val) {

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
        _head = elem->next;

        return elem;
    }

    void print() {
        auto iter = _head;
        while(iter) {
            cout << iter->value << ' ';
            iter = iter->next;
        }
        cout << endl;
    }
private:
    node<T>* _head;
};

int main() {
    stack<int>* s = new stack<int>();

    s->pop();
    s->push(4)->push(2)->push(8);
    s->print();
    auto e = s->pop();
    if(e)
        cout << e->value << endl;
    s->push(1);
    s->print();

    delete s;
    return 0;
}
