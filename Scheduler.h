#pragma once

#include <vector>

#include "Task.h"
class Scheduler
{
public:
	Scheduler();
	std::vector<Task> Schedule(std::vector<Task> waitingListTask, Task task);
	~Scheduler();
};

