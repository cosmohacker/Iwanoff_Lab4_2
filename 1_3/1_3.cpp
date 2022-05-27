#include "TextTable.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
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

class Building // Building class
{
public:
	const char* edu_name[5] = { "Kharkiv Polytechnic Institue","Stanford University","University of Oxford","Harvard University","Freie Universitat Berlin" };
	const char* building_name[5] = { "Kharkiv Polytechnic Institue","Berlin Cathedral","Empire State","Kiz Kulesi","King's College Chapel" };
	const char* location[5] = { "Ukraine/Kharkiv","Turkey/Istanbul","Germany/Berlin","USA/NYC","UK/Cambridge" };
	const char* types[5] = { "Residential","Educational","Institutional","Assembly","Business" };

	tidyConsole _t;

	virtual void printBuildings(string titles[], vector<vector<const char*>> mixed, int titleSize)
	{
		_t.tableValues(titles, mixed, titleSize);
	}

	virtual void printEdu(string titles[], vector<vector<const char*>> mixed, int titleSize)
	{
		_t.tableValues(titles, mixed, titleSize);
	}

	int titleCount = 3;
	string* titles = new string[titleCount];
	string* buildingTitles() {
		titles[0] = "Type";
		titles[1] = "Building Name";
		titles[2] = "Location";
		return titles;
	}

	int getSize() {
		return titleCount;
	}

	vector<vector<const char*>> buildings() {
		vector<vector<const char*>> mixed(5);

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			int col = 3;

			mixed[i] = vector<const char*>(col);
			for (int j = 0; j < col; j++)
			{
				int v1 = rand() % 5 + 0;

				mixed[i][0] = types[v1];
				mixed[i][1] = building_name[v1];
				mixed[i][2] = location[v1];
			}
		}

		return mixed;
	}
};

class Educational_Building : public Building // Derived class from Building
{
public:
	int titleCount = 3;
	string* titles = new string[titleCount];
	string* eduTitles() {
		titles[0] = "Type";
		titles[1] = "School Name";
		titles[2] = "Location";
		return titles;
	}

	int getSize() {
		return titleCount;
	}

	vector<vector<const char*>> edus() {
		vector<vector<const char*>> mixed(5);

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			int col = 3;

			mixed[i] = vector<const char*>(col);
			for (int j = 0; j < col; j++)
			{
				int v1 = rand() % 5 + 0;

				mixed[i][0] = types[1];
				mixed[i][1] = edu_name[v1];
				mixed[i][2] = location[v1];
			}
		}

		return mixed;
	}
};

void main() {

	tidyConsole _tidy;

	Educational_Building _edu;
	Building* _building;

	_building = &_edu;

	char choose;

	cout << "Please choose class type : ";
	cin >> choose;

	switch (choose)
	{
	case '1':
		_building->printEdu(_edu.eduTitles(), _edu.edus(), _edu.getSize());
		break;
	case '2':
		_building->printBuildings(_building->buildingTitles(), _building->buildings(), _building->getSize());
		break;
	}


}