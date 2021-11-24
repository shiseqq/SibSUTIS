#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Header.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono> 
#include <conio.h>
#include <map>
#include <cstdio>
#include <windows.h>
#include "md5.h"

#pragma execution_character_set( "utf-8" )

using namespace std;

class Server {
public:
	Server() {
		ll p = protectedPrime();
		ll q = protectedPrime();
		n = p * q;
		ll phi = (p - 1) * (q - 1);
		random_device gen;
		uniform_int_distribution<ll> dist(2, 1e9);
		while (1) {
			c = dist(gen);
			vector<ll> tmp = evklid(phi, c);
			if (tmp[0] == 1 && tmp[2] != 0) {
				d = (tmp[2] + (phi)) % (phi);
				if ((c * d) % (phi) == 1)
					break;
			}
		}
	}
	ll d;
	ll n;
	vector<ll> check(vector<ll> msg) {
		vector<ll> res;
		for (auto i : msg) {
			res.push_back(fastExp(i, c, n));
		}
		return res;
	}
private:
	ll c;
};

map<int, string> voteMap;

int main() {
	Server srv;
	voteMap[1] = "Yes";
	voteMap[2] = "No";
	voteMap[3] = "Abstained";
	int vote = 0;
	cout << "Vote:\n";
	cout << "1. Yes\n2. No\n3. Abstained\n";
	while (vote < 1 || vote>3) cin >> vote;
	string test = voteMap[vote];
	string h = md5(test);
	ll r, rr;
	ll n = srv.n;
	ll d = srv.d;
	random_device gen;
	uniform_int_distribution<ll> dist(2, 1e9);
	while (1) {
		r = dist(gen);
		vector<ll> tmp = evklid(n, r);
		if (tmp[0] == 1 && tmp[2] != 0) {
			rr = (tmp[2] + (n)) % (n);
			if ((r * rr) % (n) == 1)
				break;
		}
	}
	vector<ll> msg;
	for (auto& i : h) {
		msg.push_back((i * fastExp(r, d, n)) % n);
	}
	vector<ll> serverS = srv.check(msg);
	vector<ll> s;
	for (auto i : serverS)
		s.push_back((i * rr) % n);

	string e;
	for (auto i : s) {
		e += (char)fastExp(i, d, n);
	}
	cout << h << "\n" << e;
	return 0;
}


