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
        if(!_head) {
            _head = new node<T>{val, nullptr, nullptr};
        } else {
            _head = new node<T>{val, nullptr, _head};
            _head->next->prev = _head;
        }

        return this;
    }

    list* push_back(T val) {
        if(!_head) return this->push_front(val);

        node<T>* iter = _head;
        while(iter->next) {
            iter = iter->next;
        }
        iter->next = new node<T>{val, iter, nullptr};

        return this;
    }

    list* push_after_value(T val, T newval) {
        node<T>* elem = _search(val);
        if(elem) {
            node<T>* nod = new node<T>{newval, elem, elem->next};
            elem->next = nod;
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

        if(elem == _head) return this->pop_front();

        node<T>* iter = elem->prev;
        node<T>* temp = iter->next;
        iter->next = iter->next->next;
        iter->next->prev = iter;
        delete temp;

        return this;
    }

    list* pop_front() {
        if(!_head)
            return this;

        node<T>* elem = _head;
        _head = _head->next;
        _head->prev = nullptr;
        delete elem;

        return this;
    }

    list* pop_back() {
        if(!_head)
            return this;

        node<T>* iter = _last()->prev;

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
        while(iter) {
            cout << iter->value << ' ';
            cout << "[[ " << (iter->prev!=nullptr ? iter->prev->value : -1) << ", ";
            cout << (iter->next!=nullptr ? iter->next->value : -1) << " ]],  ";
            iter = iter->next;
        }
    }
private:
    node<T>* _last() {
        node<T>* iter = _head;
        while(iter->next) {
            iter = iter->next;
        }

        return iter;
    }

    node<T>* _search(T value) {
        node<T>* iter = _head;
        while(iter && iter->value != value)
            iter = iter->next;

        return iter;
    }

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

    delete l;

    return 0;
}
