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

    node<T>* last_element() {
        node<T>* iter = _head;
        while(iter && iter->next != _head) {
            iter = iter->next;
        }

        return iter;
    }

    node<T>* search(T val) {
        node<T>* iter = _head;
        if(iter->value == val) 
            return iter;

        while(iter && iter->value != val) {
            iter = iter->next;
            if(iter == _head) break;
        }

        if(iter == _head) return nullptr;

        return iter;
    }

    list* push_front(T val) {
        auto elem = last_element();
        if(_head == nullptr) {
            _head = new node<T>{val, nullptr, nullptr};
            _head->prev = _head->next = _head;
        } else {
            _head = new node<T>{val, elem, _head};
            elem->next = _head;
            _head->next->prev = _head;
        }

        return this;
    }

    list* push_back(T val) {
        if(_head == nullptr) {
            _head = new node<T>{val, nullptr, nullptr};
            _head->prev = _head->next = _head;
        } else {
            auto last_e = last_element();
            last_e->next = new node<T>{val, last_e, _head};
            _head->prev = last_e->next;
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

        node<T>* nod = new node<T>{newval, iter, iter->next};
        iter->next = nod;
        nod->next->prev = nod;

        return this;
    }

    list* push_before_value(T val, T newval) {
        if(!search(val)) return this;

        node<T>* iter = _head;

        if(iter->value == val)
            return this->push_front(newval);

        while(iter && iter->next && iter->next->value != val) {
            iter = iter->next;
            if(iter == _head) break;
        }

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

        if(!search(val)) return this;

        node<T>* iter = _head;
        while(iter && iter->next && iter->next->value != val) {
            iter = iter->next;
            if(iter == _head) break;
        }

        node<T>* temp = iter->next;
        iter->next = iter->next->next;
        iter->next->prev = iter;
        delete temp;

        return this;
    }

    list* pop_front() {
        if(_head == nullptr)
            return this;

        auto last_e = last_element();
        node<T>* elem = _head;
        _head = _head->next;
        _head->prev = last_e;
        last_e->next = _head;
        delete elem;

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

    return 0;
}
