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
// mt19937 rng(((int) std::chrono::steady_clock::now().time_since_epoch().count()));

ll a, x, p, y = 1;

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

int32_t main() {
	random_device gen;
	uniform_int_distribution<ll> dist(1, 1e9);
	cout << "Range of random: " << dist << "\n\n";
	a = dist(gen);
	x = dist(gen);
	p = dist(gen);
	printf("a = %lld\nx = %lld\np = %lld\n\n", a, x, p);
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
	cout << "Answer: " << y % p << endl;
	return 0;
}
