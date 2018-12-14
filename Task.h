#ifndef TASK_H
#define TASK_H

#include "User.h"
/*!
 * \file Task.h
 * \brief Task Class
 * \class Task
 * Task have all the variables and methods to cracterise and execute task
 * The hour variable represent the lengh of the code, the code take time to execute so it is a shortcut.
 */

class Task
{
public:
	//Variable
	int type;
	int hour;
	int node;
	bool exe;
	int timeOnNode;
	User user;

	//Function
	/*!
 *  \brief Empty initiator
 *
 *  basic initiator, create an empty shell
 *
 *  \return Return an object of the class Task
 */
	Task();
	/*!
 *  \brief Return the maximum time
 *
 *  Return the maximum time of running for each type
 *
 *  \param task the curent task we want the maximum time running
 *  \return Return an int
 */
	int getMaxhour(Task task);
	/*!
*  \brief Return the maximum node
*
*  Return the maximum node for each type
*
*  \param task the curent task we want the maximum node
*  \return Return an int
*/
	int getMaxNodepertype(Task task);
	/*!
*  \brief Check data
*
*  After the initiate, we check the data before run it or put it in the waiting list
*
*  \param task the curent task we want to run
*  \return Return an true if the data is good
*/
	bool taskDataOK(Task task);



	void AddHourTask(Task *task);

};

#endif