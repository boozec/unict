#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

void get_fib(vector<int> &v, int N) {
    int a = v.at(0);
    int b = v.at(1);
    while(b <= N) {
        a += b;
        v.push_back(a);
        swap(a, b);
    }
    v.pop_back();
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(short _ = 0; _ < 100; ++_) {
        int N;
        in >> N;
        vector<int> fib {1, 2};
        get_fib(fib, N);
        vector<int> seq(fib.size(), 0);

        int sum{};
        for(int i = fib.size()-1; i >= 0; --i) {
            if(fib.at(i) + sum > N) continue;

            sum += fib.at(i);
            seq[i] = 1;
        }


        for(auto const& i : seq)
            out << i;

        out << endl;
    }

    out.close();
    in.close();
    
    return 0;
}
