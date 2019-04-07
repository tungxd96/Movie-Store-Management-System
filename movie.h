#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const int WIDTH = 60;
class Movie {

public:
	Movie();	// Constructor
	~Movie();	// Destructor
	Movie(int, string, string, string, int, int);	// For storing Classic movie
	Movie(string, int, string, string, string, int, int);	// For storing invalid Id for Classic movie
	Movie(string id, int stock, string dir, string title, int year);	// For storing invalid Id for Comedy and Drama
	Movie(int, string, string, int);	// For storing Comedy and Drama movie
	virtual void display();				// Display movie
	virtual void setMovie(ifstream &);	// Set movie from file
	void displayInvalid();				// Display error code
	bool isNumber(string);				// Check if string is an integer
	//Comedy
	virtual int getIndex(string, int);
	virtual void setStock(string, int, string);
	//Drama
	virtual int getIndex(string, string);
	virtual void setStock(string, string, string);
	//Classic
	virtual int getIndex(int, int, string);
	virtual string getTitle(int, int, string);
	virtual void setStock(int, int, string, string);
	
	string id; 
	int stock;		// Stock
	string dir;		// Movie director
	string title;	// Movie title
	string actor;	// Actor
	int month;		// Released month
	int year;		// Released year
	vector<int> sum;
	vector<string> act;
		
private:
	vector<Movie> errorC_type;
	vector<Movie> error_type;
};
#endif