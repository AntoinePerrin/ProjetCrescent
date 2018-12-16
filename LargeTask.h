#pragma once

/*!
 * \file LargeTask.h
 * \brief LargeTask Class
 * \class LargeTask
 * This class contain all the necessary constant for the program for the large task
 */

class LargeTask
{
public:
	int const static maxNode = 64;			/*!< The maximum number for all the large task*/
	int const static maxNodeperJob = 32;	/*!< The maximum number for each large task*/
	int const static maxHour = 16;			/*!< The maximum time for the large task */
	int const static lastHourLunch = 2;		/*!< The last hour to lunch a large task*/
};

