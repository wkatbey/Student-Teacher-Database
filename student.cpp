#include <iostream>
#include "student.h"
using namespace std;

ostream& operator<<(ostream& osObject, const student& sObj) {

	osObject << sObj.getID() << " "
		<< sObj.getFirstName() << " "
		<< sObj.getLastName() << " "
		<< sObj.getResidence() << " "
		<< sObj.getAge() << " "
		<< sObj.getGraduationYear() << " "
		<< sObj.gpa;


	return osObject;
}

istream& operator >> (istream& isObject, student& sObj) {
	string iden;
	string first;
	string last;
	string residence;
	int a;
	int grad;
	double g;

	isObject >> iden;
	isObject >> first;
	isObject >> last;
	isObject >> residence;
	isObject >> a;
	isObject >> grad;
	isObject >> g;

	sObj.loadInfo(first, last, residence, a, iden, grad, g);

	return isObject;
}

void student::loadInfo(string first, string last,
	string res, int age, string iden, int grad, double g) {
	personType::loadInfo(first, last, res, age);
	setID(iden);
	setGraduationYear(grad);
	setGPA(g);
}

void student::setID(string i) {
	ID = i;
}


void student::setGraduationYear(int gradYear) {
	graduationYear = gradYear;
}


void student::setGPA(double g) {
	gpa = g;
}


void student::setInfo(string i) {
	setID(i);
	cout << "Enter Student " << getID() << " information: " << endl;
	personType::setInfo();

	cout << "Graduation Year: ";
	cin >> graduationYear;
	if (!cin)
		throw graduationYear;

	cout << "Grade Point Average: ";
	cin >> gpa;
	if (!cin)
		throw gpa;

}

void student::manipData() {
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
	else if (attribute == "graduation year") {
		cout << "Enter Graduation Year: ";
		cin >> graduationYear;
		if (!cin)
			throw graduationYear;
	}
	else if (attribute == "gpa") {
		cout << "Enter GPA: ";
		cin >> gpa;
		if (!cin)
			throw gpa;
	}
	else
		cout << "Invalid Attribute: Returning.." << endl;
}


void student::print() const {
	cout << "---------------------------" << endl;
	cout << "Student " << getID() << " information: " << endl;
	personType::print();
	cout << "Graduation Year: " << graduationYear << endl;
	cout << "Grade Point Average: " << gpa << endl;
	printAccount();
	cout << "---------------------------" << endl;
}


string student::getID() const {
	return ID;
}

int student::getGraduationYear() const {
	return graduationYear;
}

double student::getGPA() const {
	return gpa;
}

string student::getFunc(int functionType) {
	if (functionType == 0) {
		return getID();
	}
	else if (functionType == 1) {
		return getLastName();
	}
	//personType::(getFunc);
}

double student::getFuncI(int functionType) {
	if (functionType == 0) {
		return getGraduationYear();
	}
	else if (functionType == 1) {
		return getGPA();
	}
	else if (functionType == 2) {
		return getMainBalance();
	}
	else if (functionType == 3) {
		return getSavingsBalance();
	}
}

student::student(string first, string last,
	string res, int age, string iden, int grad,
	double g) :personType(first, last, res, age) {
	setID(iden);
	setGraduationYear(grad);
	setGPA(g);
}


student::student() {
	//Do nothing
}


void student::destroy() {
	personType::destroy();
	gpa = 0;
	graduationYear = 0;
	delete this;
}