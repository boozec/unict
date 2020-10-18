#include <iostream>
#include <algorithm>
#include <vector>
#define K 2
#define N 3

using namespace std;

template<int KK, int NN>
bool func(int (&a)[KK][NN][NN], int w) {
	vector<int> list;
	for(int i = 0; i < KK; ++i) {
		list.clear();
		for(int j = 0; j < NN; ++j)
			list.push_back(a[i][j][j]);
			
		auto mm = minmax_element(begin(list), end(list));
		float media = (static_cast<float>(*mm.first)+static_cast<float>(*mm.second))/2;
		if(media <= w)
			return true;
	}
	
	return false;
}

int main() {
	int a[K][N][N] = {
		{
			{1, 2, 30},
			{1, 80, 3},
			{1, 2, 3},
		},
		{
			{1, 2, 30},
			{1, 20, 3},
			{1, 2, 3},
		}};
		
	cout << func(a, 5);

    return 0;
}
