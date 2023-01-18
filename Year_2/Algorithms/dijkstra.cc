#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#define INF 999999

using namespace std;

template <class K, class H>
class Graph {
public:
    Graph()
    {
    }

    ~Graph()
    {
    }

    Graph<K, H>*
    add_node(K x)
    {
        auto it = nodes_.find(x);

        if (it == nodes_.end()) {
            nodes_.insert({ x, vector<pair<K, H>>() });
            size_++;
        }

        return this;
    }

    Graph<K, H>*
    add_edge(K x, K y, H w)
    {
        auto u = nodes_.find(x);
        auto v = nodes_.find(y);

        if (u != nodes_.end() && v != nodes_.end()) {
            nodes_[x].push_back({ y, w });
        }

        return this;
    }

    size_t
    dijkstra(K s, K r)
    {
        typedef pair<H, K> phk;
        priority_queue<phk, vector<phk>, greater<phk>> pq;

        auto i = nodes_.find(s);
        auto j = nodes_.find(r);

        if (i == nodes_.end() || j == nodes_.end()) {
            return INF;
        }

        map<K, int> dist;

        pq.push({ 0, s });

        for (const auto& it : nodes_)
            dist.insert({ it.first, INF });

        dist[s] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto const& i : nodes_[u]) {
                int v = i.first;
                int w = i.second;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({ dist[v], v });
                }
            }
        }

        return dist[r];
    }

private:
    size_t size_ { 0 };
    map<K, vector<pair<K, H>>> nodes_;
};

int
main(int argc, char** argv)
{
    int tasks = (argc > 1) ? stoi(argv[1]) : 100;
    int n, m;
    string buf;

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    for (int i = 0; i < tasks; ++i) {
        string t;

        fin >> n >> m >> t;

        Graph<int, int>* g = new Graph<int, int>();
        if (t == "int") {
            int k;

            for (int j = 0; j < n; ++j) {
                fin >> k;
                g->add_node(k);
            }

            int n1, n2, w;

            for (int j = 0; j < m; ++j) {
                fin >> buf;
                n1 = stoi(buf.substr(1, buf.length()));
                fin >> buf;
                n2 = stoi(buf);
                fin >> buf;
                w = stoi(buf.substr(0, buf.length() - 1));

                g->add_edge(n1, n2, w);
            }
            int s, r;
            fin >> s >> r;

            auto dist = g->dijkstra(s, r);
            if (dist == INF)
                fout << "inf." << endl;
            else
                fout << dist << endl;

        } else {
            double k;

            for (int j = 0; j < n; ++j) {
                fin >> k;
                g->add_node(k * 10);
            }

            double n1, n2;
            int w;

            for (int j = 0; j < m; ++j) {
                fin >> buf;
                n1 = stod(buf.substr(1, buf.length()));
                fin >> buf;
                n2 = stod(buf);
                fin >> buf;
                w = stoi(buf.substr(0, buf.length() - 1));

                g->add_edge(n1 * 10, n2 * 10, w);
            }

            double s, r;
            fin >> s >> r;

            auto dist = g->dijkstra(s * 10, r * 10);
            if (dist == INF)
                fout << "inf." << endl;
            else
                fout << dist << endl;
        }
        delete g;
    }

    fin.close();
    fout.close();

    return 0;
}
