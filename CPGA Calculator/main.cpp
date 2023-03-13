#include "CPGAcalculator.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
	using namespace std;
	CPGAcalculator test;
	// We will try with constructor
	string name = "Yurii Krasniuk";
	string disc = "OOP in C++";
	test.addStudent(name);
	test.setDisciplineList();
	test.addToDisciplineList(disc);
	if (!test.isStudentListEmpty() && !test.isDisciplineListEmpty())
	{
		test.setGradesOfStudent("Yurii Krasniuk");
		cout << "Courses list:\n";
		test.showDisciplineList();
		cout << "Student list:\n";
		test.showStudentList();
		cout << "Grades of Krasniuk Yurii:\n";
		test.showStudentGrades("Yurii Krasniuk");
	}
	else if (test.isStudentListEmpty())
	{
		cout << "Empty student list!\n";
	}
	else
	{
		cout << "Empty list of disciplines!\n";
	}
	return 0;
}