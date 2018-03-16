#include "bankAccount.h"
#include <string>
using namespace std;

#pragma once

class personType
{

public:

	void loadInfo(string, string, string, int);
	//Function to gather information from a .txt file

	void setFirstName(string first);
	//Function to set the first name
	void setLastName(string last);
	//Function to set the last name
	void setResidence(string address);
	//Function to set the residence
	void setAge(int a);
	//Function to set the age

	void setInfo();
	//Function to set all person information

	string getFirstName() const;
	//Function to return firstName
	string getLastName() const;
	//Function to return lastName
	string getResidence() const;
	//Function to return residence
	int getAge() const;
	//Function to return age 

	void destroy();
	//Function to initialize all
	//member variables

	void open(string);
	//Function to open a new bank account
	//allocates new memory for account
	void close();
	//Function to close a bank account
	//deallocates memory for account

	void withdrawMain(double amount);
	//Function to withdraw from main
	//balance
	void withdrawSavings(double amount);
	//Function to withdraw from savings
	//balance
	void depositMain(double amount);
	//Function to deposit to main balance
	void depositSavings(double amount);
	//Function to deposit to savings balance

	double getMainBalance() const;
	//Function to return mainBalance
	double getSavingsBalance() const;
	//Function to return savingsBalance

	bool isAccount() const;
	//Function to return if an account is open
	//Used to check if account is open before
	//depositing or withdrawing in main program

	void print() const;
	//Function to print the person information
	void printAccount() const;
	//Function to print the bank account information

	bankAccount getBankAccount() const;


	virtual string getFunc(int functionType) = 0;
	virtual double getFuncI(int functionType) = 0;
	virtual void setID(string i) = 0;
	virtual string getID() const = 0;

	personType(string first, string last, string res,
		int age);
	//Parameterized constructor

	personType();
	~personType();





protected:

	//unsigned long ID;

	string firstName;
	string lastName;

	string residence;
	int age;

	bankAccount *account;


};

