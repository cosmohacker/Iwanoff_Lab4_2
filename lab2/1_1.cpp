#include "TextTable.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "Start.h"
#include <ctime>

using namespace std;

class tidyConsole {
public:
	void tableValues(string titles[], vector<vector<const char*>> mixed, int titleSize) {
		TextTable t('-', '|', '+');

		size_t titleLenght = titleSize;

		for (int i = 0; i < titleLenght; i++) {
			t.add(titles[i]);
		}
		t.endOfRow();

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < mixed[i].size(); j++)
			{
				t.add(mixed[i][j]);
			}
			t.endOfRow();
		}
		t.setAlignment(2, TextTable::Alignment::RIGHT);
		cout << t;
	}

};

class Human // Human class
{
public:
	const char* school[5] = { "Kharkiv Polytechnic Institue","Stanford University","University of Oxford","Harvard University","Freie Universitat Berlin" };//Student
	const char* ideology[5] = { "Communism","Democracy","Environmentalism","Liberalism","Nationalism" };													//Human
	const char* estimated_date_of_death[5] = { "Kharkov","Istanbul","New York","Prague","Berlin" };															//Human
	const char* school_number[5] = { "09052001","13051997","123456789","418563297","0879213654" };															//Student
	const char* identity[5] = { "741258963","963258741","123456789","3571596482","597136480" };																//Citizen
	const char* professions[5] = { "Software Engineer","Chemist","Pilot","Soldier","Teacher" };																//Citizen
	const char* success_average[5] = { "Asian","Black","White","American Indian","Hispanic" };																//Student
	const char* gender[5] = { "Male","Female","Attack Helicopter","Nonbinary","Pansexual" };																//Citizen, Employee, Student, Human
	const char* countries[5] = { "Ukraine","Turkey","United States","Canada","England" };																	//Citizen
	const char* race[5] = { "Asian","Black","White","American Indian","Hispanic" };																			//Human
	const char* surname[5] = { "Griffin","Yavuz","Shevchenko","Martin","Wilson" };																			//Citizen, Employee, Student, Human
	const char* cities[5] = { "Kharkov","Istanbul","New York","Prague","Berlin" };																			//Citizen
	const char* name[5] = { "Peter","Yagizcan","Aleksander","Benjamin","James" };																			//Citizen, Employee, Student, Human
	const char* corporation[5] = { "Samsung","Microsoft","Apple","Nokia","IBM" };																			//Employee
	const char* age[5] = { "Youth ","Adults ","Seniors","Children","Teenager" };																			//Citizen, Employee, Student, Human
	const char* position[5] = { "Intern","Manager","CEO","Founder","CFO" };																					//Employee
	const char* salary[5] = { "10.000$","5.600$","0$","8.000$","16.000$" };																					//Employee
	const char* skin[5] = { "White","Blonde","Tan","Black","Bronze" };																						//Human

	tidyConsole _t;

	virtual void printCitizens(string titles[], vector<vector<const char*>> mixed, int titleSize)
	{
		_t.tableValues(titles, mixed, titleSize);
	}

	virtual void printStudents(string titles[], vector<vector<const char*>> mixed, int titleSize)
	{
		_t.tableValues(titles, mixed, titleSize);
	}

	virtual void printEmployees(string titles[], vector<vector<const char*>> mixed, int titleSize)
	{
		_t.tableValues(titles, mixed, titleSize);
	}

};

class Citizen : public Human // Derived class from Human
{
public:
	int titleCount = 8;
	string* titles = new string[titleCount];
	string* citizenTitles() {
		titles[0] = "Identity";
		titles[1] = "Name";
		titles[2] = "Surname";
		titles[3] = "Gender";
		titles[4] = "Age";
		titles[5] = "Country";
		titles[6] = "City";
		titles[7] = "Profession";
		return titles;
	}

	int getSize() {
		return titleCount;
	}

	vector<vector<const char*>> citizens() {
		vector<vector<const char*>> mixed(5);

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			int col = 8;

			mixed[i] = vector<const char*>(col);
			for (int j = 0; j < col; j++)
			{
				int v1 = rand() % 5 + 0;

				mixed[i][0] = identity[v1];
				mixed[i][1] = name[v1];
				mixed[i][2] = surname[v1];
				mixed[i][3] = gender[v1];
				mixed[i][4] = age[v1];
				mixed[i][5] = countries[v1];
				mixed[i][6] = cities[v1];
				mixed[i][7] = professions[v1];
			}
		}

		return mixed;
	}
};

class Student : public Human // Derived class from Human
{
public:
	int titleCount = 6;
	string* titles = new string[titleCount];
	string* studentTitles() {
		titles[0] = "Student Number";
		titles[1] = "Name";
		titles[2] = "Surname";
		titles[3] = "Gender";
		titles[4] = "Age";
		titles[5] = "School Name";
		return titles;
	}

	int getSize() {
		return titleCount;
	}

	vector<vector<const char*>> students() {
		vector<vector<const char*>> mixed(5);

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			int col = 6;

			mixed[i] = vector<const char*>(col);
			for (int j = 0; j < col; j++)
			{
				int v1 = rand() % 5 + 0;

				mixed[i][0] = school_number[v1];
				mixed[i][1] = name[v1];
				mixed[i][2] = surname[v1];
				mixed[i][3] = gender[v1];
				mixed[i][4] = age[v1];
				mixed[i][5] = school[v1];

			}
		}
		return mixed;
	}
};

class Employee : public Human // Derived class from Human
{
public:
	int titleCount = 7;
	string* titles = new string[titleCount];

	string* employeeTitles() {
		titles[0] = "Position";
		titles[1] = "Name";
		titles[2] = "Surname";
		titles[3] = "Age";
		titles[4] = "Gender";
		titles[5] = "Position";
		titles[6] = "Salary";
		return titles;
	}

	int getSize() {
		return titleCount;
	}

	vector<vector<const char*>> employees() {
		vector<vector<const char*>> mixed(5);

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			int col = 7;

			mixed[i] = vector<const char*>(col);
			for (int j = 0; j < col; j++)
			{
				int v1 = rand() % 5 + 0;

				mixed[i][0] = position[v1];
				mixed[i][1] = name[v1];
				mixed[i][2] = surname[v1];
				mixed[i][3] = age[v1];
				mixed[i][4] = gender[v1];
				mixed[i][5] = position[v1];
				mixed[i][6] = salary[v1];
			}
		}
		return mixed;
	}
};

void main() {

	start _s;
	tidyConsole _tidy;

	_s.startScreen();

	Employee _employee;
	Citizen _citizen;
	Student _student;
	Human* _human;

	_human = &_employee;
	_human = &_citizen;
	_human = &_student;

	char choose;

	cout << "Please choose class type : ";
	cin >> choose;

	switch (choose)
	{
	case '1':
		_human->printCitizens(_citizen.citizenTitles(), _citizen.citizens(), _citizen.getSize());
		break;
	case '2':
		_human->printStudents(_student.studentTitles(), _student.students(), _student.getSize());
		break;
	case '3':
		_human->printEmployees(_employee.employeeTitles(), _employee.employees(), _employee.getSize());
		break;
	}


}