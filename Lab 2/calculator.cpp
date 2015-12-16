#include "calculator.hpp"

double calculateTotal(double score, double total, double weight)
{
	return (score / total)*weight;
}
void calculateFinalGrade(unsigned int number, Artifacts *artifacts, Student* students)
{
	for (int x = 0; x < number; x++)
	{
		if (students[x].gradeOpt == 'G')
		{
			if (students[x].totalScore >= artifacts->gradePoints[0])
				students[x].finalGrades  = 'A';
			else if ( students[x].totalScore >=artifacts->gradePoints[1])
				students[x].finalGrades = 'B';
			else if (students[x].totalScore >= artifacts->gradePoints[2])
				students[x].finalGrades = 'C';
			else if (students[x].totalScore >= artifacts->gradePoints[3])
				students[x].finalGrades = 'D';
			else
				students[x].finalGrades = 'F';
		}
		else
		{
			if (students[x].totalScore >= artifacts->gradePoints[2])
			{
				students[x].finalGrades = 'P';
			}
			else
				students[x].finalGrades = "NP";
		}		
	}	
}
