#include <iostream>
#include <random>
#include <windows.h>
#include <algorithm>
#include <random>
#include "Header.h"

#define pb push_back

typedef long long ll;

using namespace std;

const ll n = 24;

vector <ll> shuffle(vector <ll> deck) {
	random_device rd; 
	mt19937 g(rd());
	shuffle(deck.begin(), deck.end(), g);
	return deck;
}

int main() {
	SetConsoleOutputCP(65001);
	random_device genQ,genDeck,genC,genD;
	uniform_int_distribution<ll> dist(2, 1e9);

	if (n * 2 + 5 > 52) {
		cout << "Not correct n\n";
		return 0;
	}

	ll p,q;
	vector <pair<ll, ll>> keys(n);
	vector <ll> deck;
							//  Diamond        Club           Heart          Spade
	vector<string> suit = { "\xE2\x99\xA6","\xE2\x99\xA3","\xE2\x99\xA5","\xE2\x99\xA0" };
	vector<string> names = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
	for (ll i = 0; i < names.size(); ++i) {
		for (ll j = 2; j < suit.size() + 2; ++j) {
			deck.pb(i * suit.size() + j);
		}
	}
	
	do {
		q = dist(genQ);
		p = 2 * q + 1;
	} while (!(isPrime(p) && isPrime(q)));

	uniform_int_distribution<ll> distC(2, p-2);

	for (auto& i : keys) {
		do {
			i.first = distC(genC);
		} while (evklid(i.first, p - 1)[0] != 1);
		i.second = evklid(i.first, p - 1)[2];
		while (i.second < 0) {
			i.second += (p - 1);
		}
	}

	for (auto& j : keys) {
		for (auto& i : deck){
			i = fastExp(i, j.first, p);
		}
		deck = shuffle(deck);
	}
	vector <vector<ll>> players;
	vector <ll> desk;
	for (int i = 0; i < 2 * n; i+=2) {
		players.pb({ deck[i],deck[i + 1] });
	}
	for (int i = deck.size()-1; desk.size() < 5; --i) {
		desk.pb(deck[i]);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j != i) {
				for (int k = 0; k < players[i].size(); ++k) {
					players[i][k] = fastExp(players[i][k], keys[j].second, p);
				}
			}
		}
		for (int k = 0; k < players[i].size(); ++k) {
			players[i][k] = fastExp(players[i][k], keys[i].second, p);
		}
	}
	for (int i = 0; i < desk.size(); ++i)
		for (int j = 0; j < n; ++j) {
			desk[i] = fastExp(desk[i], keys[j].second, p);
	}

	int count = 1;
	cout << "Desk:\n";
	for (auto& i : desk) {
		cout << names[(i - 2) / suit.size()] << suit[(i - 2) % suit.size()] << " ";
	}
	cout << "\n\n";
	for (auto& i : players) {
		cout<<"Player #" << count << " cards: ";
		for (auto& j : i) {
			cout  << names[(j - 2) / suit.size()] << suit[(j - 2) % suit.size()] << " ";
		}
		count++;
		cout << endl;
	}

	return 0;
}
