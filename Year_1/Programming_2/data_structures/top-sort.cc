
#include<iostream>
#include<vector>
#include<queue>
#define W -1
#define G 0
#define B 1

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
private:
    int _len, _nodes, _edges;
    int* _parents;
    int* _radixes;
    int* _distances;
    int* _finishes;
    int* _colors;
    int _time;
    int _current;
    H** _k; // it works like a dictionary, it saves the keys
    list<int>** _adj;
    int _index(H val) {
        for(int i = 0; i < _nodes; ++i)
            if(*_k[i] == val) return i;

        return -1;
    }
    bool _dfsvisit(int u) {
        bool cycle = false;
        _colors[u] = G;
        _distances[u] = _time++;
        _radixes[u] = _current;
        for(auto const& v : _adj[u]->as_vector()) {
            if(_colors[v] == W) {
                _parents[v] = u;
                _dfsvisit(v);
            } else if(_colors[v] == G) {
                cycle = true;
            }
        }
        _colors[u] = B;
        _finishes[u] = _time++;
        return cycle;
    }
public:
    graph(int len) : _len{len}, _nodes{0}, _edges{0} {
        _k = new H*[len];
        _adj = new list<int>*[_len];
        _parents = new int[_len];
        _radixes = new int[_len];
        _distances = new int[_len];
        _finishes = new int[_len];
        _colors = new int[_len];
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


    bool dfs() {
        bool cycle = 0;
        _time = 0;
        for(int i = 0; i < _nodes; ++i) {
            _colors[i] = W;
            _parents[i] = -1;
        }

        for(int i = 0; i < _nodes; ++i) {
            if(_colors[i] == W) {
                _current = i;
                cycle |= _dfsvisit(i);
            }
        }
        for(int i = 0; i < _nodes; ++i) {
            cout << *_k[i] << "(" << _distances[i]+1 << ',' << _finishes[i]+1 << ")" << endl;
        }
        return cycle;
    }

    void top_sort() {
        bool cycle = dfs();
        if(cycle) {
            cerr << "Grafo ciclico\n";
            return;
        }
        vector<int> s(_finishes, _finishes+_nodes);
        sort(begin(s), end(s));
        for(auto const& i : s) {
            cout << "(" << i << ", " << _finishes[i] << ") ";
        }
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
    graph<char>* g = new graph<char>(6);
    g->add_node('u')->add_node('v')->add_node('x')->add_node('y');
    g->add_node('w')->add_node('z');
    g->add_edge('u', 'v');
    g->add_edge('u', 'x');
    g->add_edge('x', 'v');
    g->add_edge('y', 'x');
    g->add_edge('v', 'y');
    g->add_edge('w', 'y');
    g->add_edge('w', 'z');
    g->add_edge('z', 'z');

    g->print();
    g->dfs();
    g->top_sort();

    delete g;
    return 0;
}
