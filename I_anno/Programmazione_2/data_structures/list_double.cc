#include<iostream>

using namespace std;

template<typename T>
struct node {
    T value;
    node* prev;
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
        if(_head == nullptr) {
            _head = new node<T>{val, nullptr, nullptr};
        } else {
            _head = new node<T>{val, nullptr, _head};
            _head->next->prev = _head;
        }

        return this;
    }

    list* push_back(T val) {
        node<T>* iter = _head;
        if(_head == nullptr) {
            _head = new node<T>{val, nullptr, nullptr};
        } else {
            while(iter->next != nullptr) {
                iter = iter->next;
            }
            iter->next = new node<T>{val, iter, nullptr};
        }

        return this;
    }

    list* push_after_value(T val, T newval) {
        node<T>* iter = _head;
        while(iter && iter->value != val)
            iter = iter->next;

        if(iter == nullptr)
            return this->push_front(newval);

        node<T>* nod = new node<T>{newval, iter, iter->next};
        iter->next = nod;
        nod->next->prev = nod;

        return this;
    }

    list* push_before_value(T val, T newval) {
        node<T>* iter = _head;

        if(iter->value == val)
            return this->push_front(newval);

        while(iter && iter->next && iter->next->value != val)
            iter = iter->next;

        if(iter == nullptr)
            return this->push_front(newval);

        node<T>* nod = new node<T>{newval, iter, iter->next};
        iter->next = nod;
        nod->next->prev = nod;

        return this;
    }

    list* pop(int val) {
        if(_head == nullptr)
            return this;
        else if(_head->value == val) 
            return pop_front();

        node<T>* iter = _head;
        while(iter && iter->next && iter->next->value != val)
            iter = iter->next;

        node<T>* temp = iter->next;
        iter->next = iter->next->next;
        iter->next->prev = iter;
        delete temp;

        return this;
    }

    list* pop_front() {
        if(_head == nullptr)
            return this;

        node<T>* elem = _head;
        _head = _head->next;
        _head->prev = nullptr;
        delete elem;

        return this;
    }

    list* pop_back() {
        if(_head == nullptr)
            return this;

        node<T>* iter = _head;

        while(iter->next && iter->next->next) {
            iter = iter->next;
        }

        if(iter->next == nullptr) {
            delete iter;
            _head = nullptr;
        } else if(iter->next->next) {
            delete iter->next->next;
        } else {
            delete iter->next;
        }

        iter->next = nullptr;

        return this;
    }

    void print() {
        node<T>* iter = _head;
        while(iter != nullptr) {
            cout << iter->value << ' ';
            cout << "[[ " << (iter->prev!=nullptr ? iter->prev->value : -1) << ", ";
            cout << (iter->next!=nullptr ? iter->next->value : -1) << " ]],  ";
            iter = iter->next;
        }
    }
private:
    node<T>* _head;
};

int main() {
    list<int>* l = new list<int>{};
    l->push_front(2)->push_front(1);
    l->print(); cout << endl;
    l->push_back(5);
    l->print(); cout << endl;
    l->push_back(10)->push_back(15);
    l->print(); cout << endl;
    l->push_after_value(5, 6);
    l->print(); cout << endl;
    l->push_after_value(5, 7);
    l->print(); cout << endl;
    l->push_before_value(5, 4);
    l->print(); cout << endl;
    l->push_before_value(5, 3);
    l->print(); cout << endl;
    l->pop_back();
    l->print(); cout << endl;
    l->pop_front();
    l->print(); cout << endl;
    l->pop(2);
    l->print(); cout << endl;

    return 0;
}
