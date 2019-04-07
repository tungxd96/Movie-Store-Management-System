#ifndef CUSTDATA_H
#define CUSTDATA_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class CustomerData {

public:
	CustomerData();	// Constructor
	CustomerData(int, int, string, string);
	~CustomerData(); // Destructor
	
	int key;
	int id;
	string last_name;
	string first_name;
	vector<int> custId;
	vector<string> custLastN;
	vector<string> custFirstN;
	
};
#endif