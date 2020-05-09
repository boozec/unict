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

    node<T>* last_element() {
        node<T>* iter = _head;
        while(iter && iter->next != _head) {
            iter = iter->next;
        }

        return iter;
    }

    node<T>* search(T val) {
        if(_head == nullptr) return nullptr;

        node<T>* iter = _head;
        if(iter->value == val) 
            return iter;

        while(iter && iter->value != val) {
            iter = iter->next;
        }

        if(iter == _head) return nullptr;

        return iter;
    }

    list* push_front(T val) {
        auto elem = last_element();
        _head = new node<T>{val, _head};
        if(elem == nullptr)
            elem = _head;

        elem->next = _head;

        return this;
    }

    list* push_back(T val) {
        node<T>* iter = _head;
        if(_head == nullptr) {
            _head = new node<T>{val, _head};
        } else {
            while(iter->next != nullptr && iter->next != _head) {
                iter = iter->next;
            }
            iter->next = new node<T>{val, _head};
        }
        return this;
    }

    list* push_after_value(T val, T newval) {
        if(!search(val)) return this;

        node<T>* iter = _head;
        while(iter && iter->value != val)
            iter = iter->next;

        if(iter == nullptr)
            return this->push_front(newval);

        iter->next = new node<T>{newval, iter->next};

        return this;
    }

    list* push_before_value(T val, T newval) {
        if(!search(val)) return this;

        node<T>* iter = _head;

        if(iter->value == val)
            return this->push_front(newval);

        while(iter && iter->next && iter->next->value != val)
            iter = iter->next;

        if(iter == nullptr)
            return this->push_front(newval);

        iter->next = new node<T>{newval, iter->next};

        return this;
    }

    list* pop_front() {
        if(_head == nullptr)
            return this;

        auto last_e = last_element();

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
        if(_head == nullptr)
            return this;

        node<T>* iter = _head;
        auto last_e = last_element();

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

    return 0;
}
