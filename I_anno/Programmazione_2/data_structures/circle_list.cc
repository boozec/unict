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
        node<T>* iter = _head;
        while(iter->next != _head) {
            node<T>* tmp = iter;
            delete tmp;
            iter = iter->next;
        }
        node<T>* tmp = iter;
        delete tmp;
    }

    list* push_front(T val) {
        auto elem = _last();
        _head = new node<T>{val, _head};
        if(!elem)
            elem = _head;

        elem->next = _head;

        return this;
    }

    list* push_back(T val) {
        if(!_head) return this->push_front(val);

        auto last_e = _last();
        last_e->next = new node<T>{val, _head};

        return this;
    }

    list* push_after_value(T val, T newval) {
        node<T>* iter = _search(val);
        if(iter)
            iter->next = new node<T>{newval, iter->next};

        return this;
    }

    list* push_before_value(T val, T newval) {
        node<T>* elem = _search(val);
        if(!elem) return this;

        node<T>* iter = _head;

        if(iter->value == val)
            return this->push_front(newval);

        while(iter->next != elem)
            iter = iter->next;

        iter->next = new node<T>{newval, iter->next};

        return this;
    }

    list* pop(int val) {
        node<T>* elem = _search(val);
        if(!elem) return this;

        node<T>* iter = _head;
        if(iter == elem) return this->pop_front();

        while(iter->next != elem)
            iter = iter->next;

        node<T>* temp = iter->next;
        iter->next = iter->next->next;
        delete temp;

        return this;
    }

    list* pop_front() {
        if(!_head)
            return this;

        auto last_e = _last();

        if(last_e == _head) {
            delete _head;
            _head = nullptr;
        } else {
            node<T>* elem = _head;
            _head = _head->next;
            last_e->next = _head;
            delete elem;
        }

        return this;
    }

    list* pop_back() {
        if(!_head)
            return this;

        node<T>* iter = _head;
        auto last_e = _last();

        if(last_e == _head) {
            delete iter;
            _head = nullptr;
        } else {
            while(iter->next != last_e) {
                iter = iter->next;
            }

            delete iter->next;
            iter->next = _head;
        }

        return this;
    }

    void print() {
        node<T>* iter = _head;
        while(iter) {
            cout << iter->value << ' ';
            iter = iter->next;
            if(iter == _head) break;
        }
    }
private:
    node<T>* _last() {
        node<T>* iter = _head;
        while(iter && iter->next != _head) {
            iter = iter->next;
        }

        return iter;
    }

    node<T>* _search(T val) {
        node<T>* iter = _head;
        if(iter->value == val) return iter;

        while(iter && iter->value != val) {
            iter = iter->next;
            if(iter == _head) return nullptr;
        }

        return iter;
    }

    node<T>* _head;
};

int main() {
    list<int>* l = new list<int>{};
    l->push_before_value(4, 1);
    l->push_back(4);
    l->push_back(1);
    l->push_back(0);
    l->push_front(2);
    l->print(); cout << endl;
    l->pop_back();
    l->print(); cout << endl;
    l->pop_front();
    l->print(); cout << endl;
    l->pop_back();
    l->print(); cout << endl;
    l->push_front(3);
    l->print(); cout << endl;
    l->push_after_value(4, 7);
    l->print(); cout << endl;
    l->push_before_value(3, 5);
    l->print(); cout << endl;
    l->pop(5);
    l->print(); cout << endl;

    delete l;
    return 0;
}
