#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair <int,int>
#define ull unsigned long long
#define mp make_pair
#define _ ios_base::sync_with_stdio(false);cin.tie(0);

using namespace std;

const int MAXN = (int)(2e5)+2;
const int MOD = (int)(1e9)+7;


int n, m, blocked[MAXN],t[4*MAXN], add[4*MAXN];

struct data {
  	int s,l,r,d,type,id;
}a[MAXN];

bool cmp(data A, data B) {
 	if (A.s != B.s) return A.s < B.s;
 	return A.type < B.type;
}
void push(int v) {
	if (add[v]!=-1) {
	 	t[v+v] = add[v];
	 	t[v+v+1] = add[v];
	 	add[v+v] = add[v];
	 	add[v+v+1] = add[v];
	 	add[v] = -1;
	}
}
void upd(int l, int r, int x, int v = 1, int tl = 1, int tr = n) {
	if (l > tr || tl > r) return;
	if (l <= tl && tr <= r) {
	 	t[v] = x;
	 	add[v] = x;
	 	return;
	}
	push(v);
	int tm = (tl+tr) >> 1;
	upd(l,r,x,v+v,tl,tm);
	upd(l,r,x,v+v+1,tm+1,tr);
	t[v] = max(t[v+v],t[v+v+1]);
}
int getmax(int l, int r, int v = 1, int tl = 1, int tr = n) {
 	if (l>tr||tl>r) return 0;
 	if (l<=tl && tr <= r) return t[v];
 	push(v);
 	int tm = (tl+tr) >> 1;
 	return max(getmax(l,r,v+v,tl,tm),getmax(l,r,v+v+1,tm+1,tr));
 	                                                      	
}                                                      


int main() {
	_
	#ifdef LOCAL
	freopen("in","r",stdin);
	freopen("out","w",stdout);
	#endif
	cin >> n >> m;
	int sz = m;
	for (int i = 1; i <= m; i++) {
	 	cin >> a[i].s >> a[i].l >> a[i].r >> a[i].d;
	 	a[i].type=1;
	 	a[i].id = i;
	 	a[++sz] = {a[i].s+a[i].d,a[i].l,a[i].r,a[i].s,-1,i};
	}
	sort(a+1,a+1+sz,cmp);
	memset(add,-1,sizeof add);

	for (int i = 1; i <= sz; i++) {
	 	if (a[i].type==1) {
	 		if (getmax(a[i].l,a[i].r) == 0)
	 		{
	 		 	blocked[a[i].id] = 1;
	 		 	upd(a[i].l,a[i].r,1);
	 		}
	 	}
	 	else {
	 		if (!blocked[a[i].id]) continue;
			upd(a[i].l,a[i].r,0);
	 	}
	}
	for (int i = 1; i <= m; i++)
		if (blocked[i])
			puts("Yes");
		else
			puts("No");
	return 0;
}