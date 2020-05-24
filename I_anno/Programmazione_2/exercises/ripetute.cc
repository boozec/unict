#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        string s;
        in >> s;
        out << s+s << '\n';
    }

    in.close();
    out.close();
    return 0;
}
