#include "rentaldata.h"

//------------------- Constructor ------------------
RentalData::RentalData() {}


RentalData::RentalData(string type, int id, string disc, string movieTitle, int movieYear) {
	this->rentType.push_back(type);
	this->customerId = id;
	this->disc = disc;
	this->movieTitle.push_back(movieTitle);
	this->movieYear.push_back(movieYear);
}

RentalData::RentalData(string type, int id, string disc, string movieDir, string movieTitle) {
	this->rentType.push_back(type);
	this->customerId = id;
	this->disc = disc;
	this->movieDir.push_back(movieDir);
	this->movieTitle.push_back(movieTitle);
}

RentalData::RentalData(string type, int id, string disc, string movieTitle, int month, int year, string movieActor) {
	this->rentType.push_back(type);
	this->customerId = id;
	this->disc = disc;
	this->movieTitle.push_back(movieTitle);
	this->movieMonth.push_back(month);
	this->movieYear.push_back(year);
	this->movieActor.push_back(movieActor);
}

//------------------- Destructor -------------------
RentalData::~RentalData() {}