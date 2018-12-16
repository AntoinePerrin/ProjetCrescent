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
	int type;			/*!< The type of of the task*/
	int hour;			/*!< The lenght of the code*/
	int node;			/*!< The number of node on which the task is running*/
	bool exe;			/*!< Say if the task is running or not. If is't true the task is running*/
	int timeOnNode;		/*!< Store the time spend on the machine*/
	int waitingTime;	/*!< Store the time spend on the waiting list*/
	User user;			/*!< Link the user who ask for the task*/

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
};

#endif