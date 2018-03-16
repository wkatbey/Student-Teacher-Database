#pragma once
#include "personType.h"
#include <string>
using namespace std;

class teacher : public personType

{
	friend ostream& operator<<(ostream& osObject, const teacher& tObj);
	friend istream& operator>>(istream& isObject, teacher& tObj);
public:

	void loadInfo(string, string, string, int, string, double, int);

	void setID(string i);
	void setSalary(double amount);
	void setYearsOfEmployment(int years);

	void setInfo(string i);

	string getID() const;
	double getSalary() const;
	int getYearsOfEmployment() const;

	void print() const;
	void manipData();

	teacher();

	string getFunc(int functionType);
	double getFuncI(int functionType);

	void destroy();

private:
	string ID;
	double salary;
	int yearsOfEmployment;
};

