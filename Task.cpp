#include <string>

#include "Machine.h"
#include "Task.h"

#include "ShortTask.h"
#include "MediumTask.h"
#include "LargeTask.h"
#include "HugeTask.h"

using namespace std;

Task::Task(){

}

Task::Task(int type, int node, int hour){
	this->type = type;
	this->node = node;
	this->hour = hour;
	this->exe = false;
}

Task::~Task(){
}

int Task::getMaxhour(Task task) {
	int res = 0;
	if (task.type == 0) {
		res = ShortTask::maxHour;
	}
	if (task.type == 1) {
		res = MediumTask::maxHour;
	}
	if (task.type == 2) {
		res = LargeTask::maxHour;
	}
	if (task.type == 3) {
		res = HugeTask::maxHour;
	}
	return res;
}

int Task::getMaxNodepertype(Task task) {
	int res = 0;
	if (task.type == 0) {
		res = ShortTask::maxNode;
	}
	if (task.type == 1) {
		res = MediumTask::maxNode;
	}
	if (task.type == 2) {
		res = LargeTask::maxNode;
	}
	if (task.type == 3) {
		res = Machine::maxNode;
	}
	return res;
}

bool Task::taskDataOK(Task task, Machine machine) {
	bool res = false;
	if (task.node > 0 && task.hour > 0) {
		int hourmax = getMaxhour(task);
		int nodeMax = getMaxNodepertype(task);
		if (task.hour < hourmax && task.node < nodeMax) {
			res = true;
		}
	}
	return res;
}

bool Task::ishourcorrect(Task task, Machine machine) {
	bool res = false;
	if (task.type == 3) {
		if (machine.getIndexDay(machine) == 5 && machine.getHour(machine) > 18) {
			res = true;
		}
		if (machine.getIndexDay(machine) > 5) {
			res = true;
		}
	} else {
		if (machine.getIndexDay(machine) < 5) {
			res = true;
		}
		if (machine.getIndexDay(machine) == 5) {
			int hour;
			if (task.type == 0) {
				hour = ShortTask::lastHourLunch;
			}
			if (task.type == 1) {
				hour = MediumTask::lastHourLunch;
			}
			if (task.type == 2) {
				hour = LargeTask::lastHourLunch;
			}
			if (machine.getHour(machine) < hour) {
				res = true;
			}
		}
	}
	return res;
}

bool Task::canbelunchpertype(Task task, Machine machine) {
	return machine.getNodeLeft(machine, task) >= task.node && ishourcorrect(task, machine);
}

void Task::addTask(Task task, Machine machine) {
	if (machine.addNode(machine, task)) {
		task.exe = true;
	}
}

void Task::ExecuteTask(Task task, Machine machine) {
	if (task.hour > 1) {
		task.hour -= 1;
	}
	else {
		task.exe = false;
		task.hour = 0;
	}
	machine.changeHour(machine);
	task.timeOnNode += 1;
}

void Task::finishTask(Task task, Machine machine) {
	if (!task.exe) {
		machine.removeNode(machine, task);
	}
}

