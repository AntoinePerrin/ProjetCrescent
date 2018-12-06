#include "Machine.h"
#include <string>



Machine::Machine()
{
	this->hour = 8;
	this->day = days[0];
	this->nodeUse = 0;
}


Machine::~Machine()
{
}


void Machine::changeHour(Machine machine) {
	if (machine.hour < 24) {
		machine.hour += 1;
	} else {
		machine.hour = 0;
		int index = getIndexDay(machine) + 1;
		if (index > 7) {
			machine.day = machine.days[0];
		} else {
			machine.day = machine.days[index];
		}
	}
}

int Machine::getHour(Machine machine) {
	return machine.hour;
}


void Machine::setHour(Machine machine, int hour) {
	machine.hour = hour;
}

std::string Machine::getDay(Machine machine) {
	return machine.day;
}

int Machine::getIndexDay(Machine machine) {
	int i = 0;
	while (machine.day == days[i]) {
		i++;
	}
	return i;
}

void Machine::setDay(Machine machine, int index) {
	if (index < 7) {
		machine.day = days[index];
	}
}

bool Machine::addNode(Machine machine, Task task) {
	bool res = false;
	if (machine.nodeUse + task.node < machine.maxNode && task.node < machine.getNodeLeft(machine,task)) {
		machine.nodeUse += task.node;
		machine.addNodePertype(machine,task);
		res = true;
	}
	return res;
}

void Machine::addNodePertype(Machine machine, Task task) {
	if (task.type == 0) {
		machine.nodeForShort += task.node;
	}
	if (task.type == 1) {
		machine.nodeForMedium += task.node;
	}
	if (task.type == 2) {
		machine.nodeForLarge += task.node;
	}
}

int Machine::getNodeLeft(Machine machine,Task task) {
	int res = 0;
	if (task.type == 0) {
		res = task.getMaxNodepertype(task) - machine.nodeForShort;
	}
	if (task.type == 1) {
		res = task.getMaxNodepertype(task) - machine.nodeForMedium;
	}
	if (task.type == 2) {
		res = task.getMaxNodepertype(task) - machine.nodeForLarge;
	}
	return res;
}

int Machine::getNumberNode(Machine machine) {
	return machine.nodeUse;
}

bool Machine::removeNode(Machine machine, Task task) {
	bool res = false;
	if (machine.nodeUse - task.node > 0) {
		machine.nodeUse -= task.node;
		machine.removeNodePertype(machine, task);
		res = true;
	}
	return res;
}

void Machine::removeNodePertype(Machine machine, Task task) {
	if (task.type == 0) {
		machine.nodeForShort -= task.node;
	}
	if (task.type == 1) {
		machine.nodeForMedium -= task.node;
	}
	if (task.type == 2) {
		machine.nodeForLarge -= task.node;
	}
}