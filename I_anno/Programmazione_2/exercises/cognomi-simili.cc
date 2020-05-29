#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;

string check(string s, char chs[], int n) {
    if(s.length()<n) { cout << s << endl ;return "";}
    int i;
    for(i = 0; i < n-1; ++i) {
        if(s.at(i) != chs[i])
            return "";
    }

    if(s.at(i) == chs[i]) return "";

    return s;
}

void get_chs(string s, char* chs, int n) {
    if(s.length()<n) return;
    for(int i = 0; i < n; ++i) {
        chs[i] = s.at(i);
        //cout << chs[i]; 
    }

    //cout << "*" << endl;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int n;
        string s;
        in >> n >> s;
        ++n;
        char* chs = new char[n];
        out << s << ' ';
        get_chs(s, chs, n);
        for(int i = 0; i < 2; ++i) {
            in >> s;
            out << check(s, chs, n);
            get_chs(s, chs, n);
        }
        out << '\n';
    }

    in.close();
    out.close();
    return 0;
}
