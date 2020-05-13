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
        if(!_head) {
            _head = new node<T>{val, nullptr, nullptr};
            _head->prev = _head->next = _head;
        } else {
            _head = new node<T>{val, elem, _head};
            elem->next = _head->next->prev = _head;
        }

        return this;
    }

    list* push_back(T val) {
        if(!_head) return this->push_front(val);

        auto last_e = _last();
        last_e->next = new node<T>{val, last_e, _head};
        _head->prev = last_e->next;

        return this;
    }

    list* push_after_value(T val, T newval) {
        node<T>* iter = _search(val);
        if(iter) {
            node<T>* nod = new node<T>{newval, iter, iter->next};
            iter->next = nod;
            nod->next->prev = nod;
        }

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

        node<T>* nod = new node<T>{newval, iter, iter->next};
        iter->next = nod;
        nod->next->prev = nod;

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
        iter->next->prev = iter;
        delete temp;

        return this;
    }

    list* pop_front() {
        if(!_head)
            return this;

        auto last_e = _last();
        node<T>* elem = _head;
        _head = _head->next;
        _head->prev = last_e;
        last_e->next = _head;
        delete elem;

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
            _head->prev = iter;
        }

        return this;
    }

    void print() {
        node<T>* iter = _head;
        while(iter != nullptr) {
            cout << iter->value << ' ';
            cout << "[[ " << iter->prev->value << ", ";
            cout << iter->next->value << " ]],  ";
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
    l->push_front(2);
    l->push_back(1)->push_back(3);
    l->push_front(5)->push_front(9);
    l->push_back(0)->push_back(6);
    l->print(); cout << '\n';
    l->push_after_value(7, -2);
    l->push_before_value(9, 10);
    l->print(); cout << '\n';
    l->pop_front();
    l->pop_front();
    l->pop_back();
    l->pop_front();
    l->print(); cout << '\n';
    l->pop(2);
    l->print(); cout << '\n';

    delete l;
    return 0;
}
