#include<iostream>
#include<fstream>
#include<map>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        string P{}, L{};
        in >> P;
        in >> L;
        map<char, int> chars;

        for(auto const& c : P) {
            (chars.find(c) == chars.end()) ? chars[c] = 1 : chars[c]+=1;
        }
        int lenn = L.length();
        int lenp = P.length();
        int counter{};

        for(int i = 0; i < lenn-lenp+1; ++i) {
            map<char, int> tmp;
            bool check{true};
            for(int j = i; j < i+lenp; ++j) {
                (tmp.find(L[j]) == tmp.end()) ? tmp[L[j]] = 1 : tmp[L[j]]+=1;
            }
            for(auto const &i : tmp) {
                if(chars[i.first] != tmp[i.first]) {
                    check = false;
                    break;
                }
            }
            if(check)
                ++counter;
        }
        out << counter << endl;

    }

    out.close();
    in.close();
    return 0;
}
