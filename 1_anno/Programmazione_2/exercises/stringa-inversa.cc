#include<iostream>
#include<fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int n;
        in >> n;
        for(int i = 0; i < 3; ++i) {
            string s;
            in >> s;
            for(int j = s.length()-1; j > -1; --j) {
                out << s.at(j);
            }
            out << ' ';
        }
        out << endl;
    }

    out.close();
    in.close();
}
