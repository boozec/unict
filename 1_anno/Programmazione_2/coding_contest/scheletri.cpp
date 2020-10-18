#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int find_i(int index, vector<int> cms) {
    for(int i = index; i < cms.size(); ++i) {
        if(cms.at(i) != 0)
            return i;
    }
    
    return 0;
}

int find_j(int index, vector<int> cms) {
    for(int j = index; j < cms.size()-1; ++j) {
        if(cms.at(j+1) == 0)
            return j+1;
    }
    
    return cms.size();
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    short N;
    for(int __c = 0; __c < 100; ++__c) {
        in >> N;
        vector<int> cms;
        int el;
        for(short i = 0; i < N; ++i) {
            in >> el;
            cms.push_back(el);
        }
        
        int counter{};
        int i{}, j{};
        while(count_if(begin(cms), end(cms), [](int num) { return num == 0; } ) != cms.size() ) {
            i = find_i(i, cms);
            j = find_j(i, cms);
            for(int ii = i; ii < j; ++ii) {
                --cms[ii];
            }
            ++counter;
        }
        out << counter << endl;
    }

    out.close();
    in.close();
    return 0;
}
