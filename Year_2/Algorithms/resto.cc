#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#define INF 9999999

using namespace std;

int
change(vector<int>& coins, int sum)
{
	int n = coins.size();

	int* table = new int[sum+1];
	memset(table, sum, 0);

	table[0] = 0;
	for (int i = 1; i < sum+1; ++i) {
		table[i] = INF;
		for (int j = 0; j < n; ++j) {
			if (coins[j] <= i)
				table[i] = min(table[i], 1+table[i-coins[j]]);
		}
	}

	int result = table[sum];
	delete[] table;

	return result;
}

int
main(int argc, char** argv)
{
	int ts = (argc > 1) ? stoi(argv[1]) : 100;
	int s, n;
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	for (int i = 0; i < ts; ++i) {
		fin >> s >> n;
		vector<int> v(n);
		for (int j = 0; j < n; ++j) {
			fin >> v[j];
		}

		fout << change(v, s) << endl;
	}


	fin.close();
	fout.close();
	return 0;
}
