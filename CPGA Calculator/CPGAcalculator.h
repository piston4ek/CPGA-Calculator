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
#include <sstream>
#include <algorithm>
#include <iterator>

// The main class of processs all CPGA
class CPGAcalculator
{
private:
	// This field has a some typedefs
	typedef std::string NameOfStudent;
	typedef std::string NameOfDiscipline;

	// Structure that has description about discipline: score, ECTS-credits
	struct Discipline
	{
		float ECTS_credit;
		int score;
	};

	// We will work with maps of Name Discipline to score & ects_credits
	// and also with name student to his map of disciplines
	typedef std::map<NameOfDiscipline, Discipline> GradeList;

public:
	//-----------------------------Get methods----------------------------------//
	//std::set<NameOfStudent> getStudentList() const { return studentList; }
	//std::set<NameOfDiscipline> getDisciplineList() const { return disciplineList; }

	size_t countOfStudents() const { return studentList.size(); }
	size_t countOfDisciplines () const { return disciplineList.size(); }

	// This function fill list of discipline from file in set of disciplines
	void setDisciplineList() { _readFromFileInSet("disciplines.txt", disciplineList); }
	void addToDisciplineList(const NameOfDiscipline& title) { disciplineList.insert(title); }

	// This function fill list of students from file students.txt
	void setStudentList() { _readFromFileInSet("students.txt", studentList); }
	void addStudent(const NameOfStudent& student) { studentList.insert(student); }

	// Function that set grade list of student
	void setGradesOfStudent(const NameOfStudent& student);
	// Function set grade & ects by title of discipline and name of student
	void setGrade(const NameOfStudent& student, const NameOfDiscipline& title,
		float ects, int grade);

	//-------------Is empty? methods ----------------------------------------//
	bool isDisciplineListEmpty() const { return disciplineList.empty(); }
	bool isStudentListEmpty() const { return studentList.empty(); }
	bool isGradListOfStudentEmpty() const { return gradeListOfStudents.empty(); }

	//----------------------- Show methods (in console)-------------------//
	void showDisciplineList() const;	
	void showStudentGrades(const NameOfStudent& student) const;
	void showStudentList() const;

	//------------------------Constructors, destructors-------------------//
	CPGAcalculator() {};
	CPGAcalculator(const char* disciplinesTXT, const char* studentsTXT);
	~CPGAcalculator();
private:
	// Private members
	std::map<NameOfStudent, GradeList> gradeListOfStudents;
	std::set<NameOfStudent> studentList;
	std::set<NameOfDiscipline> disciplineList;

	// Privated helper functions
	void _setGradeList(GradeList& gradeList, const NameOfDiscipline& title);

	// This function create or rewrite file with student grades,
	// file should be named as a student and contents courses and grades
	void _createGradeFile(const NameOfStudent& student);
	
	void _outGrades(const GradeList& grades, std::ostream& out) const;

	void _readFromFileInSet(const char* file_name, std::set<std::string>& someList);

	GradeList _getGradeListFromFile(const NameOfStudent& name);
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