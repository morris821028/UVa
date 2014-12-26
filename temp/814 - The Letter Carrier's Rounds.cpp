#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <vector> 
using namespace std;

set<string> MTA;
int readMTA() {
	string cmd, mta, name;
	int n;
	while (cin >> cmd) {
		if (cmd == "*")	return 1;
		cin >> mta >> n; 
		for (int i = 0; i < n; i++) {
			cin >> name;
			MTA.insert(string(name) + "@" + string(mta));
		}
	}
	return 0;
}
void parse_address(const string& s, string& user, string& mta) {
  int k = s.find('@');
  user = s.substr(0, k);
  mta = s.substr(k+1);
}
int main() {
	string msg;
	readMTA();
	while (cin >> msg) {
		if (msg[0] == '*')	break;	
		vector<string> user, mta, mail;
		set<string> S;
		vector<int>	used;
		string u, m;
		parse_address(msg, u, m);
		user.push_back(u), mta.push_back(m);
		while (cin >> msg && msg[0] != '*') {
			parse_address(msg, u, m);
			if (S.count(u + "@" + m))	continue;
			S.insert(u + "@" + m);
			user.push_back(u), mta.push_back(m);
		}
		while (getchar() != '\n');
		while (getline(cin, msg) && msg[0] != '*')
			mail.push_back(msg);
		used.resize(user.size(), 0);
		for (int i = 1; i < user.size(); i++) {
			if (used[i])	continue;
			printf("Connection between %s and %s\n", mta[0].c_str(), mta[i].c_str());
			printf("     HELO %s\n", mta[0].c_str());
			printf("     250\n");
			printf("     MAIL FROM:<%s@%s>\n", user[0].c_str(), mta[0].c_str());
			printf("     250\n");
			int s = 0;
			for (int j = i; j < user.size(); j++) {
				if (mta[j] == mta[i]) {
					used[j] = 1;
					printf("     RCPT TO:<%s@%s>\n", user[j].c_str(), mta[j].c_str());
					if (MTA.count(user[j] + "@" + mta[j]))
						printf("     250\n"), s++;
					else
						printf("     550\n");
				}
			}
			if (s > 0) {
				printf("     DATA\n");
				printf("     354\n");
				for (int j = 0; j < mail.size(); j++)
					printf("     %s\n", mail[j].c_str());
				printf("     .\n");
				printf("     250\n");
			}
			printf("     QUIT\n");
			printf("     221\n");
		}
	}
	return 0;
}
/*
MTA London 4 Fiona Paul Heather Nevil
MTA SanFrancisco 3 Mario Luigi Shariff
MTA Paris 3 Jacque Suzanne Maurice
MTA HongKong 3 Chen Jeng Hee
MTA MexicoCity 4 Conrado Estella Eva Raul
MTA Cairo 3 Hamdy Tarik Misa
*
Hamdy@Cairo Conrado@MexicoCity Shariff@SanFrancisco Lisa@MexicoCity
*
Congratulations on your efforts !!
--Hamdy
*
Fiona@London Chen@HongKong Natasha@Paris
*
Thanks for the report!  --Fiona
*
*
*/
