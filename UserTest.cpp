#include "UserTest.h"
#include <random>
#include <string>

string UserTest::NewRequest() {
	string res;
	int time = rand() % 25;
	int userId = rand() % 300000;
	if (time < 2) {
		res = "Short;";
	}
	if (time >= 2 && time < 9) {
		res = "Medium;";
	}
	if (time >= 9 && time < 17) {
		res = "Large;";
	}
	if (time >= 17) {
		res = "Huge;";
	}
	res += stoi(userId) + ";";
	res += stoi(time) + ";";
	res += "code of " + stoi(userId) + " ;";

	return res;
}
