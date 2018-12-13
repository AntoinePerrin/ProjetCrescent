#include "UserTest.h"
#include <random>
#include <string>
using namespace std;

string UserTest::NewRequest() {
	string res;
	res = "Panda;";
	res += "s";
	int userId = rand() % 30;// 0000;
	res += to_string(userId) + ";";

	/*int time = rand() % 25;
	if (time < 2) {
		res += "0;2;";
	}
	if (time >= 2 && time < 9) {
		res += "1;16;";
	}
	if (time >= 9 && time < 17) {
		res += "2;64;";
	}
	if (time >= 17) {
		res += "3;128;";
	}
	res += to_string(time) + ";";*/


	res += "3;2;1;";
	//res = "Panda;s299405;     2;64;54";
	//res = "Panda;student;299405;1;2;64;14;";
	//res = "Panda;s299405;3;64;14;";
	return res;
}
