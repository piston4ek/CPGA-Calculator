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
bool CPGAcalculator::getDisciplineList()
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
