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

class Digital_Device // Digital_Device class
{
public:
	const char* os[5] = { "Android","IOS","Blackberry OS","Windows OS","Symbian OS" };
	const char* model[5] = { "Galaxy S20","X","Bold 9700","Lumia 925","Redmi 9A" };
	const char* brands[5] = { "Samsung","Apple","Blackberry","Nokia","Xiaomi" };
	const char* type[5] = { "Laptop","Server","Console","Desktop","Mobile" };
	const char* storage[5] = { "32gb","64gb","128gb","16gb","256gb" };
	const char* camera[5] = { "20mp","30mp","10mp","35mp","40mp" };
	const char* signal[5] = { "2G","3G","4G","4.5G","5G" };

	tidyConsole _t;

	virtual void printDevices(string titles[], vector<vector<const char*>> mixed, int titleSize)
	{
		_t.tableValues(titles, mixed, titleSize);
	}

	virtual void printMobile(string titles[], vector<vector<const char*>> mixed, int titleSize)
	{
		_t.tableValues(titles, mixed, titleSize);
	}

	int titleCount = 7;
	string* titles = new string[titleCount];
	string* deviceTitles() {
		titles[0] = "Type";
		titles[1] = "Brand";
		titles[2] = "Model";
		titles[3] = "Storage";
		titles[4] = "Camera";
		titles[5] = "Signal";
		titles[6] = "OS";
		return titles;
	}

	int getSize() {
		return titleCount;
	}

	vector<vector<const char*>> devices() {
		vector<vector<const char*>> mixed(5);

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			int col = 7;

			mixed[i] = vector<const char*>(col);
			for (int j = 0; j < col; j++)
			{
				int v1 = rand() % 5 + 0;

				mixed[i][0] = type[v1];
				mixed[i][1] = brands[v1];
				mixed[i][2] = model[v1];
				mixed[i][3] = storage[v1];
				mixed[i][4] = camera[v1];
				mixed[i][5] = signal[v1];
				mixed[i][6] = os[v1];
			}
		}

		return mixed;
	}
};

class Mobile_Phone : public Digital_Device // Derived class from Digital_Device
{
public:
	int titleCount = 7;
	string* titles = new string[titleCount];
	string* mobileTitles() {
		titles[0] = "Type";
		titles[1] = "Brand";
		titles[2] = "Model";
		titles[3] = "Storage";
		titles[4] = "Camera";
		titles[5] = "Signal";
		titles[6] = "OS";
		return titles;
	}

	int getSize() {
		return titleCount;
	}

	vector<vector<const char*>> mobiles() {
		vector<vector<const char*>> mixed(5);

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			int col = 7;

			mixed[i] = vector<const char*>(col);
			for (int j = 0; j < col; j++)
			{
				int v1 = rand() % 5 + 0;

				mixed[i][0] = type[4];
				mixed[i][1] = brands[v1];
				mixed[i][2] = model[v1];
				mixed[i][3] = storage[v1];
				mixed[i][4] = camera[v1];
				mixed[i][5] = signal[v1];
				mixed[i][6] = os[v1];
			}
		}

		return mixed;
	}
};

void main() {

	tidyConsole _tidy;

	Digital_Device* _device;
	Mobile_Phone _mobile;

	_device = &_mobile;

	char choose;

	cout << "Please choose class type : ";
	cin >> choose;

	switch (choose)
	{
	case '1':
		_device->printMobile(_mobile.mobileTitles(), _mobile.mobiles(), _mobile.getSize());
		break;
	case '2':
		_device->printDevices(_device->deviceTitles(), _device->devices(), _device->getSize());
		break;
	}


}