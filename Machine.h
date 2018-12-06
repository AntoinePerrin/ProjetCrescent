#pragma once
#include <string>
#include "Task.h"
class Machine
{
public:
	//Variable
	int hour;
	std::string days [7] = { "Monday", "Thuesday", "Wednesdy", "Thrusday", "Friday", "Satruday", "Sunday" };
	int nodeUse;
	std::string day;
	int const static maxNode = 128;

	int nodeForShort = 0, nodeForMedium = 0, nodeForLarge = 0;

	//Function
	Machine();
	~Machine();
	//time
	void changeHour(Machine machine);
	int getHour(Machine machine);
	void setHour(Machine machine, int hour);
	std::string getDay(Machine machine);
	int getIndexDay(Machine machine);
	void setDay(Machine machine, int index);

	//node
	bool addNode(Machine machine, Task task);
	int getNumberNode(Machine machine);
	bool removeNode(Machine machine, Task task);
	int getNodeLeft(Machine machine, Task task);
	void addNodePertype(Machine machine, Task task);
	void removeNodePertype(Machine machine, Task task);
};

