#ifndef TASK_H
#define TASK_H

#include <string>
#include "Machine.h"
#include <vector>

class Task
{
public:
	//Variable
	int type;
	int hour;
	int node;
	bool exe;
	int timeOnNode;

	//Function
	Task();
	Task(int type, int node, int hour);
	~Task();
	int getMaxhour(Task task);
	int getMaxNodepertype(Task task);
	bool taskDataOK(Task task, Machine machine);
	bool ishourcorrect(Task task, Machine machine);
	bool canbelunchpertype(Task task, Machine machine);
	void addTask(Task task, Machine machine);
	void ExecuteTask(Task task, Machine machine);
	void finishTask(Task task, Machine machine);
};

#endif