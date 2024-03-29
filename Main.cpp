#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <ctype.h>

#include "UserTest.h"
#include "Machine.h"
#include "Scheduler.h"

#include "ShortTask.h"
#include "MediumTask.h"
#include "LargeTask.h"
#include "HugeTask.h"


using namespace std;

vector<Task> waitingListTask;		/*!< Waiting list for task*/
vector<Task> waitingListTaskHuge;	/*!< Waiting list for huge task*/
vector<Task> taskRunning;			/*!< List of running task*/
vector<Task> oldTask;				/*!< List of old task*/
vector<User> listLastUser;			/*!< List of last user*/

Machine machine = Machine();		/*!< Initiate the machine we will use during the simulation*/
Scheduler schedule = Scheduler();	/*!< Initiate the the scheduler*/

/*!
*  \brief Initiator with variable
*
*  Advance intiator with the type of task, the number of node and the lenght of the code
*
*  \param type the type of the task, 0 for short, 1 for medium, 2 for large and 3 for huge
*	\param node the number of node asked
*	\param hour the lenght of the code
*	\param user the user who ask for the job
*  \return Return an object of the class task with all the variable initiate
*/
Task createTask(int type, int node, int hour, User user) {
	Task temp;
	temp.type = type;
	temp.node = node;
	temp.hour = hour;
	temp.exe = false;
	temp.user = user;
	temp.timeOnNode = 0;
	temp.waitingTime = 0;
	return temp;
}
/*!
*  \brief Explode a string
*
*  Explode a string into a vector of string by ;
*
*	\param sentence the sentence we want to split
*	\param delim the character which split the string
*  \return Return a vector of string 
*/
vector<string> explode(string sentence, char delim) {
	vector<string> res;
	string temp;
	for (unsigned int i = 0; i < sentence.size(); i++) {
		if (sentence[i] == delim) {
			res.push_back(temp);
			temp = "";
		} else if (sentence[i] != ' ') {
			temp = temp + sentence[i];
		}
	}
	res.push_back(temp);
	return res;
}
/*!
*  \brief listener for user's request
*
*  call the usertest class to generate a new request
*
*  \return Return a vector of string with all the task data
*/
vector<string> listenerUser() {
	UserTest userTest;
	string requestsentence = userTest.NewRequest();
	vector<string> request = explode(requestsentence, ';');
	string res = request[3] + request[4] + request[5];
	int isdigiti = 0;
	for (unsigned int i = 0; i < res.size(); i++) {
		if (isdigit(res[i])) {
			isdigiti += 1;
		}
	}
	if (isdigiti == res.size()) {
		return request;
	} else {
		return listenerUser();
	}
}
/*!
*  \brief Return the number of node left
*
*  Return the node left for each type of task
*
*	\param task the task we want to run but the only information we need is the type of task
*  \return An int of the node left for the type of task
*/
int getNodeLeft(Task task) {
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
/*!
*  \brief Check if the task can be run by hour side
*
*  Check if the task can be run before the week end for the work day task or if the huge task can be lunch
*
*	\param task the task we want to run
*  \return Bool true if the task can be run immediately
*/
bool ishourcorrect(Task task) {
	bool res = false;
	if (task.type == 3) {
		if (machine.getIndexDay(machine) == 4 && machine.getHour(machine) > HugeTask::firstHourLunch) {
			res = true;
		}
		if (machine.getIndexDay(machine) > 4) {
			res = true;
		}
	}
	else {
		if (machine.getIndexDay(machine) == 0 && machine.getHour(machine) >= 8) {
			res = true;
		}
		if (machine.getIndexDay(machine) < 4 && machine.getIndexDay(machine) > 0) {
			res = true;
		}
		if (machine.getIndexDay(machine) == 4) {
			int hour;
			if (task.type == 0) {
				hour = ShortTask::lastHourLunch;
			}
			if (task.type == 1) {
				hour = MediumTask::lastHourLunch;
			}
			if (task.type == 2) {
				hour = LargeTask::lastHourLunch;
			}
			if (machine.hour <= hour) {
				res = true;
			}
		}
	}
	return res;
}
/*!
*  \brief check if the task be run immediatly
*
*  Regroup all the check security of the task not for the user.
*
*	\param task the task we want to run
*  \return Bool true if the task can be run immediately
*/
bool canbelunchpertype(Task task) {
	return getNodeLeft(task) >= task.node && ishourcorrect(task);
}
/*!
*  \brief Add node for each type of task
*
*  Add node for each type of task
*
*	\param task the task we want to run
*/
void addNodePertype(Task task) {
	if (task.type == 0) {
		machine.nodeForShort += task.node;
	}
	if (task.type == 1) {
		machine.nodeForMedium += task.node;
	}
	if (task.type == 2) {
		machine.nodeForLarge += task.node;
	}
	if (task.type == 3) {
		machine.nodeForHuge += task.node;
	}
}
/*!
*  \brief Add node to the machine
*
*  Add node to the machine for a specific task and call addNodePerType
*
*	\param task the task we want to run
*  \return Bool true if the task is correctly added 
*/
bool addNode(Task task) {
	bool res = false;
	if (machine.nodeUse + task.node <= machine.maxNode && task.node <= getNodeLeft(task)) {
		machine.nodeUse += task.node;
		addNodePertype(task);
		res = true;
	}
	return res;
}
/*!
*  \brief Set the task running
*
*  If the task can be lunch and the node are properly added the function set the exe variable of task to true and add the task to the vector of running task
*  If not the task is added to the vetor of waiting list of task
*
*	\param task the task we want to run
*/
void taskcreator(Task task) {
	if (addNode(task)) {
		(task).exe = true;
		taskRunning.push_back(task);
	}
}
/*!
*  \brief Check the waiting list
*
*  Check if the first element of the waiting list can be run
*  or if there is there is huge task that can be lunch
*/
void doWaitingList() {
	if (!waitingListTask.empty()) {
		if (canbelunchpertype(waitingListTask[0])) {
			taskcreator(waitingListTask[0]);
			waitingListTask.erase(waitingListTask.begin());
			if (!waitingListTask.empty()) {
				doWaitingList();
			}
		}
	}
	if (!waitingListTaskHuge.empty()) {
		if (canbelunchpertype(waitingListTaskHuge[0])) {
			taskcreator(waitingListTaskHuge[0]);
			waitingListTaskHuge.erase(waitingListTaskHuge.begin());
			if (!waitingListTaskHuge.empty()) {
				doWaitingList();
			}
		}
	}
}
/*!
*  \brief Execute the task
*
*  Execute the task if the task run out of time, it will be deactivate
*
*	\param task the task we want to run
*/
void ExecuteTask(Task *task) {
	if ((*task).timeOnNode > (*task).getMaxhour(*task) || (*task).hour == 0) {
		(*task).exe = false;
	}
	if ((*task).hour >= 1) {
		(*task).hour -= 1;
		(*task).timeOnNode += 1;
	}
	(*task).user.hoursSpend += 1 * (*task).node;
}
/*!
*  \brief Remove node for each type of task
*
*  Remove node for each type of task
*
*	\param task the task we want to run
*/
void removeNodePertype(Task task) {
	if (task.type == 0) {
		machine.nodeForShort -= task.node;
	}
	if (task.type == 1) {
		machine.nodeForMedium -= task.node;
	}
	if (task.type == 2) {
		machine.nodeForLarge -= task.node;
	}
	if (task.type == 3) {
		machine.nodeForHuge -= task.node;
	}
}
/*!
*  \brief Remove node to the machine
*
*  Remove node to the machine for a specific task and call removeNodePerType
*
*	\param task the task we want to run
*  \return Bool true if the task is correctly removed
*/
bool removeNode(Task task) {
	bool res = false;
	if (machine.nodeUse - task.node >= 0) {
		machine.nodeUse -= task.node;
		removeNodePertype(task);
		res = true;
	}
	return res;
}
/*!
*  \brief Finish the task
*
*  Finish the task aka deallocate the node
*
*  \param task the curent task we want to run
*/
void finishTask(Task *task) {
	if (!(*task).exe) {
		removeNode(*task);
	}
}
/*!
*  \brief Give the ratio time
*
*  Give the ratio time between the uptime of the machine and the total hour spend by user for one week
*
*	\param task The vector of last task
*  \return Double, the ratio
*/
double Ratio(vector<Task> task) {
	double hoursWakeupMachine = (24*7) * machine.maxNode;
	double usersHour = 0;
	for (unsigned int i = 0; i < task.size(); i++) {
		usersHour += task[i].timeOnNode * task[i].node;
	}
	return usersHour / hoursWakeupMachine;
}
/*!
*  \brief Return the index of the user
*
*  Return the index of the user on the last user vector, if it's not on the list it will return -1
*
*	\param user The user we want to know the index from the last user vector
*  \return Float, the index
*/
float indexUserLastJob(User user) {
	float res = -1;
	for (unsigned int i = 0; i < listLastUser.size(); i++) {
		if (listLastUser[i].personalId == user.personalId) {
			res = i;
		}
	}
	return res;
}
/*!
*  \brief Check if the user has already asked for a job
*
*  Check if the user has already asked for a job in the running vector or in the waiting vector
*
*	\param user User who ask for a new job
*  \return Bool, return true if the user already ask
*/
bool UserAlreadyLunchTask(User user) {
	bool res = false;
	for (unsigned int i = 0; i < taskRunning.size(); i++) {
		if (taskRunning[i].user.personalId == user.personalId) {
			res = true;
		}
	}
	for (unsigned int i = 0; i < waitingListTask.size(); i++) {
		if (waitingListTask[i].user.personalId == user.personalId) {
			res = true;
		}
	}
	return res;
}
/*!
*  \brief Check if the user can run the job
*
*  Check if the task can be lunch immediately for the user part not the task part
*
*	\param task The task we want to lunch
*  \return Bool, return true if the task can be run immedialtely
*/
bool IsUserAllowed(Task task) {
	bool res = false;
	if (!UserAlreadyLunchTask(task.user)) {
		if ((task.getMaxhour(task) * task.node) <= (int) (task.user.maxHoursPerWeekPerUser*task.user.override)) {
			float index = indexUserLastJob(task.user);
			if (index != -1) {
				if (listLastUser[index].hourSinceLastJob > exp(listLastUser[index].numberOfTask)) {
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
/*!
*  \brief Add the user to the last user vector
*
*  Add the user to the last user vector if he is already know it will add one to the numberOfTask and the hour spend on the new task
*  if not the user is just push_back to the last user vector
*
*	\param user The user we want to add to the last user vector
*/
void PushUserList(User user) {
	float res = indexUserLastJob(user);
	if (res != -1) {
		listLastUser[res].numberOfTask += 1;
		listLastUser[res].hoursSpend += user.hoursSpend;
	} else {
		listLastUser.push_back(user);
	}
}
/*!
*  \brief Output the result
*
*  Print the result of the simulation in a CSV file
*
*/
void PrintResult() {
	ofstream fd("textFile1.csv", ios::app);
	fd << "Task done" << endl;
	fd << "Type ;Node ;time spend on HPC ;Length left ;length  = " << oldTask.size() << " ;" << endl ;
	string res;
	int nbShort = 0, nbMed = 0, nbLarge = 0, nbHuge = 0;
	int nbHourTotal = 0;
	float averageWaitingTimeShort = 0, averageWaitingTimeMed = 0, averageWaitingTimeLarge = 0, averageWaitingTimeHuge = 0;
	float turnaroundtime = 0;
	for (unsigned int i = 0; i < oldTask.size(); i++) {
		nbHourTotal += oldTask[i].timeOnNode;
		turnaroundtime += (oldTask[i].timeOnNode + oldTask[i].waitingTime) / oldTask[i].timeOnNode;
		if (oldTask[i].type == 0) { res = "Short"; nbShort++; averageWaitingTimeShort += oldTask[i].waitingTime; }
		if (oldTask[i].type == 1) { res = "Medium"; nbMed++; averageWaitingTimeMed += oldTask[i].waitingTime;}
		if (oldTask[i].type == 2) { res = "Large"; nbLarge++; averageWaitingTimeLarge += oldTask[i].waitingTime; }
		if (oldTask[i].type == 3) { res = "Huge"; nbHuge++; averageWaitingTimeHuge += oldTask[i].waitingTime; }
		fd << res << ";" << oldTask[i].node << ";" << oldTask[i].timeOnNode << ";" << oldTask[i].hour << endl;
	}

	if (nbShort != 0) { averageWaitingTimeShort = averageWaitingTimeShort / nbShort; }
	if (nbMed != 0) { averageWaitingTimeMed = averageWaitingTimeMed / nbMed; }
	if (nbLarge != 0) { averageWaitingTimeLarge = averageWaitingTimeLarge / nbLarge; }
	if (nbHuge != 0) { averageWaitingTimeHuge = averageWaitingTimeHuge / nbHuge; }
	if (oldTask.size() != 0) { turnaroundtime = turnaroundtime / oldTask.size(); }

	fd << endl << "The average waiting time is " << averageWaitingTimeShort << " for short task, " << averageWaitingTimeMed << " for medium task, " << averageWaitingTimeLarge << " for large task and " << averageWaitingTimeHuge << " for huge task" << endl;
	fd << endl << "The simulation run " << nbShort << " short task, " << nbMed << " medium task, " << nbLarge << " large task and " << nbHuge << " huge task" << endl;
	fd << endl << "The machine run " << nbHourTotal << " machine hour of task" << endl;
	fd << endl << "The ratio between hour used and the total hour is : " << Ratio(oldTask) << endl;
	fd << endl << "The average turnaround time ratio is " << turnaroundtime << endl;
	
	fd << endl << "User of done task" << endl;
	fd << "Name ;Status; Group ;personnalId ;hoursSpend ;numberOfTask ;hoursincelastjob ;Money spend ;length  = " << listLastUser.size() << " ;" << endl;
	for (unsigned int i = 0; i < listLastUser.size(); i++) {
		fd << listLastUser[i].name << ";" << listLastUser[i].status << ";" << listLastUser[i].group << ";" << listLastUser[i].personalId << ";" << listLastUser[i].hoursSpend << ";" << listLastUser[i].numberOfTask << ";" << listLastUser[i].hourSinceLastJob << ";" << listLastUser[i].GetMoneyFromUser(listLastUser[i]) << endl;
	}
	if (waitingListTask.size() > 0) {
		fd << endl << "Waiting List" << endl;
		fd << "Type ;Node ;Waiting Time ;Name ;Groupe ;personnalId ;hoursSpend ;numberOfTask ;hoursincelastjob ;length  = " << waitingListTask.size() << " ;" << endl;
		/*for (unsigned int i = 0; i < waitingListTask.size(); i++) {
			if (waitingListTask[i].type == 0) { res = "Short"; }
			if (waitingListTask[i].type == 1) { res = "Medium"; }
			if (waitingListTask[i].type == 2) { res = "Large"; }
			if (waitingListTask[i].type == 3) { res = "Huge"; }
			fd << res << ";" << waitingListTask[i].node << ";" << waitingListTask[i].waitingTime << ";" << waitingListTask[i].user.name << ";" << waitingListTask[i].user.group << ";" << waitingListTask[i].user.personalId << ";" << waitingListTask[i].user.hoursSpend << ";" << waitingListTask[i].user.numberOfTask << ";" << waitingListTask[i].user.hourSinceLastJob << endl;
		}*/
	}
	fd.close();
}
/*!
*  \brief The main function
*
*  The main function, handle everything 
*
*  \return Int, if everything work properly it will return 42
*/
int main() {
	Task temptask;
	User user;
	//while ((machine.day != 0 || machine.hour != 8)) {
		int nbRequet = 0;//rand()%49+1
		for (unsigned int i = 0; i <= nbRequet; i++) {
			vector<string> request = listenerUser();
			user = User(request[0], request[1], request[2]);
			temptask = createTask(stoi(request[3]), stoi(request[4]), stoi(request[5]), user);
			while (!(temptask.taskDataOK(temptask) && IsUserAllowed(temptask))) {
				request = listenerUser();
				user = User(request[0], request[1], request[2]);
				temptask = createTask(stoi(request[3]), stoi(request[4]), stoi(request[5]), user);
			}
			if (temptask.type != 3) {
				schedule.Schedule(&waitingListTask, temptask);
			} else {
				schedule.Schedule(&waitingListTaskHuge, temptask);
			}
		}
		if ((waitingListTask.empty() || waitingListTaskHuge.empty())) {
			doWaitingList();
		}

		for (unsigned int i = 0; i < taskRunning.size(); i++) {
			ExecuteTask(&taskRunning[i]);
			if (!taskRunning[i].exe) {
				finishTask(&taskRunning[i]);
				PushUserList(taskRunning[i].user);
				oldTask.push_back(taskRunning[i]);
				taskRunning.erase(taskRunning.begin() + i);
			}	
		}

		if (listLastUser.size() > 0) {
			listLastUser[0].AddHourUser(&listLastUser);
		}
		if (!waitingListTask.empty()) {
			for (unsigned int i = 0; i < waitingListTask.size(); i++) {
				waitingListTask[i].waitingTime += 1;
			}
		}
		if (!waitingListTaskHuge.empty()) {
			for (unsigned int i = 0; i < waitingListTaskHuge.size(); i++) {
				waitingListTaskHuge[i].waitingTime += 1;
			}
		}
		machine.changeHour(&machine);
		cout << machine.hour << ";" << machine.day << "  " << machine.nodeUse << " " << waitingListTask.size() << endl;
	//}
	if (!taskRunning.empty()) {
		for (unsigned int i = 0; i < taskRunning.size(); i++) {
			PushUserList(taskRunning[i].user);
			oldTask.push_back(taskRunning[i]);
		}
	}
	PrintResult();
	return 42;
}

