#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "User.h"

using namespace std;

void executeBatch(string BatchFile) {
	string cmd(BatchFile);
	system(cmd.c_str());
}

int main() {
	
	executeBatch("Test.bat");
	return 0;
}
