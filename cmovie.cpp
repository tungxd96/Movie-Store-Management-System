#include "cmovie.h"

//------------------- Constructor ------------------
C::C() {}

//------------------- Destructor -------------------
C::~C() {}

//-------------------- setMovie --------------------
void C::setMovie(ifstream &infile) {

	string l, comma = ",", space = " ", s, actor, id;
	int pos = 0, c_pos = 0, actor_count = 0;
	bool isC = false;
	vector<string> c_vec, c_sort;
	
	// Read type C data and add to array 
	for(;;) {
		getline(infile, l);
		id = l[0];
		while ((pos = l.find(comma)) != -1) {				
			s = l.substr(0, pos);
			if (id == "C") {
				c_vec.push_back(s);
				isC = true;
			}
			l.erase(0, pos + comma.length() + space.length());
		}
		if (isC) {
			while ((c_pos = l.find(space)) != -1) {
				s = l.substr(0, c_pos);
				if(!isNumber(s)) {
					if (actor_count == 0) {
						actor = s;
						actor_count++;
					} else if (actor_count > 0) {
						actor += space + s;
						c_vec.push_back(actor);
					}
				} else {
					c_vec.push_back(s);
				}
				l.erase(0, c_pos + space.length());
			}
			actor_count = 0;
			c_vec.push_back(l);
		}
		isC = false;
		if (infile.eof()) break;
	}
	
	int del;
	int minStock = stoi(c_vec[1]);
	string minDir = c_vec[2];
	string minTitle = c_vec[3];
	string minActor = c_vec[4];
	int minMonth = stoi(c_vec[5]);	
	int minYear = stoi(c_vec[6]);
	int minSize = c_vec.size();
	
	// Sort classic movie based on released date, then major actor
	while (c_vec.size() > 7) {
		for (int i = 1; i < minSize; i+=7) {
			if (stoi(c_vec[i+5]) < minYear) {
				minStock = stoi(c_vec[i]);
				minDir = c_vec[i+1];
				minTitle = c_vec[i+2];
				minActor = c_vec[i+3];
				minMonth = stoi(c_vec[i+4]);
				minYear = stoi(c_vec[i+5]);
			} else if (stoi(c_vec[i+5]) == minYear) {
				if (stoi(c_vec[i+4]) < minMonth) {
					minStock = stoi(c_vec[i]);
					minDir = c_vec[i+1];
					minTitle = c_vec[i+2];
					minActor = c_vec[i+3];
					minMonth = stoi(c_vec[i+4]);
					minYear = stoi(c_vec[i+5]);
				} else if (stoi(c_vec[i+4]) == minMonth) {
					if (c_vec[i+3] < minActor) {
						minStock = stoi(c_vec[i]);
						minDir = c_vec[i+1];
						minTitle = c_vec[i+2];
						minActor = c_vec[i+3];
						minMonth = stoi(c_vec[i+4]);
						minYear = stoi(c_vec[i+5]);
					}
				}
			}
		}
		// Get minimum priority movie, then delete from array
		for (int i = 1; i < minSize; i+=7) {
			if (c_vec[i+3] == minActor && stoi(c_vec[i+4]) == minMonth && stoi(c_vec[i+5]) == minYear) {
				del = i;
				c_vec.erase(c_vec.begin()+ del - 1, c_vec.begin() + del - 1 + 7);
				minSize = c_vec.size();
				break;
			}
		}
		// Add minimum priority movie to new vector c_sort
		c_sort.push_back(to_string(minStock));
		c_sort.push_back(minDir);
		c_sort.push_back(minTitle);
		c_sort.push_back(minActor);
		c_sort.push_back(to_string(minMonth));
		c_sort.push_back(to_string(minYear));
		
		minActor = c_vec[4];
		minMonth = stoi(c_vec[5]);	
		minYear = stoi(c_vec[6]);
	}
	// Add last priority movie to c_sort vector
	for (int i = 1; i < c_vec.size(); i++) {
		c_sort.push_back(c_vec[i]);
	}
	int cur = 0;
	// Add sorted movies into main vector
	for (int i = 0; i < c_sort.size() - 6; i+=6) {
		if (c_sort[i+2] == c_sort[i+8]) {
			Movie *type = new Movie(stoi(c_sort[i]), c_sort[i+1], c_sort[i+2], c_sort[i+3], stoi(c_sort[i+4]), stoi(c_sort[i+5]));
			c.push_back(*type);
			c[cur].sum.push_back(stoi(c_sort[i+6]));
			c[cur].act.push_back(c_sort[i+9]);
			cur++;
			i+=6;
		} else {
											//stock, director, title, actor, month, year
			Movie *type = new Movie(stoi(c_sort[i]), c_sort[i+1], c_sort[i+2], c_sort[i+3], stoi(c_sort[i+4]), stoi(c_sort[i+5]));
			c.push_back(*type);
			cur++;
		}
	}
	for (int i = c_sort.size()-6; i < c_sort.size(); i+=6) {
		Movie *type = new Movie(stoi(c_sort[i]), c_sort[i+1], c_sort[i+2], c_sort[i+3], stoi(c_sort[i+4]), stoi(c_sort[i+5]));
		c.push_back(*type);
	}
}

//---------------------- display --------------------
void C::display() {
	
	int total = 0;
	
	cout << "---------- Classic ----------" << endl;
	
	for (int i = 0; i < c.size(); i++) {
		//------------------------------- Display movie info. ---------------------------------
		// Title
		cout << i+1 << ". " << c[i].title << endl;
		// Stock
		if (c[i].sum.size() > 1) {
			for (int k = 0; k < c[i].sum.size(); k++) {
				total += c[i].sum[k];
			}
		} else {
			total = c[i].sum[0];
		}
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ In stock: " << total << endl;
		
		// Director
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ Director: " << c[i].dir << endl;
		
		// Actor
		if (c[i].act.size() > 1) {
			for (int k = 0; k < c[i].act.size(); k++) {
				for (int j = 0; j < to_string(i+1).length() + 2; j++) {
					cout << " ";
				}
				cout << "+ Actor" << " " << k+1 << ": " << c[i].act[k] << endl;
			}
		} else {
			for (int j = 0; j < to_string(i+1).length() + 2; j++) {
				cout << " ";
			}
			cout << "+ Actor" << ": " << c[i].actor << endl;
		}
		
		// Released Date
		for (int j = 0; j < to_string(i+1).length() + 2; j++) {
			cout << " ";
		}
		cout << "+ Released Date: " << c[i].month << "/" << c[i].year << endl << endl;
		//--------------------------------------------------------------------------------------
		total = 0;
	}
}

//---------------------- getIndex --------------------
int C::getIndex(int month, int year, string actor) {
	for(int i = 0; i < c.size(); i++) {
		for (int j = 0; j < c[i].act.size(); j++) {
			if (c[i].month == month && c[i].year == year && actor.find(c[i].act[j]) != -1) {
				return i;
			}
		}
	}
	return -1;
}

int C::actorIndex(int pos, string actor) {
	for(int i = 0; i < c[pos].act.size(); i++) {
		if (actor.find(c[pos].act[i]) != -1) {
			return i;
		}
	}
	return -1;
}

//---------------------- getTitle --------------------
string C::getTitle(int month, int year, string actor) {
	string title = "";
	for(int i = 0; i < c.size(); i++) {
		for (int j = 0; j < c[i].act.size(); j++) {
			if (c[i].month == month && c[i].year == year && actor.find(c[i].act[j]) != -1) {
				title = c[i].title;
				break;
			}
		}
	}
	return title;
}
//---------------------- setStock --------------------
void C::setStock(int month, int year, string actor, string rentType) {
	int pos = getIndex(month, year, actor);
	int actorPos = actorIndex(pos, actor);
	int total = 0;
	if (pos != -1) {
		if (rentType == "B") {
			for (int k = 0; k < c[pos].sum.size(); k++) {
				total += c[pos].sum[k];
			}
			if (total > 0) { 
				c[pos].sum[actorPos] -= 1;
			} else {
				cout << c[pos].title << ": out of stock" << endl;
				c[pos].sum[actorPos] = 0;
			}
		} else if (rentType == "R") {
			c[pos].sum[actorPos] += 1;
		}
	}
}