#include "dmovie.h"

//------------------- Constructor ------------------
D::D() {}

//------------------- Destructor ------------------
D::~D() {}

void D::setMovie(ifstream &infile) {
	string l, comma = ",", space = " ", s, actor, id;
	int pos = 0;
	bool isD = false;
	vector<string> d_vec, d_sort;
	for(;;) {
		getline(infile, l);
		id = l[0];
		while ((pos = l.find(comma)) != -1) {		
			s = l.substr(0, pos);
			if (id == "D") {
				d_vec.push_back(s);
				isD = true;
			}
			l.erase(0, pos + comma.length() + space.length());
		}
		if (isD) {
			d_vec.push_back(l);
		}
		isD = false;
		if (infile.eof()) break;
	}
	
	int del;
	int minStock = stoi(d_vec[1]);
	string minDir = d_vec[2];
	string minTitle = d_vec[3];
	int minYear = stoi(d_vec[4]);
	int minSize = d_vec.size();

	while (d_vec.size() > 5) {
		for (int i = 1; i < minSize; i+=5) {
			if (d_vec[i+1] < minDir) {
				minStock = stoi(d_vec[i]);
				minDir = d_vec[i+1];
				minTitle = d_vec[i+2];
				minYear = stoi(d_vec[i+3]);
			} else if (d_vec[i+1] == minDir) {
				if (d_vec[i+2] < minTitle) {
					minStock = stoi(d_vec[i]);
					minDir = d_vec[i+1];
					minTitle = d_vec[i+2];
					minYear = stoi(d_vec[i+3]);
				} 
			}
		}
		for (int i = 1; i < minSize; i+=5) {
			if (d_vec[i+1] == minDir && d_vec[i+2] == minTitle) {
				del = i;
				d_vec.erase(d_vec.begin()+ del - 1, d_vec.begin() + del - 1 + 5);
				minSize = d_vec.size();
				break;
			}
		}
		d_sort.push_back(to_string(minStock));
		d_sort.push_back(minDir);
		d_sort.push_back(minTitle);
		d_sort.push_back(to_string(minYear));
		minDir = d_vec[2];	
		minTitle = d_vec[3];	
	}
	// Add last movie to vector f_sort
	for (int i = 1; i < d_vec.size(); i++) {
		d_sort.push_back(d_vec[i]);
	}

	for (int i = 0; i < d_sort.size(); i+=4) {
		Movie *type = new Movie(stoi(d_sort[i]), d_sort[i+1], d_sort[i+2], stoi(d_sort[i+3]));
		d.push_back(*type);
	}
}

//---------------------- display --------------------
void D::display() {
	
	cout << "---------- Drama ----------" << endl;
	
	for (int i = 0; i < d.size(); i++) {
		//------------------------------- Display movie info. ---------------------------------
		cout << i+1 << ". " << d[i].title << endl;
		
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ In stock: " << d[i].stock << endl;
		
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ Director: " << d[i].dir << endl;
		
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ Released Date: " << d[i].year << endl << endl;
		//--------------------------------------------------------------------------------------
	}
	cout << endl;
}
	
//---------------------- getIndex --------------------
int D::getIndex(string dir, string title) {
	for(int i = 0; i < d.size(); i++) {
		if (d[i].dir == dir && d[i].title == title) {
			return i;
		} 
	}
	return -1;
}

//---------------------- setStock --------------------
void D::setStock(string dir, string title, string rentType) {
	int pos = getIndex(dir, title);
	if (pos != -1) {
		if (rentType == "B") {
			d[pos].stock -= 1;
		} else if (rentType == "R") {
			d[pos].stock += 1;
		}
	}
}	
	
	
	
	
	
	