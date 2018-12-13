#include "User.h"
#include <string>

using namespace std;


User::User()
{
	this->Name = "null";
	this->hoursSpend = 0;
	this->personnalId = 0;
	this->group = "null";
	this->override = 1;
	this->hoursincelastjob = 0;
	this->numberOfTask = 1;
}

User::User(string name, string Id) {
	this->Name = name;
	//this->personnalId = (int)Id[1,Id.size()];
	this->personnalId = stoi(Id.substr(1, Id.size()));
	if (Id[0] == 's') {
		this->group = "student";
		this->override = 1;
	} else if (Id[0] == 't') {
		this->group = "teacher";
		this->override = 1.5;
	} else if (Id[0] == 'i') {
		this->group = "It Staff";
		this->override = 1;
	}
	
	this->hoursSpend = 0;
	this->hoursincelastjob = 0;
	this->numberOfTask = 1;
}

bool User::IsUserKnow(int id, vector<User> *users) {
	bool res = false;
	for (unsigned int i = 0; i < (*users).size(); i++) {
		if ((*users)[i].personnalId == id) {
			res = true;
		}
	}
	return res;
}

void User::AddHourUser(vector<User> *users) {
	for (unsigned int i = 0; i < (*users).size(); i++) {
		(*users)[i].hoursincelastjob += 1;
	}
	
}

double User::GetMoneyFromUser(User user) {
	return user.hoursSpend*0.11;
}

