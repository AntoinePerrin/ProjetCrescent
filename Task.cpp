#include "Task.h"


using namespace std;

Task::Task(){

}

int Task::getMaxhour(Task task) {
	int res = 0;
	if (task.type == 0) {
		res = 2;
	}
	if (task.type == 1) {
		res = 8;
	}
	if (task.type == 2) {
		res = 16;
	}
	if (task.type == 3) {
		res = 62;
	}
	return res;
}

int Task::getMaxNodepertype(Task task) {
	int res = 0;
	if (task.type == 0) {
		res = 12;
	}
	if (task.type == 1) {
		res = 36;
	}
	if (task.type == 2) {
		res = 64;
	}
	if (task.type == 3) {
		res = 128;
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
