#include "Header.h"
#include <fstream>

void Shamir(string FILENAME) {
	random_device gen;
	uniform_int_distribution<ll> dist(2, 1e9);
	ll p = dist(gen);
	while (!prime(p)) {
		p = dist(gen);
	}
	uniform_int_distribution<ll> distP(1, p - 1);
	ll Ca = distP(gen), da;
	while (evklid(Ca, p - 1)[0] != 1) {
		Ca = distP(gen);
	}
	da = evklid(Ca, p - 1)[2];
	while (da < 0) {
		da += (p - 1);
	}
	ll Cb = distP(gen), db;
	while (evklid(Cb, p - 1)[0] != 1) {
		Cb = distP(gen);
	}
	db = evklid(Cb, p - 1)[2];
	while (db < 0) {
		db += (p - 1);
	}
	vector <ll> m1;
	char buf;
	string NEWFILENAME = "Shamir " + FILENAME;
	ifstream in(FILENAME, ios::binary);
	ofstream out(NEWFILENAME, ios::binary);
	while (in.read((char*)& buf, sizeof(buf))) {
		ll x1 = fastExp(buf, Ca, p);
		ll x2 = fastExp(x1, Cb, p);
		ll x3 = fastExp(x2, da, p);
		char tmp = fastExp(x3, db, p);
		out.write((char*)& tmp, sizeof(tmp));
	}
	out.close();
}

void EG(string FILENAME) {
	random_device gen;
	uniform_int_distribution<ll> dist(2, 1e9);
	ll q = dist(gen);
	ll p = 2 * q + 1;
	while (!(prime(q) && prime(p))) {
		q = dist(gen);
		p = 2 * q + 1;
	}
	uniform_int_distribution<ll> distG(2, p - 2);
	ll g = distG(gen);
	while (fastExp(g, q, p) == 1) {
		g = distG(gen);
		if (g >= p - 1) {
			g = distG(gen);
		}
	}
	ll C = distG(gen);
	ll d = fastExp(g,C,p);
	ll k = distG(gen);
	char buf;
	string NEWFILENAME = "EG " + FILENAME;
	ifstream in(FILENAME, ios::binary);
	ofstream out(NEWFILENAME, ios::binary);
	while (in.read((char*)& buf, sizeof(buf))) {
		ll r = fastExp(g, k, p);
		ll e = ((buf % p) * fastExp(d, k, p)) % p;
		char tmp = ((e % p) * fastExp(r, p - 1 - C, p)) % p;
		out.write((char*)& tmp, sizeof(tmp));
	}
	out.close();
}

void RSA(string FILENAME) {
	random_device gen;
	uniform_int_distribution<ll> dist(2, 1e4);
	ll q = dist(gen);
	ll p = dist(gen);
	while (!(prime(q) && prime(p))) {
		q = dist(gen);
		p = dist(gen);
	}
	ll N = p * q, f=(p-1)*(q-1);
	uniform_int_distribution<ll> distD(2, 1e9);
	ll d = distD(gen), C;
	while (evklid(f, d)[0] != 1) {
		d = distD(gen);
	}
	C = evklid(f, d)[1];
	while (C < 0) {
		C += f;
	}
	char buf;
	string NEWFILENAME = "RSA " + FILENAME;
	ifstream in(FILENAME, ios::binary);
	ofstream out(NEWFILENAME, ios::binary);
	while (in.read((char*)& buf, sizeof(buf))) {
		ll e = fastExp(buf, d, N);
		char tmp = fastExp(e, C, N);
		out.write((char*)& tmp, sizeof(tmp));
	}
	out.close();
}

void Vernam(string FILENAME) {
	random_device gen;
	uniform_int_distribution<ll> dist(1, 1e9);
	ll X = dist(gen);
	char buf;
	string NEWFILENAME = "Vernam " + FILENAME;
	string NEWFILENAME1 = "VernamCript " + FILENAME;
	ifstream in(FILENAME, ios::binary);
	ofstream out(NEWFILENAME, ios::binary);
	ofstream out1(NEWFILENAME1, ios::binary);
	while (in.read((char*)& buf, sizeof(buf))) {
		char C = buf ^ X;
		char tmp = C ^ X;
		out.write((char*)& tmp, sizeof(tmp));
	}
	out.close();
	out1.close();
}

int32_t main() {
	Shamir("scr.png");
	EG("scr.png");
	RSA("scr.png");
	Vernam("scr.png");
}
