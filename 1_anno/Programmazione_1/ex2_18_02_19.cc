#include<iostream>
#include<cctype>

using namespace std;

short func(string (*M)[4], unsigned short k, unsigned short s) {
    short counter{};

    for(int i = 0; i < 4; ++i) {
        short _rowcounter{};
        for(int j = 0; j < 3; ++j) {
            short _vocals{};
            for(char& c : M[j][i]) {
                switch(tolower(c)) {
                    case 'a': case 'e': case 'i': case 'o': case 'u':
                        ++_vocals;
                        break;
                    default: break;
                }
            }

            if(_vocals < s) ++_rowcounter;
        }

        if(_rowcounter >= k) ++counter;
    }

    return counter;
}


int main() {
    string M[3][4] = {
        {"HEI", "we", "ciao", "com'è?"},
        {"HEI", "we", "ciao", "com'è?"},
        {"HEI", "we", "ciao", "com'è?"},
    };
    
    cout << func(&M[0], 2, 3);


    return 0;
}
