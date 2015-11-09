#include "calculator.hpp"

// converts angles to radians. 
double angleToRadian(double angle)
{
	return(angle / 180)*PI;
}


/*
Calulates the distance between two locations based on the formula provided.
*/
double getDistance(Airport depart, Airport arrival)
{
	double departLat = angleToRadian(depart.lat);
	double departLng = angleToRadian(depart.lng);
	double arrivalLat = angleToRadian(arrival.lat);
	double arrivalLng = angleToRadian(arrival.lng);
	double dlat = arrivalLat - departLat;
	double dlng = arrivalLng - departLng;
	double a = pow(sin(dlat / 2), 2) + cos(departLat)*cos(arrivalLat)*pow(sin(dlng / 2), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double d = 3959.9*c;
	return d;
}