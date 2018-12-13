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
	//Task createTask(int type, int node, int hour, User user);
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
	/*!
*  \brief Check hour to run
*
*  Before run it we check is there is still time before the week end
*
*  \param task the curent task we want to run
*  \param machine the machine we run the code
*  \return Return an true if the task can be run.
*/
	//bool ishourcorrect(Task task, Machine machine);
	/*!
*  \brief Check data
*
*  Check if there is still node left to run and if there is still time with is hour correct
*
*  \param task the curent task we want to run
*  \param machine the machine we run the code
*  \return Return an true if the task can be run imediately
*/
	//bool canbelunchpertype(Task task, Machine machine);
	/*!
*  \brief Allocate the node
*
*  Adding the task to the machine aka allocate the node on the machine.
*
*  \param task the curent task we want to run
*  \param machine the machine we run the code
*/
	//void addTask(Task *task, Machine *machine);
	/*!
*  \brief execute the task
*
*  Execute the task, if the task ended deactivate the task
*
*  \param task the curent task we want to run
*  \param machine the machine we run the code
*/
	//void ExecuteTask(Task *task, Machine *machine);
	/*!
*  \brief Finish the task
*
*  finish the task aka deallocate the node
*
*  \param task the curent task we want to run
*  \param machine the machine we run the code
*/
	//void finishTask(Task *task, Machine *machine);


	void AddHourTask(Task *task);

};

#endif