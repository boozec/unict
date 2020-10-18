#include <iostream>

using namespace std;

template<int N, int M>
short func(string (&S)[N][M], short (&B)[M]) {
    short index{0};
    short ex_count{0};
    short i{0};

    for(auto const& row : S) {
        short count{0};
        if(i > M)
            break;

        for(auto const& col : row) {
            if(col.length() <= B[i])
                ++count;            
        }

        if(count > ex_count) {
            index = i;
            ex_count = count;
        }
        ++i;
    }

    return index;
}

int main() {
    string t[2][3]{
        {"greeeeee", "aaaaaaa", "bbbbbb"},
        {"abc", "sooca", "icsdi"},
    };
    short bb[3]{3, 10};
    short x = func(t, bb);

    cout << x << endl;
    return 0;
}
