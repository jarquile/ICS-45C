#include "Inputs.hpp"
#include "calculator.hpp"

std::string getName()
{
	std::string name;
	std::getline(std::cin, name);
	return name;

}

void getArtifacts(Artifacts *artifact)
{
	std::cin >> artifact->number;
	artifact->total_points = new unsigned int[artifact->number];
	artifact->weight = new unsigned int[artifact->number];
	
	for (int x = 0; x < artifact->number; x++)
	{
		std::cin >> artifact->total_points[x];
	}

	for (int y = 0; y < artifact->number; y++)
	{
		std::cin >> artifact->weight[y];
	}
}

void getStudents(unsigned int number,  Student *students)
{
	for (int x = 0; x < number; x++)
	{
		Student s;
		std::cin >> s.ID;
		std::cin >> s.gradeOpt;
		s.name = getName();
		s.totalScore = 0;
		students[x] = s;
		
	}
}

void getScores(unsigned int number, Artifacts *artifacts, Student *students)
{
	unsigned int scores;
	std::cin >> scores;

	for (int z = 0; z < scores;z++)
	{ 
		unsigned int id;
		std::cin >> id;
		for (int y = 0; y < number; y++)
		{
			
			if (students[y].ID == id)
			{
				for (int x = 0; x < artifacts->number; x++)
				{
					double score;
					std::cin >> score;
					students[y].totalScore += calculateTotal(score, artifacts->total_points[x], artifacts->weight[x]);
				}
			}
		}
	}
	
}

void getCutoffs(unsigned int number, Artifacts *artifacts, Student *students)
{
	std::cin >> artifacts->cutpoint_sets;
	artifacts->gradePoints = new double[4];
	for (int x = 0; x < number; x++)
	{
		students[x].finalGrades = " ";
	}
}

void getCutpoints(unsigned int number, Artifacts *artifacts, Student *students)
{
	std::cin >> artifacts->gradePoints[0];
	std::cin >> artifacts->gradePoints[1];
	std::cin >> artifacts->gradePoints[2];
	std::cin >> artifacts->gradePoints[3];

	calculateFinalGrade(number, artifacts, students);
}