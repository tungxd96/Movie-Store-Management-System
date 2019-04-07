#ifndef DMOVIE_H
#define DMOVIE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "movie.h"
using namespace std;

class D : public Movie {

public:
	D();	// Constructor
	~D();	// Destructor
	void setMovie(ifstream &);
	void display();
	int getIndex(string, string);
	void setStock(string, string, string);
	
private:
	vector<Movie> d;
};
#endif
