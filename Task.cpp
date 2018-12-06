#include <string>

#include "Machine.h"
#include "Task.h"

#include "ShortTask.h"
#include "MediumTask.h"
#include "LargeTask.h"
#include "HugeTask.h"

using namespace std;



void Task::ExecuteTask(Task task, Machine machine) {
	if (task.hour > 1) {
		task.hour -= 1;
	} else {
		task.exe = false;
	}
	machine.changeHour(machine);
}

Task::Task(){

}

Task::Task(int type, int node, int hour)
{
	this->type = type;
	this->node = node;
	this->hour = hour;
	this->exe = false;
}

Task::~Task()
{
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
	return res;

}
bool Task::taskDataOK(Task task, Machine machine) {//ajouter controle huge
	bool res = false;
	if (task.node > 0 && task.hour > 0) {
		int hourmax = getMaxhour(task);
		int nodeMax = maxCorepertype(task);
		if (task.hour < hourmax && task.node < nodeMax && ishourcorrect(task, machine)) {
			res = true;
		}
	}
	return res;
}

bool Task::canbelunchpertype(Task task, Machine machine) {
	bool res = false;
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
		res = LargeTask::maxNode;
	}

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
	return res;
}

bool Task::ishourcorrect(Task task, Machine machine) {
	bool res = false;
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
		else {
			res = false;
		}
	}
	return res;
}



void Task::addTask(Task task, Machine machine) {
	machine.addNode(machine, task.node);
	task.exe = true;
}


void Task::finishTask(Task task, Machine machine) {
	if (!task.exe) {
		machine.removeNode(machine, task.node);
	}
}
