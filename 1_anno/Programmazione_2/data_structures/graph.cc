#include<iostream>
#include<vector>

using namespace std;

template<class H>
class node {
public:
    explicit node(H key, node<H>* next) : _key{key}, _next(next) {}
    const H& key() const { return _key; }
    H& key() { return _key; }
    const node<H>*& next() const { return _next; }
    node<H>*& next() { return _next; }
private:
    H _key;
    node<H>* _next;
};

template<class H>
class list {
public:
    list() : _head{nullptr} {}
    ~list() {
        while(_head) {
            auto tmp = _head;
            _head = _head->next();
            delete tmp;
        }
    }
    list<H>* push(H val) {
        auto iter = _head;
        while(iter && iter->next())
            iter = iter->next();

        if(!iter)
            _head = new node<H>{val, nullptr};
        else
            iter->next() = new node<H>{val, nullptr};

        return this;
    }
    list<H>* pop(H val) {
        auto elem = search(val);
        if(!elem)
            return this;

        auto iter = _head;
        // This is the case when head is the element we want to pop
        if(iter == elem) {
            delete _head;
            _head = nullptr;
            return this;
        }

        while(iter && iter->next() != elem)
            iter = iter->next();

        auto tmp = iter->next();
        if(iter->next()->next()) { 
            iter->next() = iter->next()->next();
        } else { // the element we want to pop is the tail
            iter->next() = nullptr;
        }
        delete tmp;

        return this;
    }
    void print() {
        auto iter = _head;
        while(iter) {
            cout << iter->key() << ' ';
            iter = iter->next();
        }
    }
    vector<H> as_vector() {
        vector<H> v;
        auto iter = _head;
        while(iter) {
            v.push_back(iter->key());
            iter = iter->next();
        }
        return v;
    }
    node<H>* search(H val) {
        auto iter = _head;
        while(iter && iter->key() != val) {
            iter = iter->next();
        }

        return iter;
    }
private:
    node<H>* _head;
};

template<class H>
class graph {
public:

private:
    int _len, _nodes, _edges;
    H **_k;
    list<int> **_adj;
    int _index(H val) {
        for(int i = 0; i < _nodes; ++i)
            if(*_k[i] == val) return i;

        return -1;
    }
public:
    graph(int len) : _len{len}, _nodes{0}, _edges{0} {
        _k = new H*[len];
        _adj = new list<int>*[_len];
        for(int i = 0; i < _len; ++i) {
            _k[i] = nullptr;
            _adj[i] = new list<int>{};
        }
    }

    graph<H>* add_node(H k) {
        if(_nodes == _len) return this;
        if(_index(k) >= 0) return this; // node is already there

        _k[_nodes++] = new H(k);

        return this;
    }

    graph<H>* add_edge(H x, H y) {
        int i = _index(x);
        int j = _index(y);
        if(i < 0 || j < 0) return this;

        if(!_adj[i]->search(j)) {
            _adj[i]->push(j);
            _edges++;
        }

        return this;
    }

    void print() {
        for(int i = 0; i < _nodes; ++i) {
            cout << "(" << i << ", " << *_k[i] << "): ";
            for(auto const& j : _adj[i]->as_vector())
                cout << "(" << j << ", " << *_k[j] << "), ";
            cout << '\n';
        } 
    }
};


int main() {
    graph<string>* g = new graph<string>(5);
    g->add_node("hello")->add_node("greg")->add_node("yes");
    g->add_node("nop")->add_node("ok");
    g->add_edge("hello", "ok");
    g->add_edge("ok", "yes")->add_edge("yes", "ok")->add_edge("yes", "yes");
    g->add_edge("yes", "nop");
    g->print();

    delete g;
    return 0;
}
