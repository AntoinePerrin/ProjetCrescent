#pragma once
#include <string>
#include "Task.h"
class Machine
{
public:
	int hour;
	std::string days [7] = { "Monday", "thuesday", "wednesdy", "Thrusday", "Friday", "satruday", "Sunday" };
	int nodeUse;
	std::string day;
	int maxNode = 128;

	int nodeForShort = 0, nodeForMedium = 0, nodeForLarge = 0;

	void changeHour(Machine machine);
	int getHour(Machine machine);
	void setHour(Machine machine, int hour);
	std::string getDay(Machine machine);
	int getIndexDay(Machine machine);
	void setDay(Machine machine, int index);
	bool addNode(Machine machine, Task task);
	int getNumberNode(Machine machine);
	bool removeNode(Machine machine, Task task);
	int getNodeLeft(Machine machine, Task task);
	void addNodePertype(Machine machine, Task task);
	void removeNodePertype(Machine machine, Task task);
	Machine();
	~Machine();
};

