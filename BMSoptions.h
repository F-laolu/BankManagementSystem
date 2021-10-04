#include<iostream> //for standard input/output and file processing
#include<fstream> //library function for performing file processing
#include<cctype> //library function for classifying characters
#include<iomanip> //library function for manipulating output

using namespace std; 

class mainacc { //creates a class, data structure declaration
	int accnum; //stores account number 
	char fname[20]; // stores user names
	int dep_cash; //stores amount to be deposited
	char ac_type; //stores account type, that is Savings or Current

public:
	void new_acc(); //function for creating a new account
	void display_acc() const; //function for displaying account
	void amend(); //function for amending account
	void deposit(int); //function for depositing money into account
	void with_draw(int); //function for withdrawing money into account
	void disp_rep() const; //function for displaying all account in tabular report
	int ret_accnum() const; //function for returning account number
	int ret_dep() const; //function for returning balance account
	char ret_acctype() const; //function to return account type
};
//end of classes created


void mainacc::new_acc() { //function for creating new account in mainacc
	cout << "Type account number :";
	while (!(cin >> accnum)) { //validation check to permit only numbers
		cout << "Wrong Input, it has to be numbers: "; //error message displayed
		cin.clear(); //clears input, permit new input
		cin.ignore(123, '\n'); //ignore the wrong input
	}
	cout << "Enter account holder full name : ";
	cin.ignore();
	cin.getline(fname, 20); //reads the unformatted string
	cout << "Enter Account type (C for Current/S for Savings) : ";
	cin >> ac_type; //variable for storing account type
	ac_type = toupper(ac_type); //changes user input to uppercase
	cout << "Enter first amount(>=50 for Savings and >=200 for Current) : ";
	while (!(cin >> dep_cash)) { //validation check to permit only numbers to withdraw
		cout << "Wrong Input, it has to be numbers: ";
		cin.clear(); //clears user input, per,it new input
		cin.ignore(123, '\n'); //ignore input
	}
	cout << "\n\nNew Account has been created....."; //Output message for new account created
}

void mainacc::display_acc() const { //function for displaying account in mainacc
	cout <<"\nAccount Number : " << accnum;
	cout <<"\nName of Account Holder : ";
	cout <<fname;
	cout << "\nAccount Type : " << ac_type;
	cout << "\nAccount Balance is : " << dep_cash;
}

void mainacc::amend() { //function for amending account in mainacc
	cout << "\nAccount Number : " << accnum;
	cout << "\nUpdate the name of account holder : ";
	cin.ignore();
	cin.getline(fname, 20);
	cout << "\nUpdate the Account Type (C/S) : ";
	cin >> ac_type;
	ac_type = toupper(ac_type); //changes the user input from lower case to upper case
	cout << "\nUpdate the Account Balance : ";
	cin >> dep_cash;
}


void mainacc::deposit(int x) { //function for depositing cash
	dep_cash += x;
}

void mainacc::with_draw(int x) { //function for withdrawing cash
	dep_cash -= x;
}

void mainacc::disp_rep() const { //function for displaying all account in tabular form
	cout << accnum << setw(10) << " " << fname << setw(10) << " " << ac_type << setw(5) << dep_cash << endl; 
	//format for displaying all account in tabular form
}

int mainacc::ret_accnum() const {
	return accnum;
}

int mainacc::ret_dep() const {
	return dep_cash;
}

char mainacc::ret_acctype() const {
	return ac_type;
}


void acc_write(); //creating account
void disp_accdet(int); //displaying deleted account
void amend_acc(int); //amending account
void acc_del(int); //deleting account
void disp_allacc(); //display all account
void dep_withd(int, int); //withdrawing/depositing
void begin(); //beging the banking management system menu options