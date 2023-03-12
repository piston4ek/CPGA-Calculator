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
#include <iomanip>
#include <algorithm>
#include <iterator>

// The main class of processs all CPGA
class CPGAcalculator
{
private:
	// This field has a some typedefs
	typedef std::string NameOfStudent;
	typedef std::string NameOfDiscipline;
	typedef int Score;			// score represents in scale 0-100

public:
	// This function fill list of discipline from file in set of disciplines
	bool setDisciplineList();
	void addToDisciplineList(const NameOfDiscipline& discipline) { disciplineList.insert(discipline); }
	// This function fill list of students from file students.txt
	bool setStudentList();
	void addStudent(const NameOfStudent& student) { studentList.insert(student); }

	// Function that set grade list of student
	void setGradesOfStudent(const NameOfStudent& student);

	//-------------Is empty? methods ----------------------------------------//
	bool isDisciplineListEmpty() const { return disciplineList.empty(); }
	bool isStudentListEmpty() const { return studentList.empty(); }
	bool isGradListOfStudentEmpty() const { return gradeListOfStudents.empty(); }

	//----------------------- Show methods (in console)-------------------//
	void showDisciplineList() const;	
	void showStudentGrades(const NameOfStudent& student) const;
	void showStudentList() const;

private:
	// Structure that has description about discipline: score, ECTS-credits
	struct Discipline
	{
		float ECTS_credit;
		Score score;
	};
	// We will work with maps of Name Discipline to score & ects_credits
	// and also with name student to his map of disciplines
	typedef std::map<NameOfDiscipline, Discipline> GradeList;

	// Private members
	std::map<NameOfStudent, GradeList> gradeListOfStudents;
	std::set<NameOfDiscipline> disciplineList;
	std::set<NameOfStudent> studentList;

	// Privated functions
	void _setGradeList(GradeList& gradeList, const NameOfDiscipline& discipline);
};

//--------------------- Space for some inline functions------------------//

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

inline void CPGAcalculator::showStudentList() const
{
	if (isStudentListEmpty())
	{
		std::cout << "Nothing to show.\n";
	}
	else
	{
		std::copy(studentList.begin(), studentList.end(),
			std::ostream_iterator<NameOfDiscipline, char>(std::cout, "\n"));
	}
}

#endif // ! CPGACALCULATOR_H_