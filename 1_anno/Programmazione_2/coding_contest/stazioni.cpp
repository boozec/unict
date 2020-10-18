#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 1; ++ts) {
        int N, S;
        in >> N >> S;
        vector<long> st;
        vector<vector<long>> paths;
        vector<vector<long>> paths2;
        vector<vector<long>> paths3;

        int e;
        for(int i = 0; i < N; ++i) {
            in >> e;
            st.push_back(e);
        }

        int index{};
        for(int i = 0; i < N-S+1; ++i) {
            for(int j = 0; j < N; ++j) {
                paths.push_back(vector<long>{});
                paths[index].push_back(i);
                for(int k = j; paths[index].size() < S; ++k) {
                    int t = (k == N) ? 0 : k;
                    if(k > N) break;
                    paths[index].push_back(t);
                }
                sort(begin(paths[index]), end(paths[index]));
                if(paths[index].size() == S)
                    paths2.push_back(paths[index]);
                ++index;
            }
        }
        for(int i = 0; i < paths2.size(); ++i) {
            bool check{true};
            if(paths2[i].size() != S) continue;
            for(int j = 0; j < paths2[i].size()-1; ++j) {
                if(paths2[i].at(j) == paths2[i].at(j+1)) {
                    check = false;
                    break;
                }
            }
            if(check)
                paths3.push_back(paths2[i]);
        }

        for(auto const& i : paths3) {
            for(auto const& j : i) 
                cout << st[j] << ' ';

            cout << endl;
        }
        cout << endl;

        int major{};
        for(int i = 0; i < paths3.size(); ++i) {
            vector<long> diffs;
            for(int j = 0; j < paths3[i].size()-1; ++j) {
                int p1 = st[paths3[i][j+1]];
                int p2 = st[paths3[i][j]];
                diffs.push_back(p1 - p2);
            }
            int miner = *min_element(begin(diffs), end(diffs));
            if(miner > major)
                major = miner;
        }
        cout << ts << ' ' << major << endl;
        out << major << endl;
    }

    in.close();
    out.close();
    return 0;
}
