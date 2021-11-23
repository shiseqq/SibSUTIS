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

ll a, b;

ll _gcd(ll a, ll b) {
	return b ? _gcd(b, a % b) : a;
}

bool check(ll x, ll y, ll gcd) {
	return (a * x + b * y == gcd);
}

int32_t main() {
	random_device gen;
	uniform_int_distribution<ll> dist(1, 1e9);
	cout << "Range of random: " << dist << "\n\n";
	a = dist(gen);
	b = dist(gen);
	printf("a = %lld\nb = %lld\n\n", a, b);
	if (a < b)swap(a, b);
	ll q = a / b;
	vector <ll> u = { b,0,1 };
	vector <ll> v = { a % b,1,-q };
	vector <ll> t = v;
	while (v[0] != 0) {
		q = u[0] / v[0];
		t = { u[0] % v[0], u[1] - q * v[1], u[2] - q * v[2] };
		u = v;
		v = t;
	}
	cout << "GCD(a,b) = " << u[0] << endl;
	cout << "GCD from emaxx: " << _gcd(a, b) << endl;
	cout << "Check: " << (check(u[1], u[2], u[0]) ? "OK\n" : "ERROR\n");
	return 0;
}
