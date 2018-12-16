#pragma once

/*!
 * \file HugeTask.h
 * \brief HugeTask Class
 * \class HugeTask
 * This class contain all the necessary constant for the program for the huge task
 */

class HugeTask
{
public:
	int const static maxNode = 128;			/*!< The maximum number for all the huge task*/
	int const static maxNodeperJob = 128;	/*!< The maximum number for each huge task*/
	int const static maxHour = 66;			/*!< The maximum time for the huge task */
	int const static firstHourLunch = 17;	/*!< The last hour to lunch a huge task*/
};

