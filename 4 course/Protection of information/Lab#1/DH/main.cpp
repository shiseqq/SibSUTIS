#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <iterator>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <ctime>
#include <chrono>
#include <random>

#define pi acos(-1)
#define pb push_back
#define F first
#define S second
#define ll long long
#define SP setprecision
#define lp(i,n) for (int i=0; i<n; ++i)
#define all(v) (v).begin(), (v).end()
#define rsort(a) sort (a.begin(),a.end(),greater<int>());

using namespace std;

string revITB(ll x) {
	string ans;
	if (x == 0) ans = '0';
	while (x) {
		if (x % 2 == 0)
			ans += '0';
		else ans += '1';
		x /= 2;
	}
	return ans;
}

ll fastExp(ll a,ll x, ll p) {
	ll y = 1;
	string biX = revITB(x);
	vector <ll> mods;
	ll tmp = a % p;
	mods.pb(tmp);
	for (int i = 0; i < biX.size() - 1; ++i) {
		mods.pb((mods[i] % p * mods[i] % p) % p);
	}
	for (int i = 0; i < biX.size(); ++i) {
		if (biX[i] == '0')
			continue;
		else {
			y *= mods[i] % p;
			y %= p;
		}
	}
	return y % p;
}

bool prime(ll x) {
	for (ll i = 2; i < sqrt(x); ++i) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
}

int32_t main() {
	random_device gen;
	uniform_int_distribution<ll> dist(2, 1e9);
	ll q = dist(gen);
	ll p=2*q+1;
	while (!(prime(q) && prime(p))) {
		q = dist(gen);
		p = 2 * q + 1;
	}
	uniform_int_distribution<ll> distG(2, p-2);
	ll g = distG(gen);
	while (fastExp(g, q, p) == 1) {
		g = distG(gen);
		if (g >= p - 1) {
			g = distG(gen);
		}
	}
	printf("q = %lld\np = %lld\ng = %lld\n\n", q, p, g);
	ll xa = distG(gen), xb = distG(gen), xc = distG(gen);
	ll ya = fastExp(g,xa,p), yb = fastExp(g, xb, p), yc = fastExp(g, xc, p);
	printf("Ya = %lld\nYb = %lld\nYc = %lld\n\n", ya, yb, yc);
	ll zab = fastExp(yb, xa, p), zba = fastExp(ya, xb, p);
	if (zab == zba) {
		cout << "Answer = " << zab << endl;
	}
	else {
		cout << "Error! Zab!=Zba\n" << "Zab = " << zab << endl << "Zba = " << zba << endl;
	}
	return 0;
}
