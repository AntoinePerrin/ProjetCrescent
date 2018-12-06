#include "Scheduler.h"

std::vector<Task> Schedule(std::vector<Task> waitingListTask, Task task) {
	waitingListTask.push_back(task);
	return waitingListTask;
}

Scheduler::Scheduler()
{
}


Scheduler::~Scheduler()
{
}
