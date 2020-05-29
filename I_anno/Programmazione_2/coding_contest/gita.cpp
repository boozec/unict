#include<iostream>
#include<fstream>
#include<vector>
#include<map>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    for(int c = 0; c < 100; ++c) {
        int N, L;
        in >> N >> L;
        vector<pair<short, int>> students;
        for(int i = 0; i < N; ++i) {
            int num;
            in >> num;
            students.push_back({num, 0});
        }

        int index, val;
        for(int i = 0; i < L; ++i) {
            in >> index >> val;
            students[index].second += val;
        }

        vector<pair<short, int>> errors;
        short _j{};
        for(auto const& i : students) {
            if(i.second < i.first) {
                errors.push_back({_j, i.first-i.second});
            }
            _j++;
        }

        out << errors.size() << ' ';
        for(auto const& i : errors) {
            out << i.first << ' ' << i.second << ' ';
        }
        out << endl;
    }
    out.close();
    in.close();
    return 0;
}
