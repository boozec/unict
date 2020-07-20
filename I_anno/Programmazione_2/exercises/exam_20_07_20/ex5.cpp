#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<fstream>
#define INF 99999999
#define W -1
#define G 0
#define B 1

using namespace std;

template<class H>
class graph {
public:
    graph(int len) : _len{len}, _nodes{0}, _edges{0} {
        _k = new H*[len];
        _adj = new vector<int>[len];
        _colors = new int[len];
        _d = new int[len];
        _f = new int[len];
        _p = new int[len];

        for(int i = 0; i < len; ++i) {
            _k[i] = nullptr;
        }
    }
    ~graph() {
        delete[] _k;
        delete[] _adj;
    }

    graph<H>* add_node(H x) {
        if(_index(x) > -1) return this;
        if(_nodes == _len) return this;
        _k[_nodes++] = new H(x);

        return this;
    }
    graph<H>* add_edge(H u, H v) {
        int i = _index(u);
        int j = _index(v);
        if(i < 0 || j < 0) return this;

        if(find(_adj[i].begin(), _adj[i].end(), j) == _adj[i].end()) {
            _adj[i].push_back(j);
        }
        return this;
    }
    void print() {
        for(int i = 0; i < _nodes; ++i) {
            cout << "(" << *_k[i] << ", " << i << "): ";
            for(auto const& j : _adj[i]) {
                cout << "(" << *_k[j] << ", " << j << ") ";
            }
            cout << endl;
        }
    }
    void dfsvisit(int u, bool visited[]) {
        visited[u] = true;
        cout << "(" << *_k[u] << ", " << u << ") ";
        for(auto const& i : _adj[u]) {
            if(!visited[i])
                dfsvisit(i, visited);
        }
    }
    int dfsvisit(int u) {
        int cycle = 0;
        _colors[u] = G;
        _d[u] = _time++;

        for(auto const& j : _adj[u]) {
            if(_colors[j] == W)
                cycle |= dfsvisit(j);
        }

        _colors[u] = B;
        _stack.push(u);
        _f[u] = _time++;
        return cycle;
    }
    int dfs() {
        int cycle = 0;
        for(int i = 0; i < _nodes; ++i) {
            _colors[i] = W;
        }
        _time = 0;
        for(int i = 0; i < _nodes; ++i) {
            if(_colors[i] == W)
                cycle |= dfsvisit(i);
            else if(_colors[i] == G)
                cycle = 1;
        }
        for(int i = 0; i < _nodes; ++i) {
            cout << "(" << *_k[i] << ", " << i << "): [" << _d[i] << "," << _f[i] << "]" << endl;
        }
        return cycle;
    }

    void top_sort() {
        int cycle = dfs();
        if(cycle) {
            cout << "cyclic graph!" << endl;
            return;
        }
        int* s = new int[_nodes];
        for(int i = 0; i < _nodes; ++i) s[i] = i;
        _sort(s, _nodes, _f);
        for(int i = 0; i < _nodes; ++i) {
            cout << "(" << s[i] << ", " << _f[s[i]] << ") ";
        }

    }

    void bfs(H v) {
        int s = _index(v);
        if(s < 0) return;

        for(int i = 0; i < _nodes; ++i) {
            _colors[i] = W;
            _d[i] = INF;
            _p[i] = -1;
        }
        _colors[s] = G;
        _d[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto const& j : _adj[u]) {
                if(_colors[j] == W) {
                    _colors[j] = G;
                    _d[j] = _d[u]+1;
                    _p[j] = u;
                    q.push(j);
                }
            }
            _colors[u] = B;
        }
        for(int i = 0; i < _nodes; ++i) {
            cout << "(" << *_k[i] << ", " << i << "): [" << _d[i] << "]" << endl;
        }
    }
    int ssc() {
        dfs();
        cout << endl << endl;
        bool* visited = new bool[_nodes];
        for(int i = 0; i < _nodes; ++i)
            visited[i] = false;
        int count = 0;
        while(!_stack.empty()) {
            int v = _stack.top();
            _stack.pop();
            if(!visited[v]) {
                dfsvisit(v, visited);
                count++;
                cout << endl;
            }
        }
        delete[] visited;
        return count;
    }
private:
    graph<H>* _transpose() {
        graph<H>* g = new graph<H>{_len};
        for(int i = 0; i < _nodes; ++i) {
            g->add_node(*_k[i]);
        }

        for(int i = 0; i < _nodes; ++i) {
            for(auto const& j : _adj[i]) {
                g->add_edge(j, i);
            }
        }

        return g;
    }
    void _sort(int* d, int n, int* s) {
        for(int i = -1; i < n; ++i) {
            int j = i-1;
            while(j > -1 && s[d[j+1]]>s[d[j]]) {
                swap(d[s[j+1]], d[s[j]]);
                --j;
            }
        }
    }
    int _index(H x) {
        for(int i = 0; i < _nodes; ++i)
            if(*_k[i] == x) return i;

        return -1;
    }
    stack<int> _stack;
    H** _k;
    vector<int>* _adj;
    int _len, _nodes, _edges;
    int* _colors;
    int _time;
    int* _d;
    int* _f;
    int* _p;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int n, e;
        in >> n>>e;
        string t;
        in >> t;
        char _t;
        switch(t.at(0)){
            case 'd':{
                graph<double>* g = new graph<double>{n};
                double x, y;
                for(int i = 0; i < n; ++i) {
                    in >> x;
                    g->add_node(x);
                }
                for(int i = 0; i < e; ++i) {
                    in >>_t;
                    in >> x >> y;
                    in >> _t;
                    g->add_edge(x, y);
                    g->add_edge(y, x);
                }
                g->print();
                cout << endl << endl;
                out << g->ssc()<<endl;
                delete g;
                break;
             }
            case 'i':{

                graph<int>* g = new graph<int>{n};
                int x, y;
                for(int i = 0; i < n; ++i) {
                    in >> x;
                    g->add_node(x);
                }
                for(int i = 0; i < e; ++i) {
                    in >>_t;
                    in >> x >> y;
                    in >> _t;
                    g->add_edge(x, y);
                    g->add_edge(y, x);
                }
                g->print();
                cout << endl << endl;
                out << g->ssc()<<endl;
                delete g;
                break;
                     }
            case 'c': {

                graph<char>* g = new graph<char>{n};
                char x, y;
                for(int i = 0; i < n; ++i) {
                    in >> x;
                    g->add_node(x);
                }
                for(int i = 0; i < e; ++i) {
                    in >>_t;
                    in >> x >> y;
                    in >> _t;
                    g->add_edge(x, y);
                    g->add_edge(y, x);
                }
                g->print();
                cout << endl << endl;
                out << g->ssc()<<endl;
                delete g;
                break;
                      }
        }
    }
    in.close();
    out.close();
    return 0;
}

