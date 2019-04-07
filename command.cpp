#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cmovie.h"
#include "fmovie.h"
#include "dmovie.h"
#include "movie.h"
#include "customer.h"
#include "custdata.h"
#include "rentaldata.h"

void setRequest(ifstream &);
void setComedyTrans(F*, Customer*, vector<string>);
void setDramaTrans(D*, Customer*, vector<string>);
void setClassicTrans(C*, Customer*, vector<string>);
void setRentalMovie(vector<string>);
vector<string> type, rent, rentF, rentD, rentC;
	
int main() {
	
	// Display not found movies 
	ifstream moviefile1("data4movies.txt");
	if (!moviefile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	Movie store;
	store.setMovie(moviefile1);
	
	// Input movie for comedy, drama, and classic
	moviefile1.clear();
	ifstream moviefile2("data4movies.txt");
	if (!moviefile2) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	//Movie *comedy = new F;
	F* comedy = new F;
	comedy->setMovie(moviefile2);
	
	moviefile1.clear();
	ifstream moviefile3("data4movies.txt");
	if (!moviefile3) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	D* drama = new D;
	drama->setMovie(moviefile3);
	
	moviefile1.clear();
	ifstream moviefile4("data4movies.txt");
	if (!moviefile4) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	C* classic = new C;
	classic->setMovie(moviefile4);
	
	// Input customer
	ifstream customerfile("data4customers.txt");
	if (!customerfile) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	
	Customer* customer = new Customer;
	customer->setCustomer(customerfile);
	
	// Request 
	ifstream requestedfile("data4commands.txt");
	if (!requestedfile) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	setRequest(requestedfile);
	
	for (int i = 0; i < type.size(); i++) {
		if (type[i] == "I") {
			store.display();
			store.displayInvalid();
			// Display inventory
			comedy->display();
			drama->display();
			classic->display();
		} else if (type[i] == "H") {
			customer->display(stoi(type[i+1]));
		} else if ((type[i] != "H" || type[i] != "I") && type[i].length() <= 1) {
			if (type[i+1] == "I" || type[i+1] == "H") {
				setRentalMovie(rent);
				setComedyTrans(comedy, customer, rentF);
				setDramaTrans(drama, customer, rentD);
				setClassicTrans(classic, customer, rentC);
			}
		}
	}
}

void setRequest(ifstream &infile) {
	string l, space = " ", s, id;
	int pos = 0;
	
	// Read type C data and add to array 
	for(;;) {
		getline(infile, l);
		id = l[0];
		type.push_back(id);
		while ((pos = l.find(space)) != -1) {				
			s = l.substr(0, pos);
			if (id == "B" || id == "R") {
				rent.push_back(s);
			}
			l.erase(0, pos + space.length());
		}
		if (id == "H") {
			type.push_back(l);
		} else if (id == "B" || id == "R") {
			if (l[l.length()-2] == ',') {
				s = l.substr(0, l.length() - 2);
				rent.push_back(s);
			} else {
				rent.push_back(l);
			}
		}
		if (infile.eof()) break;
	}
	type.erase(type.begin() + type.size() - 1);
}

void setRentalMovie(vector<string> rent) {
	for (int i = 0; i < rent.size(); i++) {
		if (rent[i+3] == "F") {
			rentF.push_back(rent[i]);
			rentF.push_back(rent[i+1]);
			rentF.push_back(rent[i+2]);
			int temp = i+4;
			string result = "";
			while (rent[temp][rent[temp].length()-1] != ',') {
				result += rent[temp] + " ";
				temp++;
			}
			if (rent[temp][rent[temp].length()-1] == ',') {
				rent[temp] = rent[temp].substr(0, rent[temp].length()-1);
			}
			result += rent[temp];
			rent[i+4] = result;
			rent.erase(rent.begin() + i + 4 + 1, rent.begin() + 1 + temp);
			rentF.push_back(result);
			rentF.push_back(rent[i+5]);
		} else if (rent[i+3] == "D") {
			if (rent[i+4] == "D") {
				i = i + 1;
				rentD.push_back(rent[i]);
				rentD.push_back(rent[i+1]);
				rentD.push_back(rent[i+2]);
				int temp = i+4;
				string result = "";
				while (rent[temp][rent[temp].length()-1] != ',') {
					result += rent[temp] + " ";
					temp++;
				}
				if (rent[temp][rent[temp].length()-1] == ',') {
					rent[temp] = rent[temp].substr(0, rent[temp].length()-1);
				}
				result += rent[temp];
				rent[i+4] = result;
				rent.erase(rent.begin() + i + 4 + 1, rent.begin() + 1 + temp);
				rentD.push_back(result);
				temp = i+5;
				result = rent[i+5];
				if (temp + 1 < rent.size() - 1) {
					while (rent[temp + 1].length() > 1) {
						result += " " + rent[temp+1];
						temp++;
					}
					rent.erase(rent.begin() + i + 5 + 1, rent.begin() + 1 + temp);
				} else if (temp + 1 == rent.size() - 1) {
					result += " " + rent[temp+1];
					rent.erase(rent.begin() + i + 5 + 1);
				}
				rent[i+5] = result;
				rentD.push_back(result);
			}
		} else if (rent[i+3] == "C") {
			rentC.push_back(rent[i]);
			rentC.push_back(rent[i+1]);
			rentC.push_back(rent[i+2]);
			rentC.push_back(rent[i+4]);
			rentC.push_back(rent[i+5]);
			int temp = i+6;
			string result = rent[i+6];
			if (temp + 1 < rent.size() - 1) {
				while (rent[temp + 1].length() > 1) {
					result += " " + rent[temp+1];
					temp++;
				}
				rent.erase(rent.begin() + i + 6 + 1, rent.begin() + 1 + temp);
			} else if (temp + 1 == rent.size() - 1) {
				result += " " + rent[temp+1];
				rent.erase(rent.begin() + i + 6 + 1);
			}
			rent[i+6] = result;
			rentC.push_back(result);
		}
	}
}

void setComedyTrans(F* comedy, Customer* customer, vector<string> rentF) {
	for (int i = 0; i < rentF.size(); i+=5) {
		int moviePos = comedy->getIndex(rentF[i+3], stoi(rentF[i+4]));
		if (moviePos != -1) {
			customer->setRent(rentF[i], stoi(rentF[i+1]), rentF[i+2], rentF[i+3], stoi(rentF[i+4]));
			comedy->setStock(rentF[i+3], stoi(rentF[i+4]), rentF[i]);
		} else {
			cout << rentF[i+3] << " (Released Year: " << stoi(rentF[i+4]) << ") can not be found" << endl << endl;
		}
	}
}

void setDramaTrans(D* drama, Customer* customer, vector<string> rentD) {
	for (int i = 0; i < rentD.size(); i+=5) {
		int moviePos = drama->getIndex(rentD[i+3], rentD[i+4]);
		if (moviePos != -1) {
			customer->setRent(rentD[i], stoi(rentD[i+1]), rentD[i+2], rentD[i+3], rentD[i+4]);
			drama->setStock(rentD[i+3], rentD[i+4], rentD[i]);
		} else {
			cout << rentD[i+4] << " (Director: " << rentD[i+3] << ") can not be found" << endl << endl;
		}
	}
}

void setClassicTrans(C* classic, Customer* customer, vector<string> rentC) {
	for (int i = 0; i < rentC.size(); i+=6) {
		string title = classic->getTitle(stoi(rentC[i+3]), stoi(rentC[i+4]), rentC[i+5]);
		if (title != "") {
			customer->setRent(rentC[i], stoi(rentC[i+1]), rentC[i+2], title, stoi(rentC[i+3]), stoi(rentC[i+4]), rentC[i+5]);
			classic->setStock(stoi(rentC[i+3]), stoi(rentC[i+4]), rentC[i+5], rentC[i]);
		} else {
			cout << "Movie (Actor: " << rentC[i+5] << ") can not be found" << endl;
		}
	}
}








