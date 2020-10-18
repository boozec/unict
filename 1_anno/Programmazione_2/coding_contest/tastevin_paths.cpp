// It prints all possible paths

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int N;
        in >> N;
        vector<int> arr;
        int e;
        for(int i = 0; i < N; ++i) {
            in >> e;
            arr.push_back(e);
        }

        int max_value{};
        int value;

        for(int i = 0; i < N; ++i) {
            vector<int> tmp;
            tmp.push_back(i);
            value = arr[i];
            for(int j = i+2; j < N; ++j) {
                if(arr[j] >= value) {
                    tmp.push_back(j);
                    value = arr[j];
                    ++j;
                }
            }
            while(!tmp.empty()) {
                if(tmp.size() > max_value) {
                    for(auto const&i : tmp) {
                        cout << i << ' ';
                    }
                    cout << endl;
                    max_value = tmp.size();
                }
                int k = tmp.back();
                tmp.pop_back();
                if(tmp.size() > 0)
                    value = arr[tmp.back()];
                else
                    value = arr[k];
                for(int j = k+1; j < N; ++j) {
                    if(arr[j] >= value) {
                        value = arr[j];
                        tmp.push_back(j);
                        ++j;
                    }
                }
            }
        }

        out << max_value << '\n';
    }

    in.close();
    out.close();
    return 0;
}
