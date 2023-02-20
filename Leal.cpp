/*
	Matheus Leal V

	OBI 2019 - Fase 03 - Corrida

	Complexidade O( (N + Q)*log^2(N) )
*/
#include <bits/stdc++.h>
#define N 200010
#define l (2*nod)
#define r (2*nod + 1)
#define mid ((a + b)/2)
using namespace std;

int n, q, cnt, vis[5*N];

int tree[4*N], lazy[4*N], grau[5*N], degree[5*N];

vector<int> grafo[5*N];

vector<int> nodes;

void dfs(int x)
{
	vis[x] = 1;

	for(auto v: grafo[x])
	{
		grau[v] ++;

		if(!vis[v])
			dfs(v);
	}
}

void build(int nod, int a, int b)
{
	if(a == b)
	{
		tree[nod] = a;

		return;
	}

	build(l, a, mid), build(r, mid + 1, b);

	tree[nod] = ++cnt;

	grafo[tree[nod]].push_back(tree[l]);

	grafo[tree[nod]].push_back(tree[r]);
}

void add_edge(int nod, int a, int b, int i, int j, int x)
{
	if(j < a or i > b) return;

	if(i <= a and j >= b)
	{
		grafo[x].push_back(tree[nod]);

		return;
	}

	add_edge(l, a, mid, i, j, x);

	add_edge(r, mid + 1, b, i, j, x);
}

//Top sort para verificar se tem ciclo
bool check()
{
	memset(grau, 0, sizeof grau);

	memset(vis, 0, sizeof vis);

	vector<int> lista;

	for(int i = 0; i < 5*N; i++)
		if(!vis[i])
			dfs(i);

	for(int i = 0; i < 5*N; i++)
	{
		if(!grau[i])
			lista.push_back(i);
	}

	for(int i = 0; i < lista.size(); i++)
	{
		int x = lista[i];

		for(auto v: grafo[x])
		{
			grau[v] --;

			if(!grau[v])
				lista.push_back(v);
		}
	}

	return lista.size() == 5*N;
}

int X[N], A[N], B[N];

int main()
{
	cin>>n>>q;

	cnt = n;

	build(1, 1, n);

	for(int i = 1, x, a, b; i <= q; i++) cin>>X[i]>>A[i]>>B[i];

	int ini = 1, fim = q, md, best = -1;

	//Busca binaria na resposta
	while(fim >= ini)
	{
		md = (ini + fim)/2;

		for(int j = 0; j <= n; j++) grafo[j].clear();

		for(int i = 1; i <= md; i++) add_edge(1, 1, n, A[i], B[i], X[i]);

		if(!check()) best = md, fim = md - 1;

		else ini = md + 1;
	}

	cout<<best<<"\n";
}