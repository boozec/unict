#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;

template<class T>
struct node {
    T key;
    node<T>* prev;
    node<T>* right;
    node<T>* left;
};

template<class T>
class bst {
public:
    bst() : root{nullptr} , _val{0}{}

    ~bst() {
        // TODO
    }

    bst<T>* insert(initializer_list<T>&& list) {
        for(auto const& i : list)
            insert(i);

        return this;
    }

    bst<T>* insert(T k) {
        node<T>* nodus = new node<T>{k, nullptr, nullptr, nullptr};
        node<T>* iter = root;
        node<T>* prev = nullptr;

        while(iter) {
            prev = iter;
            iter = (k < iter->key) ? iter->left : iter->right;
        }

        nodus->prev = prev;
        if(!prev)
            root = nodus;
        else if(k < prev->key)
            prev->left = nodus;
        else
            prev->right = nodus;

        return this;
    }

    bst<T>* remove(initializer_list<T>&& list) {
        for(auto const& i : list)
            remove(i);

        return this;
    }

    bst<T>* remove(T k) {
        node<T>* nodus = search(k);
        if(!nodus) return this;

        if(!nodus->left) {
            _transplant(nodus, nodus->right);
        } else if(!nodus->right) {
            _transplant(nodus, nodus->left);
        } else {
            node<T>* iter = _min(nodus->right);
            if(iter->prev != nodus) {
                _transplant(iter, iter->right);
                iter->right = nodus->right;
                iter->right->prev = iter;
            }
            _transplant(nodus, iter);
            iter->left = nodus->left;
            iter->left->prev = iter;
        }

        delete nodus;
        return this;
    }

    node<T>* min() {
        return _min(root);
    }

    node<T>* min(node<T>* nodus) {
        return _min(nodus);
    }

    node<T>* max() {
        return _max(root);
    }

    node<T>* max(node<T>* nodus) {
        return _max(nodus);
    }

    node<T>* search(T k) {
        node<T>* iter = root;
        while(iter && iter->key != k)
            iter = (iter->key > k) ? iter->left : iter->right;

        return iter;
    }

    node<T>* successor(T k) {
        node<T>* nodus = search(k);
        if(!nodus) return nullptr;

        if(nodus->right)
            return min(nodus->right);

        node<T>* prev = nodus->prev;
        while(prev && nodus == prev->right) {
            nodus = prev;
            prev = prev->prev;
        }

        return prev;

    }
    node<T>* predecessor(T k) {
        node<T>* nodus = search(k);
        if(!nodus) return nullptr;

        if(nodus->left)
            return max(nodus->left);

        node<T>* prev = nodus->prev;
        while(prev && nodus == prev->left) {
            nodus = prev;
            prev = prev->prev;
        }

        return prev;
    }

    friend ostream& operator<<(ostream& os, bst<T>* tree) {
        tree->_inorder(os, tree->root);
        return os;
    }
    T sol(T k) {
        return _max(search(k))->key;
    }
private:
    int _val;
    void _transplant(node<T>* u, node<T>* v) {
        if(!u->prev) {
            root = v;
        } else if(u == u->prev->left) {
            u->prev->left = v;
        } else {
            u->prev->right = v;
        }

        if(v)
            v->prev = u->prev;
    }

    node<T>* _min(node<T>* root) {
        node<T>* iter = root;
        while(iter && iter->left)
            iter = iter->left;

        return iter;
    }

    node<T>* _max(node<T>* root) {
        node<T>* iter = root;
        while(iter && iter->right)
            iter = iter->right;

        return iter;
    }

    void _inorder(ostream& os, node<T>* root) {
        if(root) {
            if(root->right && root->left) {
                _val++;
            }
            _inorder(os, root->left);
            os << root->key << ' ';
            _inorder(os, root->right);
        }
    }

    void _preorder(ostream& os, node<T>* root) {
        if(root) {
            os << root->key << ' ';
            _inorder(os, root->left);
            _inorder(os, root->right);
        }
    }

    void _postorder(ostream& os, node<T>* root) {
        if(root) {
            _inorder(os, root->left);
            _inorder(os, root->right);
            os << root->key << ' ';
        }
    }
    node<T>* root;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        string t, comm;
        in >> t;
        int n;
        switch(t.at(0)) {
        case 'd':
            {
                bst<double>* b = new bst<double>{};
                in >> n;
                double k;
                for(int i = 0; i < n; ++i) {
                    in >> comm;
                    stringstream tcomm(comm);
                    int ex= 0;
                    while(getline(tcomm, comm, ':')) {
                        if(ex == 0) {
                            if(comm == "ins")
                                ex = 1;
                            else
                                ex = 2;
                        } else {
                            if(ex == 1)
                                b->insert(stod(comm));
                            else
                                b->remove(stod(comm));
                            ex = 0;
                        }
                    }
                }
                in >> k;
                cout << b << endl;
                out << b->sol(k) << endl;
 
                delete b;
                break;
            }
        case 'i':
            {
                bst<int>* b = new bst<int>{};
                in >> n;
                int k;
                for(int i = 0; i < n; ++i) {
                    in >> comm;
                    stringstream tcomm(comm);
                    int ex= 0;
                    while(getline(tcomm, comm, ':')) {
                        if(ex == 0) {
                            if(comm == "ins")
                                ex = 1;
                            else
                                ex = 2;
                        } else {
                            if(ex == 1)
                                b->insert(stoi(comm));
                            else
                                b->remove(stoi(comm));
                            ex = 0;
                        }
                    }
                }
                in >> k;
                cout << b << endl;
                out << b->sol(k) << endl;
 
                delete b;
                break;
            }
        }
    }

    in.close();
    out.close();
    return 0;
}

