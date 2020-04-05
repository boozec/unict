#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

int maxpath(vector<vector<int>>& v) {
    for(int i = v.size()-2; i >= 0; --i) {
        for(int j = 0; j <= i; ++j) {
            if(v[i+1][j] > v[i+1][j+1]) {
                v[i][j] += v[i+1][j];
            } else {
                v[i][j] += v[i+1][j+1];
            }
        }
    }

    return v[0][0];
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 1; ++ts) {
        int N;
        in >> N;
        vector<vector<int>> triangle;

        for(int i = 0; i < N; ++i) {
            int e;
            triangle.push_back(vector<int>{});
            int j;
            for(j = 0; j <= i; ++j) {
                in >> e;
                triangle[i].push_back(e);
            }
            for(; j < N; ++j) 
                triangle[i].push_back(0);
        }
        out << maxpath(triangle) << endl;
    }

    in.close();
    out.close();
    return 0;
}
