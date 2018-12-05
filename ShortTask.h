#pragma once
#include <string>
#include "Task.h"
#include "User.h"

class ShortTask
{
public:
	ShortTask();
	~ShortTask();
	void CreateTask(User user, string details, string programName);
};

