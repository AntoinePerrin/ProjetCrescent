#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "UserTest.h"
#include "ShortTask.h"
#include "User.h"

using namespace std;

vector<string> explode(string sentence, char delim) {
	vector<string> res;
	string temp;
	for (int i = 0; i < sentence.size(); i++) {
		if (sentence[i] == delim) {
			res.push_back(temp);
		} else {
			temp = temp + sentence[i];
		}
	}
	res.push_back(temp);
	return res;
}


int main() {
	UserTest userTest;
	string requestsentence = userTest.NewRequest();
	vector<string> request;
	request = explode(requestsentence, ';');
	if (request[0] == "Short") {
		ShortTask task;
		User user;

		user = user.GetFromId(stoi(request[1]));
		task.CreateTask(user, request[2], request[3]);
	}
	if (request[0] == "Medium") {

	}
	if (request[0] == "Large") {

	}
	if (request[0] == "Huge") {

	}
	if (request[0] == "Interactive") {

	}
	return 0;
}


