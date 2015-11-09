#include "Process.hpp"
#include "Student.hpp"
#include "calculator.hpp"
#include "Inputs.hpp"

void printCutpoint(unsigned int number, unsigned int set,Student *students)
{
	std::cout << "CUTPOINT SET " << set + 1 << std::endl;
	for (int i = 0; i < number; i++)
		std::cout << students[i].ID << " " << students[i].name << " " << students[i].finalGrades << std::endl;
}


void clean(unsigned int numstudents,Artifacts *artifact)
{
	delete[] artifact->gradePoints;
	delete[] artifact->total_points;
	delete[] artifact->weight;
}

void calculateAll()
{
	unsigned int numstudents;
	Artifacts* artifact = new Artifacts;
	getArtifacts(artifact);
	std::cin >> numstudents;
	Student* students = new Student[numstudents];
	getStudents(numstudents, students);
	getScores(numstudents, artifact, students);
	std::cout << "TOTAL SCORES" << std::endl;
	for (int i = 0; i < numstudents; i++)
		std::cout << students[i].ID << "" << students[i].name << " " << students[i].totalScore << std::endl;
	getCutoffs(numstudents, artifact, students);
	for (int x = 0; x < artifact->cutpoint_sets; x++)
	{
		getCutpoints(numstudents, x, artifact, students);
		printCutpoint(numstudents,x,students);
	}
	clean(numstudents,artifact);
	delete artifact;
	delete[] students;
}