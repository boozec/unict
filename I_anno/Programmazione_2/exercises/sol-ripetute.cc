#include<iostream>
#include<string>
#include<fstream>

using namespace std;

string result(string s) {
    int half = s.length()/2;
    return s.substr(0, half);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        string s;
        in >> s;
        out << result(s) << '\n';
    }

    in.close();
    out.close();
    return 0;
}
