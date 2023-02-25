#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int vet[N], n, r[N], l[N];

int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> vet[i];
	int res = 0;
	l[0] = vet[0];
	r[n-1] = vet[n-1];
	for (int i = 1; i < n; ++i)
		l[i] = max(l[i-1], vet[i]);
	for (int i = n-2; i >= 0; --i)
		r[i] = max(r[i+1], vet[i]);
	for (int i = 0; i < n; ++i)
		res += vet[i] < r[i] && vet[i] < l[i];
	cout << res << endl;
}

