#pragma once

/*!
 * \file Machine.h
 * \brief Machine Class
 * \class Machine
 * Machine class have all the variable and tool to manage the machine
 * 
 */

class Machine
{
public:
	//Variable
	int hour;							/*!< The hour of the machine*/
	int day;							/*!< The day of the machine*/
	int nodeUse;						/*!< Number of node use*/
	int const static maxNode = 128;		/*!< The last hour to lunch a huge task*/
	int nodeForShort = 0,/*!< Number of node use for the short task*/ nodeForMedium = 0,/*!< Number of node use for the medium task*/ nodeForLarge = 0,/*!< Number of node use for the large task*/ nodeForHuge = 0;/*!< Number of node use for the huge task*/

	//Function
	/*!
	*  \brief Initiator with variable
	*
	*  Basic initiator for the class machine
	*
	*  \return Return a new object of the class machine
	*/
	Machine();

	//time
	/*!
	*  \brief Add one hour to the machine
	*
	*  Add one hour to the machine, if the day is over start a new day if the week is over start a new week
	*
	*	\param *machine the machine we want to add one hour
	*/
	void changeHour(Machine *machine);
	/*!
	*  \brief Return the hour of the machine
	*
	*  Return the hour of the machine
	*
	*	\param *machine the machine we want to get the hour
	*  \return Int, the hour of the machine
	*/
	int getHour(Machine machine);
	/*!
	*  \brief Set the hour of the machine
	*
	*  Set the hour of the machine
	*
	*	\param *machine the machine we want to set the hour
	*	\param hour the hour to apply to the machine
	*/
	void setHour(Machine *machine, int hour);
	/*!
	*  \brief Return the index of the day
	*
	*  Return the index of the day in the week(0 for Monday and 6 for Sunday)
	*
	*	\param machine the machine we want to get the index day
	*  \return Return the index of the day in the week
	*/
	int getIndexDay(Machine machine);
	/*!
	*  \brief Set a day
	*
	*  Set the day to the machine by the index 
	*
	*	\param *machine The machine we want to add one hour
	*	\param index The index of the day in the week
	*/
	void setDay(Machine *machine, int index);

	//node
	/*!
	*  \brief Return the number of node left
	*
	*  Return the number of node left in the machine
	*
	*  \param machine the machine we want to get the number of node left
	*  \return Int, return the number of node left
	*/
	int getNumberNode(Machine machine);
};

