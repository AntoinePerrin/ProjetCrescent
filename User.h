#pragma once
class User
{
public:
	std::string Name, group;
	int studentId, Wallet, override;

	User();
	~User();
	User GetFromId(int id);
};

