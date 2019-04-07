#include "customer.h"

//------------------- Constructor ------------------
Customer::Customer() {
	customerData = new CustomerData[SIZE];
	for (int i = 0; i < SIZE; i++) {
		customerData[i].key = 0;
		customerData[i].id = 0;
		customerData[i].last_name = "";
		customerData[i].first_name = "";
	}
}

//------------------- Destructor -------------------
Customer::~Customer() {}

//------------------- setCustomer ------------------
void Customer::setCustomer(ifstream &infile) {
	string l, space = " ", s;
	int pos = 0;
	vector<string> customer_vec, customer_sort;
	vector<int> key_vec;
	
	// Read type C data and add to array 
	for(;;) {
		getline(infile, l);
		while ((pos = l.find(space)) != -1) {				
			s = l.substr(0, pos);
			customer_vec.push_back(s);
			l.erase(0, pos + space.length());
		}
		customer_vec.push_back(l);
		if (infile.eof()) break;
	}
	customer_vec.erase(customer_vec.begin() + customer_vec.size() - 1);
	
	int j = 0;
	int minId = stoi(customer_vec[0]);
	string minLastname = customer_vec[1];
	string minFirstname = customer_vec[2];
	int minSize = customer_vec.size(), del;
	
	while (customer_vec.size() > 3) {
		for (int j = 0; j < minSize; j+=3) {
			if (customer_vec[j+1] < minLastname) {
				minId = stoi(customer_vec[j]);
				minLastname = customer_vec[j+1];
				minFirstname = customer_vec[j+2];
			} else if (customer_vec[j+1] == minLastname) {
				if (customer_vec[j+2] < minFirstname) {
					minId = stoi(customer_vec[j]);
					minLastname = customer_vec[j+1];
					minFirstname = customer_vec[j+2];
				}
			}
		}
		for (int j = 0; j < minSize; j+=3) {
			if (stoi(customer_vec[j]) == minId && customer_vec[j+1] == minLastname && customer_vec[j+2] == minFirstname) {
				del = j;
				customer_vec.erase(customer_vec.begin() + del, customer_vec.begin() + del + 3);
				minSize = customer_vec.size();
				break;
			}
		}
		customer_sort.push_back(to_string(minId));
		customer_sort.push_back(minLastname);
		customer_sort.push_back(minFirstname);
		
		minId = stoi(customer_vec[0]);
		minLastname = customer_vec[1];
		minFirstname = customer_vec[2];
	}
	
	for (int i = 0; i < customer_vec.size(); i++) {
		customer_sort.push_back(customer_vec[i]);
	}
	
	char c;
	int sum = 0;
	
	for (int i = 0; i < customer_sort.size(); i+=3) {
		key_vec.push_back(stoi(customer_sort[i]) % SIZE);
	}
	
	for (int i = 0; i < customer_sort.size(); i+=3) {
		customerData[key_vec[j]].key = key_vec[j];
		customerData[key_vec[j]].id = stoi(customer_sort[i]);
		customerData[key_vec[j]].custId.push_back(stoi(customer_sort[i]));
		customerData[key_vec[j]].last_name = customer_sort[i+1];
		customerData[key_vec[j]].custLastN.push_back(customer_sort[i+1]);
		customerData[key_vec[j]].first_name = customer_sort[i+2];
		customerData[key_vec[j]].custFirstN.push_back(customer_sort[i+2]);
		j++;
	}
}

int Customer::retrieveKey(int id) {
	int key = id % SIZE;
	return key;
}

string Customer::find(int id) {
	int key = retrieveKey(id);
	string result;
	for (int i = 0; i < customerData[key].custId.size(); i++) {
		if (customerData[key].custId[i] == id) {
			result = customerData[key].custFirstN[i] + " " + customerData[key].custLastN[i];
			break;
		}
	}
	return result;
}

string Customer::getLastname(int id) {
	int key = retrieveKey(id);
	string result;
	for (int i = 0; i < customerData[key].custId.size(); i++) {
		if (customerData[key].custId[i] == id) {
			result = customerData[key].custLastN[i];
			break;
		}
	}
	return result;
}

string Customer::getFirstname(int id) {
	int key = retrieveKey(id);
	string result;
	for (int i = 0; i < customerData[key].custId.size(); i++) {
		if (customerData[key].custId[i] == id) {
			result = customerData[key].custFirstN[i];
			break;
		}
	}
	return result;
}
// setRent for Comedy
void Customer::setRent(string type, int id, string disc, string title, int year) {
	int cur = -1;
	for (int i = 0; i < rentComedy.size(); i++) {
		if (rentComedy[i].customerId == id) {
			cur = i;
		}
	}
	if (cur != -1) {
		rentComedy[cur].rentType.push_back(type);
		rentComedy[cur].movieTitle.push_back(title);
		rentComedy[cur].movieYear.push_back(year);
	} else {
		RentalData *data = new RentalData(type, id, disc, title, year);
		rentComedy.push_back(*data);
	}
}	
// setRent for Drama
void Customer::setRent(string type, int id, string disc, string dir, string title) {
	int cur = -1;
	for (int i = 0; i < rentDrama.size(); i++) {
		if (rentDrama[i].customerId == id) {
			cur = i;
		}
	}
	if (cur != -1) {
		rentDrama[cur].rentType.push_back(type);
		rentDrama[cur].movieDir.push_back(dir);
		rentDrama[cur].movieTitle.push_back(title);
	} else {
		RentalData *data = new RentalData(type, id, disc, dir, title);
		rentDrama.push_back(*data);
	}
}

void Customer::setRent(string type, int id, string disc, string title, int month, int year, string actor) {
	int cur = -1;
	for (int i = 0; i < rentClassic.size(); i++) {
		if (rentClassic[i].customerId == id) {
			cur = i;
		}
	}
	if (cur != -1) {
		rentClassic[cur].rentType.push_back(type);
		rentClassic[cur].movieTitle.push_back(title);
		rentClassic[cur].movieMonth.push_back(month);
		rentClassic[cur].movieYear.push_back(year);
		rentClassic[cur].movieActor.push_back(actor);
	} else {
		RentalData *data = new RentalData(type, id, disc, title, month, year, actor);
		rentClassic.push_back(*data);
	}
}

void Customer::display(int id) {
	cout << "-------------------- CUSTOMER TRANSACTION ------------------" << endl << endl;
	string custName = find(id);
	
	int keyF = -1;
	for (int i = 0; i < rentComedy.size(); i++) {
		if (rentComedy[i].customerId == id) {
			keyF = i;
			break;
		}
	}
	
	int keyD = -1;
	for (int i = 0; i < rentDrama.size(); i++) {
		if (rentDrama[i].customerId == id) {
			keyD = i;
			break;
		}
	}
	
	int keyC = -1;
	for (int i = 0; i < rentClassic.size(); i++) {
		if (rentClassic[i].customerId == id) {
			keyC = i;
			break;
		}
	}
	
	if (rentComedy.size() > 0 || rentDrama.size() > 0 || rentClassic.size() > 0) {
		cout << id << "     | " << custName << endl;
		if (rentComedy.size() > 0) {
			if (keyF != -1) {
				if (rentComedy[keyF].disc == "D") {
					for (int i = 0; i < rentComedy[keyF].rentType.size(); i++) {
						if (rentComedy[keyF].rentType[i] == "B") {
							cout << "Borrowed" << " | " << rentComedy[keyF].movieTitle[i] << " (Type: Comedy)" << endl;
						} else if (rentComedy[keyF].rentType[i] == "R") {
							cout << "Returned" << " | " << rentComedy[keyF].movieTitle[i] << " (Type: Comedy)" << endl;
						}
					}
				} else {
					
				}
			}
		}
		if (rentDrama.size() > 0) {
			if (keyD != -1) {
				if (rentDrama[keyD].disc == "D") {
					for (int i = 0; i < rentDrama[keyD].rentType.size(); i++) {
						if (rentDrama[keyD].rentType[i] == "B") {
							cout << "Borrowed" << " | " << rentDrama[keyD].movieTitle[i] << " (Type: Drama)" << endl;
						} else if (rentComedy[keyD].rentType[i] == "R") {
							cout << "Returned" << " | " << rentDrama[keyD].movieTitle[i] << " (Type: Drama)" << endl;
						}
					}
				} else {
					
				}
			}
		}
		if (rentClassic.size() > 0) {
			if (keyC != -1) {
				if (rentClassic[keyC].disc == "D") {
					for (int i = 0; i < rentClassic[keyC].rentType.size(); i++) {
						if (rentClassic[keyC].rentType[i] == "B") {
							cout << "Borrowed" << " | " << rentClassic[keyC].movieTitle[i] << " (Type: Classic)" << endl;
						} else if (rentClassic[keyC].rentType[i] == "R") {
							cout << "Returned" << " | " << rentClassic[keyC].movieTitle[i] << " (Type: Classic)" << endl;
						}
					}
				} else {
					
				}
			}
		}
		cout << endl;
	} else {
		cout << id << "     | " << custName << endl;
		cout << "No transactions found" << endl << endl;
	}
}

