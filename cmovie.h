#ifndef CMOVIE_H
#define CMOVIE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "movie.h"
using namespace std;

class C : public Movie {
	
public:
	C();	// Constructor
	~C();	// Destructor
	void setMovie(ifstream &);	// Get movie data from file
	void display();
	string getTitle(int, int, string);
	int getIndex(int, int, string);
	int actorIndex(int, string);
	void setStock(int, int, string, string);
	
private:
	vector<Movie> c; 
};
#endif