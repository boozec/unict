#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#define INF 9999999

using namespace std;

typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;

class Graph
{
public:
	explicit Graph(size_t size, size_t k)
		: sizes_ { size }
		, k_ { k }
	{
		for (size_t i = 0; i < size; ++i)
			add_node(i);
	}

	Graph*
	add_node(int x)
   	{
		auto it = nodes_.find(x);

		if (it != nodes_.end()) {
			nodes_[x] = vector<pii>();
		}

		return this;
	}

	Graph*
	add_edge(int x, int y, int w)
	{
		nodes_[x].push_back({y, w});
		edges_.push_back({x, y, w});

		return this;
	}

	void
	bellmanford(int s, int r, ostream& out)
	{
		vector<int> dist(sizes_, INF);
		dist[s] = 0;

		for (size_t i = 0; i < min(k_, sizes_); ++i) {
			for (const auto& e : edges_) {
				auto u = get<0>(e);
				auto v = get<1>(e);
				auto w = get<2>(e);

				if (dist[u] != INF && dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
				}
			}
		}

		if (dist[r] == INF) {
			out << "inf." << endl;
		} else {
			out << dist[r] << endl;
		}
	}
	
private:
	map<int, vector<pii>> nodes_;
	vector<tii> edges_;
	size_t sizes_;
	size_t k_;
};

int
main(int argc, char** argv)
{
	int nt = (argc > 1) ? stoi(argv[1]) : 100;
	int n, m, k, s, r;
	string ch;
	int n1, n2, w;

	ifstream fin("input.txt");
	ofstream fout("output.txt");

	for (int i = 0; i < nt; ++i) {
		fin >> n >> m >> k;

		Graph* g = new Graph(n, k);

		for (int j = 0; j < m; ++j) {
			fin >> ch;
			n1 = stoi(ch.substr(1, ch.length()));
			fin >> n2 >> ch;
			w = stoi(ch.substr(0, ch.length()-1));

			g->add_edge(n1, n2, w);
		}

		fin >> s >> r;
		g->bellmanford(s, r, fout);

		delete g;
	}

	fout.close();
	fin.close();
	return 0;
}
