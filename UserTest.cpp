#include "UserTest.h"
#include <random>
#include <string>
using namespace std;

string UserTest::NewRequest() {
	string res;
	res = "Panda;";
	res += "s";
	int userId = rand() % 300000;
	res += to_string(userId) + ";";
	res += "SETC;";

	int time = rand() % 30;
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
	res += to_string(time) + ";";


	//res += "3;2;10;";
	//res = "Panda;s299405;     2;64;54";
	//res = "Panda;student;299405;1;2;64;14;";
	//res = "Panda;s299405;3;64;14;";
	return res;
}
