#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int N;
        in >> N;
        vector<int> arr(N);
        for(int i = 0; i < N; ++i) {
            in >> arr.at(i);
        }

        vector<int> paths(N, 1);

        for(int i = N-2; i >= 0; --i) {
            int mx = 0;
            for(int j = i+2; j < N; ++j) {
                if(mx < paths[j] && arr[j] >= arr[i]) {
                    mx = paths[j];
                }
            }
            paths[i] += mx;
        }

        out << *max_element(begin(paths), end(paths)) << '\n';
    }

    in.close();
    out.close();
    return 0;
}
