#include "Machine.h"



Machine::Machine()
{
	this->hour = 9;
	this->nodeUse = 0;
}

void Machine::changeHour(Machine *machine) {
	if ((*machine).hour < 23) {
		(*machine).hour += 1;
	} else {
		(*machine).hour = 0;
		if (day + 1 > 6) {
			(*machine).day = 0;
		} else {
			(*machine).day += 1 ;
		}
	}
}

int Machine::getHour(Machine machine) {
	return machine.hour;
}

void Machine::setHour(Machine *machine, int hour) {
	(*machine).hour = hour;
}

int Machine::getIndexDay(Machine machine) {
	return day;
}

void Machine::setDay(Machine *machine, int index) {
	if (index > 7) {
		while (index > 7){
			index -= 7;
		}
	}
	(*machine).day = index;
}

int Machine::getNumberNode(Machine machine) {
	return machine.nodeUse;
}
