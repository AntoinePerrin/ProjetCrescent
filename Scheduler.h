#pragma once

#include <vector>
#include "Task.h"

/*!
 * \file Scheduler.h
 * \brief Scheduler Class
 * \class Scheduler
 * Handle the place in the waiting list. Here the order is given by the first in first out.
 */

class Scheduler : public Task
{
public:
	/*!
 *  \brief function called for add the task in the waiting list
 *
 *  Return the waiting list with the task added.
 *
 *  \param waitingListTask the waiting list of the main
 *	\param task the task we want to add to the wainting list
 *  \return Return a vector of Task with all the task which wait to be executed.
 */
	void Schedule(std::vector<Task> *waitingListTask, Task task);
};

