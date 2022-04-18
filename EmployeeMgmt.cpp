#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/* ******** Employee Management System ********
            by harryse7en, 12/23/2021

   This console application was created for Study.com Course #CS112 */

/* For this assignment, you will write a program that keeps track of employees at a company.
   Three types of users can access the system: Human Resources, Management, and General Employees.
     - A Human Resources user will be able to add, view, search, modify, and delete employees.
     - A Management user can only search and view employees.
	 - A General Employee user can only view his or her own file.
   Employee files will have at least the employee's name and numeric user id.
   1) Your program will implement a management information system.
   2) The minimum requirements of the system are:
         implement a base employee class that will be defined for each employee type or function
		 implement a log-in feature
		 and the login will determine what functions are accessible to the employee
   3) The program will be interactive. At a minimum, a log-in screen and menu screen will be used.
      Input should be validated for correct login credentials.
   4) Functions and classes should be used where appropriate to produce readable, reusable code.
      Library functions and user-defined functions should be used where appropriate. */



// Declare classes and structures
class Employee {

public:
	int	empId;
	string empName;
	string empTitle;
	string empRole;
	string empUser;
	string empPass;
	
	//Constructor
	Employee(int aId, string aName, string aTitle, string aRole, string aUser, string aPass){
		empId = aId;
		empName = aName;
		empTitle = aTitle;
		empRole = aRole;
		empUser = aUser;
		empPass = aPass;
	};
	Employee(){
	};
	
	int doLogin(string aPass) {
		if (aPass == empPass){
			return 1;
		} else {
			return 0;
		}
	};
	
};



// Declare GLOBAL variables
vector<Employee> empList;
string activeUser = "None";
string activeRole = "";
int activeIdx = 0;
int empCount = 0;



// Declare GLOBAL functions
void initDatabase() {
	// In lieu of a database connection, this code initializes the data
	empList.push_back({1, "Harry Stafford", "HR Manager", "HR", "harrys", "1qaz!QAZ"});
	empList.push_back({2, "Michael Toon", "HR Specialist", "HR", "miket", "Plc4035"});
	empList.push_back({3, "Craig McNeil", "General Manager", "Mgmt", "craigm", "FTFE"});
	empList.push_back({4, "David Skeptic", "Assistant Manager", "Mgmt", "daves", "D!ng"});
	empList.push_back({5, "Noah Williams", "Student", "Employee", "noahw", "leaves"});
	empList.push_back({6, "Hannah Williams", "Student", "Employee", "hannahw", "TacoBell"});
	empList.push_back({7, "Jeremy Barger", "Specialist", "Employee", "jeremyb", "ChadSux"});
	empCount = empList.size();
};



int loginPrompt() {

	// Declare variables
	string username, password;

	cout << "Please login to use this system" << endl << "Username: ";
	getline(cin, username);
	cout << "Password: " ;
	getline(cin, password);

	// Search for the entered username and if found, validate password
	for (int i = 0; i < empList.size(); i++) {
		if (username == empList[i].empUser) {
			if (empList[i].doLogin(password) == 1) {
				activeUser = empList[i].empUser;
				activeRole = empList[i].empRole;
				activeIdx = i;
				cout << "User " << activeUser << " logged in successfully as " << activeRole << " role." << endl << endl;
				return 1;
			} else {
				cout << "Invalid credentials!" << endl << endl;
				return 2;
			};
		};
	};
	
	cout << "Unknown username!" << endl << endl;
	return 0;

};



void showMenuHead() {
	cout << "--------  Study.com Employee Management System  --------" << endl;
	cout << "USER:  " << activeUser << "                    ROLE:  " << activeRole << endl << endl;
};



void addEmp() {
	Employee newEmp;
	newEmp.empRole = "";
	cin.ignore();
	cout << "Enter the new employee details below" << endl;
	cout << "Name: ";
	getline(cin, newEmp.empName);
	cout << "Title: ";
	getline(cin, newEmp.empTitle);
	cout << "Role: ";
	getline(cin, newEmp.empRole);
	cout << "Username: ";
	getline(cin, newEmp.empUser);
	cout << "Password: ";
	getline(cin, newEmp.empPass);

	// empCount incremented to create a new, unique ID number for the employee
	empCount++;
	newEmp.empId = empCount;
	
	empList.push_back(newEmp);
	cout << endl << "New employee ID# " << empCount << " added successfully" << endl << endl << endl << endl;
};



void viewAllEmp() {
	cin.ignore();
	cout << "List of all employees" << endl << endl;
	cout << "ID   NAME                     TITLE                    ROLE" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < empList.size(); i++) {
		cout << left << setw(5) << empList[i].empId;
		cout << left << setw(25) << empList[i].empName;
		cout << left << setw(25) << empList[i].empTitle;
		cout << empList[i].empRole << endl;
	};
	cout << "---------------------------------------------------------------------";
	cout << endl << endl << endl << endl;
};



void viewOneEmp() {
	cin.ignore();
	cout << "Here is your employee record:" << endl;
	cout << "ID   NAME                     TITLE                    ROLE          USER" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < empList.size(); i++) {
		if (empList[i].empUser == activeUser) {
			cout << left << setw(5) << empList[i].empId;
			cout << left << setw(25) << empList[i].empName;
			cout << left << setw(25) << empList[i].empTitle;
			cout << left << setw(14) << empList[i].empRole;
			cout << empList[i].empUser << endl;
			break;
		};
	};
	cout << "-------------------------------------------------------------------------------" << endl << endl << endl << endl;
};



void searchEmp() {
	bool isFound = false;
	string keyword;
	cin.ignore();
	cout << "Please enter a keyword to seach:" << endl;
	getline(cin, keyword);
	cout << "Records containing your search keyword:" << endl;
	cout << "ID   NAME                     TITLE                    ROLE" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < empList.size(); i++) {
		if (empList[i].empName.find(keyword) != string::npos || empList[i].empTitle.find(keyword) != string::npos || empList[i].empRole.find(keyword) != string::npos) {
			isFound = true;
			cout << left << setw(5) << empList[i].empId;
			cout << left << setw(25) << empList[i].empName;
			cout << left << setw(25) << empList[i].empTitle;
			cout << empList[i].empRole << endl;
		};
	};
	if (!isFound) {
		cout << "          NO RESULTS FOUND" << endl;
	};
	cout << "---------------------------------------------------------------------" << endl << endl << endl << endl;
};



void editEmp() {
	bool isFound = false;
	int idx = -1;
	string input;
	cin.ignore();
	cout << "Please enter the employee ID# you would like to modify" << endl;
	cout << "(You can find the ID# by viewing all records or performing a search)" << endl;
	getline(cin, input);
	cout << endl << "ID   NAME                     TITLE                    ROLE" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < empList.size(); i++) {
		if (empList[i].empId == atoi(input.c_str())) {
			isFound = true;
			idx = i;
			cout << left << setw(5) << empList[i].empId;
			cout << left << setw(25) << empList[i].empName;
			cout << left << setw(25) << empList[i].empTitle;
			cout << empList[i].empRole << endl;
			cout << "---------------------------------------------------------------------" << endl << endl;

			break;
		};
	};

	if (!isFound) {
		cout << "          ERROR!! Employee ID# " << input << " does not exist" << endl;
		cout << "---------------------------------------------------------------------" << endl << endl << endl << endl;
	} else {
		cout << "Are you sure you want to modify the above record?  Type 'y' to confirm: ";
		getline(cin, input);
		if (input == "y") {
			cout << "Enter the new employee details below.  To retain an old setting, hit Enter" << endl;
			cout << "Name: ";
			getline(cin, input);
			if (input != ""){
				empList[idx].empName = input;
			};
			cout << "Title: ";
			getline(cin, input);
			if (input != ""){
				empList[idx].empTitle = input;
			};
			cout << "Role: ";
			getline(cin, input);
			if (input != ""){
				empList[idx].empRole = input;
			};
			cout << "Username: ";
			getline(cin, input);
			if (input != ""){
				empList[idx].empUser = input;
			};
			cout << "Password: ";
			getline(cin, input);
			if (input != ""){
				empList[idx].empPass = input;
			};
			cout << "Record modified successfully" << endl << endl << endl << endl;
		} else {
			cout << "Record was NOT modified" << endl << endl << endl << endl;
		};
	};
};
	
	

void delEmp() {
	bool isFound = false;
	int idx = -1;
	string input;
	cin.ignore();
	cout << "Please enter the employee ID# you would like to delete" << endl;
	cout << "(You can find the ID# by viewing all records or performing a search)" << endl;
	getline(cin, input);
	cout << endl << "ID   NAME                     TITLE                    ROLE" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < empList.size(); i++) {
		if (empList[i].empId == atoi(input.c_str())) {
			isFound = true;
			idx = i;
			cout << left << setw(5) << empList[i].empId;
			cout << left << setw(25) << empList[i].empName;
			cout << left << setw(25) << empList[i].empTitle;
			cout << empList[i].empRole << endl;
			cout << "---------------------------------------------------------------------" << endl << endl;

			break;
		};
	};

	if (!isFound) {
		cout << "          ERROR!! Employee ID# " << input << " does not exist" << endl;
		cout << "---------------------------------------------------------------------" << endl << endl << endl << endl;
	} else {
		cout << "Are you sure you want to delete the above record?  Type 'y' to confirm: ";
		getline(cin, input);
		if (input == "y" && empList[idx].empUser != activeUser) {
			empList.erase(empList.begin() + idx);
			cout << "Record deleted successfully" << endl << endl << endl << endl;
		} else if (empList[idx].empUser == activeUser) {
			cout << "ERROR!! You cannot delete your own record" << endl;
			cout << "Record was NOT deleted" << endl << endl << endl << endl;
		} else {
			cout << "Record was NOT deleted" << endl << endl << endl << endl;
		};
	};
};



void showHRMenu() {
	int choice;
	showMenuHead();
	
	cout << "Please choose an available option:" << endl;
	cout << "1) ADD a new employee" << endl;
	cout << "2) VIEW all employees" << endl;
	cout << "3) VIEW my employee record" << endl;
	cout << "4) SEARCH for an employee" << endl;
	cout << "5) MODIFY an employee" << endl;
	cout << "6) DELETE an employee" << endl;
	cout << "7) LOGOUT" << endl << endl;
	
	cin >> choice;
	switch (choice) {
		case 1:
			addEmp();
			break;
		case 2:
			viewAllEmp();
			break;
		case 3:
			viewOneEmp();
			break;
		case 4:
			searchEmp();
			break;
		case 5:
			editEmp();
			break;
		case 6:
			delEmp();
			break;
		case 7:
			activeUser = "None";
			activeRole = "";
			break;
		default:
			cout << "Invalid choice" << endl << endl;
		};
};



void showMgmtMenu() {
	int choice;
	showMenuHead();
	
	cout << "Please choose an available option:" << endl;
	cout << "1) VIEW all employees" << endl;
	cout << "2) VIEW my employee record" << endl;
	cout << "3) SEARCH for an employee" << endl;
	cout << "4) LOGOUT" << endl << endl;
	
	cin >> choice;
	switch (choice) {
		case 1:
			viewAllEmp();
			break;
		case 2:
			viewOneEmp();
			break;
		case 3:
			searchEmp();
			break;
		case 4:
			activeUser = "None";
			activeRole = "";
			break;
		default:
			cout << "Invalid choice" << endl << endl;
		};
};



void showEmpMenu() {
	int choice;
	showMenuHead();
	
	cout << "Please choose an available option:" << endl;
	cout << "1) VIEW my employee record" << endl;
	cout << "2) LOGOUT" << endl << endl;
	
	cin >> choice;
	switch (choice) {
		case 1:
			viewOneEmp();
			break;
		case 2:
			activeUser = "None";
			activeRole = "";
			break;
		default:
			cout << "Invalid choice" << endl << endl;
		};
};



// MAIN routine
int main(int argc, char** argv) {
	
	// Initialize the employee database for the assignment
	initDatabase();
	
	while (activeUser == "None") {
		int x = loginPrompt();
	};

	while (activeRole == "HR") {
		showHRMenu();
	};
	
	while (activeRole == "Mgmt") {
		showMgmtMenu();
	};

	while (activeRole != "HR" && activeRole != "Mgmt" && activeRole != "") {
		showEmpMenu();
	};
	
	cout << "USER LOGGED OUT";

	return 1;
}

