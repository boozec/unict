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
        int minor = stoi(s);
        for(in >> s; s != "STOP"; in >> s) {
            int si = stoi(s);
            if(si < minor)
                minor = si;
        }

        out << minor << '\n';
    }

    in.close();
    out.close();
    return 0;
}
