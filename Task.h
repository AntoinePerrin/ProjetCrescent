#ifndef TASK_H
#define TASK_H

#include <string>
#include "Machine.h"
#include <vector>

class Task
{
public:
	int type;
	int hour;
	int node;
	bool exe;

	void addTask(Task task, Machine machine);
	void ExecuteTask(Task task, Machine machine);
	int getMaxhour(Task task);
	bool canbelunchpertype(Task task, Machine machine);
	int getMaxNodepertype(Task task);
	bool ishourcorrect(Task task, Machine machine);
	Task(int type, int node, int hour);
	Task();
	~Task();
	void finishTask(Task task, Machine machine);
	bool taskDataOK(Task task, Machine machine);
};

#endif