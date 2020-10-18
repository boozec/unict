#include<iostream>
#include<fstream>
#include<queue>
#include<vector>

using namespace std;

int main() {
    using tii = tuple<int, int, int>;
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int N;
        in >> N;

        priority_queue<tii, vector<tii>> pq;
        tii qq;
        for(int i = 0; i < N; ++i) {
            int e1, e2;
            in >> e1 >> e2;
            get<0>(qq) = e1-e2;
            get<1>(qq) = e1;
            get<2>(qq) = e2;

            pq.push(qq);
        }
        
        int counter = N;
        int sum{};

        while(counter-- > N/2) {
            qq = pq.top();
            sum += get<1>(qq);
            pq.pop();
        }

        while(!pq.empty()) {
            qq = pq.top();
            sum += get<2>(qq);
            pq.pop();
        }

        out << sum << endl;
    }

    in.close();
    out.close();
    return 0;
}

