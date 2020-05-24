#include<iostream>
#include<string>
#include<fstream>

using namespace std;

string result(string s) {
    s.at(0) = toupper(s.at(0));

    return s;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int _;
        string s;
        for(int i = 0; i < 3; ++i) {
            in >> _ >> s;
            out << result(s) << ' ';
        }
        out << '\n';
    }

    in.close();
    out.close();
    return 0;
}
