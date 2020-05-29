#include<iostream>
#include<fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int n; string s;
        in >> n >> s;
        string tm;
        for(int i = 0; i < n; ++i) {
            in >> tm;
            if(tm.find(s) != string::npos)
                out << tm << ' ';
        }
        out << '\n';
    }

    in.close();
    out.close();

    return 0;
}
