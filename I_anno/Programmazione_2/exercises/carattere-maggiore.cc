#include<iostream>
#include<map>
#include<fstream>

using namespace std;



int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        string line;
        getline(in, line);
        map<char, int> chs;
        for(auto const& c : line) {
            if(c == ' ') continue;
            if(chs.find(c) != chs.end())
                chs[c]++;
            else
                chs[c] = 1;
        }
        int n = 0;
        char c = 'a';
        for(auto const& i : chs) {
            if(i.second >= n) {
                if(i.first >= c) {
                    n = i.second;
                    c = i.first;
                }
            }
        }
        out << c << ' ' << n << endl;
    }

    out.close();
    in.close();
    return 0;
}
