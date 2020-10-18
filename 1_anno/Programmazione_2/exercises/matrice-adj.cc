#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

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
    vector<vector<H>> print() {
        vector<vector<H>> v;
        for(int i = 0; i < _len; ++i) {
            v.push_back(vector<H>{*_k[i]});
            vector<H> temp;
            for(int j = 0; j < _len; ++j) {
                if(_m[i][j]) {
                    temp.push_back(*_k[j]);
                }
            }
            sort(begin(temp), end(temp));
            for(auto const& j : temp)
                v[i].push_back(j);
        }

        sort(begin(v), end(v));
        return v;
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

template<class H>
string result(vector<vector<H>> v) {
    string s{""};
    ostringstream ss;
    for(auto const& i : v) {
        s += "(";
        for(auto const& j : i) {
            ss << j;
            s+= ss.str();
            s+= ' ';
            ss.str(""); ss.clear();
        }
        s.pop_back();
        s += ") ";
    }
    return s;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    for(int ts = 0; ts < 100; ++ts) {
        int n, m;
        in >> n >> m;
        string t;
        in >> t;
        if(t == "int") {
            matrix_graph<int>* g = new matrix_graph<int>(n);
            int x,y;
            for(int i = 0; i < n; ++i) {
               in >> x;
               g->add_node(x);
            }
            char ex;
            for(int i = 0; i < m; ++i) {
                in >> ex >> x >> y >> ex;
                g->add_edge(x, y);
            }
            auto v = g->print();
            out << result(v) << endl;
            delete g;
        } else if(t == "double") {
            matrix_graph<double>* g = new matrix_graph<double>(n);
            double x,y;
            for(int i = 0; i < n; ++i) {
               in >> x;
               g->add_node(x);
            }
            char ex;
            for(int i = 0; i < m; ++i) {
                in >> ex >> x >> y >> ex;
                g->add_edge(x, y);
            }
            auto v = g->print();
            out << result(v) << endl;
            delete g;
        } else {
            matrix_graph<char>* g = new matrix_graph<char>(n);
            char x,y;
            for(int i = 0; i < n; ++i) {
               in >> x;
               g->add_node(x);
            }
            char ex;
            for(int i = 0; i < m; ++i) {
                in >> ex >> x >> y >> ex;
                g->add_edge(x, y);
            }

            auto v = g->print();
            out << result(v) << endl;
            delete g;
        }
    }
    in.close();
    out.close();
    return 0;
}
