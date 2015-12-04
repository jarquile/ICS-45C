#include "Commands.hpp"
#include <iostream>    
#include <sstream> 
Commands::Commands()
	:debugFlag{ false }
{
}

void Commands::handleCommands()
{

	std::string line, first, second, third;
	do
	{
		std::string temp;
		int count = 0;
		first = second = third = "";
		std::getline(std::cin, line);
		std::stringstream lineStream1(line);
		std::stringstream lineStream2(line);

		while (lineStream1 >> temp)
			count++;

		if (count>3)
		{
			std::cout << "INVALID" << std::endl;
			continue;
		}

		lineStream2 >> first;
		lineStream2 >> second;
		lineStream2 >> third;

		line = first + " " + second + " " + third;

		if (line.find(" ") == -1)
			first = line;
		else
		{
			first = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);
			if (line.find(" ") == -1)
				second = line;
			else
			{
				second = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);
				third = line;
			}
		}
		if (first == "CREATE" && second != "" && third != "")
			create(second, third);
		else if (first == "LOGIN" && second != "" && third != "")
			login(second, third);
		else if (first == "LOGIN" && second == "COUNT" && third == "")
			loginCount();
		else if (first == "REMOVE")
			remove(second);
		else if (first == "DEBUG" && (second == "ON" || second == "OFF"))
			debug(debugFlag, second);
		else if (first == "BUCKET" && second == "COUNT")
			bucketCount();
		else if (first == "LOAD" && second == "FACTOR")
			loadFactor();
		else if (first == "CLEAR")
		{
			logins.deleteBucket();
			std::cout << "CLEARED" << std::endl;
		}
		else if (first == "QUIT")
			std::cout << "GOODBYE" << std::endl;

		else if (first == "MAX" && second == "BUCKET" && third == "SIZE")
			maxBucketSize();
		else
			std::cout << "INVALID" << std::endl;
	} while (first != "QUIT");
}


void Commands::create(const std::string & username, const std::string & password)
{
	if (logins.contains(username))
	{
		std::cout << "EXISTS" << std::endl;
	}
	else
	{
		logins.add(username, password);
		std::cout << "CREATED" << std::endl;
	}
}

void Commands::login(const std::string & username, const std::string & password)
{
	if (logins.contains(username))
	{
		if (logins.value(username) == password)
			std::cout << "SUCCEEDED" << std::endl;
		else
			std::cout << "FAILED" << std::endl;
	}
	else
		std::cout << "FAILED" << std::endl;
}

void Commands::remove(const std::string & username)
{
	if (!logins.contains(username))
		std::cout << "NONEXISTENT" << std::endl;
	else
	{
		logins.remove(username);
		std::cout << "REMOVED" << std::endl;
	}

}

void Commands::debug(bool & debugFlg, std::string & cmd)
{
	if (cmd == "ON" && debugFlag == true)
		std::cout << "ON ALREADY" << std::endl;
	else if (cmd == "OFF" && debugFlag == false)
		std::cout << "OFF ALREADY" << std::endl;
	else if (cmd == "ON" && debugFlag == false)
	{
		std::cout << "ON NOW" << std::endl;
		debugFlag = true;
	}
	else if (cmd == "OFF" && debugFlag == true)
	{
		std::cout << "OFF NOW" << std::endl;
		debugFlag = false;
	}
}

void Commands::loginCount()
{
	if (debugFlag)
		std::cout << logins.size() << std::endl;
	else
		std::cout << "INVALID" << std::endl;
}

void Commands::bucketCount()
{
	if (debugFlag)
		std::cout << logins.bucketCount() << std::endl;
	else
		std::cout << "INVALID" << std::endl;
}

void Commands::loadFactor()
{
	if (debugFlag)
		std::cout << logins.loadFactor() << std::endl;
	else
		std::cout << "INVALID" << std::endl;
}

void Commands::maxBucketSize()
{
	std::cout << logins.maxBucketSize() << std::endl;
}



