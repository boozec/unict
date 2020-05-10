#include<iostream>

using namespace std;

template<typename T>
struct node {
    T value;
    node<T>* next;
};

template<class T>
class queue {
public:
    queue() : _head{nullptr} {}
    ~queue() {
        auto iter = _head;
        while(iter) {
            delete iter;
            iter = iter->next;
        }
    }
    queue<T>* enqueue(T val) {

        if(!_head) {
            _head = new node<T>{val, nullptr};
            _tail = _head;
        } else {
            _tail->next = new node<T>{val, nullptr};
            _tail = _tail->next;
        }

        return this;
    }

    queue<T>* dequeue() {
        auto iter = _head;

        if(!_head) return this;
        while(iter->next != _tail) {
            iter = iter->next;
        }

        delete iter->next;
        iter->next = nullptr;
        _tail = iter;

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
    node<T>* _tail;
    node<T>* _head;
};

int main() {
    queue<int>* q = new queue<int>();

    q->dequeue();
    q->enqueue(4)->enqueue(2)->enqueue(8);
    q->dequeue();
    q->enqueue(1);
    q->print();

    delete q;
    return 0;
}
