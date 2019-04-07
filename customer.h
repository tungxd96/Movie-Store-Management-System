#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "custdata.h"
#include "rentaldata.h"
using namespace std;

const int SIZE = 26;

class Customer : CustomerData {

public: 
	Customer();	// Constructor
	~Customer();	// Destructor
	void setCustomer(ifstream &);	// Store customer data 
	int retrieveKey(int);
	string find(int);
	string getFirstname(int);
	string getLastname(int);
	void setRent(string, int, string, string, int);
	void setRent(string, int, string, string, string);
	void setRent(string, int, string, string, int, int, string);
	void display(int);
	
private:
	CustomerData* customerData;
	vector<RentalData> rentComedy;
	vector<RentalData> rentDrama;
	vector<RentalData> rentClassic;
};
#endif