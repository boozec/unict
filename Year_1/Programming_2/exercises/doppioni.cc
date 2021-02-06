#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class node {
public:
    node(T key, node* parent, node* right, node* left) : _key{key}, _parent{parent}, _right{right}, _left{left} {}
    T& key() { return _key; }
    const T& key() const { return _key; }
    node<T>*& parent() { return _parent; }
    const node<T>*& parent() const { return _parent; }
    node<T>*& right() { return _right; }
    const node<T>*& right() const { return _right; }
    node<T>*& left() { return _left; }
    const node<T>*& left() const { return _left; }
private:
    T _key;
    node<T>* _parent;
    node<T>* _right;
    node<T>* _left;
};

class bst {
public:
    bst() : _duplicates{0}, _root{nullptr} {}
    bst* add(int val) {
        node<int>* iter = _root;
        node<int>* prev = nullptr;
        while(iter) {
            prev = iter;
            if(iter->key() == val) {
                _duplicates++;
                return this;
            }

            if(iter->key() > val)
                iter = iter->right();
            else
                iter = iter->left();
        }

        node<int>* nodus = new node<int>{val, prev, nullptr, nullptr};
        if(!prev)
            _root = nodus;
        else if(prev->key() > val)
            prev->right() = nodus;
        else
            prev->left() = nodus;

        return this;
    }
    const int& duplicates() const { return _duplicates; }
private:
    int _duplicates;
    node<int>* _root;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    for(int ts = 0; ts < 100; ++ts) {
        bst* b = new bst{};
        int n;
        in >> n;
        int e;
        for(int i = 0; i < n; ++i) {
            in >> e;
            b->add(e);
        }
        out << b->duplicates() << endl;
    }
    in.close();
    out.close();
    return 0;
}
