#include<iostream>

using namespace std;

template<class H> class MultiBST {
    virtual MultiBST<H>* ins(H x) = 0;
    virtual int multiplicity(H x) = 0;
    virtual void inorder() = 0;
};

template<class H>
class node {
public:
    node(H val) : _key{val}, _parent{nullptr}, _left{nullptr}, _right{nullptr}, _rk{1} {}
    H& key() { return _key; }  
    const H& key() const { return _key; }  
    node<H>*& parent() { return _parent; }
    const node<H>*& parent() const { return _parent; }
    node<H>*& left() { return _left; }
    const node<H>*& left() const { return _left; }
    node<H>*& right() { return _right; }
    const node<H>*& right() const { return _right; }
    int& rk() { return _rk; }
    const int& rk() const { return _rk; }
private:
    H _key;
    node<H>* _parent;
    node<H>* _left;
    node<H>* _right;
    int _rk;
};

template<class H>
class MyMultiBST : public MultiBST<H> {
public:
    MyMultiBST() : _root{nullptr} {}
    node<H>*& root() { return _root; }
    const node<H>*& root() const { return _root; }
    int multiplicity(H x) {
        auto elem = _search(x);
        if(elem)
            return elem->rk();
        return 0;
    }
    MyMultiBST<H>* ins(H x) {
        auto iter = _search(x);
        if(iter) {
            iter->rk() = iter->rk()+1;
        } else {
            iter = _root;
            node<H>* y{nullptr};

            while(iter) {
                y = iter;
                if(iter->key() > x) 
                    iter = iter->left();
                else
                    iter = iter->right();
            }

            node<H>* nodus = new node<H>{x};
            nodus->parent() = y;
            if(!y) {
                _root = nodus;
            } else if(y->key() > x) {
                y->left() = nodus;
            } else {
                y->right() = nodus;
            }
        }

        return this;
    }
    void inorder() {
       _inorder(_root);
    }
    MyMultiBST<H>* del(H x) {
        node<H>* y;
        node<H>* z = _search(x);

        if(!z) return this;

        if(z->rk() > 1) {
            z->rk() = z->rk()-1;
        } else {
            if(!z->left()) {
                _transplant(z, z->right());
            } else if(!z->right()) {
                _transplant(z, z->left());
            } else {
                y = _min(z->right());
                if(y->parent() != z) {
                    _transplant(y, y->right());
                    y->right() = z->right();
                    y->right()->parent() = y;
                }
                _transplant(z, y);
                y->left() = z->left();
                y->left()->parent() = y;
                delete z;
            }
        }

        return this;
    }
    node<H>* predecessor(H x) {
        auto iter = _search(x);
        if(!iter) return nullptr;
        if(iter->left())
            return _max(iter->left());

        auto y = iter->parent();
        while(y && iter == y->left()) {
            iter = y;
            y = y->parent();
        }

        return y;
    }
    int rank(H x) {
        auto iter = predecessor(x);
        int sum{1};
        while(iter) {
            sum+=iter->rk();
            iter = predecessor(iter->key());
        }
        return sum;
    }
private:
    void _transplant(node<H>* u, node<H>* v) {
        if(!u->parent()) _root = v;
        else if(u == u->parent()->left())
            u->parent()->left() = v;
        else
            u->parent()->right() = v;

        if(v)
            v->parent() = u->parent();
    }
    node<H>* _max(node<H>* x) {
        if(!x) return nullptr;

        auto iter = x;
        while(iter->right()) {
            iter = iter->right();
        }

        return iter;
    }
    node<H>* _min(node<H>* x) {
        if(!x) return nullptr;

        auto iter = x;
        while(iter->left()) {
            iter = iter->left();
        }

        return iter;
    }
    void _inorder(node<H>* p) {
        if(p) {
            _inorder(p->left());
            for(int i = 0; i < p->rk(); ++i) {
                cout << p->key() << ' ';
            }
            _inorder(p->right());
        }
    }
    node<H>* _search(H val) {
        auto iter = _root;
        while(iter && iter->key() != val) {
            if(iter->key() > val)
                iter = iter->left();
            else
                iter = iter->right();
        }

        return iter;
    }
    node<H>* _root;
};

int main() {
    MyMultiBST<int>* t = new MyMultiBST<int>{};

    for(auto const& i : {10, 7, 7, 23, 30, 4, 1, 5, 9, 5, 1, 7, 1, 9})
        t->ins(i);

    t->inorder();
    cout << '\n';
    for(auto const& i : {5, 7, 17})
        cout << i << ": " << t->multiplicity(i) << endl;

    for(auto const& i : {7, 4, 23, 7, 7})
        t->del(i);
    t->inorder();
    cout << '\n';
    for(auto const& i: {5, 9, 30})
        cout << t->rank(i) << ' ';
    delete t;
    return 0;
}
