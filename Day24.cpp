#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;



struct group
{
	int num;
	int units;
	int hp;
	int attack;
	int type;
	int initiative;
	bool side;
	bool weak[5];
	bool immune[5];
	bool alive;
	bool targeted;
	int target;
	int EP;
	int damage;

	group(int n, int u, int h, int a, int t, int i, bool s) : num(n),units(u),hp(h),attack(a),type(t),initiative(i),side(s),alive(true),targeted(false),target(-1),EP(u*a) {}
};

struct less_than_select
{
	inline bool operator() (const group& a1, const group& a2)
	{
		if (a1.EP != a2.EP) {
			return a1.EP > a2.EP;
		}
		else return a1.initiative > a2.initiative;
	}
};

struct less_than_attack
{
	inline bool operator() (const group& a1, const group& a2)
	{
		return a1.initiative > a2.initiative;
	}
};

int Type(string t) {
	if (t.compare("slashing") == 0) {
		return 0;
	}
	if (t.compare("cold") == 0) {
		return 1;
	}
	if (t.compare("bludgeoning") == 0) {
		return 2;
	}
	if (t.compare("radiation") == 0) {
		return 3;
	}
	if (t.compare("fire") == 0) {
		return 4;
	}

}

vector<group> o;
vector<group> v;

bool finished() {
	bool s;
	int i;
	for (i = 0; i < v.size(); i++) {
		if (v[i].alive) {
			s = v[i].side;
			break;
		}
	}
	for (int j = i + 1; j < v.size(); j++) {
		if (v[j].alive && v[j].side != s) {
			return false;
		}
	}
	return true;
}

int damage(int i, int type, int d) {
	if (v[i].weak[type]) {
		return 2 * d;
	}
	else if (v[i].immune[type]) {
		return 0;
	}
	else {
		return d;
	}
}

int main(int argc, char * argv[]) {

	regex re1("([\\d]+) units each with ([\\d]+) hit points ");
	regex re2("does ([\\d]+) ([a-z]+) damage at initiative ([\\d]+)");
	regex weak1("weak to ([a-z]+)");
	regex weak2("weak to ([a-z]+), ([a-z]+)");
	regex imm1("immune to ([a-z]+)");
	regex imm2("immune to ([a-z]+), ([a-z]+)");
	string s;
	smatch match;
	smatch match2;
	smatch match3;
	ifstream f("data.txt");
	int number = 0; 
	bool side = true;
	getline(f, s);
	while (getline(f, s)) {
		if (s.compare("") == 0) {
			getline(f, s);
			side = false;
			getline(f, s);
		}
		int units;
		int hp;
		if (regex_search(s, match, re1) == true) {
			units = stoi(match.str(1));
			hp = stoi(match.str(2));
		}
		int attack;
		int init;
		int t;
		if (regex_search(s, match, re2) == true) {
			attack = stoi(match.str(1));
			init = stoi(match.str(3));
			string type = match.str(2);
			t = Type(type);
		}
		group g = group(number, units, hp, attack, t, init, side);
		for (int i = 0; i < 5; i++) {
			g.weak[i] = false;
			g.immune[i] = false;
		}
		if(regex_search(s, match2, weak2) == true) {
			string type = match2.str(1);
			int t = Type(type);
			g.weak[t] = true;
			type = match2.str(2);
			t = Type(type);
			g.weak[t] = true;
		}
		else if (regex_search(s, match2, weak1) == true) {
			string type = match2.str(1);
			int t = Type(type);
			g.weak[t] = true;
		}
		if (regex_search(s, match3, imm2) == true) {
			string type = match3.str(1);
			int t = Type(type);
			g.immune[t] = true;
			type = match3.str(2);
			t = Type(type);
			g.immune[t] = true;
		}
		else if (regex_search(s, match3, imm1) == true) {
			string type = match3.str(1);
			int t = Type(type);
			g.immune[t] = true;
		}
		o.push_back(g);
		number++;
	}


	/*for (int i = 0; i < v.size(); i++) {
		group g = v[i];
		cout << "group " << g.num << " has " << g.units << " units with hp " << g.hp << " and " << g.attack << " of type " << g.type << " at init " << g.initiative << endl;
		cout << "It is immune to ";
		for (int i = 0; i < 5; i++) {
			if (g.immune[i]) {
				cout << i << " ";
			}
		}
		cout << endl << "It is weak to ";
		for (int i = 0; i < 5; i++) {
			if (g.weak[i]) {
				cout << i << " ";
			}
		}
		cout << endl;
		if (g.side) {
			cout << "It is part of the immune system\n";
		}
		else {

			cout << "It is part of the infection\n";
		}
	}*/

	int boost = 0;

	while (boost < 75) {
		v.clear();
		for (int i = 0; i < o.size(); i++) {
			v.push_back(o[i]);
		}
		for (int i = 0; i < v.size(); i++) {
			if (v[i].side) {
				v[i].attack += boost;
				v[i].EP = v[i].units * v[i].attack;
			}
		}
		int rounds = 0;
		while (!finished() && rounds < 2500) {//prevent deadlocks running forever
			rounds++;
			sort(v.begin(), v.end(), less_than_select());
			for (int i = 0; i < v.size(); i++) {
				if (v[i].alive) {
					int bestDamage = -1;
					int target;
					v[i].target = -1;
					for (int j = 0; j < v.size(); j++) {
						if (v[i].side != v[j].side && v[j].alive && !v[j].targeted) {
							int d = damage(j, v[i].type, v[i].EP);
							if (d > bestDamage) {
								bestDamage = d;
								target = j;
							}
							else if (d == bestDamage) {
								if (v[j].EP > v[target].EP) {
									bestDamage = d;
									target = j;
								}
								else if (v[j].EP == v[target].EP) {
									if (v[j].initiative > v[target].initiative) {
										bestDamage = d;
										target = j;
									}
								}
							}
						}
					}
					if (bestDamage > 0) {
						v[i].target = v[target].num;
						v[target].targeted = true;
						v[i].damage = bestDamage;
					}
					else {
						v[i].target = -1;
					}
				}
			}

			sort(v.begin(), v.end(), less_than_attack());
			for (int i = 0; i < v.size(); i++) {
				if (v[i].alive && v[i].target != -1) {
					int target;
					for (int j = 0; j < v.size(); j++) {
						if (v[i].target == v[j].num) {
							target = j;
							break;
						}
					}
					int dam = damage(target, v[i].type, v[i].EP);
					int kills = dam / v[target].hp;
					//cout << dam << " " << v[target].hp << " " << kills <<" " << v[target].units << " " << v[target].attack << " " << v[target].EP << endl;
					v[target].units -= kills;
					v[target].EP = v[target].units * v[target].attack;
					//cout << dam << " " << v[target].hp << " " << kills << " " << v[target].units << " " << v[target].attack << " " << v[target].EP << endl;
					if (v[target].units <= 0) {
						v[target].alive = false;
					}
				}
			}
			for (int i = 0; i < v.size(); i++) {
				v[i].targeted = false;
				v[i].target = -1;
			}
		}
		cout << "Combat over for boost " << boost << " after " << rounds << " rounds" << endl;
		int total = 0;
		bool si;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].alive) {
				si = v[i].side;
				total += v[i].units;
			}
		}
		if (si) {
			cout << "The immune system had " << total << " units left." << endl;
		}
		else {
			cout << "The infection had " << total << " units left." << endl;
		}

		for (int i = 0; i < v.size(); i++) {
			if (v[i].side == true && v[i].alive) {//survivor is the immune system
				cout << "Immune system won with boost " << boost << endl;
				break;
			}
		}
		boost++;
	}

	return 0;
}