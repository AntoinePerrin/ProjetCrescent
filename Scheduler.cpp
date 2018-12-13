#include "Scheduler.h"

void Scheduler::Schedule(std::vector<Task> *waitingListTask, Task task) {
	(*waitingListTask).push_back(task);
}
