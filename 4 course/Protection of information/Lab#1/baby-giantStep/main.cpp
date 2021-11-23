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
#define lp(i,n) for (long long i=0; i<n; ++i)
#define all(v) (v).begin(), (v).end()
#define rsort(a) sort (a.begin(),a.end(),greater<int>());

using namespace std;
// mt19937 rng(((int) std::chrono::steady_clock::now().time_since_epoch().count()));

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

ll fastExp(ll a, ll x, ll p) {
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

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll a, p, y;

int32_t main() {
	random_device gen;
	uniform_int_distribution<ll> dist(1, 1e9);
	cout << "Range of random: " << dist << "\n\n";
	do {
		a = dist(gen);
		p = dist(gen);
	} while (gcd(a, p) != 1);
	uniform_int_distribution<ll> distY(2, p-1);
	y = distY(gen);
	printf("a = %lld\np = %lld\ny = %lld\n\n", a, p, y);
	ll m = (ll)sqrt(p+.0) + 1;
	ll k = m+1;
	map<ll, ll> mp;
	ll an = 1;
	lp(i, m) {
		an = (an%p * a%p) % p;
	}
	for (ll i = 1, tmp = an; i <= k; ++i) {
		if (!mp.count(tmp)) {
			mp[tmp] = i;
		}
		tmp = (tmp%p * an%p) % p;
	}
	for (ll i = 0; i < m; ++i) {
		ll tmp = (y%p*fastExp(a, i, p))%p;
		if (mp.count(tmp)) {
			cout << "x = " << m * mp[tmp] - i << endl;
			if (y == fastExp(a, m * mp[tmp] - i, p)) {
				cout << "Check: OK\n";
			}else cout << "Check: Error!\n";
			return 0;
		}
	}
	cout << "No answer\n";
	return 0;
}
