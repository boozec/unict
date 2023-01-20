#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

void
activity(vector<pii> v, ostream& out)
{
	int n = v.size();
	int c = 0;
	for (int i = 0; i < n; ++i) {
		for (int k = i+1; k < n; ++k) {
			int pivot = v[i].second;
			int lc = 1;
			for (int j = k; j < n; ++j) {
				if (v[j].first >= pivot) {
					lc++;
					pivot = v[j].second;
				}
			}

			c = max(c, lc);
		}
	}

	out << c << endl;
}

int
main(int argc, char** argv)
{
	int ts = (argc > 1) ? stoi(argv[1]) : 100;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n;
	string s;
	int x1, x2;

	for (int i = 0; i < ts; ++i) {
		fin >> n;
		vector<pii> v;

		for (int j = 0; j < n; ++j) {
			fin >> s;
			x1 = stoi(s.substr(1, s.length()));
			fin >> s;
			x2 = stoi(s.substr(0, s.length()-1));
			v.push_back({x1, x2});
		}

		sort(v.begin(), v.end(), [] (pii x1, pii x2) {
			return x1.second < x2.second;
		});

		activity(v, fout);
	}

	fin.close();
	fout.close();

	return 0;
}
