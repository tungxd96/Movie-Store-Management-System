#include "movie.h"

Movie::Movie() {
	stock = 0;
	dir = "";
	title = "";
	actor = "";
	month = 0;
	year = 0;
}

Movie::~Movie() {}

Movie::Movie(int stock, string dir, string title, string actor, int month, int year) {
	this->stock = stock;
	this->sum.push_back(this->stock);
	this->dir = dir;
	this->title = title;
	this->actor = actor;
	this->act.push_back(this->actor);
	this->month = month;
	this->year = year;
}

Movie::Movie(int stock, string dir, string title, int year) {
	this->stock = stock;
	this->dir = dir;
	this->title = title;
	this->year = year;
}

Movie::Movie(string id, int stock, string dir, string title, string actor, int month, int year) {
	this->id = id;
	this->stock = stock;
	this->dir = dir;
	this->title = title;
	this->actor = actor;
	this->month = month;
	this->year = year;
}

Movie::Movie(string id, int stock, string dir, string title, int year) {
	this->id = id;
	this->stock = stock;
	this->dir = dir;
	this->title = title;
	this->year = year;
}

void Movie::display() {
	string store = " MOVIE STORE ";
	for (int i = 0; i < WIDTH/2 - store.length()/2; i++) cout << "-";
	cout << store;
	for (int i = 0; i < WIDTH/2 - store.length()/2 - store.length()%2; i++) cout << "-";
	cout << endl;
}

void Movie::setMovie(ifstream &infile) {
	string l, comma = ",", space = " ", s, actor, id;
	int pos = 0, invalid_pos = 0, actor_count = 0;
	bool isInvalid = false;
	vector<string> invalidC_vec, invalid_vec;
	
	// Read type C data and add to array 
	for(;;) {
		getline(infile, l);
		id = l[0];
		while ((pos = l.find(comma)) != -1) {				
			s = l.substr(0, pos);
			if (id != "F" && id != "D" && id != "C") {
				invalidC_vec.push_back(s);
				isInvalid = true;
			}
			l.erase(0, pos + comma.length() + space.length());
		}
		if (isInvalid) {
			if (l.length() > 5) {
				while ((invalid_pos = l.find(space)) != -1) {
					s = l.substr(0, invalid_pos);
					if(!isNumber(s)) {
						if (actor_count == 0) {
							actor = s;
							actor_count++;
						} else if (actor_count > 0) {
							actor += space + s;
							invalidC_vec.push_back(actor);
						}
					} else {
						invalidC_vec.push_back(s);
					}
					l.erase(0, invalid_pos + space.length());
				}
				actor_count = 0;
				invalidC_vec.push_back(l);
			} else {
				invalidC_vec.push_back(l);
				for (int i = invalidC_vec.size() - 5; i < invalidC_vec.size(); i++) {
					invalid_vec.push_back(invalidC_vec[i]);
				}
				invalidC_vec.erase(invalidC_vec.begin() + invalidC_vec.size() - 5, invalidC_vec.begin() + invalidC_vec.size());
			}
		}
		isInvalid = false;
		if (infile.eof()) break;
	}
	
	// Add invalid id of classic movie to data 
	for (int i = 0; i < invalidC_vec.size(); i+=7) {
		Movie *type = new Movie(invalidC_vec[i], stoi(invalidC_vec[i+1]), invalidC_vec[i+2], invalidC_vec[i+3], invalidC_vec[i+4], stoi(invalidC_vec[i+5]), stoi(invalidC_vec[i+6]));
		errorC_type.push_back(*type);
	}
	
	// Add invalid id of comedy & drama to data 
	for (int i = 0; i < invalid_vec.size(); i+=5) {
		Movie *type = new Movie(invalid_vec[i], stoi(invalid_vec[i+1]), invalid_vec[i+2], invalid_vec[i+3], stoi(invalid_vec[i+4]));
		error_type.push_back(*type);
	}
}

void Movie::displayInvalid() {
	cout << endl;
	string stock = "+ In stock: ", dir = "+ Director: ", actor = "+ Actor: ", date = "+ Released Date: ", type = "Classic";
	cout << "*** Movie Not Found ***" << endl << endl;
	
	for (int i = 0; i < errorC_type.size(); i++) {
		cout << i+1 << ". " << errorC_type[i].title << " (Error: Invalid ID)"<< endl; 
		cout << "+ Id: " << errorC_type[i].id << " (Suggested: C for Classic)" << endl;
		cout << dir << errorC_type[i].dir << endl;
		cout << actor << errorC_type[i].actor << endl;
		cout << date << errorC_type[i].month << "/" << errorC_type[i].year << endl;
		cout << endl;
	}
	
	for (int i = 0; i < error_type.size(); i++) {
		cout << i+1 + errorC_type.size() << ". " << error_type[i].title << " (Error: Invalid ID)"<< endl; 
		cout << "+ Id: " << error_type[i].id << " (Suggested: F for Comedy or D for Drama)" << endl;
		cout << dir << error_type[i].dir << endl;
		cout << date << error_type[i].year << endl;
		cout << endl;
	}
}

bool Movie::isNumber(string s) { 
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == false) {
			return false; 
		}
	}
	return true; 
} 

//Comedy
int Movie::getIndex(string, int) {}
void Movie::setStock(string, int, string) {}

//Drama
int Movie::getIndex(string, string) {}
void Movie::setStock(string, string, string) {}

//Classic
int Movie::getIndex(int, int, string) {}
string Movie::getTitle(int, int, string) {}
void Movie::setStock(int, int, string, string) {}	