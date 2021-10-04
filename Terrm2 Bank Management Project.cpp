// Terrm2 Bank Management Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> //for standard input/output and file processing
#include "Register.h" //header file for register back-end code
#include "BMSoptions.h" //header file for Bank Management menu options

using namespace std; //using everything in standard as cout and cin are used throughout the code


int main() { //calls function 
	char opt; //stores the variable entered for menu options
	int numb; //Stores the account number for various activities in the program
	begin();
	mainlabel://label to take the user to when there is an invalid input in ligin or signup

	int start;
	cout << "Log in to access this system:\n1.Log in\n2.Change login details" << endl;
	while (!(cin >> start)) { //validation check to permit only numbers
		cout << "Wrong Input, it has to be numbers, Press enter to try again. "; //error message displayed
		cin.clear(); //clears input, permit new input
		cin.ignore(123, '\n'); //ignore the wrong input
	}

	switch (start) //case statement, an alternative for if-else statement begins
	{
		case 1:
			login(); //option for login
			break;
		case 2:
			createloginfo(); //option for sign up
			break;
		default:
		{
			cout << "\nInvalid input! Enter again: \n"; //validation check for if a number different from the options is entered
			system("pause");
			goto mainlabel; //takes user back to label
		}

	}


	do { //output all the options given
		system("cls");
		cout << "\n\n\tMENU";
		cout << "\n\n\t01. CREATE NEW ACCOUNT";
		cout << "\n\n\t02. AMOUNT DEPOSIT";
		cout << "\n\n\t03. WITHDRAW FROM ACCOUNT";
		cout << "\n\n\t04. VIEW BALANCE";
		cout << "\n\n\t05. DISPLAY LIST OF ACCOUNT HOLDERS";
		cout << "\n\n\t06. DELETE ACCOUNT";
		cout << "\n\n\t07. AMEND ACCOUNT";
		cout << "\n\n\t08. EXIT SYSTEM";
		cout << "\n\n\tChoose option (1-8)";
		cin >> opt; //saves the users selection
		system("cls");

		switch (opt) { //switch statements for each menu options
		case '1':
			acc_write();
			break;
		case '2':
			cout << "\n\n\tType Account Number : "; cin >> numb;
			dep_withd(numb, 1);
			break;
		case '3':
			cout << "\n\n\tType Account Number : "; cin >> numb;
			dep_withd(numb, 2);
			break;
		case '4':
			cout << "\n\n\tType Account Number : "; cin >> numb;
			disp_accdet(numb);
			break;
		case '5':
			disp_allacc();
			break;
		case '6':
			cout << "\n\n\tType Account Number : "; cin >> numb;
			acc_del(numb);
			break;
		case '7':
			cout << "\n\n\tType Account Number : "; cin >> numb;
			amend_acc(numb);
			break;
		case '8':
			cout << "\n\n\tThank you for using the services provided by the Banking Management System. ";
			break;
		default: cout << "Invalid input!! Please enter options between 1 to 8, Press enter to try again.\n";
		//validation check for when another number out of the menu option is entered
		}
		cin.ignore();
		cin.get();
		
		
	} while (opt != '8'); //when menu option is not 8, returns other values
	return 0;
}

void acc_write() { //function for creating account
	mainacc acc;
	ofstream outFile; //creates a file
	outFile.open("mainaccounts.txt", ios::binary | ios::app); //opens text file mainaccounts.txt and stores as binary
	acc.new_acc();
	outFile.write(reinterpret_cast<char*> (&acc), sizeof(mainacc)); //writes into file: also casting operator used to decrypt pointer from different pointer type
	outFile.close(); // closes the file
}

void disp_accdet(int n){ //function for displaying deleted account
	mainacc acc;
	bool flag = false; //set condition to when its false
	ifstream inFile;
	inFile.open("mainaccounts.txt", ios::binary); //opens mainaccounts.txt
	if (!inFile) {
		cout << "File not found!!! Press any key....."; //output message when file is false, that is, not found
		return;
	}
	cout << "\nBALANCE\n"; 

	while (inFile.read(reinterpret_cast<char*> (&acc), sizeof(mainacc))) { //when file is found
		if (acc.ret_accnum() == n) {
			acc.display_acc(); //displays account details
			flag = true; //condition is true
		}
	}
	inFile.close(); //file is closed
	if (flag == false)
		cout << "\n\nAccount number not found!!"; //output message when detail is wrong or not in file
}

void amend_acc(int n) { //function for amending file
	bool found = false;
	mainacc acc;
	fstream File;
	File.open("mainaccounts.txt", ios::binary | ios::in | ios::out);
	if (!File) {
		cout << "File not found!! Press any key to exit..";
		return;
	}
	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char*> (&acc), sizeof(mainacc));//reads file
		if (acc.ret_accnum() == n) {
			acc.display_acc();
			cout << "\n\nType in the updated Account Details" << endl;
			acc.amend();
			int pos = (-1) * static_cast<int>(sizeof(mainacc));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&acc), sizeof(mainacc));
			cout << "\n\n\tAccount Record is now updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\nAccount Record is not in file";
}

void acc_del(int n) { //function for deleting an account
	mainacc acc;
	ifstream inFile;
	ofstream outFile;
	inFile.open("mainaccounts.txt", ios::binary);
	if (!inFile) {
		cout << "File not seen!! Press any key..";
		return;
	}
	outFile.open("notacc.txt", ios::binary); //new text file for deleted file is opened
	inFile.seekg(0, ios::beg); //used to get file from beginning
	while (inFile.read(reinterpret_cast<char*> (&acc), sizeof(mainacc))) {
		if (acc.ret_accnum() != n) {
			outFile.write(reinterpret_cast<char*> (&acc), sizeof(mainacc));
		}
	}
	inFile.close();
	outFile.close();
	remove("mainaccounts.txt"); 
	rename("notacc.txt","mainaccounts.txt"); //text file for deleted file is renamed
	cout << "\n\n\tThe File has been Deleted..";
}

void disp_allacc() { //function for displaying all account
	mainacc acc;
	ifstream inFile;
	inFile.open("mainaccounts.txt", ios::binary);
	if (!inFile) {
		cout << "File not found!! Press any key...";
		return;
	}
	cout << "\n\n\tLIST OF ACCOUNT HOLDERS\n\n";
	cout << "==============================================\n";
	cout << "Account no.		Name		 Account Type/Balance\n"; //format for displaying all account
	cout << "==============================================\n";
	while (inFile.read(reinterpret_cast<char*> (&acc), sizeof(mainacc))) { //file in binary form is read
		acc.disp_rep();
	}
	inFile.close();
}

void dep_withd(int n, int opt) { //function for depositing and withdrawing cash
	int amount;
	bool found = false;
	mainacc acc;
	fstream File;
	File.open("mainaccounts.txt", ios::binary | ios::in | ios::out);
	if (!File) {
		cout << "File not found!!! Press any key...";
		return;
	}
	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char*> (&acc), sizeof(mainacc)); //reads file to carry out if statements
		if (acc.ret_accnum() == n) {
			acc.display_acc();
			if (opt == 1) {
				cout << "\n\n\tTO PAY IN AMOUNT ";
				cout << "\n\nEnter amount to be paid ";
				cin >> amount;
				acc.deposit(amount);
			}
			if (opt == 2) {
				cout << "\n\n\tTO WITHDRAW ";
				cout << "\n\nEnter the amount you wish to withdraw (Minimum Balance for Savings = 25 and Minimum Balance for Current = 50) ";
				cin >> amount;
				int bal = acc.ret_dep() - amount;
				if ((bal < 25 && acc.ret_acctype() == 'S') || (bal < 50 && acc.ret_acctype() == 'C'))
					//condition for current and savings account limit
					cout << "Not enough balance";
				else
					acc.with_draw(amount);
			}
			int pos = (-1) * static_cast<int>(sizeof(acc));
			File.seekp(pos, ios::cur); //search file 
			File.write(reinterpret_cast<char*> (&acc), sizeof(mainacc)); //writes in file
			cout << "\n\n\t File Record is up to date"; //output message after file record is updated
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n File Record not seen ";
}

void begin() { //function for outputting Bank Management welcome message
	cout << "\n\n\t WELCOME TO THE";
	cout << "\n\n\t	BANKING MANAGEMENT SYSTEM";
	cout << "\n\n\t	CREATED BY: OLAOLUWA FOLORUNSHO";
	cout << "\n\n\t Press enter to access this system";
	cin.get();
}



