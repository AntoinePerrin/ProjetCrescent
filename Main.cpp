#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "UserTest.h"
#include "User.h"
#include "Scheduler.h"

#include "ShortTask.h"
#include "MediumTask.h"
#include "LargeTask.h"
#include "HugeTask.h"


using namespace std;

vector<Task> waitingListTask;
vector<Task> taskRunning;

Machine machine = Machine();
Scheduler schedule = Scheduler();

vector<string> explode(string sentence, char delim) {
	vector<string> res;
	string temp;
	for (int i = 0; i < sentence.size(); i++) {
		if (sentence[i] == delim) {
			res.push_back(temp);
		} else {
			temp = temp + sentence[i];
		}
	}
	res.push_back(temp);
	return res;
}

void addtothewaitinglist(Task task) {
	waitingListTask = schedule.Schedule(waitingListTask, task);
}
vector<string> listenerUser() {
	UserTest userTest;
	string requestsentence = userTest.NewRequest();
	return explode(requestsentence, ';');
}

void taskcreator(Task task) {
	if (task.canbelunchpertype(task, machine)) {
		task.addTask(task, machine);
		taskRunning.push_back(task);
	}
	else {
		addtothewaitinglist(task);
	}
}

void doWaitingList() {
	Task task;
	for (int i = 0; i < waitingListTask.size(); i++) {
		task = waitingListTask[i];
		if (task.canbelunchpertype(task, machine)) {
			taskcreator(task);										//taskcreator will rerun the previous condition
			waitingListTask.erase(waitingListTask.begin() + i);
		}
	}
}

int main() {
	Task temptask;

	if (!waitingListTask.empty()) {
		doWaitingList();
	} else {
		vector<string> request = listenerUser();
		temptask = Task(stoi(request[0]), stoi(request[1]), stoi(request[2]));
		while (!temptask.taskDataOK(temptask,machine)) {
			request = listenerUser();
			temptask = Task(stoi(request[0]), stoi(request[1]), stoi(request[2]));
		}
		taskcreator(temptask);
	}

	
	for (int i = 0; i < taskRunning.size(); i++) {
		temptask = taskRunning[i];
		temptask.ExecuteTask(temptask, machine);
		if (!temptask.exe) {
			temptask.finishTask(temptask, machine);
			taskRunning.erase(taskRunning.begin() + i);
		}
	}

	return 0;
}


