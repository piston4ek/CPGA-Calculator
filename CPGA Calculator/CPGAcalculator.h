// CPGAcalculator.h -- declaration of the main class, that	//
// process all scores of students, disciplines, etc. 		//
// --------------------------------------------------------	//
// @author Yurii Krasniuk,									//
// Igor Sykorsky KPI										//
//---------------------------------------------------------	//
#ifndef CPGACALCULATOR_H_
#define CPGACALCULATOR_H_

#include <map>
#include <string>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>

// The main class of processs all CPGA
class CPGAcalculator
{
public:
	// This function fill list of discipline from file in set of disciplines
	bool getDisciplineList();

	//-------------Is empty? methods ----------------------------------------//
	bool isDisciplineListEmpty() const { return disciplineList.empty(); }
	bool isStudentListEmpty() const { return studentList.empty(); }
	//---------------------------------------------------------------------//
	//
	//----------------------- Show methods (in console)-------------------//
	void showDisciplineList() const;
	//---------------------------------------------------------------------//
private:
	// Some definitons of typedef, structus
	typedef std::string NameOfStudent;
	typedef std::string NameOfDiscipline;
	typedef unsigned char Score;			// score represents in scale 0-100
	
	// Structure that has description about discipline: score, ECTS-credits
	struct Discipline
	{
		float ECTS_credit;
		Score score;
	};
	// We will work with maps of Name Discipline to score & ects_credits
	// and also with name student to his map of disciplines
	typedef std::map<NameOfDiscipline, Discipline> GradeList;

	std::map<NameOfStudent, GradeList> studentList;
	std::set<NameOfDiscipline> disciplineList;
};

// Space for some inline functions
inline void CPGAcalculator::showDisciplineList() const
{
	// If nothing to process
	if (isDisciplineListEmpty())
	{
		std::cout << "Nothing to show.\n";
	}
	// Otherwise, copy in ostream flow
	else
	{
		std::copy(disciplineList.begin(), disciplineList.end(),
			std::ostream_iterator<NameOfDiscipline, char>(std::cout, "\n"));
	}
}

#endif // ! CPGACALCULATOR_H_