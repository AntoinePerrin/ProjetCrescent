#pragma once

/*!
 * \file MediumTask.h
 * \brief MediumTask Class
 * \class MediumTask
 * This class contain all the necessary constant for the program for the medium task
 */

class MediumTask
{
public:
	int const static maxNode = 36;			/*!< The maximum number for all the medium task*/
	int const static maxNodeperJob = 12;	/*!< The maximum number for each medium task*/
	int const static maxHour = 8;			/*!< The maximum time for the medium task */
	int const static lastHourLunch = 10;	/*!< The last hour to lunch a medium task*/
};

