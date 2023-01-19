#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#define INF 9999999

using namespace std;

template <class H>
class Graph {
public:
    Graph<H>*
    add_node(H u)
    {
        auto it = nodes_.find(u);

        if (it == nodes_.end()) {
            nodes_.insert({ u, vector<pair<H, int>>() });
            size_++;
        }

        return this;
    }

    Graph<H>*
    add_edge(H u, H v, int w)
    {
        auto i = nodes_.find(u);
        auto j = nodes_.find(v);

        if (i != nodes_.end() && j != nodes_.end()) {
            nodes_[u].push_back({ v, w });
            edges_.push_back({ u, v, w });
        }

        return this;
    }

    void
    bellmanford(H s, H r, ostream& out)
    {
        map<H, int> dist;
        map<H, pair<H, int>> p;

        for (const auto& it : nodes_) {
            dist.insert({ it.first, INF });
        }

        dist[s] = 0;

        for (size_t i = 0; i < size_; ++i) {
            for (const auto& e : edges_) {
                auto u = get<0>(e);
                auto v = get<1>(e);
                auto w = get<2>(e);

                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    p[v] = make_pair(u, dist[v]);
                }
            }
        }

        for (size_t i = 0; i < size_; ++i) {
            for (const auto& e : edges_) {
                auto u = get<0>(e);
                auto v = get<1>(e);
                auto w = get<2>(e);

                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    out << "undef." << endl;
                    return;
                }
            }
        }

        if (p.find(r) == p.end()) {
            out << "inf." << endl;
            return;
        } else {
            out << p[r].second << endl;
        }
    }

private:
    // `nodes_` is map which has the node as key and the edges as value.
    // eg:
    // nodes_[0] = [[1, 300]];
    // there is an edge 0<->1 with 300 as weight
    map<H, vector<pair<H, int>>> nodes_;

    vector<tuple<H, H, int>> edges_;

    size_t size_ { 0 };
};

int
main(int argc, char** argv)
{
    int ts = (argc > 1) ? stoi(argv[1]) : 100;
    int n, m;
    string tp;
    string ch;
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    for (int i = 0; i < ts; ++i) {
        fin >> n >> m >> tp;

        if (tp == "int") {
            Graph<int>* g = new Graph<int>();
            int k, n1, n2, s, r;
            int w;

            for (int j = 0; j < n; ++j) {
                fin >> k;
                g->add_node(k);
            }

            for (int j = 0; j < m; ++j) {
                fin >> ch;
                n1 = stoi(ch.substr(1, ch.length()));
                fin >> n2;
                fin >> ch;
                w = stoi(ch.substr(0, ch.length() - 1));

                g->add_edge(n1, n2, w);
            }

            fin >> s >> r;

            g->bellmanford(s, r, fout);

            delete g;
        } else if (tp == "double") {
            Graph<int>* g = new Graph<int>();
            double k, n1, n2, s, r;
            int w;

            for (int j = 0; j < n; ++j) {
                fin >> k;
                g->add_node(k * 10);
            }

            for (int j = 0; j < m; ++j) {
                fin >> ch;
                n1 = stod(ch.substr(1, ch.length()));
                fin >> n2;
                fin >> ch;
                w = stoi(ch.substr(0, ch.length() - 1));

                g->add_edge(n1 * 10, n2 * 10, w);
            }

            fin >> s >> r;

            g->bellmanford(s * 10, r * 10, fout);

            delete g;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
