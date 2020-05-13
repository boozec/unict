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

    stack<T>* pop() {
        if(!_head) return this;

        auto old_head = _head;
        _head = _head->next;
        delete old_head;

        return this;
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
    s->pop();
    s->push(1);
    s->print();

    delete s;
    return 0;
}
