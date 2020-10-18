#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>

using namespace std;
int insertionsort(vector<int>& a, int n) {
    int c = 0;
    for(int i = 1; i < n; ++i) {
        int j = i-1;
        int key = a[i];
        while(j > -1 && a[j] > key) {
            swap(a[j+1], a[j]);
            --j;
            c++;
        }
        a[j+1] = key;
    }
    return c;
}
int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int ts = 0; ts < 100; ++ts) {
        int N;
        in >> N;
        int a, b;
        vector<int> v;
        for(int i = 0; i < N; ++i) {
            in >> a >> b;
            v.push_back(a+b);
        }
        out << insertionsort(v, v.size()) << endl;
    }
    in.close();
    out.close();
    return 0;
}
