// CPGAcalculator.cpp -- definiton functions of CPGAcalculator,	//
// that process with scrores, list of students etc. 			//
// -------------------------------------------------------------//
// @author Yurii Krasniuk,										//
// Igor Sykorsky KPI											//
//--------------------------------------------------------------//

#include "CPGAcalculator.h"

//------------------------Constructors, destructors-------------------//

// Constructor has to place all of data from .txt files
// in data structures
CPGAcalculator::CPGAcalculator(const char* disciplinesTXT, const char* studentsTXT)
{

}
// The main goal of destructor - is write all of data in files.txt
CPGAcalculator::~CPGAcalculator()
{
	using std::ofstream;
	using std::ios;
	using std::cerr;
	using std::copy;
	using std::ostream_iterator;
	using std::string;
	using std::for_each;
	// First step -- write all list of students in students.txt
	ofstream studentsTXT("students.txt", ios::trunc);
	if (!studentsTXT.is_open())
	{
		cerr << "Error openning students.txt file to overwrite data.\n"
			<< "Program determinating...";
		exit(EXIT_FAILURE);
	}
	copy(studentList.begin(), studentList.end(),
		ostream_iterator<NameOfDiscipline, char>(studentsTXT, "\n"));
	studentsTXT.close();
	// Second step -- write all of disciplines in disciplines.txt
	ofstream disciplinesTXT("disciplines.txt", ios::trunc);
	if (!disciplinesTXT.is_open())
	{
		cerr << "Error openning disciplines.txt file to overwrite data.\n"
			<< "Program determinating...";
		exit(EXIT_FAILURE);
	}
	copy(disciplineList.begin(), disciplineList.end(),
		ostream_iterator<NameOfDiscipline, char>(disciplinesTXT, "\n"));
	disciplinesTXT.close();
	// 3-rd step -- create all of files with each student name and content a grades
	for_each(studentList.begin(), studentList.end(), 
		[&](const NameOfStudent& student) {_createGradeFile(student); });
}

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
		std::cerr << "Student with this name doesn't exist. "
			<< "Stop processing...\n";
		return;
	}
	GradeList grades;
	for (auto it = disciplineList.begin(); it != disciplineList.end(); ++it)
	{
		_setGradeList(grades, *it);
	}
	gradeListOfStudents[student] = grades;
	//_createGradeFile(student);
}

void CPGAcalculator::showStudentGrades(const NameOfStudent& student) const
{
	auto it = gradeListOfStudents.find(student);
	if (it == gradeListOfStudents.end())
	{
		std::cerr << "Student with this name doesn't exist. "
			<< "Stop processing...\n";
		return;
	}
	_outGrades(it->second, std::cout);
}

void CPGAcalculator::_setGradeList(GradeList& gradeList, const NameOfDiscipline& title)
{
	using std::cout;
	using std::cin;
	using std::ignore;
	using std::endl;
	cout << '\"' << title << '\"' << endl;
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
	gradeList[title] = temp;
}

void CPGAcalculator::_createGradeFile(const NameOfStudent& student)
{
	auto it = gradeListOfStudents.find(student);
	if (it == gradeListOfStudents.end())
	{
		std::cerr << "Error, cannot find grades of student.\n"
			<< "Determinating program...";
		exit(EXIT_FAILURE);
	}
	const std::string file_name = student + ".txt";
	std::ofstream gradeFile(file_name, std::ios::trunc);	// clear file, if exist
	if (!gradeFile.is_open())
	{
		std::cerr << "Error openning " << file_name << ". "
			<< "Stop processing.\n";
		return;
	}
	_outGrades(it->second, gradeFile);
	gradeFile.close();
}

void CPGAcalculator::_outGrades(const GradeList& grades, std::ostream& out) const
{
	using namespace std;
	out << left << setw(30) << "Name of discipline"
		<< setw(10) << "ECTS" << setw(10) << "Total Score" << endl;
	for (auto it = grades.begin(); it != grades.end(); ++it)
	{
		out << left << fixed << setw(30) << it->first <<
			setw(10) << setprecision(1) << it->second.ECTS_credit
			<< setw(10) << it->second.score << endl;
	}
}
