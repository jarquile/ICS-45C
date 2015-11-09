#include "input.hpp"

/*Input will take the 1 line of information and parse it into a struct containing the lat and lng in both string form and double form. 
The struct also houses the name of the location.*/
Airport input()
{
	std::string destination;
	std::getline(std::cin, destination);
	std::string lat1 = destination.substr(0, (destination.find("/") + 2));
	std::string lng2 = destination.substr((destination.find("/") + 3), (destination.find("/") + 3));
	double lat = stod(lat1);
	double lng = stod(lng2);
	if (lat1.find("S") != -1)
		lat = -lat;
	if (lng2.find("W") != -1)
		lng = -lng;
	std::string name = destination.substr(destination.rfind("/") + 3, destination.length());
	return Airport{ lat,lng,name,lat1,lng2 };
}

/*
Takes the variables returned from getInput and prints them out in the specified manner.
*/
void printResult(Airport starting,Airport near, Airport far, double near1, double far1)
{
	std::cout << "Start Location: " << starting.lat1 << " " << starting.lng2 << " " << "(" << starting.name << ")" << std::endl;
	std::cout << "Closest Location: " << near.lat1 << " " << near.lng2 << " " << "(" << near.name << ")" << " (" << near1 << " miles)" << std::endl;
	std::cout << "Fartheset Location: " << far.lat1 << " " << far.lng2 << " " << "(" << far.name << ")" << " (" << far1 <<" miles)" << std::endl;
}
/*
getInput will ask the user for an initial starting location. Then will loop x many times for locations. 
Each time an input is put in, comparisions will be made to see if the location is a new 
furtheset or closest. 

The usage of 2 if statements instead of if else is to take or the case that the user only enterd 2 locations which would make the closest and farthest the same. So I would need a way to enter the conditonal. 
*/

void getInput()
{
	double closest = 9999999;
	double farthest = -9999999;
	double far1, near1;
	Airport near, far;
	Airport starting = input();
	int locations;
	std::cin >> locations;
	std::cin.ignore();
	for (int x = 0; x < locations; x++)
	{
		Airport arrival = input();
		double dist = getDistance(starting, arrival);
		if (dist < closest)
		{
			closest = dist;
			near = arrival;
			near1 = dist;
		}
		if (dist > farthest)
		{
			farthest = dist;
			far = arrival;
			far1 = dist;
		}
	}
	printResult(starting, near, far, near1,far1);
}