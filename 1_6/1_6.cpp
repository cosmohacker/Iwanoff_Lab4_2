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
T storePair( string element1,T element2) {
	pair <string, int> p = make_pair(element1, element2);
	cout << p.first << " " << p.second << endl;
	return 0;
}

void main() {

	string element1;
	int element2;

	cout << "\nPair element 1 : ";
	cin >> element1;
	cout << "\nPair element 2 : ";
	cin >> element2;

	storePair(element1, element2);
}