#pragma once
class User
{
public:
	//variable
	string userName, idName, type;
	string nameBatch, pathToFile;
	//function
	User CreateTask(string userName, string idName, string type, string nameBatch, string pathToFile);
	User();
	~User();
};

