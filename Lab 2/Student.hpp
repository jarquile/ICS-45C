#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>

struct Student
{
	unsigned int ID;
	char gradeOpt;
	std::string name;
	double totalScore;
	std::string finalGrades;

};

struct Artifacts
{
	unsigned int number;
	unsigned int* total_points;
	unsigned int* weight;
	unsigned int cutpoint_sets;
	double* gradePoints;
};
	

#endif
