#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Task.h"

using namespace std;

Task listTask[];



int main() {
	listTask[1].CreateTask("toto", "120552", "St", "Test.bat");
	listTask[1].ExecuteTask(listTask[1]);
	return 0;
}
