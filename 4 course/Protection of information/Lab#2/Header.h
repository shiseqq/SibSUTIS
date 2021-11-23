#pragma once
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

bool prime(ll x) {
	for (ll i = 2; i < sqrt(x); ++i) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
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

vector <ll> evklid(ll a, ll b) {
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
	return u;
}

