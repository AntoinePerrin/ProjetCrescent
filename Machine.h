#pragma once


class Machine
{
public:
	//Variable
	int hour;
	int day;
	int nodeUse;
	int const static maxNode = 128;
	int nodeForShort = 0, nodeForMedium = 0, nodeForLarge = 0, nodeForHuge = 0;

	//Function
	Machine();
	//time
	void changeHour(Machine *machine);
	int getHour(Machine machine);
	void setHour(Machine *machine, int hour);
	int getIndexDay(Machine machine);
	void setDay(Machine *machine, int index);

	//node
	int getNumberNode(Machine machine);
};

