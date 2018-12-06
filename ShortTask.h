#pragma once
#include <string>
#include "Task.h"
#include "User.h"

class ShortTask
{
public:
	ShortTask();
	~ShortTask();

	int const static maxNode = 12;
	int const static maxNodeperJob = 2;
	int const static maxHour = 2;
	int const static lastHourLunch = 16;
};

