#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "UserTest.h"
/*#include "Task.h"
#include "User.h"*/
#include "Machine.h"
#include "Scheduler.h"

#include "ShortTask.h"
#include "MediumTask.h"
#include "LargeTask.h"
#include "HugeTask.h"


using namespace std;

vector<Task> waitingListTask;
vector<Task> taskRunning;
vector<Task> oldTask;
vector<User> listLastUser;

Machine machine = Machine();
Scheduler schedule = Scheduler();

Task createTask(int type, int node, int hour, User user) {
	Task temp;
	temp.type = type;
	temp.node = node;
	temp.hour = hour;
	temp.exe = false;
	temp.user = user;
	temp.timeOnNode = 0;
	return temp;
}

vector<string> explode(string sentence, char delim) {
	vector<string> res;
	string temp;
	for (unsigned int i = 0; i < sentence.size(); i++) {
		if (sentence[i] == delim) {
			res.push_back(temp);
			temp = "";
		} else {
			temp = temp + sentence[i];
		}
	}
	res.push_back(temp);
	return res;
}

void addtothewaitinglist(Task task) {
	schedule.Schedule(&waitingListTask, task);
}

vector<string> listenerUser() {
	UserTest userTest;
	string requestsentence = userTest.NewRequest();
	return explode(requestsentence, ';');
}

int getNodeLeft(Machine machine, Task task) {
	int res = 0;
	if (task.type == 0) {
		res = task.getMaxNodepertype(task) - machine.nodeForShort;
	}
	if (task.type == 1) {
		res = task.getMaxNodepertype(task) - machine.nodeForMedium;
	}
	if (task.type == 2) {
		res = task.getMaxNodepertype(task) - machine.nodeForLarge;
	}
	if (task.type == 3) {
		res = task.getMaxNodepertype(task) - machine.nodeForHuge;
	}
	return res;
}

bool ishourcorrect(Task task, Machine machine) {
	bool res = false;
	if (task.type == 3) {
		if (machine.getIndexDay(machine) == 5 && machine.getHour(machine) > 18) {
			res = true;
		}
		if (machine.getIndexDay(machine) > 5) {
			res = true;
		}
	}
	else {
		if (machine.getIndexDay(machine) < 5) {
			res = true;
		}
		if (machine.getIndexDay(machine) == 5) {
			int hour;
			if (task.type == 0) {
				hour = 16;
			}
			if (task.type == 1) {
				hour = 10;
			}
			if (task.type == 2) {
				hour = 2;
			}
			if (machine.getHour(machine) < hour) {
				res = true;
			}
		}
	}
	return res;
}

bool canbelunchpertype(Task task, Machine machine) {
	return getNodeLeft(machine, task) >= task.node && ishourcorrect(task, machine);
}

void addNodePertype(Machine *machine, Task task) {
	if (task.type == 0) {
		(*machine).nodeForShort += task.node;
	}
	if (task.type == 1) {
		(*machine).nodeForMedium += task.node;
	}
	if (task.type == 2) {
		(*machine).nodeForLarge += task.node;
	}
	if (task.type == 3) {
		(*machine).nodeForHuge += task.node;
	}
}

bool addNode(Machine *machine, Task task) {
	bool res = false;
	if ((*machine).nodeUse + task.node <= (*machine).maxNode && task.node <= getNodeLeft(*machine, task)) {
		(*machine).nodeUse += task.node;
		addNodePertype(machine, task);
		res = true;
	}
	return res;
}

void taskcreator(Task task) {
	if (canbelunchpertype(task, machine)) {
		if (addNode(&machine, task)) {
			(task).exe = true;
		}
		taskRunning.push_back(task);
	}
	else {
		addtothewaitinglist(task);
	}
}

void doWaitingList() {
	Task task;
	if (canbelunchpertype(waitingListTask[0], machine)) {
		taskcreator(waitingListTask[0]);										//taskcreator will rerun the previous condition
		waitingListTask.erase(waitingListTask.begin());
	}
	for (unsigned int i = 1; i < waitingListTask.size(); i++) {
		task = waitingListTask[i];
		if (task.type == 3 && canbelunchpertype(task, machine)) {
			taskcreator(task);										//taskcreator will rerun the previous condition
			waitingListTask.erase(waitingListTask.begin() + i);
		}
	}
}

void ExecuteTask(Task *task, Machine *machine) {
	if ((*task).timeOnNode > (*task).getMaxhour(*task) || (*task).hour == 0) {
		(*task).exe = false;
	}
	if ((*task).hour >= 1) {
		(*task).hour -= 1;
		(*task).timeOnNode += 1;
	}
	(*task).user.hoursSpend += 1 * (*task).node;
}

void removeNodePertype(Machine *machine, Task task) {
	if (task.type == 0) {
		(*machine).nodeForShort -= task.node;
	}
	if (task.type == 1) {
		(*machine).nodeForMedium -= task.node;
	}
	if (task.type == 2) {
		(*machine).nodeForLarge -= task.node;
	}
	if (task.type == 3) {
		(*machine).nodeForHuge -= task.node;
	}
}

bool removeNode(Machine *machine, Task task) {
	bool res = false;
	if ((*machine).nodeUse - task.node > 0) {
		(*machine).nodeUse -= task.node;
		removeNodePertype(machine, task);
		res = true;
	}
	return res;
}

void finishTask(Task *task, Machine *machine) {
	if (!(*task).exe) {
		removeNode(machine, *task);
	}
}

double Ratio(vector<User> users, Machine machine) {
	double hoursWakeupMachine = machine.getIndexDay(machine) * 24 + machine.getHour(machine) * machine.maxNode;
	double usersHour = 0;
	for (unsigned int i = 0; i < users.size(); i++) {
		usersHour += users[i].hoursSpend;
	}
	return usersHour / hoursWakeupMachine;
}

/*bool UserAlreadyKnow(User user) {
	bool res = false;
	for (unsigned int i = 0; i < listLastUser.size(); i++) {
		if (listLastUser[i].personnalId == user.personnalId) {
			res = true;
		}
	}
	return res;
}*/

float indexUserLastJob(User user) {
	float res = -1;
	for (unsigned int i = 0; i < listLastUser.size(); i++) {
		if (listLastUser[i].personnalId == user.personnalId) {
			res = i;
		}
	}
	return res;
}

bool UserAlreadyLunchTask(User user) {
	bool res = false;
	for (unsigned int i = 0; i < taskRunning.size(); i++) {
		if (taskRunning[i].user.personnalId == user.personnalId) {
			res = true;
		}
	}
	return res;
}

bool IsUserAllowed(Task task) {
	bool res = false;
	if (!UserAlreadyLunchTask(task.user)) {
		if ((task.getMaxhour(task) * task.node) <= task.user.maxHoursPerWeekPerUser*task.user.override) { //source d'erreur eventuel int ?
			float index = indexUserLastJob(task.user);
			if (index != -1) {
				if (listLastUser[index].hoursincelastjob > exp(listLastUser[index].numberOfTask)) {
					res = true;
				}
			}
			else {
				res = true;
			}
		}
	}
	return res;
}



void CleanData(vector<string> *request) {
	int n = 0;
	for (unsigned int i = 0; i < (*request).size(); i++) {
		n = 0;
		for (unsigned int j = 0; j < (*request)[i].size(); j++) {
			if (request[i][j] != " ") {
				request[i][n++] = request[i][j];
			}
		}
		request[i][n] = '\0';
	}
}

void PushUserList(User user) {
	float res = indexUserLastJob(user);
	if (res != -1) {
		listLastUser[res].numberOfTask += 1;
		listLastUser[res].hoursSpend += user.hoursSpend;
	} else {
		listLastUser.push_back(user);
	}
}

void PrintResult() {
	ofstream fd("textFile1.csv", ios::app);
	fd << "Task done" << endl;
	fd << "Type ;Node ;time spend on HPC ; lenght = " << oldTask.size() << " ;" << endl ;
	string res;
	for (unsigned int i = 0; i < oldTask.size(); i++) {
		if (oldTask[i].type == 0) { res = "Short"; }
		if (oldTask[i].type == 1) { res = "Medium"; }
		if (oldTask[i].type == 2) { res = "Large"; }
		if (oldTask[i].type == 3) { res = "Huge"; }
		fd << res << ";" << oldTask[i].node << ";" << oldTask[i].timeOnNode << endl;
	}
	fd << "User of done task" << endl;
	fd << endl << "Name ; Groupe ;personnalId ;hoursSpend ;numberOfTask ;hoursincelastjob ;Money spend ;lenght = " << listLastUser.size() << " ;" << endl;
	for (unsigned int i = 0; i < listLastUser.size(); i++) {
		fd << listLastUser[i].Name << ";" << listLastUser[i].group << ";" << listLastUser[i].personnalId << ";" << listLastUser[i].hoursSpend << ";" << listLastUser[i].numberOfTask << ";" << listLastUser[i].hoursincelastjob << ";" << listLastUser[i].GetMoneyFromUser(listLastUser[i]) << endl;
	}
	if (waitingListTask.size() > 0) {
		fd << endl << "Waiting List" << endl;
		fd << "Name ; Groupe ;personnalId ;hoursSpend ;numberOfTask ;hoursincelastjob ;lenght = " << waitingListTask.size() << " ;" << endl;
		for (unsigned int i = 0; i < waitingListTask.size(); i++) {
			fd << waitingListTask[i].user.Name << ";" << waitingListTask[i].user.group << ";" << waitingListTask[i].user.personnalId << ";" << waitingListTask[i].user.hoursSpend << ";" << waitingListTask[i].user.numberOfTask << ";" << waitingListTask[i].user.hoursincelastjob << endl;
		}
	}
	fd.close();
}

int main() {
	Task temptask;
	while ((machine.day != 7 || machine.hour != 23)) {
		if (!waitingListTask.empty()) {
			doWaitingList();
		}
		vector<string> request = listenerUser();
		//CleanData(&request);
		User user = User(request[0], request[1]);
		temptask = createTask(stoi(request[2]), stoi(request[3]), stoi(request[4]), user);
		while (!(temptask.taskDataOK(temptask) && IsUserAllowed(temptask))) {
			request = listenerUser();
			//CleanData(&request);
			user = User(request[0], request[1]);
			temptask = createTask(stoi(request[2]), stoi(request[3]), stoi(request[4]), user);
		}
		taskcreator(temptask);

		for (unsigned int i = 0; i < taskRunning.size(); i++) {
			ExecuteTask(&taskRunning[i], &machine);
			if (!taskRunning[i].exe) {
				finishTask(&taskRunning[i], &machine);
				PushUserList(taskRunning[i].user);
				oldTask.push_back(taskRunning[i]);
				taskRunning.erase(taskRunning.begin() + i);
			}	
		}

		if (listLastUser.size() > 0) {
			listLastUser[0].AddHourUser(&listLastUser);
		}
		machine.changeHour(&machine);
		cout << machine.hour << ";" << machine.day << endl;
	}
	PrintResult();
	return 42;
}

