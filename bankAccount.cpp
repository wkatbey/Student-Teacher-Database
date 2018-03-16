#include "bankAccount.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& osObject, const bankAccount& bObj) {
	osObject << bObj.getBankID() << " "
		<< bObj.getMainBalance() << " "
		<< bObj.getSavingsBalance();
	return osObject;
}

istream& operator>>(istream& isObject, bankAccount& bObj) {

	string iden;
	double main;
	double savings;

	isObject >> iden;
	isObject >> main;
	isObject >> savings;

	bObj.loadInfo(iden, main, savings);

	return isObject;
}

void bankAccount::loadInfo(string i, double main, double savings) {
	setBankID(i);
	depositMain(main);
	depositSavings(savings);
}

void bankAccount::setBankID(string i) {
	bankID = i;
}

void bankAccount::setInfo(string i) {
	setBankID(i);
	mainBalance = 0;
	savingsBalance = 0;
}

void bankAccount::withdrawMain(double amount) {
	mainBalance = mainBalance - amount;
}
void bankAccount::withdrawSavings(double amount) {
	savingsBalance = savingsBalance - amount;
}

void bankAccount::depositMain(double amount) {
	mainBalance = mainBalance + amount;
}
void bankAccount::depositSavings(double amount) {
	savingsBalance = savingsBalance + amount;
}

double bankAccount::getMainBalance() const {
	return mainBalance;
}
double bankAccount::getSavingsBalance() const {
	return savingsBalance;
}

string bankAccount::getBankID() const {
	return bankID;
}

void bankAccount::printAccount() const {
	cout << "Bank Information for Bank ID: "
		<< bankID << endl;
	cout << "Main Balance: " << mainBalance << endl;
	cout << "Savings Balance: " << savingsBalance << endl;

}

string bankAccount::getFunc(int f) const {
	if (f == 0)
		return getBankID();
}

bankAccount::bankAccount() {
	mainBalance = 0;
	savingsBalance = 0;
}

