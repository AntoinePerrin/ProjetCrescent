#ifndef TASK_H
#define TASK_H

#include <string>

class Task
{
public:

	virtual void CreateTask() = 0;

	void TaskManager(ShortTask Short[]);
	int ExecuteTask(int time);


	/*//variable
	string userName, idName, type, nameBatch, pathToFile;
	//function
	Task CreateTask(string userName, string idName, string type, string nameBatch);
	void ExecuteTask(Task userdata);*/
	Task();
	~Task();
};

#endif