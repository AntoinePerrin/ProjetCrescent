#include "Task.h"
#include "ShortTask.h"
#include "MediumTask.h"
#include "LargeTask.h"
#include "HugeTask.h"


using namespace std;

Task::Task(){

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
		res = ShortTask::maxNodeperJob;
	}
	if (task.type == 1) {
		res = MediumTask::maxNodeperJob;
	}
	if (task.type == 2) {
		res = LargeTask::maxNodeperJob;
	}
	if (task.type == 3) {
		res = HugeTask::maxNodeperJob;
	}
	return res;
}

bool Task::taskDataOK(Task task) {
	bool res = false;
	if (task.node > 0 && task.hour > 0 && task.type <4) {
		int nodemax = task.getMaxNodepertype(task);
		if (task.node <= nodemax) {
			res = true;
		}
	}
	return res;
}
