#include<iostream>

using namespace std;

template<typename T>
struct node {
    T value;
    node* next;
};


template<typename T>
class list {
public:
    list() : _head{nullptr} {}

    ~list() {
        while(_head != nullptr) {
            node<T>* tmp = _head->next;
            delete tmp;
            _head = tmp;
        }
    }

    list* push_front(T val) {
        _head = new node<T>{val, _head};

        return this;
    }

    list* push_back(T val) {
        node<T>* iter = _head;
        if(_head == nullptr) {
            _head = new node<T>{val, nullptr};
        } else {
            while(iter->next != nullptr) {
                iter = iter->next;
            }
            iter->next = new node<T>{val, nullptr};
        }

        return this;
    }

    list* push_after_value(T val, T newval) {
        node<T>* iter = _head;
        while(iter && iter->value != val)
            iter = iter->next;

        if(iter == nullptr)
            return this->push_front(newval);

        iter->next = new node<T>{newval, iter->next};

        return this;
    }

    list* push_before_value(T val, T newval) {
        node<T>* iter = _head;

        while(iter && iter->next && iter->next->value != val)
            iter = iter->next;

        if(iter == nullptr)
            return this->push_front(newval);

        iter->next = new node<T>{newval, iter->next};

        return this;
    }

    void print() {
        node<T>* iter = _head;
        while(iter != nullptr) {
            cout << iter->value << ' ';
            iter = iter->next;
        }
    }
private:
    node<T>* _head;
};

int main() {
    list<double>* l = new list<double>{};
    l->push_front(2)->push_front(1.7);
    // 1.7 2

    l->push_back(5.2);
    // 2 1.7 5.2

    l->push_back(10.1)->push_back(15);
    // 2 1.7 5.2 10.1 15

    l->push_after_value(5.2, 6.4);
    // 2 1.7 5.2 6.4 10.1 15

    l->push_before_value(5.2, 4.1);
    // 2 1.7 4.1 5.2 6.4 10.1 15

    l->push_before_value(4.1, 3.0);
    // 2 1.7 3.0 4.1 5.2 6.4 10.1 15
    l->print();

    return 0;
}
