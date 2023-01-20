#include <iostream>
#include <fstream>

using namespace std;

int
lev(string x, string y)
{
	int m = x.length() + 1;
	int n = y.length() + 1;
	int i, j;

	int** c = new int*[m];

	for (i = 0; i < m; ++i)
		c[i] = new int[n];

	for (i = 0; i < m; ++i)
		c[i][0] = i;

	for (i = 0; i < n; ++i)
		c[0][i] = i;


	for (i = 1; i < m; ++i) {
		for (j = 1; j < n; ++j) {
			int cost = (x[i-1] != y[j-1]);

			c[i][j] = min(min(c[i-1][j]+1, c[i][j-1]+1), c[i-1][j-1]+cost);
		}
	}

	int r = c[m-1][n-1];

	for (i = 0; i < m; ++i)
		delete[] c[i];

	delete[] c;
	
	return r;
}

int
main(int argc, char** argv)
{
	int ts = (argc > 1) ? stoi(argv[1]) : 100;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n, m;
	string s1, s2;


	for (int i = 0; i < ts; ++i) {
		fin >> n >> m >> s1 >> s2;

		fout << lev(s1, s2) << endl;
	}

	fin.close();
	fout.close();

	return 0;
}
