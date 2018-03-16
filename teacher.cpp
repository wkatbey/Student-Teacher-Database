#include "teacher.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& osObject, const teacher& tObj) {

	osObject << tObj.getID() << " "
		<< tObj.getFirstName() << " " 
		<< tObj.getLastName() << " "
		<< tObj.getResidence() << " "
		<< tObj.getAge() << " "
		<< tObj.yearsOfEmployment << " "
		<< tObj.salary;

	return osObject;
}

istream& operator>>(istream& isObject, teacher& tObj) {
	string iden;
	string first;
	string last;
	string residence;
	int a;
	double sal;
	int years;


	isObject >> iden;
	isObject >> first;
	isObject >> last;
	isObject >> residence;
	isObject >> a;
	isObject >> years;
	isObject >> sal;

	tObj.loadInfo(first, last, residence, a, iden, sal, years);

	return isObject;
}

void teacher::loadInfo(string first, string last,
	string res, int age, string iden, double sal, int years) {
	personType::loadInfo(first, last, res, age);
	setID(iden);
	setSalary(sal);
	setYearsOfEmployment(years);
}

void teacher::setID(string i) {
	ID = i;
}

void teacher::setSalary(double amount) {
	salary = amount;
}

void teacher::setYearsOfEmployment(int years) {
	yearsOfEmployment = years;
}

void teacher::setInfo(string i) {
	setID(i);
	cout << "Enter Teacher " << getID() << " information: " << endl;
	personType::setInfo();

	cout << "Enter Salary: ";
	cin >> salary;
	if (!cin)
		throw salary;

	cout << "Enter Years Of Employment: ";
	cin >> yearsOfEmployment;
	if (!cin)
		throw yearsOfEmployment;


}

string teacher::getID() const {
	return ID;
}
double teacher::getSalary() const {
	return salary;
}

int teacher::getYearsOfEmployment() const {
	return yearsOfEmployment;
}

void teacher::print() const {
	cout << "---------------------------" << endl;
	cout << "Teacher " << getID() << " information: " << endl;
	personType::print();
	cout << "Salary: " << salary << endl;
	cout << "Years of Employment: " << yearsOfEmployment << endl;
	printAccount();
	cout << "---------------------------" << endl;
}

void teacher::manipData() {
	string attribute;
	cout << "What would you like to change (enter attribute): ";
	cin.ignore();
	getline(cin, attribute);

	if (attribute == "name"
		|| attribute == "first name"
		|| attribute == "last name") {

		string first;
		string last;
		cout << "Enter First Name: ";
		getline(cin, first);
		cout << "Enter Last Name: ";
		getline(cin, last);

		setFirstName(first);
		setLastName(last);
	}
	else if (attribute == "residence") {
		string res;
		cout << "Enter Residence: ";
		getline(cin, res);
		setResidence(res);
	}
	else if (attribute == "age") {
		int a;
		cout << "Enter Age: ";
		cin >> a;
		if (!cin)
			throw a;
		setAge(a);
	}
	else if (attribute == "years of employment") {
		cout << "Enter Years of Employment: ";
		cin >> yearsOfEmployment;
		if (!cin)
			throw yearsOfEmployment;
	}
	else if (attribute == "salary") {
		cout << "Enter salary: ";
		cin >> salary;
		if (!cin)
			throw salary;
	}
	else
		cout << "Invalid Attribute: Returning.." << endl;
}

teacher::teacher() {
	//Do nothing
}

string teacher::getFunc(int functionType) {
	if (functionType == 0) {
		return getID();
	}
	else if (functionType == 1) {
		return getLastName();
	}
}

double teacher::getFuncI(int functionType) {
	if (functionType == 0) {
		return yearsOfEmployment;
	}
	else if (functionType == 1) {
		return salary;
	}
	else if (functionType == 2) {
		return getMainBalance();
	}
	else if (functionType == 3) {
		return getSavingsBalance();
	}
}

void teacher::destroy() {
	personType::destroy();
	salary = 0;
	yearsOfEmployment = 0;
	delete this;
}
