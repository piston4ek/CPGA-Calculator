// CPGAcalculator.cpp -- definiton functions of CPGAcalculator,	//
// that process with scrores, list of students etc. 			//
// -------------------------------------------------------------//
// @author Yurii Krasniuk,										//
// Igor Sykorsky KPI											//
//--------------------------------------------------------------//

#include "CPGAcalculator.h"

// This function read discipline list from disciplines.txt file
// and set in disciplineList (set<NameOfDiscipline>);
// return false, if file isn't oppening
bool CPGAcalculator::setDisciplineList()
{
	const char* file_name = "disciplines.txt";
	std::ifstream input(file_name);
	if (!input.is_open())
	{
		std::cerr << "Cannot open " << file_name
			<< ".\tStop reading from file.\n";
		return false;
	}
	NameOfDiscipline temp;
	while (std::getline(input,temp))
	{
		disciplineList.insert(temp);
	}
	input.close();
	return true;
}

bool CPGAcalculator::setStudentList()
{
	const char* file_name = "students.txt";
	std::ifstream input(file_name);
	if (!input.is_open())
	{
		std::cerr << "Cannot open " << file_name
			<< ".\tStop reading from file.\n";
		return false;
	}
	NameOfStudent temp;
	while (std::getline(input, temp))
	{
		studentList.insert(temp);
	}
	input.close();
	return true;
}

void CPGAcalculator::setGradesOfStudent(const NameOfStudent& student)
{
	// Check that we have the student in our list
	auto stud = studentList.find(student);
	if (stud == studentList.end())
	{
		std::cout << "Student with this name doesn't exist. "
			<< "Stop processing...\n";
		return;
	}
	GradeList grades;
	for (auto it = disciplineList.begin(); it != disciplineList.end(); ++it)
	{
		_setGradeList(grades, *it);
	}
	gradeListOfStudents[student] = grades;
}

void CPGAcalculator::showStudentGrades(const NameOfStudent& student) const
{
	using namespace std;
	auto it = gradeListOfStudents.find(student);
	if (it == gradeListOfStudents.end())
	{
		std::cout << "Student with this name doesn't exist. "
			<< "Stop processing...\n";
		return;
	}
	auto grades = it->second;
	cout << left << setw(40) << "Name of discipline"
		<< setw(10) << "ECTS" << setw(10) << "Total Score" << endl;
	for (auto it = grades.begin(); it != grades.end(); ++it)
	{
		cout << left << fixed << setw(40) << it->first <<
			setw(10) << setprecision(1) << it->second.ECTS_credit
			<< setw(10) << it->second.score << endl;
	}
}

void CPGAcalculator::_setGradeList(GradeList& gradeList, const NameOfDiscipline& discipline)
{
	using std::cout;
	using std::cin;
	using std::ignore;
	using std::endl;
	cout << '\"' << discipline << '\"' << endl;
	Discipline temp{};
	// Total score
	cout << "score(0-100): ";
	cin >> temp.score;
	// bad input or not in range
	while (!cin||(temp.score < 0 || temp.score > 100))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "score(0-100): ";
		cin >> temp.score;
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// ECTS credit
	cout << "ECTS-credits(>0): ";
	cin >> temp.ECTS_credit;
	while (temp.ECTS_credit < 0.0f || !cin)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "ECTS-credits(>0): ";
		cin >> temp.ECTS_credit;
	} 
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// Initialization of new value
	gradeList[discipline] = temp;
}
