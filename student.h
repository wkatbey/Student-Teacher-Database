#pragma once
#include "personType.h"

class student : public personType
{
	friend ostream& operator<<(ostream&, const student&);
	friend istream& operator >> (istream&, student&);

public:

	void loadInfo(string, string, string, int,
		string, int, double);

	void setID(string i);
	void setGraduationYear(int gradYear);
	void setGPA(double g);
	void setInfo(string i);
	void manipData();

	void print() const;

	int getGraduationYear() const;
	double getGPA() const;

	string getID() const;
	student(string first, string last,
		string res, int age, string iden, int grad,
		double g);
	student();

	void destroy();
	string getFunc(int functionType);
	double getFuncI(int functionType);

private:
	string ID;
	int graduationYear;
	double gpa;
};


