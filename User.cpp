#include "User.h"
#include <string>
using namespace std;

string userName, idName, type;
string nameBatch, pathToFile;




User User::CreateTask(string userName, string idName, string type, string nameBatch, string pathToFile = "")
{
	User temp;
	temp.userName = userName;
	temp.idName = idName;
	temp.type = type;
	temp.nameBatch = nameBatch;
	temp.pathToFile = pathToFile;
	return temp;
}

User::User()
{
}

User::~User()
{
}
