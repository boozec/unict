#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(short _ = 0; _ < 100; ++_) {
        int N, K, M;
        in >> N >> K >> M;
        int* path = new int[N+1];
        int i;
        for(i = 0; i < N; ++i)
            in >> path[i];

        path[i] = M;
        int start = 0;
        vector<int> values;
        /* 1 31 33 38 62 69 93 97 98 99 */
        /* x x     x  x   x          x       
         * K = 30
         */
        for(int i = 0; i < N+1; ++i) {
            if(path[i] - start > K) {
                for(int j = i-1; j >= 0; --j) {
                    if(path[i] - path[j] <= K) {
                        values.push_back(path[j]);
                        start = path[j];
                        i = j;
                        break;
                    }
                }
            }
        }

        // Stampa la path corretta per debug
        for(auto const& i: values) 
            cout << i << ' ';

        cout << endl;
        out << values.size() << endl;
        delete[] path;
    }


    out.close();
    in.close();

    return 0;
}
