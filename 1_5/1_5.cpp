#include <algorithm>
#include <iostream>
#include <cstdlib>
#include<stdlib.h>
#include<conio.h>
#include <ctime>

#define MAX_SIZE 5

using namespace std;

// Template Declaration

template<class T>
T getSearch(T x[], T element) {
	int i;

	cout << "\nYour Data   :";
	for (i = 0; i < MAX_SIZE; i++) {
		cout << "\t" << x[i];
	}

	for (i = 0; i < MAX_SIZE; i++) {
		if (x[i] == element) {
			cout << "\nFunction Template : Element  : " << element << " : Found :  Position : " << i + 1 << ".\n";
			break;
		}
	}

	if (i == MAX_SIZE)
		cout << "\nSearch Element : " << element << "  : Not Found \n";

	return MAX_SIZE;
}
template<class T>
T getSearchBetween(T x[], T el1, T el2) {
	int i, j;

	cout << "\nYour Data   :";
	for (i = 0; i < MAX_SIZE; i++) {
		cout << "\t" << x[i];
	}

	for (int i = el1; i < el2; i++) {
		if (i > el1)
		{
			cout << "\n Numbers Between  " << el1 << " and " << el2 << " : " << i  << "\n";
		}
	}

	if (i == MAX_SIZE)
		cout << "\nSearch Element : " << el1 << "  : Not Found \n";

	return MAX_SIZE;
}

void main() {

	int arr_search[MAX_SIZE], i, element, el1, el2;
	float f_arr_search[MAX_SIZE], f_element;

	cout << "Simple Function Template Array Program Example : Search Number\n";
	cout << "\nEnter " << MAX_SIZE << " Elements for Searching Int : " << endl;
	for (i = 0; i < MAX_SIZE; i++)
		cin >> arr_search[i];

	cout << "\nEnter Element to Search (Int) : ";
	cin >> element;

	cout << "\nEnter Two Int Elements To Get Elements Between Range : ";
	cin >> el1;
	cin >> el2;

	getSearchBetween(arr_search, el1, el2);

	// Passing int Array to Template Function
	getSearch(arr_search, element);

	cout << "\nEnter " << MAX_SIZE << " Elements for Searching Float : " << endl;
	for (i = 0; i < MAX_SIZE; i++)
		cin >> f_arr_search[i];

	cout << "\nEnter Element to Search (Float) : ";
	cin >> f_element;

	// Passing int Array to Template Function
	getSearch(f_arr_search, f_element);
}