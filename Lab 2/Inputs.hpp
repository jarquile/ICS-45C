#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <iostream>
#include <string>
#include "Student.hpp"



std::string getName();

void getArtifacts(Artifacts *artifacts);
void getStudents(unsigned int number,  Student *students);
void getScores(unsigned int number, Artifacts *artifacts, Student *students);
void getCutoffs(unsigned int number, Artifacts *artifacts, Student *students);
void getCutpoints(unsigned int number,Artifacts *artifacts, Student *students);
#endif
