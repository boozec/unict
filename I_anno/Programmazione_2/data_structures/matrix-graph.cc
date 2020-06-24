#include<iostream>
#include<list>

using namespace std;

template<class H>
class matrix_graph {
public:
    ~matrix_graph() {
        delete[] _m;
        delete[] _k;
    }
    matrix_graph(int len) : _len{len}, _nodes{0}, _edges{0} {
        _m = new int*[len];
        _k = new H*[len];
        for(int i = 0; i < len; ++i) {
            _m[i] = new int[len];
            _k[i] = nullptr;
            for(int j = 0; j < len; ++j)
                _m[i][j] = 0;
        }
    }

    matrix_graph<H>* add_node(H k) {
        if(_len == _nodes) return this; // no more space for new nodes
        if(_index(k) > -1) return this; // nodes already exists

        _k[_nodes++] = new H(k);

        return this;
    }

    matrix_graph<H>* add_edge(H x, H y) {
        int i = _index(x);
        int j = _index(y);
        if(i < 0 || j < 0) return this;
        if(!_m[i][j]) {
            _m[i][j] = 1;
            _edges++;
        }
        return this;
    }
    void print() {
        for(int i = 0; i < _len; ++i) {
            cout << i << ' ' << *_k[i] << ": ";
            for(int j = 0; j < _len; ++j) {
                if(_m[i][j])
                    cout << *_k[j] << ' ';
            }
            cout << '\n';
        }
        cout << endl;
        for(int i = 0; i < _len; ++i) {
            for(int j = 0; j < _len; ++j) {
                cout << _m[i][j] << ' ';
            }
            cout << '\n';
        }
    }
private:
    int _len, _nodes, _edges;
    int** _m;
    H** _k;
    int _index(H x) {
        for(int i = 0; i < _nodes; ++i)
            if(*_k[i] == x) return i;
        return -1;
    }
};

int main() {
    matrix_graph<string>* g = new matrix_graph<string>(5);
    g->add_node("hello")->add_node("greg")->add_node("yes");
    g->add_node("nop")->add_node("ok");
    g->add_edge("hello", "ok");
    g->add_edge("ok", "yes")->add_edge("yes", "ok")->add_edge("yes", "yes");
    g->add_edge("yes", "nop");
    g->print();
    delete g;
    return 0;
}
