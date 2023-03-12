#include "CPGAcalculator.h"
#include <string>
#include <iostream>

int main()
{
	using namespace std;
	CPGAcalculator test;
	string name = "Yurii Krasniuk";
	test.addStudent(name);
	test.setDisciplineList();
	if (!test.isStudentListEmpty() && !test.isDisciplineListEmpty())
	{
		cout << "That disciplines you'll set:\n";
		test.showDisciplineList();
		cout << "for your student " << name << endl;
		test.setGradesOfStudent(name);
	}
	else if (test.isStudentListEmpty())
	{
		cout << "Empty student list!\n";
	}
	else
	{
		cout << "Empty list of disciplines!\n";
	}
	test.showStudentGrades(name);
	return 0;
}