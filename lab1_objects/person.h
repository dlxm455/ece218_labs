#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
#include <string>

using namespace std;

class Person {
private:
	string name;
public:
	Person(); // default constructor
	void setName(string n) { name = n;} // setter
	string getName() { return name;} //getter
	void print(ostream &);
};

#endif

