#include <iostream> // basic C++ library
#include <fstream> // for file i/o
#include <string> // for string functions
#include <vector> // for vectors
#include <stdexcept> // for exceptions

using namespace std; // for cin, cout etc

char status = 'n'; // current exception status

/********** VECTOR PROTOTYPES **********/
string checkPassword(string pass);
string checkUsername(string username);
bool isNameTaken(string username, vector<string>& takenNames);
bool isCapital(string pass);
void printMenuUsername();
void printMenuPassword();
void UsernameException(string username);
void PasswordException(string pass);

/********* EXCEPTIONS *********/
class NameTaken { /*** Empty Error Class ***/ }; // NameTaken exception, thrown if the chosen username is already taken
class TooShort { /*** Empty Error Class ***/ }; // TooShort exception, thrown if the chosen username/password is too short
class NoUppercase { /*** Empty Error Class ***/ }; // NoUppercase exception, thrown if there is no uppercase letter in password
class NoSpecialChar { /*** Empty Error Class ***/ }; // NoSpecialChar exception, thrown if there is not special char in password

int main() // main driver function
{
	string username; // username variable to hold chosen username
	string pass; // password variable to hold chosen password
	printMenuUsername(); // print menu for username
	cin >> username; // obtain username

	while (1) // infinite loop
	{
		while (status == 'L') // loop while the exception sets a status of L
		{
			cout << "Please try again: "; // prompt user for a different username
			cin >> username;
			status = 'n';
			UsernameException(username);
		}

		UsernameException(username);
		if (status == 'n') // once the status is cleared, break out of infinite loop
		{
			break;
		}
	}


	printMenuPassword();
	cin >> pass;

	while (1)
	{
		while (status == 'L') // loop while the exception sets a status of L
		{
			cout << "Please try again: "; // prompt user for a different password
			cin >> pass;
			status = 'n';
			PasswordException(pass);
		}

		PasswordException(pass);
		if (status == 'n') // once the status is cleared, break out of infinite loop
		{
			break;
		}
	}

	return 0;
}


string checkPassword(string pass)
{
	vector<char> Special = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' }; // vector of allowed special characters

	if (pass.length() < 6) // if password is less than 6 chars,
	{
		throw TooShort(); // throw TooShort exception
	}

	if (!isCapital(pass)) // if there is no capital letter in password,
	{
		throw NoUppercase(); // throw NoUppercase exception
	}

	bool SpecialChar = false; // initialize SpecialChar boolean

	for (char c : pass) // iterate through vector
	{
		if (find(Special.begin(), Special.end(), c) != Special.end())
		{
			SpecialChar = true; // if a special character is found, set SpecialChar to true
			break;
		}
	}

	if (!SpecialChar) // if there is no special character present in the password,
	{
		throw NoSpecialChar(); // throw NoSpecialChar exception
	}



	return pass; // return password
}

string checkUsername(string username) // checkUsername function, checks the validity of the chosen username by the user
{

	vector<string> takenNames = { "user123", "cooluser", "admin_007" }; // initial usernames that are taken

	if (username.length() < 5) // check to make sure the length of the username is greater or equal to 5
	{
		throw TooShort(); // if it's not, then throw TooShort exception
	}
	else if (isNameTaken(username, takenNames)) // check to see if username chosen is already in use
	{
		throw NameTaken(); // if so, throw NameTaken exception
	}

	takenNames.push_back(username); // if criteria is filled, insert this username into the takeNames vector
	return username; // return the username chosen
}

bool isNameTaken(string username, vector<string>& takenNames) // boolean function that determines whether username is already taken
{
	return (find(takenNames.begin(), takenNames.end(), username) != takenNames.end()); // if the name is already taken, return true, otherwise return false
}

bool isCapital(string pass) // boolean helper function for checking if there is an uppercase letter in the password
{
	for (char c : pass)
	{
		if (isupper(c))
		{
			return true;
		}
	}
	return false;
}

void printMenuUsername()
{
	cout << "********************************************************************" << endl;
	cout << "Hello and welcome to our website, here you can make an" << endl;
	cout << "account before you start to browse. Please input username here: " << endl;
	cout << "(Username must be at least 5 characters and cannot be already taken)" << endl;
	cout << "********************************************************************" << endl;
}

void printMenuPassword()
{
	cout << "\n********************************************************************" << endl;
	cout << "Good! Now please input a password. It must be at least 6 characters" << endl;
	cout << "and must contain one uppercase letter and special character." << endl;
	cout << "These special characters include: !, @, #, $, %, ^, &, *, (, )" << endl;
	cout << "********************************************************************" << endl;
}

void UsernameException(string username)
{
	try
	{
		checkUsername(username); // check username
	}
	catch (const TooShort&) // catch TooShort exception
	{
		cout << "That username is not long enough!\n"; // inform user their username is not long enough
		status = 'L';
		return;
	}
	catch (const NameTaken&) // catch NameTaken exception
	{
		cout << "Sorry, that name is taken\n"; // inform user that their username choice has already been taken
		status = 'L';
		return;
	}
}

void PasswordException(string pass)
{
	try
	{
		checkPassword(pass); // check password
	}
	catch (const TooShort&) // catch TooShort exception
	{
		cout << "That password is too short!\n"; // inform user their password is too short
		status = 'L';
		return;
	}
	catch (const NoSpecialChar&) // catch NoSpecialChar exception
	{
		cout << "That password does not contain any special characters!\n"; // inform user that their password has no special characters
		status = 'L';
		return;
	}
	catch (const NoUppercase&) // catch NoUppercase exception
	{
		cout << "That password does not contain any uppercase letters!\n"; // inform user their password has no uppercase letters
		status = 'L';
		return;
	}
}
