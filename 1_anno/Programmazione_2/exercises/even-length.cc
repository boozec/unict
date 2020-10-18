#include<iostream>
#include<string>
#include<fstream>

using namespace std;

string result(string s) {
    if(s.length() % 2 == 0)
        return s;

    return s.substr(0, s.length()-1);
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
