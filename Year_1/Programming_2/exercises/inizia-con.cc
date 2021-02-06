#include<iostream>
#include<string>
#include<fstream>

using namespace std;

string result(string s, char c) {
    if(s.at(0) == c)
        return s + ' ';

    return "";
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int _;
        string s;
        char c;
        in >> c;
        for(int i = 0; i < 3; ++i) {
            in >> _ >> s;
            out << result(s, c);
        }
        out << '\n';
    }

    in.close();
    out.close();
    return 0;
}
