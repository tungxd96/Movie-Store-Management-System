#ifndef RENTALDATA_H
#define RENTALDATA_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class RentalData {

public:
	RentalData();	// Constructor
	RentalData(string, int, string, string, int);
	RentalData(string, int, string, string, string);
	RentalData(string, int, string, string, int, int, string);
	~RentalData(); // Destructor
	
	int customerId;
	string disc;
	vector<string> rentType;
	vector<string> movieTitle;
	vector<string> movieDir;
	vector<string> movieActor;
	vector<int> movieMonth;
	vector<int> movieYear;
	
};
#endif