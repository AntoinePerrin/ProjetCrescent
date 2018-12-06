#pragma once
class LargeTask
{
public:
	LargeTask();
	~LargeTask();

	int const static maxNode = 64;
	int const static maxNodeperJob = 32;
	int const static maxHour = 16;
	int const static lastHourLunch = 2;
};

