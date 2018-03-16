#include "personType.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void personType::loadInfo(string first, string last, string res,
	int age) {
	setFirstName(first);
	setLastName(last);
	setResidence(res);
	setAge(age);
}

void personType::setFirstName(string first) {
	firstName = first;
}

void personType::setLastName(string last) {
	lastName = last;
}

void personType::setResidence(string address) {
	residence = address;
}

void personType::setAge(int a) {
	age = a;
}

void personType::setInfo() {

	//Enter Student/Teacher Information:
	cout << "First Name: ";
	cin.ignore();
	getline(cin, firstName);

	cout << "Last Name: ";
	getline(cin, lastName);

	cout << "Residence: ";
	getline(cin, residence);

	cout << "Age: ";
	cin >> age;
	if (!cin)
		throw age;


}

string personType::getFirstName() const {
	return firstName;
}
string personType::getLastName() const {
	return lastName;
}
string personType::getResidence() const {
	return residence;
}
int personType::getAge() const {
	return age;
}

void personType::open(string id) {
	account = new bankAccount;
	account->setInfo(id);
}
void personType::close() {
	delete account;
	account = nullptr;
}

void personType::withdrawMain(double amount) {
	account->withdrawMain(amount);
}
void personType::withdrawSavings(double amount) {
	account->withdrawSavings(amount);
}

void personType::depositMain(double amount) {
	account->depositMain(amount);
}
void personType::depositSavings(double amount) {
	account->depositSavings(amount);
}

double personType::getMainBalance() const {
	return account->getMainBalance();
}
double personType::getSavingsBalance() const {
	return account->getSavingsBalance();
}

bool personType::isAccount() const {
	return (account != nullptr);
}

void personType::print() const {
	//cout << "Student " << ID << " information: " << endl;
	//cout << "Teacher " << ID << " information: " << endl;

	cout << "Name: " << firstName << " " << lastName << endl;
	cout << "Residence: " << residence << endl;
	cout << "Age: " << age << endl;

	//student and teacher implementation follow
}

void personType::printAccount() const {
	if (account != nullptr) { //If an account is open
		cout << "Bank Account Standing: " << endl;
		account->printAccount();
	}
}

personType::personType(string first, string last, string res,
	int age) {
	setFirstName(first);
	setLastName(last);
	setResidence(res);
	setAge(age);
}

personType::personType() {
	//do nothing
}

personType::~personType() {
	destroy();
}

void personType::destroy() {
	firstName = "";
	lastName = "";
	residence = "";
	age = 0;
	delete account;
}

bankAccount personType::getBankAccount() const {
	return *account;
}