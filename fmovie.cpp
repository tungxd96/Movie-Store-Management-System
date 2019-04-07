#include "fmovie.h"

//------------------- Constructor ------------------
F::F() {}

//------------------- Destructor -------------------
F::~F() {}

//--------------------- setMovie -------------------
void F::setMovie(ifstream &infile) {
	string l, comma = ",", space = " ", s, actor, id;
	int pos = 0;
	bool isF = false;
	vector<string> f_vec, f_sort;
	for(;;) {
		getline(infile, l);
		id = l[0];
		while ((pos = l.find(comma)) != -1) {		
			s = l.substr(0, pos);
			if (id == "F") {
				f_vec.push_back(s);
				isF = true;
			}
			l.erase(0, pos + comma.length() + space.length());
		}
		if (isF) {
			f_vec.push_back(l);
		}
		isF = false;
		if (infile.eof()) break;
	}
	
	int del;
	int minStock = stoi(f_vec[1]);
	string minDir = f_vec[2];
	string minTitle = f_vec[3];
	int minYear = stoi(f_vec[4]);
	int minSize = f_vec.size();

	while (f_vec.size() > 5) {
		for (int i = 1; i < minSize; i+=5) {
			if (f_vec[i+2] < minTitle) {
				minStock = stoi(f_vec[i]);
				minDir = f_vec[i+1];
				minTitle = f_vec[i+2];
				minYear = stoi(f_vec[i+3]);
			} else if (f_vec[i+2] == minTitle) {
				if (stoi(f_vec[i+3]) < minYear) {
					minStock = stoi(f_vec[i]);
					minDir = f_vec[i+1];
					minTitle = f_vec[i+2];
					minYear = stoi(f_vec[i+3]);
				} 
			}
		}
		for (int i = 1; i < minSize; i+=5) {
			if (f_vec[i+2] == minTitle && stoi(f_vec[i+3]) == minYear) {
				del = i;
				f_vec.erase(f_vec.begin()+ del - 1, f_vec.begin() + del - 1 + 5);
				minSize = f_vec.size();
				break;
			}
		}
		f_sort.push_back(to_string(minStock));
		f_sort.push_back(minDir);
		f_sort.push_back(minTitle);
		f_sort.push_back(to_string(minYear));
		minTitle = f_vec[3];	
		minYear = stoi(f_vec[4]);
	}
	// Add last movie to vector f_sort
	for (int i = 1; i < f_vec.size(); i++) {
		f_sort.push_back(f_vec[i]);
	}

	for (int i = 0; i < f_sort.size(); i+=4) {
		Movie *type = new Movie(stoi(f_sort[i]), f_sort[i+1], f_sort[i+2], stoi(f_sort[i+3]));
		f.push_back(*type);
	}
}

//---------------------- display --------------------
void F::display() {

	cout << "---------- Comedy ----------" << endl;
	
	for (int i = 0; i < f.size(); i++) {
		//------------------------------- Display movie info. ---------------------------------
		cout << i+1 << ". " << f[i].title << endl;
		
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ In stock: " << f[i].stock << endl;
		
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ Director: " << f[i].dir << endl;
		
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ Released Date: " << f[i].year << endl << endl;
		//--------------------------------------------------------------------------------------
	}
	cout << endl;
}

//---------------------- getIndex --------------------
int F::getIndex(string title, int year) {
	for(int i = 0; i < f.size(); i++) {
		if (f[i].title == title && f[i].year == year) {
			return i;
		}
	}
	return -1;
}

//---------------------- setStock --------------------
void F::setStock(string title, int year, string rentType) {
	int pos = getIndex(title, year);
	if (pos != -1) {
		if (rentType == "B") {
			f[pos].stock -= 1;
		} else if (rentType == "R") {
			f[pos].stock += 1;
		}
	}
}














