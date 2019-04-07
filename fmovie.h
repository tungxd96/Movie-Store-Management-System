#ifndef FMOVIE_H
#define FMOVIE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "movie.h"
using namespace std;

class F : public Movie {
	
public:
	F();	// Constructor
	~F();	// Destructor
	void setMovie(ifstream &);
	void display();
	int getIndex(string, int);
	void setStock(string, int, string);
	
private:
	vector<Movie> f; 
};
#endif
