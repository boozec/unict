#include <iostream>
#include <fstream>

using namespace std;

enum class Arrow {
	Top,
	Left,
	TopLeft,
};

int
lcs(string x, string y)
{
	int m = x.length()+1;
	int n = y.length()+1;
	int** C = new int*[m];
	Arrow** B = new Arrow*[m];
	int i, j;

	for (i = 0; i < m; ++i) {
		C[i] = new int[n];
		C[i][0] = 0;

		B[i] = new Arrow[n];
	}

	for (i = 0; i < n; ++i)
		C[0][i] = 0;

	for (i = 1; i < m; ++i) {
		for (j = 1; j < n; ++j) {
			if (x.at(i-1) == y.at(j-1)) {
				C[i][j] = C[i-1][j-1]+1;
				B[i][j] = Arrow::TopLeft;
			} else if (C[i-1][j] >= C[i][j-1]) {
				C[i][j] = C[i-1][j];
				B[i][j] = Arrow::Top;
			} else {
				C[i][j] = C[i][j-1];
				B[i][j] = Arrow::Left;
			}
		}
	}

	int r { 0 };
	for (i = m-1, j = n-1; i != 0 && j != 0; ) {
		if (B[i][j] == Arrow::TopLeft) {
			r++;
			i--;
			j--;
		} else if (B[i][j] == Arrow::Top) {
			i--;
		} else {
			j--;
		}
	}

	for (i = 0; i < m; ++i) {
		delete[] C[i];
		delete[] B[i];
	}
	delete[] C;
	delete[] B;

	return r;
}

int
main(int argc, char** argv)
{
	int ts = (argc > 1) ? stoi(argv[1]) : 100;

	ifstream fin("input.txt");
	ofstream fout("output.txt");

	for (int i = 0; i < ts; ++i) {
		int n;
		string s1, s2;
		fin >> n >> n >> s1 >> s2;
		fout << lcs(s1, s2) << endl;
	}

	fin.close();
	fout.close();

	return 0;
}
