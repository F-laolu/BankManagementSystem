#pragma once
#include <cstdlib> //library that defines general purpose function
#include <iostream> //for standard input/output and file processing
#include <string> //inbuilt header that helps define string variable in std namespace
#include <fstream> //library function for performing file processing

using namespace std;

void createloginfo() // Function for storing the login information
{

    string username; //username stored in string
    string password; //password stored in string
    cout << "Please create a username" << endl;
    cin >> username; //username entered is stored
    cout << "Please create a password" << endl;
    cin >> password; //password entered is stored
    ofstream createloginfo;// creates a text file for storing the information
    createloginfo.open("bms.txt"); // Opens the text file created.
    createloginfo << username << " " << password << endl; //Stores the login info
    createloginfo.close(); //Text file is closed 
    cout << "Login info created!" << endl; //output message

}
void login() // Function for when user wants to log in
{
    string username; 
    string password; 
    string username2, password2;
    char choice;


    int attemptCount = 0; // assign initial login attempts

    ifstream loginfo;
    loginfo.open("bms.txt"); // bms.txt will verify user information.

    while (attemptCount < 3) //programs what happens when attemps to login is < 3
    {
        cout << "Enter your username: " << endl;
        cin >> username;
        cout << "Enter your password: " << endl;
        cin >> password;

        loginfo >> username2 >> password2;
        loginfo.close();

        if (username == username2 && password == password2) //compares the login info entered by user to login info stored in bms.txt
        {
            cout << "Access granted"; //permits access to the system if info entered is similar to stored info
            return;
        }

        else
        {
            cout << "Incorrect username/password combination. Please try again." << "\n" << //displays error message when login info is not similar
                endl;

            attemptCount++; //begins count for login attempts 
      
        }

    }
    cout << "\n\n\tYou have exceeded the maximum amount of tries which is 3 trials"; //error message when login attempt exceeds 3
    exit(0); //program ends
}
    





    


   
  

