#include <string>
#include "Task.h"
using namespace std;

string username, idName, type;
string nameBatch, pathToFile;




Task Task::CreateTask(string userName, string idName, string type, string nameBatch)
{
	Task temp;
	temp.userName = userName;
	temp.idName = idName;
	temp.type = type;
	temp.nameBatch = nameBatch;
	return temp;
}

void Task::ExecuteTask(Task userdata) {
	string cmd(userdata.nameBatch);
	system(cmd.c_str());
}

Task::Task()
{
}

Task::~Task()
{
}
