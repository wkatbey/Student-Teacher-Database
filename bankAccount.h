#pragma once
#include <string>
using namespace std;

class bankAccount
{
	friend ostream& operator<<(ostream&, const bankAccount&);
	friend istream& operator>>(istream&, bankAccount&);
public:
	void loadInfo(string, double, double);

	void setBankID(string i);
	void setInfo(string i);

	void withdrawMain(double amount);
	void withdrawSavings(double amount);

	void depositMain(double amount);
	void depositSavings(double amount);

	double getMainBalance() const;
	double getSavingsBalance() const;

	string getBankID() const;

	void printAccount() const;

	string getFunc(int f) const;

	bankAccount();


protected:

	string bankID;
	double mainBalance;
	double savingsBalance;
};

