#include "User.h"
#include <string>

using namespace std;


User::User()
{
	this->name = "null";
	this->hoursSpend = 0;
	this->personalId = 0;
	this->group = "null";
	this->override = 1;
	this->hourSinceLastJob = 0;
	this->numberOfTask = 1;
}

User::User(string name, string Id, string group) {
	this->name = name;
	//this->personnalId = (int)Id[1,Id.size()];
	this->personalId = stoi(Id.substr(1, Id.size()));
	if (Id[0] == 's') {
		this->status = "student";
		this->group = group;
		if (group == "SETC") {
			this->override = 1.5;
		} else {
			this->override = 1;
		}
	} else if (Id[0] == 't') {
		this->status = "teacher";
		this->override = 1.5;
		this->group = group;
	} else if (Id[0] == 'i') {
		this->status = "IT Support";
		this->override = 1;
	}

	
	
	this->hoursSpend = 0;
	this->hourSinceLastJob = 0;
	this->numberOfTask = 1;
}

bool User::IsUserKnow(int id, vector<User> *users) {
	bool res = false;
	for (unsigned int i = 0; i < (*users).size(); i++) {
		if ((*users)[i].personalId == id) {
			res = true;
		}
	}
	return res;
}

void User::AddHourUser(vector<User> *users) {
	for (unsigned int i = 0; i < (*users).size(); i++) {
		(*users)[i].hourSinceLastJob += 1;
	}
	
}

double User::GetMoneyFromUser(User user) {
	return user.hoursSpend*0.11;
}

