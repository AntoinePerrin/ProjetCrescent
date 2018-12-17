#include "UserTest.h"
#include <random>
#include <string>
using namespace std;

string UserTest::NewRequest() {
	string res;
	/*res = "Antoine Perrin-Valery;";
	res += "s";
	//int userId = rand() % 300000;
	int userId = 299405;
	res += to_string(userId) + ";";
	res += "SETC;";

	//int time = rand() % 30;
	int time = 10;
	int nodes;
	if (time < 1) {
		nodes = rand() % 2;
		res += "0;" + to_string(nodes) + ';';
	}
	if (time >= 1 && time < 8) {
		nodes = rand() % 12;
		res += "1;" + to_string(nodes) + ';';
	}
	if (time >= 8 && time < 16) {
		nodes = rand() % 32;
		res += "2;" + to_string(nodes) + ';';
	}
	if (time >= 16) {
		nodes = rand() % 128;
		res += "3;" + to_string(nodes) + ';';
	}
	res += to_string(time) + ";";*/


	//res += "3;2;10;";
	//res = "Panda;s2   99405;   SETC;2;10;   14;";
	res = "Panda;s299405;SETC;2;1;14;";
	return res;
}
