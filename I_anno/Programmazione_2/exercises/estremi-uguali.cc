#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int result(string s) {
    if(s.at(0) == s.at(s.length()-1))
        return 1;

    return 0;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int _;
        string s;
        int size{};
        for(int i = 0; i < 3; ++i) {
            in >> _ >> s;
            size += result(s);
        }
        out << size << '\n';
    }

    in.close();
    out.close();
    return 0;
}
