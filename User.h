#pragma once

#include <vector>

/*!
 * \file User.h
 * \brief User Class
 * \class User
 * User class have all the variable and tool to manage the User
 *
 */
class User
{
public:
	std::string name,/*!< The name of the user*/ status,/*!< Researcher/Student or IT Staff*/ group;/*!< Store the group of the user for researcher or student*/
	int personalId,/*!< The personnal Id of the user*/ hoursSpend,/*!< The number of hour spend on HPC*/ numberOfTask,/*!< The number of previous task asked by the user*/ hourSinceLastJob;/*!< Number of hour since the last job asked*/
	float override;/*!< The percentage of override, if equal to 1 there is no override. This parameter allow to use the HPC more than the max hour per week*/
	int const static maxHoursPerWeekPerUser = 1536;/*!< The max hour of use per week per user (24 hours * 64 nodes)*/
	
	/*!
	*  \brief Basic initiator
	*
	*  Basic initator, return a basic object of the class user
	*
	*  \return User, return a basic object of the class user
	*/
	User();
	/*!
	*  \brief Advanced initiator
	*
	*  Advanced initiator with 3 parameters
	*
	*	\param name the name of the user
	*	\param Id the personnal id of the user (s299405 for example)
	*	\param group is the group of researcher or student
	*  \return User, a full parametrize user
	*/
	User(std::string name, std::string Id, std::string group);
	/*!
	*  \brief Add hour for the last job
	*
	*  Add hour for the last job to a vector of user
	*
	*	\param *users
	*/
	void AddHourUser(std::vector<User> *users);
	/*!
	*  \brief Return the money spend by one user
	*
	*  Return the money spend by one user for the time spend on HPC
	*
	*	\param user the user we want to know the money he spend
	*  \return Double,the money spend 
	*/
	double GetMoneyFromUser(User user);
	/*!
	*  \brief Say if the user is in the vector
	*
	*  Return true if the user is in the list of vector by the personnal Id
	*
	*	\param id the Id we want search
	*	\param *users the vector of user we are currently looking
	*  \return Bool, return true if the Id is in the vector of user
	*/
	bool IsUserKnow(int id, std::vector<User> *users);
};

