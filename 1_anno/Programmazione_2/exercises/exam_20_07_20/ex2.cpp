#include<iostream>
#include<sstream>
#include<fstream>
#include<queue>

using namespace std;
using pi = tuple<int, int, vector<int>>;

class comp {
public:
    bool operator()(const pi& lhs, const pi& rhs) const {
        auto xl = get<0>(lhs);
        auto yl = get<0>(rhs);

        auto il = get<1>(lhs);
        auto jl = get<1>(rhs);
        if(xl == yl)
            return il > jl;
        return xl > yl;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int R, C;
        in >> R >> C;
        vector<vector<int>> v;
        priority_queue<pi, vector<pi>, comp> pq;
        int k;
        for(int i = 0; i < R; ++i) {
            v.push_back(vector<int>{});
            for(int j = 0; j < C; ++j) {
                in >> k;
                v[i].push_back(k);
            }
        }

        int index = 0;
        for(auto const& i : v) {
            int s = 0;
            pi qq;
            for(auto const& j : i)
                s += j;
            get<0>(qq) = s;
            get<1>(qq) = index++;
            get<2>(qq) = i;
            pq.push(qq);
        }
        while(!pq.empty()) {
            auto q = pq.top();
            pq.pop();
            for(auto const& i : get<2>(q))
                out << i << ' ';
        }
        out << endl;
    }
    in.close();
    out.close();
    return 0;
}
