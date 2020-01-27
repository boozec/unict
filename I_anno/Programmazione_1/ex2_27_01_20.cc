#include<iostream>
#include<set>

using namespace std;

template<int N, int M>
double func(string (&A)[N][M], string x, string y, short k, short w) {
    set<char> s;
    for(char const&c : x) s.insert(c);
    x = "";
    for(char const&c: s) x+=c;

    s.clear();
    for(char const&c : y) s.insert(c);
    y = "";
    for(char const&c: s) y+=c;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            s.clear();
            for(char const&c : A[i][j]) s.insert(c);
            A[i][j] = "";
            for(char const&c: s) A[i][j]+=c;
        }
    }

    short counter{};
    for(int i = 0; i < M; ++i) {
        short k_i{};
        for(int j = 0; j < N; ++j) {
            if(A[j][i].length() < w) continue;
            short char_counter{};
            for(char const& c: A[j][i]) {
                if(x.find(c) != std::string::npos && y.find(c) != std::string::npos)
                    ++char_counter;
            }
            if(char_counter >= w)
                ++k_i;
        }
        if(k_i >= k)
            ++counter;
    }

    return static_cast<double>(counter*100)/static_cast<double>(M);
}

int main() {
    string A[3][4] = {
        {"we,", "heila", "ciaone", ""},
        {"we,", "heila", "ciaone", ""},
        {"we,", "heila", "ciaone", ""},
    };

    cout << func(A, "we", "we", 2, 2);    

    return 0;
}
