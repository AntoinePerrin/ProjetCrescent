#pragma once

#include <vector>

class User
{
public:
	std::string Name, group;
	int personnalId, hoursSpend, numberOfTask, hoursincelastjob;
	double override;
	int maxHoursPerWeekPerUser = 24;
	
	User();
	User(std::string name, std::string Id);
	void AddHourUser(std::vector<User> *users);
	double GetMoneyFromUser(User user);
	bool IsUserKnow(int id, std::vector<User> *users);
};

