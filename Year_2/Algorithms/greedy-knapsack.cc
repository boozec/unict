#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int
main(int argc, char** argv)
{
	int ts = (argc > 1) ? stoi(argv[1]) : 100;
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	for (int i = 0; i < ts; ++i) {
		int n, target;
		vector<int> v;
		fin >> n >> target;
		v.resize(n);

		for (int j = 0; j < n; ++j) {
			fin >> v[j];
		}

		sort(v.begin(), v.end(), [](int a, int b) {
			return a > b;
		});

		int result { 0 };
		for (int j = 0; j < min(target, n); ++j)
			result += v[j];

		fout << result << endl;
	}

	fin.close();
	fout.close();

	return 0;
}
