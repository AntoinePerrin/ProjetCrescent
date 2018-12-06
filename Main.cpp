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
	}
	else {
		addtothewaitinglist(task);
	}
}

Task doWaitingList() {
	Task returntask;
	if (!waitingListTask.empty()) {
		Task task = waitingListTask[0];
		if (task.canbelunchpertype(task, machine)) {
			task.addTask(task, machine);
			returntask = task;
			waitingListTask.erase(waitingListTask.begin());
		}
	}
	return returntask;
}

int main() {
	Task temptask;

	if (!waitingListTask.empty()) {
		temptask = doWaitingList();
	} else {
		vector<string> request = listenerUser();
		temptask = Task(stoi(request[0]), stoi(request[1]), stoi(request[2]));
		while (!temptask.taskDataOK(temptask,machine)) {
			request = listenerUser();
			temptask = Task(stoi(request[0]), stoi(request[1]), stoi(request[2]));
		}
		taskcreator(temptask);
	}
	


	while (temptask.exe) {
		temptask.ExecuteTask(temptask, machine);
	}
	temptask.finishTask(temptask, machine);


	return 0;
}


