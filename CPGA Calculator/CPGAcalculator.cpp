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
	// Read from studentsTXT and place all of in studentList
	_readFromFileInSet(studentsTXT, studentList);
	// Read from disciplinesTXT
	_readFromFileInSet(disciplinesTXT, disciplineList);
	// Now the goal -- is copy from all of student_name_example.txt files info
	// and place in gradeListOfStudents
	for (auto name = studentList.begin(); name != studentList.end(); ++name)
	{
		gradeListOfStudents[*name] = _getGradeListFromFile(*name);
	}
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

void CPGAcalculator::_readFromFileInSet(const char* file_name, std::set<std::string>& someList)
{
	using namespace std;
	ifstream file;
	// Openning file.txt
	file.open(file_name);
	if (!file.is_open())
	{
		cerr << "Error oppening and reading " << file_name << " file.\n"
			<< "Error exit\n";
		exit(EXIT_FAILURE);
	}
	// Copy in someList(set<string>) from file.txt
	string line;
	while (getline(file,line))
	{
		someList.insert(line);
	}
	file.close();
}

CPGAcalculator::GradeList CPGAcalculator::_getGradeListFromFile(const NameOfStudent& name)
{
	using namespace std;
	// Open a file with grades of student_name
	const string file_name = name + ".txt";
	ifstream file(file_name);
	if (!file.is_open())
	{
		cerr << "Error openning " << file_name << ". "
			<< "Stop Program.\n";
		exit(EXIT_FAILURE);
	}
	GradeList courses;
	string line;
	// Skip first line with "Name of Discipline	ECTS Score..."
	getline(file, line);
	// Read next data
	while (getline(file, line))
	{
		istringstream ss(line);
		string title;
		float ects;
		int score;
		getline(ss, title, '\t');
		if (!(ss >> ects >> score) || ects < 0 || (score < 0 || score > 100))
		{
			cerr << "Invalid input, skip \"" << line << "\"\n";
			continue;
		}
		// If we don't have a discipline in disciplineList case
		auto disc = disciplineList.find(title);
		if (disc == disciplineList.end())
		{
			cerr << '\"' << title << "\" no matches found in discipine list.\n"
				<< "Skip \"" << line << "\"\n";
			continue;
		}
		courses[title] = { ects,score };
	}
	return courses;
}
