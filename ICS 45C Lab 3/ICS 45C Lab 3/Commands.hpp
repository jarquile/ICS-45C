#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <algorithm>
#include <string>
#include <iostream>
#include "HashMap.hpp"  
#include <sstream> 
#include <vector>
class Commands
{
public:
	Commands();

	void handleCommands();

private:
	bool debugFlag;
	
	HashMap logins;
	void create(const std::string& username, const std::string& password);

	void login(const std::string& username, const std::string& password);

	void remove(const std::string& username);

	void debug(bool &debugFlg,std::string &cmd);

	void loginCount();

	void bucketCount();

	void loadFactor();

	void maxBucketSize();

};



#endif