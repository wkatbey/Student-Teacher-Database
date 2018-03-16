#include "personType.h"
#include "student.h"
#include "teacher.h"
#include "bankAccount.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void instructionMenu();
void primaryMenu();
void accountMenu();
void studentMenu();
void teacherMenu();


void personTypeSelect();
void bankMenu();

template <class Type>
void bubbleSort(vector<Type>& list, int length, int f);

template <class Type>
void bubbleSortInt(vector<Type>& list, int length, int f);

template <class Type>
int seqSearch(vector<Type>& list, int length, string searchItem, int f);

int largest(vector<bankAccount>& list, int length);

bool isEmpty(ifstream& inputFile);

template <class Type>
int seqSearch(vector<Type>& list, int length, string searchItem);

int main() {
	//Menu Variables
	int pMenuOption; //primary menu 
	int sMenuOption; //student administration menu
	int tMenuOption; //teacher administration menu
	int bMenuOption; //account menu option
	int genericOption; //generic menu option

					   //Indexing variables
	unsigned long personIndex; //for iterating and searching
	unsigned long person1Index; //for iterating and searching
	unsigned long j; //For iterating and searching
	unsigned long k; //For iterating and searching
	bool isStudent; //Differentiate between student and teacher
	int c = 8;

	//Identification - First character
	char studID = 's';
	char teachID = 't';
	char bankID = 'b';

	//Identification - Suffix
	string identity;
	string bankIdentity;

	//Variables for input
	double amount;


	//Student and Teacher vectors
	vector<student> studentList(0);
	vector<teacher> teacherList(0);
	vector<bankAccount> bankList(0);

	//Temporary objects to be pushed
	//into teacherList and studentList
	student *tempStudent;
	teacher *tempTeacher;
	bankAccount *tempAccount;

	//File input and output variables
	ifstream readStudent;
	ifstream readTeacher;
	ofstream writeStudent;
	ofstream writeTeacher;
	ifstream readBank;
	ofstream writeBank;

	readStudent.open("student.txt");

	while (!readStudent.eof() && !isEmpty(readStudent)) {
		tempStudent = new student;
		readStudent >> *tempStudent;
		studentList.push_back(*tempStudent);
	}
	readStudent.close();

	readBank.open("bankAccount.txt");
	while (!readBank.eof() && !isEmpty(readBank)) {
		tempAccount = new bankAccount;
		readBank >> *tempAccount;
		bankList.push_back(*tempAccount);
	}
	readBank.close();

	readTeacher.open("teacher.txt");

	while (!readTeacher.eof() && !isEmpty(readTeacher)) {
		tempTeacher = new teacher;
		readTeacher >> *tempTeacher;
		teacherList.push_back(*tempTeacher);
	}

	readTeacher.close();


	try {
		//Primary menu
		instructionMenu();
		primaryMenu();
		cin >> pMenuOption;
		if (!cin)
			throw pMenuOption;
		while (pMenuOption != 4) {
			switch (pMenuOption) {
			case 1:

				
				
				personTypeSelect();
				cin >> genericOption;
				
				if (!cin) {
					cout << "Incorrect menu option. Returning to primary menu" << endl;
					break;
				}
				
				//Register for an account with a person ID
				if (genericOption == 1) {
					cout << "Open an account.." << endl;
					cout << "Enter the ID of the person: ";
					cin.ignore();
					getline(cin, identity);

					//Check if identity exists
					personIndex = seqSearch(studentList, studentList.size(), identity, 0);
					person1Index = seqSearch(teacherList, teacherList.size(), identity, 0);
					
					//Creating new bank ID
					bankIdentity = bankID + identity;

					if (identity >= "s0" && identity < "t0") {

						if (personIndex == -1) {
							cout << "Person ID was not found" << endl;
							break;
						}
						else if (studentList[personIndex].isAccount()) {
							cout << "An Account with this ID already exists. Login"
								<< endl;
							break;
						}
						studentList[personIndex].open(bankIdentity);
						bankList.push_back(studentList[personIndex].getBankAccount());
					}
					else if (identity >= "t0" && identity <= "u0") {
						if (person1Index == -1) {
							cout << "Person ID was not found" << endl;
							break;
						}
						else if (teacherList[person1Index].isAccount()) {
							cout << "An Account with this ID already exists. Login"
								<< endl;
							break;
						}
						teacherList[person1Index].open(bankIdentity);
						bankList.push_back(teacherList[person1Index].getBankAccount());
					}
					else
						throw("Incorrect Identity"); 


					//Set the index of bankList for the session
					j = seqSearch(bankList, bankList.size(), bankIdentity, 0);
					cout << "Created new bank account with ID: " << bankList[j].getBankID() << endl;
				}
				//Login to an existing account
				else if (genericOption == 2) {
					cout << "Login to an account.." << endl;
					cout << "Enter your bank ID: ";
					cin >> identity;
					j = seqSearch(bankList, bankList.size(), identity);
					if (j != -1) {
						cout << "Logged into bank account with ID: " << bankList[j].getBankID()
							<< endl;
					}
					else {
						cout << "No such bank ID exists, returning to primary menu" << endl;
						break;
					}
				}
				else 
					throw("Invlalid input, input is in fail state");

				accountMenu(); //Display account menu
				cin >> bMenuOption;
				if (!cin)
					throw bMenuOption;

				while (bMenuOption != 7) {
					switch (bMenuOption) {
					case 1:
						cout << "------------------------------------------" << endl;
						cout << "Displaying current account.." << endl;
						bankList[j].printAccount();
						cout << "------------------------------------------" << endl;
						break; //end case 1 - account menu
					case 2:
						cout << "------------------------------------------" << endl;
						cout << "Closing Account - You can no longer login with "
							<< bankList[j].getBankID() << endl;
						bankList.erase(bankList.begin() + j);
						cout << "Account closed, returning to primary menu" << endl;
						cout << "------------------------------------------" << endl;
						while (true) 
							break;
						
						break; //end case 2 - account menu
					case 3: //Withdraw from Account
						bankMenu();
						cin >> genericOption;
						cout << "Enter Amount to Withdraw: ";
						cin >> amount;
						if (!cin)
							throw string("input stream in fail state");

						if (amount < 0)
							amount = -1 * amount;

						if (bankList[j].getMainBalance() - amount >= 0) {
							if (genericOption == 1) {
								bankList[j].withdrawMain(amount);
								cout << "------------------------------------------" << endl;
								cout << "Withdrew " << amount << " from main balance" << endl;
								cout << "------------------------------------------" << endl;
							}
							else if (genericOption == 2) {
								bankList[j].withdrawSavings(amount);
								cout << "------------------------------------------" << endl;
								cout << "Withdrew " << amount << " from savings balance" << endl;
								cout << "------------------------------------------" << endl;
							}
							else
								throw genericOption;
						}
						else
							cout << "Cannot overdraft.." << endl;

						break; //end case 3 - account menu
					case 4: //Deposit to account
						bankMenu();
						cin >> genericOption;
						cout << "Enter Amount to Deposit: ";
						cin >> amount;
						if (!cin)
							throw string("input stream in fail state");

						if (amount < 0)
							amount = -1 * amount;

						if (genericOption == 1) {
							bankList[j].depositMain(amount);
							cout << "------------------------------------------" << endl;
							cout << "Deposited " << amount << " from main balance" << endl;
							cout << "------------------------------------------" << endl;
						}
						else if (genericOption == 2) {
							bankList[j].depositSavings(amount);
							cout << "------------------------------------------" << endl;
							cout << "Deposited " << amount << " from savings balance" << endl;
							cout << "------------------------------------------" << endl;
						}
						else
							throw genericOption;
						break; //end case 4
					case 5:
						if (bankList.empty())
							throw string("Cannot display bank database. There are no accounts");
						cout << "------------------------------------------" << endl;
						personIndex = largest(bankList, bankList.size());
						cout << "Person with largest main balance: " << endl;
						bankList[personIndex].printAccount();
						cout << "------------------------------------------" << endl;

						break; //end case 5
					case 6:
						if (bankList.empty())
							throw string("Cannot display bank database. There are no accounts");

						for (k = 0; k < bankList.size(); k++) {
							cout << "------------------------------------------" << endl;
							bankList[k].printAccount();
							cout << "------------------------------------------" << endl;
						}
						break; //end case 6
					} //end switch bMenuOption
					accountMenu();
					cin >> bMenuOption;
					if (!cin)
						throw bMenuOption;
				} //end while
				

				writeBank.open("bankAccount.txt");
				for (j = 0; j < bankList.size(); j++)
					writeBank << bankList[j];
			
				writeBank.close();
				
				break; //end case 1
			case 2:
				
				
                //student administration Menu
				studentMenu();
				cin >> sMenuOption;
				if (!cin)
					throw sMenuOption;

				while (sMenuOption != 9) {
					switch (sMenuOption) {
					case 1:
						

						//Assigning an ID to student with char 's' and integer
						identity = studID + to_string(studentList.size());
						tempStudent = new student;
						tempStudent->setInfo(identity);

						//Adding this student to the vector studentList
						studentList.push_back(*tempStudent);

						break; //end case 1 - student administrator menu
					case 2:
						if (!studentList.empty()) {
							bubbleSort(studentList, studentList.size(), 0);
							cout << "Printing all student records.." << endl << endl;
							for (j = 0; j < studentList.size(); j++)
								studentList[j].print();
						}
						else
							cout << "Student database is empty.." << endl;
						break; //end case 2 - student administrator menu
					case 3:
						if (!studentList.empty()) {
							cout << "Printing all student records by last name.." << endl;
							cout << "-------------------------------------------" << endl;
							bubbleSort(studentList, studentList.size(), 1);
							for (j = 0; j < studentList.size(); j++)
								studentList[j].print();
							cout << "-------------------------------------------" << endl;
						}
						else
							cout << "Student database is empty.." << endl;
						break; //end case 3 - student administrator menu
					case 4:
						if (!studentList.empty()) {
							cout << "Printing all student records by graduation year.." << endl;
							cout << "-------------------------------------------" << endl;
							bubbleSortInt(studentList, studentList.size(), 0);
							for (j = 0; j < studentList.size(); j++)
								studentList[j].print();
							cout << "-------------------------------------------" << endl;
						}
						else
							cout << "Student database is empty.." << endl;
						break; //end case 4 - student administrator menu
					case 5:
						if (!studentList.empty()) {
							cout << "Printing all student records by GPA.." << endl;
							cout << "-------------------------------------------" << endl;
							bubbleSortInt(studentList, studentList.size(), 1);
							for (j = 0; j < studentList.size(); j++)
								studentList[j].print();
							cout << "-------------------------------------------" << endl;
						}
						else
							cout << "Student database is empty.." << endl;
						break; //end case 5 - student administrator menu
					case 6:
						cout << "Enter Student ID: ";
						cin >> identity;

						j = seqSearch(studentList, studentList.size(), identity, 0);
						if (j != -1)
							studentList[j].print();
						else
							cout << "Student identity does not exist.." << endl;
						break; //end case 6 - student administrator menu
					case 7:
						cout << "Enter Student ID: ";
						cin >> identity;
						j = seqSearch(studentList, studentList.size(), identity, 0);
						if (j != -1)
							studentList[j].manipData();
						else
							cout << "Student identity does not exist.." << endl;
						break; //end case 7 - student administrator menu
					case 8:
						cout << "Enter Student ID: ";
						cin >> identity;
						j = seqSearch(studentList, studentList.size(), identity, 0);
						if (j != -1) {
							cout << "-------------------------------------------" << endl;
							cout << "Deleting student with ID: " << studentList[j].getID()
								<< endl;
							bankIdentity = bankID + studentList[j].getID();
							if (studentList[j].isAccount()) {
								personIndex = seqSearch(bankList, bankList.size(), bankIdentity);
								bankList.erase(bankList.begin() + personIndex);
							}
							studentList.erase(studentList.begin() + j);
							

							cout << "-------------------------------------------" << endl;
						}
						else
							cout << "Student identity does not exist.." << endl;
						break;
					} //end sMenuOption switch 
					studentMenu();
					cin >> sMenuOption;
					if (!cin)
						throw sMenuOption;
				} //end while
				 
                writeStudent.open("student.txt");
				for (j = 0; j < studentList.size(); j++) 
					writeStudent << studentList[j];
				
				writeStudent.close();


				break; //end case 2
			case 3:
				
				//teacher administration Menu
				teacherMenu();
				cin >> tMenuOption;
				if (!cin)
					throw tMenuOption;

				while (tMenuOption != 9) {
					switch (tMenuOption) {
					case 1:
						

						//Assinging an teacher ID beginning with char 't' 
						//followed integer
						identity = teachID + to_string(teacherList.size());
						tempTeacher = new teacher;
						tempTeacher->setInfo(identity);
						
						//Adding this teacher to the vector teacherList
						teacherList.push_back(*tempTeacher);
						
						break; //end case 1 - teacher administrator menu
					case 2:
						if (!teacherList.empty()) {
							bubbleSort(teacherList, teacherList.size(), 0);
							cout << "Printing all teacher records.." << endl << endl;
							for (j = 0; j < teacherList.size(); j++)
								teacherList[j].print();
						}
						else
							cout << "Teacher database is empty.." << endl;
						break; //end case 2 - teacher administrator menu
					case 3:
						if (!teacherList.empty()) {
							cout << "Printing all teacher records by last name.." << endl;
							cout << "-------------------------------------------" << endl;
							bubbleSort(teacherList, teacherList.size(), 1);
							for (j = 0; j < teacherList.size(); j++)
								teacherList[j].print();
							cout << "-------------------------------------------" << endl;
						}
						else
							cout << "Teacher database is empty.." << endl;
						break; //end case 3 - teacher administrator menu
					case 4:
						if (!teacherList.empty()) {
							cout << "Printing all teacher records by years of employment.." << endl;
							cout << "-------------------------------------------" << endl;
							bubbleSortInt(teacherList, teacherList.size(), 0);
							for (j = 0; j < teacherList.size(); j++)
								teacherList[j].print();
							cout << "-------------------------------------------" << endl;
						}
						else
							cout << "Teacher database is empty.." << endl;
						break; //end case 4 - teacher administrator menu
					case 5:
						if (!teacherList.empty()) {
							cout << "Printing all teacher records by salary.." << endl;
							cout << "-------------------------------------------" << endl;
							bubbleSortInt(teacherList, teacherList.size(), 1);
							for (j = 0; j < teacherList.size(); j++)
								teacherList[j].print();
							cout << "-------------------------------------------" << endl;
						}
						else
							cout << "Teacher database is empty.." << endl;
						break; //end case 5 - teacher administrator menu
					case 6:
						cout << "Enter Teacher ID: ";
						cin >> identity;
						j = seqSearch(teacherList, teacherList.size(), identity, 0);
						if (j != -1)
							teacherList[j].print();
						else
							cout << "Teacher identity does not exist.." << endl;
						break; //end case 6 - teacher student administrator
					case 7:
						cout << "Enter Teacher ID: ";
						cin >> identity;
						j = seqSearch(teacherList, teacherList.size(), identity, 0);
						if (j != -1)
							teacherList[j].manipData();
						else
							cout << "Teacher identity does not exist.." << endl;
						break; //end case 7 - teacher administrator
					case 8:
						cout << "Enter Teacher ID: ";
						cin >> identity;
						cout << "------------------------------------------" << endl;
						j = seqSearch(teacherList, teacherList.size(), identity, 0);
						
						if (j != -1) {
							cout << "Deleting teacher with ID: " << teacherList[j].getID()
								<< endl;
							cout << "------------------------------------------" << endl;
							bankIdentity = bankID + teacherList[j].getID();
							if (teacherList[j].isAccount()) {
								personIndex = seqSearch(bankList, bankList.size(), bankIdentity);
								bankList.erase(bankList.begin() + personIndex);
							}
							teacherList.erase(teacherList.begin() + j);
							
							
							
							
							cout << "------------------------------------------" << endl;
						}
							
						else
							cout << "Teacher identity does not exist.." << endl;
						
						break;

					} //end tMenuOption switch 
					teacherMenu();
					cin >> tMenuOption;
					if (!cin)
						throw tMenuOption;
				} //end while

				writeTeacher.open("teacher.txt");
				for (j = 0; j < teacherList.size(); j++) 
					writeTeacher << teacherList[j];
				
				writeTeacher.close();

				break;
			} //end pMenuOption switch 
			primaryMenu();
			cin >> pMenuOption;
			if (!cin)
				throw pMenuOption;
		} //end primaryMenu while
	} //end try block

	catch (string message) {
		cout << "Error: " << message << endl;
	}
	catch (unsigned long j) {
		cout << "Error: " << "index not found" << endl;
	}
	catch (...) {
		cout << "Error..caught in main" << endl;
	}

	system("pause");
	return(0);

}

void instructionMenu() {
	cout << "Welcome to Wassim's CSC2110 Term Project" << endl;
	cout << "To use the program: " << endl;
	cout << "-Create a person (student/teacher)" << endl;
	cout << "-Create a bank account using your person's ID"
		<< " (e.g. s0 or t0)" << endl;
	cout << endl;
}

void primaryMenu() {
	cout << "-------------------------------------------" << endl;
	cout << "Primary Menu" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "1 - Bank Account Register/Login" << endl;
	cout << "2 - Student Database Administration" << endl;
	cout << "3 - Teacher Database Administration" << endl;
	cout << "4 - Exit Program" << endl;
	cout << "Enter Option: ";
}

void accountMenu() {
	cout << "-------------------------------------------" << endl;
	cout << "Bank Account Menu" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "1 - Display Account" << endl;
	cout << "2 - Close Account" << endl;
	cout << "3 - Withdraw Money" << endl;
	cout << "4 - Deposit Money" << endl;
	cout << "5 - Display Account Holder "
		<< "with Maximum Balance" << endl;
	cout << "6 - Display All Bank Accounts" << endl;
	cout << "7 - Return to Primary Menu" << endl;
	cout << "Enter Option: ";
}


void studentMenu() {
	cout << "-------------------------------------------" << endl;
	cout << "Student Database Administration" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "1 - Create Student Record" << endl;
	cout << "2 - Display All Student Records" << endl;
	cout << "3 - Display All Students by Last Name" << endl;
	cout << "4 - Dispaly All Students by Graduation Year" << endl;
	cout << "5 - Display All Students by GPA" << endl;
	cout << "6 - Display Specific Student Record" << endl;
	cout << "7 - Modify Student Record" << endl;
	cout << "8 - Delete Student Record" << endl;
	cout << "9 - Return to Primary Menu" << endl;
	cout << "Enter an option: ";
}

void teacherMenu() {
	cout << "-------------------------------------------" << endl;
	cout << "Teacher Database Administration" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "1 - Create Teacher Record" << endl;
	cout << "2 - Display All Teacher Records" << endl;
	cout << "3 - Display All Teachers by Last Name" << endl;
	cout << "4 - Dispaly All Teachers by Years of Employment" << endl;
	cout << "5 - Display All Teachers by Income" << endl;
	cout << "6 - Display Specific Teacher Record" << endl;
	cout << "7 - Modify Teacher Record" << endl;
	cout << "8 - Delete Teacher Record" << endl;
	cout << "9 - Return to Primary Menu" << endl;
	cout << "Enter an option: ";
}

void personTypeSelect() {
	cout << "1 - Open/Register an Account" << endl;
	cout << "2 - Login to an Account" << endl;
	cout << "Enter an option: ";
}
void bankMenu() {
	cout << "1 - Main Balance" << endl;
	cout << "2 - Savings Balance" << endl;
	cout << "Enter an option: ";
}

template <class Type>
void bubbleSort(vector<Type>& list, int length, int f) {
	int iteration;
	int index;
	Type temp;
	for (iteration = 1; iteration < length; iteration++) {
		for (index = 0; index < length - iteration; index++) {
			if (list[index].getFunc(f) > list[index + 1].getFunc(f)) {
				temp = list[index];
				list[index] = list[index + 1];
				list[index + 1] = temp;
			}
		}
	}
}

template <class Type>
void bubbleSortInt(vector<Type>& list, int length, int f) {
	int iteration;
	int index;
	Type temp;
	for (iteration = 1; iteration < length; iteration++) {
		for (index = 0; index < length - iteration; index++) {
			if (list[index].getFuncI(f) > list[index + 1].getFuncI(f)) {
				temp = list[index];
				list[index] = list[index + 1];
				list[index + 1] = temp;
			}
		}
	}
}

template <class Type>
int seqSearch(vector<Type>& list, int length, string searchItem, int f) {
	int loc;
	bool found = false;
	loc = 0;

	while (loc < length && !found)
		if (list[loc].getFunc(f) == searchItem)
			found = true;
		else
			loc++;

	if (found)
		return loc;
	else
		return -1;
}

template <class Type>
int seqSearch(vector<Type>& list, int length, string searchItem) {
	int loc;
	bool found = false;
	loc = 0;

	while (loc < length && !found)
		if (list[loc].getBankID() == searchItem)
			found = true;
		else
			loc++;

	if (found)
		return loc;
	else
		return -1;
}


int largest(vector<bankAccount>& list, int length) {
	int max = 0;

	for (int i = 1; i < length; i++) {
		if (list[max].getMainBalance() < list[i].getMainBalance())
			max = i;
	}


	return max;
}


bool isEmpty(ifstream& inputFile)
{
	return inputFile.peek() == ifstream::traits_type::eof();
}





