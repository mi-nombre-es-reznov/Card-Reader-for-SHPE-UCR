// Created by Nicholas Perez-Aguilar
// Start Date: 15 Aug 18
// Card reader test for SHPE @ UCR
//
//
// Last Modified: 27 Aug 18
//
// This program will allow for the user to pick between the options of adding a new member, looking up a member, or even updating
// a members data. It has bound checks almost everywhere and cannot easily be broken, from observations thus far. User data will be
// displayed on the screen for the user to see but also is constantly opening and closing files to write and save data, this is also
// a security measure employed to, hopefully, protect the external data as much as possible. The data consists of card number (SID card
// UCR specific), first and last name, Student ID number, netID, email, birthday, and even member's major. It now has a password protective cover layer
// to weed out unauthorized users. It has several data paths to obtain statistics. Everything is now interlinked with eachother and it is a complete
// program. It is also setup to run with best visual aesthetics with full screen command prompt. New addition now allows for user to save a
// copy of the current data after every GM sign-in.

#include <iostream>		// For input/output
#include <cstring>		// In order to use the substring function
#include <string>		// In order to use strings
#include <fstream>		// In order to write/read from an external file
#include <algorithm>	// To allow for removal of spaces in strings
using namespace std;	// Using standard namespace declaration

						/* ----------------------------------------------------------------------------------
						Structs to allow for multiple values to be returned at once from a call function
						---------------------------------------------------------------------------------- */
						// Main struct to pass data for updating
struct replacements
{
	char choice;			// Holds value from menu selection
	string replacement;		// Holds returned string of data from whichever menu selection was picked
	int SID;				// Holds specifically Student Id number
	int day;				// Holds specifically the day of birth
	int year;				// Holds specifically the year of birth
};

// Data to hold data values for member birthdays
struct Bday
{
	int day;				// Holds the day of birth
	string month;			// Holds the month of birth
	int year;				// Holds the year of birth
};

struct get_GM
{
	string quarter;
	string number;
	string together;
};

// Call function preprocessors
void new_user();
void menu_choices();
void option_selection();
char Retry();
void member_search();
void update_member_info();
replacements replace_choice(string, string, string, string, string, string, int, string, string, int, string, int, string);
void Replace_Menu();
Bday get_Birthday();
void Months();
string get_Major();
void Major_Choice();
string Insert_Major();
void all_member_data();
void search_other();
void GM_Update();
get_GM get_GM_info();
void Quarters();
void GM_Numbers();
void Individual_GM_data();
void Stats();
void Stats_Menu();
string get_Gender();
void stats_birthdays();
void stats_attendance_records();
void stats_majors();
void stats_sign_ins();
string stats_pick_month();
void get_all_months(string);
int Password();
void get_individual_GM_members();
void Summer_opportunites(string, string, int);

// -------------------------------
//              Main
// -------------------------------
int main()
{
	char retry;
	int key;

	do
	{
		key = Password();	// Added for extra security
	} while (key != 1);

	/* ------------------------------------------
			  SHPE Menu Internal File Intro
	   ------------------------------------------ */
	do
	{
		option_selection();		// Main Menu operations following input to main display

								// Loop for input validation
		do
		{
			retry = Retry();	// Asks about looping Main Menu (Main) again
		} while (retry != 'y' && retry != 'n');

	} while (retry == 'y');

	// Closing message at the very end of the program

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nThank you for using NCompEng technologies. We appreciate that you have chosen our product for your database needs.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	system("pause");	// Pause program for viewing
	return 0;			// Null return. End of program.
}

// -------------------------------
//         Insert new user
// -------------------------------
void new_user()
{
	bool numFail;
	Bday birthday;
	ofstream data;
	string major, gender;
	data.open("records.txt", ios::app);
	if (data.is_open())
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "File has opened successfully!" << endl << endl << endl << endl << endl;
		/* ------------------------------------------
		SHPE Menu Internal File Intro
		------------------------------------------ */

		cout << "\t\t\t\t---------------------------------------------------" << endl;
		cout << "\t\t\t\t                  Add a new User                   " << endl;
		cout << "\t\t\t\t---------------------------------------------------" << endl;

		string get_card_info, var, card_number, first_name, last_name, netID;	// String variables
		char semi = ';';	// Token item to look for using find function
		int count2 = 0;	// integer variables to use for counters
		int ID = -1;

		cin.ignore();
		// Do while to test for a minimum card input (bounds may need to be changed later)
		do
		{
			cout << "\n\n\nPlease swipe a card: ";	// Intro message
			getline(cin, get_card_info);		// Take in all data form card swipe

												// Used to test length intially. If failed, display message
			if (get_card_info.length() < 95)
			{
				cout << "Card read error. Please retry swipe." << endl << endl;	// If executed, the min length was not reached by the card swipe, usually read error
			}
		} while (get_card_info.length() < 95);	// Bound check to see if min data entry was reached

		cout << endl << endl << endl << endl << endl;
		size_t pos = get_card_info.find(";");
		string place_holder = get_card_info.substr(pos + 1);	// Push one (1) position past the semi colon. Will be start of the card number
		card_number = place_holder.substr(0, 16);	// Take in 16 places from the intial card number

													// Insert spaces at appropriate spots to allow for user readability  of card numbers. 4 numbers each, then space. Spans the entire 16 digits.
		card_number.insert(4, " ");
		card_number.insert(9, " ");
		card_number.insert(14, " ");

		// Message to display the card number with the spaces.
		cout << "Card number: " << card_number << endl;
		data << card_number << " ";

		// Get the cardholders name
		cout << "Last Name (no spaces): ";
		cin >> last_name;
		cout << "First name (no spaces): ";
		cin >> first_name;
		data << last_name << ", " << first_name << " ";

		// Get student ID number
		do
		{
			cout << "Student ID number: ";
			cin >> ID;

			numFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (numFail == true)
			{
				cout << "You entered an invalid option, please enter a valid number!" << endl;
			}
		} while (numFail == true);
		data << ID << " ";

		// Get student netID
		cout << "netID: ";
		getline(cin, netID);
		int position = netID.find(" ");
		if (position > 0)
		{
			netID = netID.substr(position);
		}
		data << netID << " ";

		// Write e-mail address
		data << netID << "@ucr.edu ";

		// Get member birthday
		birthday = get_Birthday();
		cout << "Your birthday is: " << birthday.day << " " << birthday.month << " " << birthday.year << endl;
		data << birthday.day << " " << birthday.month << " " << birthday.year << " ";

		// Get member major
		major = get_Major();
		data << major << " ";

		// Gender
		gender = get_Gender();
		data << gender << " ";

		// Fall entries of data pushes of no attendence
		string F1 = "No", F2 = "No", F3 = "No", F4 = "No", F5 = "No";
		data << F1 << " " << F2 << " " << F3 << " " << F4 << " " << F5 << " ";
		// Winter entries of data pushes of no attendence
		string W1 = "No", W2 = "No", W3 = "No", W4 = "No", W5 = "No";
		data << W1 << " " << W2 << " " << W3 << " " << W4 << " " << W5 << " ";
		// Spring entries of data pushes of no attendence
		string S1 = "No", S2 = "No", S3 = "No", S4 = "No", S5 = "No";
		data << S1 << " " << S2 << " " << S3 << " " << S4 << " " << S5 << " ";

		// End user row
		data << "END";

		data << endl;					// Newline in external file
		cout << endl << endl << endl;	// Space in terminal
	}
	else
	{
		cout << "Unable to open file! File may be corrupt/deleted." << endl << endl;
	}

	// Close the file and testing to verify
	data.close();
	if (!data.is_open())
	{
		cout << "File has been successfully closed and ammendment has been saved!" << endl << endl << endl;
	}
}

// -------------------------------
//           Menu Choices
// -------------------------------
void menu_choices()
{
	cout << endl << endl << endl;	// create space before displaying menu
	cout << "\t\tA) Create a new member" << endl;
	cout << "\t\tB) Retrieve member info" << endl;
	cout << "\t\tC) Update user info" << endl;
	cout << "\t\tD) Retrieve all user info" << endl;
	cout << "\t\tE) General Meeting Sign-In" << endl;
	cout << "\t\tF) Retrieve individual GM data" << endl;
	cout << "\t\tG) Statistics" << endl;
	cout << "\t\tH) Exit program" << endl;
}

// -------------------------------
//         Choice Selection
// -------------------------------
void option_selection()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t              Welcome to the SHPE @ UCR card reader database                   " << endl;
	cout << "\t\t\t-------------------------------------------------------------------------------" << endl;
	char option;
	menu_choices();

	/* -----------------------------------------------------
	This will be for selection of a menu option
	----------------------------------------------------- */
	cout << "\n\n\nPlease select an option: ";
	cin >> option;
	if (isalpha(option))
	{
		option = toupper(option);
	}
	else
	{
		cout << "Incorrect value. Please retry with a valid option." << endl;
		option_selection();
	}

	// This will be the case options that the above selection runs through, if successful.
	switch (option)
	{
		// New User choice
	case 'A':
	{
		cout << "Option A selected!" << endl << endl << endl << endl;
		new_user();
		break;
	}
	// Member search choice
	case 'B':
	{
		cout << "Option B selected!" << endl << endl << endl << endl;
		member_search();
		break;
	}
	// Update member info choice
	case 'C':
	{
		cout << "Option C selected!" << endl << endl << endl << endl;
		update_member_info();
		break;
	}
	// Retrieve all user data
	case 'D':
	{
		cout << "Option D selected!" << endl << endl << endl << endl;
		all_member_data();
		break;
	}
	case 'E':
	{
		cout << "Option E selected" << endl << endl << endl << endl;
		GM_Update();
		break;
	}
	case 'F':
	{
		cout << "Option F selected" << endl << endl << endl << endl;
		Individual_GM_data();
		break;
	}
	case 'G':
	{
		cout << "Option G selected" << endl << endl << endl << endl;
		Stats();
		break;
	}
	case 'H':
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nThank you for using NCompEng technologies. We appreciate that you have chosen our product for your database needs.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		system("pause");
		exit(0);
	}
	// An error has occured/Invalid option selected.
	default:
	{
		cout << "\n\nIncorrect value. Please retry with a valid option." << endl;
		option_selection();
		break;
	}
	}
}

// -------------------------------
//         Retry Program
// -------------------------------
char Retry()
{
	char again;

	// Retry choice
	cout << "Would you like to see the menu again? (y or n): ";
	cin >> again;

	// If statement to test whether or not input was valid
	if (isalpha(again))
	{
		// Alphabetic option
		again = tolower(again);				// Convert whatever input alphabetic option to a capital version
		if (again != 'y' && again != 'n')	// Test if option is a capitol 'Y' or 'N'.
		{
			cout << "You input an incorrect option. Please choose a valid option!" << endl << endl;
		}
	}
	else
	{
		// Non-alphabetic option
		cout << "You input an incorrect option. Please choose a valid option!" << endl << endl;
	}

	return again;	// Return option again if valid
}

// -------------------------------
//       Search for member
// -------------------------------
void member_search()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_gender, get_email;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year, count = 0;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	// Open database
	ifstream database;
	database.open("records.txt");

	// Test to see if file has opened
	if (database.is_open())
	{
		cout << "File has successfully been opened!" << endl << endl;	// Verification that file has been opened succesfully
		cin.ignore();	// Ignore previous input to allow for new input.
						// Do while to test for a minimum card input (bounds may need to be changed later)
		do
		{
			cout << "Please swipe card for member lookup: ";	// Intro message
			getline(cin, search_ID);		// Take in all data form card swipe

											// Used to test length intially. If failed, display message
			if (search_ID.length() < 95)
			{
				cout << "Card read error. Please retry swipe." << endl << endl;	// If executed, the min length was not reached by the card swipe, usually read error
			}
		} while (search_ID.length() < 95);	// Bound check to see if min data entry was reached

		cout << endl << endl << endl << endl << endl;
		size_t pos = search_ID.find(";");
		string place_holder = search_ID.substr(pos + 1);	// Push one (1) position past the semi colon. Will be start of the card number
		search_ID = place_holder.substr(0, 16);	// Take in 16 places from the intial card number

												// Insert spaces at appropriate spots to allow for sub-divide the data that will be compared. It needs to have 4 groups of 4 for the 16 digits.
		search_ID1 = search_ID.substr(0, 4);
		search_ID2 = search_ID.substr(4, 4);
		search_ID3 = search_ID.substr(8, 4);
		search_ID4 = search_ID.substr(12, 4);


		// Data retrieveal from database to display for user.
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			// To replace major '_' with spaces
			string altered_major = get_major;
			int position = altered_major.find("_");
			while (position != string::npos)
			{
				altered_major.replace(position, 1, " ");
				position = altered_major.find("_", position + 1);
			}

			// If card number matches
			if ((search_ID1 == get_ID1) && (search_ID2 == get_ID2) && (search_ID3 == get_ID3) && (search_ID4 == get_ID4))
			{
				if (get_F1 == "Yes")
				{
					count++;
				}
				if (get_F2 == "Yes")
				{
					count++;
				}
				if (get_F3 == "Yes")
				{
					count++;
				}
				if (get_F4 == "Yes")
				{
					count++;
				}
				if (get_F5 == "Yes")
				{
					count++;
				}
				if (get_W1 == "Yes")
				{
					count++;
				}
				if (get_W2 == "Yes")
				{
					count++;
				}
				if (get_W3 == "Yes")
				{
					count++;
				}
				if (get_W4 == "Yes")
				{
					count++;
				}
				if (get_W5 == "Yes")
				{
					count++;
				}
				if (get_S1 == "Yes")
				{
					count++;
				}
				if (get_S2 == "Yes")
				{
					count++;
				}
				if (get_S3 == "Yes")
				{
					count++;
				}
				if (get_S4 == "Yes")
				{
					count++;
				}
				if (get_S5 == "Yes")
				{
					count++;
				}


				// Setup database retrieval for user to easily read.
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				cout << "************************" << endl;
				cout << "   Member Information" << endl;
				cout << "************************" << endl << endl << endl << endl;
				cout << "Card number: " << get_ID1 << " " << get_ID2 << " " << get_ID3 << " " << get_ID4 << endl;
				cout << "Name: " << get_last_name << " " << get_first_name << endl;
				cout << "Student ID: " << get_SID << endl;
				cout << "Student netID: " << get_netID << endl;
				cout << "Student email: " << get_email << endl;
				cout << "Student date of birth: " << get_birth_day << " " << get_birth_month << " " << get_birth_year << endl;
				cout << "Student major: " << altered_major << endl;
				cout << "General Meetings attended: " << count << endl;
				cout << end_tag << endl;
				if (count >= 10)
				{
					cout << endl << endl;
					cout << "\t\t\t*****************************************************************" << endl;
					cout << "\t\t\t*  Congratulations! You are now considered a current member!!!  *" << endl;
					cout << "\t\t\t*****************************************************************" << endl;
				}
				break;
			}

		}

		// Test if the data is not found in database
		if (!(search_ID1 == get_ID1) || !(search_ID2 == get_ID2) || !(search_ID3 == get_ID3) || !(search_ID4 == get_ID4))
		{
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nData cannot be found!" << endl << endl;
		}

		// Close file and verify
		database.close();
		if (!database.is_open())
		{
			cout << "\n\nThe file has successfully closed!" << endl << endl << endl;
		}
	}
	// Verify that the file has opened successfully.
	else
	{
		cout << "The file has failed to open. Data may be corrupt! Please verify filename and location." << endl;
	}
}

// -------------------------------
//       Update member info
// -------------------------------
void update_member_info()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag, line;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_email, get_birth_month, get_major, get_gender, replace;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year;
	replacements replaced;
	Bday birthday;
	ifstream database;
	database.open("records.txt");

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	// Test if database is open
	if (database.is_open())
	{
		cout << "File has successfully been opened!" << endl << endl;	// Database has opened successfully
		cin.ignore();	// Ignore previous input to allow for new input
						// Do while to test for a minimum card input (bounds may need to be changed later)
		do
		{
			cout << "Please swipe card for member lookup (if updating card, please enter 'card'): ";	// Intro message
			getline(cin, search_ID);		// Take in all data form card swipe

			if (search_ID == "card")
			{
				cout << "Understood. We are changing parameters for you. Please wait." << endl;
				search_ID = "%B00000000000000^Emeritus/Papa  ^54894878740000000000000      ?;00000000000000000=000000000000000000000000?";
				search_other();
				break;
			}

			// Used to test length intially. If failed, display message
			if (search_ID.length() < 95)
			{
				cout << "Card read error. Please retry swipe." << endl << endl;	// If executed, the min length was not reached by the card swipe, usually read error
			}
		} while (search_ID.length() < 95);	// Bound check to see if min data entry was reached

		cout << endl << endl << endl << endl << endl;
		size_t pos = search_ID.find(";");
		string place_holder = search_ID.substr(pos + 1);	// Push one (1) position past the semi colon. Will be start of the card number
		search_ID = place_holder.substr(0, 16);	// Take in 16 places from the intial card number

												// Insert spaces at appropriate spots to allow for sub-divide the data that will be compared. It needs to have 4 groups of 4 for the 16 digits.
		search_ID1 = search_ID.substr(0, 4);
		search_ID2 = search_ID.substr(4, 4);
		search_ID3 = search_ID.substr(8, 4);
		search_ID4 = search_ID.substr(12, 4);

		// Retrieve data from database to allow for user to see
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			string altered_major = get_major;
			int position = altered_major.find("_");
			while (position != string::npos)
			{
				altered_major.replace(position, 1, " ");
				position = altered_major.find("_", position + 1);
			}
			// If card number is the same as database card number
			if ((search_ID1 == get_ID1) && (search_ID2 == get_ID2) && (search_ID3 == get_ID3) && (search_ID4 == get_ID4))
			{
				// Setup to allow for retrieval of data to be easily viewed by user
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				cout << "************************" << endl;
				cout << "   Member Information" << endl;
				cout << "************************" << endl;
				cout << "Card number: " << get_ID1 << " " << get_ID2 << " " << get_ID3 << " " << get_ID4 << endl;
				cout << "Name: " << get_last_name << " " << get_first_name << endl;
				cout << "Student ID: " << get_SID << endl;
				cout << "Student netID: " << get_netID << endl;
				cout << "Student email: " << get_email << endl;
				cout << "Student date of birth: " << get_birth_day << " " << get_birth_month << " " << get_birth_year << endl;
				cout << "Student major: " << altered_major << endl;
				cout << end_tag << endl;

				// Call for replacement choice functions
				do
				{
					// Allow for replacement data to be retrieved
					replaced = replace_choice(get_ID1, get_ID2, get_ID3, get_ID4, get_last_name, get_first_name, get_SID, get_netID, get_email, get_birth_day, get_birth_month, get_birth_year, get_major);

					// If data value matches up to canceled option
					if (replaced.replacement == "canceled")
					{
						cout << endl << endl;
						cout << "Canceled has been completed!" << endl;
						break;
					}
				} while (replaced.replacement == "null");	// Repeat while data value is equal to 'null'

															// Breaks out of loop - no error messages occur
				if (replaced.choice == 'I')
				{
					break;
				}

				database.seekg(0);			// Reset pointer in file to the beginning of the file
				while (!database.eof())		// Run through file while pointer is not at the End of File (EOF).
				{
					getline(database, line);	// Take in an entire line of data from the database
					switch (replaced.choice)	// Use data to cycle through the option selection
					{
						// ---------------------------------
						//        Updates Card number
						// ---------------------------------
					case 'A':
					{

						// Insert spaces at appropriate spots to allow for sub-divide the data that will be compared. It needs to have 4 groups of 4 for the 16 digits.
						string replacement1 = replaced.replacement.substr(0, 4);
						string replacement2 = replaced.replacement.substr(4, 4);
						string replacement3 = replaced.replacement.substr(8, 4);
						string replacement4 = replaced.replacement.substr(12, 4);

						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;


						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4))
							{
								rep_ID1 = replacement1;
								rep_ID2 = replacement2;
								rep_ID3 = replacement3;
								rep_ID4 = replacement4;
							}
							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;
						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4))
							{
								ret_ID1 = rep_ID1;
								ret_ID2 = rep_ID2;
								ret_ID3 = rep_ID3;
								ret_ID4 = rep_ID4;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					// ---------------------------------
					//         Updates first name
					// ---------------------------------
					case 'B':
					{
						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_first_name == get_first_name))
							{
								rep_first_name = replaced.replacement;
							}
							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_first_name == ret_first_name))
							{
								ret_first_name == rep_first_name;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					// ---------------------------------
					//         Updates Last name
					// ---------------------------------
					case 'C':
					{
						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_last_name == get_last_name))
							{
								rep_last_name = replaced.replacement;
							}
							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_last_name == ret_last_name))
							{
								ret_last_name == rep_last_name;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					// ---------------------------------
					//         Updates SID number
					// ---------------------------------
					case 'D':
					{
						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_SID == get_SID))
							{
								rep_SID = replaced.SID;
							}

							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;
						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_SID == ret_SID))
							{
								ret_SID = rep_SID;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					// ---------------------------------
					//           Updates netID
					// ---------------------------------
					case 'E':
					{
						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_netID == get_netID))
							{
								rep_netID = replaced.replacement;
							}

							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_netID == ret_netID))
							{
								ret_netID = rep_netID;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					// ---------------------------------
					//           Updates email
					// ---------------------------------
					case 'F':
					{
						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_email == get_email))
							{
								rep_email = replaced.replacement;
							}

							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_last_name == ret_last_name))
							{
								ret_email = rep_email;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					// ---------------------------------
					//          Updates birthday
					// ---------------------------------
					case 'G':
					{
						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_birth_day == get_birth_day) && (rep_birth_month == get_birth_month) && (rep_birth_year == get_birth_year))
							{
								rep_birth_day = replaced.day;
								rep_birth_month = replaced.replacement;
								rep_birth_year = replaced.year;
							}

							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (ret_birth_day == rep_birth_day) && (ret_birth_month == rep_birth_month) && (ret_birth_year == rep_birth_year))
							{
								ret_birth_day = rep_birth_day;
								ret_birth_month = rep_birth_month;
								ret_birth_year = rep_birth_year;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					// ---------------------------------
					//            Updates major
					// ---------------------------------
					case 'H':
					{
						string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
						int rep_SID, rep_birth_day, rep_birth_year;
						string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

						// Put data in temp file
						ifstream filein("records.txt"); //File to read from
						ofstream fileout("text.txt"); //Temporary file

						while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
							rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
							rep_S4 >> rep_S5 >> end_tag)
						{
							if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_major == get_major))
							{
								rep_major = replaced.replacement;
							}

							fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
								" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
								rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
						}

						filein.close();
						fileout.close();

						// Put data in back in original file
						ifstream filein2("text.txt"); //File to read from
						ofstream fileout2("records.txt"); //Temporary file

						string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
						int ret_SID, ret_birth_day, ret_birth_year;
						string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

						while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
							ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
							ret_S4 >> ret_S5 >> end_tag)
						{
							if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_last_name == ret_last_name))
							{
								ret_major = rep_major;
							}
							fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
								" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
								ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

						}

						filein2.close();
						fileout2.close();

						break;
					}
					default:
					{
						cout << "You have encountered an error. Please retry the program." << endl;
						break;
					}
					}
				}
			}
		}

		// Test to see if card number does not match up to any in database
		if ((!(search_ID1 == get_ID1) || !(search_ID2 == get_ID2) || !(search_ID3 == get_ID3) || !(search_ID4 == get_ID4)) && (search_ID != "0000000000000000"))
		{
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nData cannot be found!" << endl << endl;
		}

		database.close();
		if (!database.is_open())
		{
			cout << "\n\nThe file has successfully closed!" << endl << endl << endl;
		}
	}
	else
	{
		cout << "The file has failed to open. Data may be corrupt! Please verify filename and location." << endl;
	}
}

// -------------------------------
//       Replacement choice
// -------------------------------
replacements replace_choice(string num1, string num2, string num3, string num4, string last, string first, int id, string netID, string email, int day, string month, int year, string curr_major)
{
	char choice, choice2;
	string card_num, replacement_card, replacement_first, replacement_last, replacement_netID, replacement_email, replacement_major;
	int replacement_SID;
	bool numFail;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	Replace_Menu();	// Update Menu options

					// Allow user to input choice from menu in which they want to update in database
	cin >> choice;

	// Test choice that user entered to see if it is alphabetic.
	if (isalpha(choice))
	{
		choice = toupper(choice);
	}
	// User input is not aplphabetic.
	else
	{
		cout << "You have entered an incorrect value. Please retry with a valid option!" << endl;
		return replacements{ choice, "null" , 0 };
	}

	// Switch statement to run through choices
	switch (choice)
	{
	case 'A':
	{
		// Update Card number
		cin.ignore();
		// Do while to test for a minimum card input (bounds may need to be changed later)
		do
		{
			cout << "Please swipe card for replacement numbers: ";	// Intro message
			getline(cin, replacement_card);		// Take in all data form card swipe

												// Used to test length intially. If failed, display message
			if (replacement_card.length() < 95)
			{
				cout << "Card read error. Please retry swipe." << endl << endl;	// If executed, the min length was not reached by the card swipe, usually read error
			}
		} while (replacement_card.length() < 95);	// Bound check to see if min data entry was reached

		cout << endl << endl << endl << endl << endl;
		size_t pos = replacement_card.find(";");
		string place_holder = replacement_card.substr(pos + 1);	// Push one (1) position past the semi colon. Will be start of the card number
		replacement_card = place_holder.substr(0, 16);	// Take in 16 places from the intial card number

		string replacement_card1 = replacement_card.substr(0, 4);
		string replacement_card2 = replacement_card.substr(4, 4);
		string replacement_card3 = replacement_card.substr(8, 4);
		string replacement_card4 = replacement_card.substr(12, 4);

		cout << "\n\nYour documented card number is: " << num1 << " " << num2 << " " << num3 << " " << num4 << "." << endl;
		cout << "Your requested new card number is: " << replacement_card1 << " " << replacement_card2 << " " << replacement_card3 << " " << replacement_card4 << "." << endl;

		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, replacement_card, 0 };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');

		break;
	}
	case 'B':
	{
		// Update First Name
		cin.ignore();
		cout << "Please enter replacement first name (no spaces): ";
		getline(cin, replacement_first);
		int position = replacement_first.find(" ");
		if (position > 0)
		{
			replacement_first = replacement_first.substr(position);
		}

		cout << "Your documented first name is: " << first << "." << endl;
		cout << "Your preferred changed first name is: " << replacement_first << "." << endl;

		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, replacement_first, 0 };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');

		break;
	}
	case 'C':
	{
		// Update Last Name
		cin.ignore();
		cout << "Please enter replacement last name (no spaces): ";
		getline(cin, replacement_last);
		int position = replacement_last.find(" ");
		if (position > 0)
		{
			replacement_last = replacement_last.substr(position);
		}

		cout << "Your documented last name is: " << last << "." << endl;
		cout << "Your preferred changed last name is: " << replacement_last << "." << endl;

		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, replacement_last, 0 };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');

		break;
	}
	case 'D':
	{
		// Update Student ID

		// Loop to rerun through if user gives invalid choice for SID.
		do
		{
			cout << "What is your SID: ";
			cin >> replacement_SID;

			numFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (numFail == true)
			{
				cout << "You entered an invalid option, please enter a valid number!" << endl;
			}
		} while (numFail == true);

		cout << "Your documented Student ID is: " << id << "." << endl;
		cout << "Your requested new Student ID is: " << replacement_SID << "." << endl;

		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, "none", replacement_SID };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');

		break;
	}
	case 'E':
	{
		// Update netID
		cin.ignore();
		cout << "Please enter replacement netID (no spaces): ";
		getline(cin, replacement_netID);
		int position = replacement_netID.find(" ");
		if (position > 0)
		{
			replacement_netID = replacement_netID.substr(position);
		}

		cout << "Your documented netID is: " << netID << "." << endl;
		cout << "Your preferred changed netID is: " << replacement_netID << "." << endl;

		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, replacement_netID, 0 };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');

		break;
	}
	case 'F':
	{
		// Update Email
		cin.ignore();
		cout << "Please enter updated email (no spaces): ";
		getline(cin, replacement_email);
		int position = replacement_email.find(" ");
		if (position > 0)
		{
			replacement_email = replacement_email.substr(position);
		}

		cout << "Your documented email is: " << email << "." << endl;
		cout << "Your preferred email is: " << replacement_email << "." << endl;

		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, replacement_email, 0 };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');
		break;
	}
	case 'G':
	{
		Bday birthday;
		// Update Birthday
		birthday = get_Birthday();
		string date;

		cout << "Your documented birthday is: " << day << " " << month << " " << year << "." << endl;
		cout << "Your preferred birthday is: " << birthday.day << " " << birthday.month << " " << birthday.year << "." << endl;

		date = (to_string(birthday.day) + " " + birthday.month + " " + to_string(birthday.year));
		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, birthday.month, 0, birthday.day, birthday.year };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');
		break;
	}
	case 'H':
	{
		// Update Major
		string major;
		replacement_major = get_Major();

		cout << "Your documented major is: " << curr_major << "." << endl;
		cout << "Your preferred major is: " << replacement_major << "." << endl;

		do
		{
			cout << "Is this correct? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! We are working on ammending your information." << endl;
				return replacements{ choice, replacement_major, 0 };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! We have not made any changes." << endl;
				return replacements{ choice, "null" };
			}
		} while (choice2 != 'Y' && choice2 != 'N');
		break;
	}
	case 'I':
	{
		// Cancel
		do
		{
			cout << "Are you sure you want to cancel update? (y or n): ";
			cin >> choice2;
			choice2 = toupper(choice2);

			if (choice2 == 'Y')
			{
				cout << "Understood! No changes will be made." << endl;
				return replacements{ choice, "canceled", 0 };
			}

			if (choice2 == 'N')
			{
				cout << "Understood! Here you go!" << endl;
				return replacements{ choice, "null" };

			}
		} while (choice2 != 'Y' && choice2 != 'N');

		break;
	}
	default:
	{
		cout << "You have input an incorrect choice. Please retry with a valid option!" << endl;
		return replacements{ choice, "null" };
		break;
	}
	}
}

// -------------------------------
//        Replacement Menu
// -------------------------------
void Replace_Menu()
{
	cout << endl << endl << endl << "What data do you want to replace?" << endl << endl << endl;
	cout << "\t\t\t\tA) Card Number" << endl;
	cout << "\t\t\t\tB) First Name" << endl;
	cout << "\t\t\t\tC) Last Name" << endl;
	cout << "\t\t\t\tD) Student ID number" << endl;
	cout << "\t\t\t\tE) netID" << endl;
	cout << "\t\t\t\tF) Email" << endl;
	cout << "\t\t\t\tG) Birthday" << endl;
	cout << "\t\t\t\tH) Major" << endl;
	cout << "\t\t\t\tI) Cancel" << endl;

	cout << endl << endl << endl;
	cout << "I want to replace: ";
}

// -------------------------------
//       Get member Birthday
// -------------------------------
Bday get_Birthday()
{
	int day, year;
	string month;
	bool numFail;
	int choice;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	// Loop to rerun through if user gives invalid choice for year born in.
	do
	{
		cout << "What year were you born in: ";
		cin >> year;

		numFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (numFail == true)
		{
			cout << "You entered an invalid option, please enter a valid number!" << endl;
		}
	} while ((numFail == true) || (year < 1950) || (year > 2018));

	// Loop to run through if user were to give invalid choice for day born on.
	do
	{
		cout << "Please enter the day in which you were born: ";
		cin >> day;

		numFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (numFail == true)
		{
			cout << "You entered an invalid option, please enter a valid number!" << endl;
		}
	} while ((numFail == true) || (day < 1) || (day > 31));

	// Loop to have user select from options of months and to rerun if choice is invalid.
	do
	{
		Months();
		cout << "Please enter the month in which you were born: ";
		cin >> choice;

		numFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (numFail == true)
		{
			cout << "You entered an invalid option, please enter a valid number!" << endl;
		}
	} while ((numFail == true) || (choice < 1) || (choice > 12));

	// Switch statement to run through if user choices are all valid and also returns selections in a struct to be processed.
	switch (choice)
	{
	case 1:
	{
		cout << "\n\nChoice accepted. You picked January." << endl;
		month = "January";
		return Bday{ day, month, year };
		break;
	}
	case 2:
	{
		cout << "\n\nChoice accepted. You picked February." << endl;
		month = "February";
		return Bday{ day, month, year };
		break;
	}
	case 3:
	{
		cout << "\n\nChoice accepted. You picked March." << endl;
		month = "March";
		return Bday{ day, month, year };
		break;
	}
	case 4:
	{
		cout << "\n\nChoice accepted. You picked April." << endl;
		month = "April";
		return Bday{ day, month, year };
		break;
	}
	case 5:
	{
		cout << "\n\nChoice accepted. You picked May." << endl;
		month = "May";
		return Bday{ day, month, year };
		break;
	}
	case 6:
	{
		cout << "\n\nChoice accepted. You picked June." << endl;
		month = "June";
		return Bday{ day, month, year };
		break;
	}
	case 7:
	{
		cout << "\n\nChoice accepted. You picked July." << endl;
		month = "July";
		return Bday{ day, month, year };
		break;
	}
	case 8:
	{
		cout << "\n\nChoice accepted. You picked August." << endl;
		month = "August";
		return Bday{ day, month, year };
		break;
	}
	case 9:
	{
		cout << "\n\nChoice accepted. You picked Septmeber." << endl;
		month = "September";
		return Bday{ day, month, year };
		break;
	}
	case 10:
	{
		cout << "\n\nChoice accepted. You picked October." << endl;
		month = "October";
		return Bday{ day, month, year };
		break;
	}
	case 11:
	{
		cout << "\n\nChoice accepted. You picked November." << endl;
		month = "November";
		return Bday{ day, month, year };
		break;
	}
	case 12:
	{
		cout << "\n\nChoice accepted. You picked December." << endl;
		month = "December";
		return Bday{ day, month, year };
		break;
	}
	default:
	{
		cout << "An error has occured. Try again.";
		break;
	}
	}
}

// -------------------------------
//       Display Month Menu
// -------------------------------
void Months()
{
	cout << endl << endl << endl << endl;	// Give space in beginning
	cout << "\t\t\t*********************************" << endl;
	cout << "\t\t\t       Month Selection Menu" << endl;
	cout << "\t\t\t*********************************" << endl << endl << endl;

	cout << "\t\t\t1) January" << endl;
	cout << "\t\t\t2) February" << endl;
	cout << "\t\t\t3) March" << endl;
	cout << "\t\t\t4) April" << endl;
	cout << "\t\t\t5) May" << endl;
	cout << "\t\t\t6) June" << endl;
	cout << "\t\t\t7) July" << endl;
	cout << "\t\t\t8) August" << endl;
	cout << "\t\t\t9) Septemeber" << endl;
	cout << "\t\t\t10) October" << endl;
	cout << "\t\t\t11) November" << endl;
	cout << "\t\t\t12) December" << endl;

	// Give space at the end
	cout << endl << endl << endl << endl;
}

// -------------------------------
//        Get member major
// -------------------------------
string get_Major()
{
	string major;
	char choice;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	Major_Choice();	// Major choice Menu

					// Allows for user to select choice from major choice menu
	cout << "Please select your major: ";
	cin >> choice;

	// Verify choice is alphabetic.
	if (isalpha(choice))
	{
		choice = toupper(choice);
	}
	else
	{
		cout << "Invalid input. Please try again." << endl << endl;
		major = get_Major();
	}

	// Switch statment to run through is choice is valid and returns choice.
	switch (choice)
	{
	case 'A':
	{
		major = "Bioengineering";
		break;
	}
	case 'B':
	{
		major = "Chemical_Engineering";
		break;
	}
	case 'C':
	{
		major = "Computer_Engineering";
		break;
	}
	case 'D':
	{
		major = "Computer_Science";
		break;
	}
	case 'E':
	{
		major = "Computer_Science_with_business_Applications";
		break;
	}
	case 'F':
	{
		major = "Electrical_Engineering";
		break;
	}
	case 'G':
	{
		major = "Enviornmental_Engineering";
		break;
	}
	case 'H':
	{
		major = "Materials_Science_and_Engineering";
		break;
	}
	case 'I':
	{
		major = "Mechanical_Engineering";
		break;
	}
	case 'J':
	{
		major = Insert_Major();
		break;
	}
	default:
	{
		cout << "An error has occured. Please, try again." << endl << endl;
	}
	}

	return major;
}

// -------------------------------
//      Display major choices
// -------------------------------
void Major_Choice()
{
	cout << endl << endl << endl << endl;
	cout << "\t\t\t*****************************" << endl;
	cout << "\t\t\t        Major Options" << endl;
	cout << "\t\t\t*****************************" << endl;

	cout << endl << endl << endl;
	cout << "\t\t\tA) Bioengineering\n";
	cout << "\t\t\tB) Chemical Engineering\n";
	cout << "\t\t\tC) Computer Engineering\n";
	cout << "\t\t\tD) Computer Science\n";
	cout << "\t\t\tE) Computer Science with Business Applications\n";
	cout << "\t\t\tF) Electrical Engineering\n";
	cout << "\t\t\tG) Enviornmental Engineering\n";
	cout << "\t\t\tH) Materials Science and Engineering\n";
	cout << "\t\t\tI) Mechanical Engineering\n";
	cout << "\t\t\tJ) Other\n";
	cout << endl << endl << endl;
}

// -------------------------------
//    Allow member to put major
// -------------------------------
string Insert_Major()
{
	string major;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cin.ignore();	// Ignore previous input

					// Message to demonstrate how to insert major and to accept input.
	cout << "\n\n\nYou have selected the option for a major outside of Bourns College of Engineering (BCOE).\nPlease insert your major: ";
	getline(cin, major);

	// Find any whitespaces and replace them with '_' to be inserted into the database.
	int position = major.find(" ");
	while (position != string::npos)
	{
		major.replace(position, 1, "_");
		position = major.find(" ", position + 1);
	}

	// Returns major
	return major;
}

// -------------------------------
//      Display all user data
// -------------------------------
void all_member_data()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_email, get_gender;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	ifstream retrieve;
	retrieve.open("records.txt");

	if (retrieve.is_open())
	{
		cout << "File has opened successfully." << endl << endl;

		// Data retrieval from database to display all users.
		while (retrieve >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			// To replace major '_' with spaces
			string altered_major = get_major;
			int position = altered_major.find("_");
			while (position != string::npos)
			{
				altered_major.replace(position, 1, " ");
				position = altered_major.find("_", position + 1);
			}

			int count = 0;

			if (get_F1 == "Yes")
			{
				count++;
			}
			if (get_F2 == "Yes")
			{
				count++;
			}
			if (get_F3 == "Yes")
			{
				count++;
			}
			if (get_F4 == "Yes")
			{
				count++;
			}
			if (get_F5 == "Yes")
			{
				count++;
			}
			if (get_W1 == "Yes")
			{
				count++;
			}
			if (get_W2 == "Yes")
			{
				count++;
			}
			if (get_W3 == "Yes")
			{
				count++;
			}
			if (get_W4 == "Yes")
			{
				count++;
			}
			if (get_W5 == "Yes")
			{
				count++;
			}
			if (get_S1 == "Yes")
			{
				count++;
			}
			if (get_S2 == "Yes")
			{
				count++;
			}
			if (get_S3 == "Yes")
			{
				count++;
			}
			if (get_S4 == "Yes")
			{
				count++;
			}
			if (get_S5 == "Yes")
			{
				count++;
			}

			// Setup database retrieval for user to easily read.
			cout << "\n\n\n";
			cout << "************************" << endl;
			cout << "   Member Information" << endl;
			cout << "************************" << endl;
			cout << "Card number: " << get_ID1 << " " << get_ID2 << " " << get_ID3 << " " << get_ID4 << endl;
			cout << "Name: " << get_last_name << " " << get_first_name << endl;
			cout << "Student ID: " << get_SID << endl;
			cout << "Student netID: " << get_netID << endl;
			cout << "Student email: " << get_email << endl;
			cout << "Student date of birth: " << get_birth_day << " " << get_birth_month << " " << get_birth_year << endl;
			cout << "Student major: " << altered_major << endl;
			cout << "General Meetings attended: " << count << endl;
			cout << end_tag << endl;
			if (count >= 10)
			{
				cout << endl << endl;
				cout << "\t\t\t*****************************************************************" << endl;
				cout << "\t\t\t*  Congratulations! You are now considered a current member!!!  *" << endl;
				cout << "\t\t\t*****************************************************************" << endl;
			}
		}

		// Close file and verify
		retrieve.close();
		if (!retrieve.is_open())
		{
			cout << "\n\n\nFile has closed successfully!" << endl << endl;
		}
	}
}

// -------------------------------
//     Card number replacement
// -------------------------------
void search_other()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_email, get_birth_month, get_major, get_gender, replace;
	string line, last_name;
	int get_SID, get_birth_day, get_birth_year, SID;
	char choice, choice2;
	string card_num, replacement_card, replacement_first, replacement_last, replacement_netID, replacement_email, replacement_major;
	int replacement_SID, position = 0, token = 0;
	bool numFail;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	ifstream database;
	database.open("records.txt");
	// Test if database is open
	if (database.is_open())
	{
		cout << "File has successfully been opened!" << endl << endl;	// Database has opened successfully

		cout << "Please enter your last name: ";
		getline(cin, last_name);
		int position = last_name.find(" ");
		if (position > 0)
		{
			last_name = last_name.substr(position);
		}

		// Loop to rerun through if user gives invalid choice for SID.
		do
		{
			cout << "What is your SID: ";
			cin >> SID;

			numFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (numFail == true)
			{
				cout << "You entered an invalid option, please enter a valid number!" << endl;
			}
		} while (numFail == true);


		cout << endl << endl << endl << endl << endl;

		// Retrieve data from database to allow for user to see
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			get_last_name.erase(remove(get_last_name.begin(), get_last_name.end(), ','), get_last_name.end());
			string altered_major = get_major;
			int position = altered_major.find("_");
			while (position != string::npos)
			{
				altered_major.replace(position, 1, " ");
				position = altered_major.find("_", position + 1);
			}

			// If last name and SID is the same as database
			if ((last_name == get_last_name) && (SID == get_SID))
			{
				// Setup to allow for retrieval of data to be easily viewed by user
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				cout << "************************" << endl;
				cout << "   Member Information" << endl;
				cout << "************************" << endl;
				cout << "Card number: " << get_ID1 << " " << get_ID2 << " " << get_ID3 << " " << get_ID4 << endl;
				cout << "Name: " << get_last_name << ", " << get_first_name << endl;
				cout << "Student ID: " << get_SID << endl;
				cout << "Student netID: " << get_netID << endl;
				cout << "Student email: " << get_email << endl;
				cout << "Student date of birth: " << get_birth_day << " " << get_birth_month << " " << get_birth_year << endl;
				cout << "Student major: " << altered_major << endl;
				cout << end_tag << endl;

				token = 1;	// Information found!

							// Update Card number
							// Do while to test for a minimum card input (bounds may need to be changed later)
				do
				{
					cout << "\n\nPlease swipe card for replacement numbers: ";	// Intro message
					getline(cin, replacement_card);		// Take in all data form card swipe

														// Used to test length intially. If failed, display message
					if (replacement_card.length() < 95)
					{
						cout << "Card read error. Please retry swipe." << endl << endl;	// If executed, the min length was not reached by the card swipe, usually read error
					}
				} while (replacement_card.length() < 95);	// Bound check to see if min data entry was reached

				cout << endl << endl << endl << endl << endl;
				size_t pos = replacement_card.find(";");
				string place_holder = replacement_card.substr(pos + 1);	// Push one (1) position past the semi colon. Will be start of the card number
				replacement_card = place_holder.substr(0, 16);	// Take in 16 places from the intial card number

																// Create card substrings
				string replacement1 = replacement_card.substr(0, 4);
				string replacement2 = replacement_card.substr(4, 4);
				string replacement3 = replacement_card.substr(8, 4);
				string replacement4 = replacement_card.substr(12, 4);

				cout << "\n\nYour documented card number is: " << get_ID1 << " " << get_ID2 << " " << get_ID3 << " " << get_ID4 << "." << endl;
				cout << "Your requested new card number is: " << replacement1 << " " << replacement2 << " " << replacement3 << " " << replacement4 << "." << endl;

				do
				{
					cout << "Is this correct? (y or n): ";
					cin >> choice2;
					choice2 = toupper(choice2);

					if (choice2 == 'Y')
					{
						cout << "Understood! We are working on ammending your information." << endl;
					}

					if (choice2 == 'N')
					{
						cout << "Understood! We have not made any changes." << endl;
					}
				} while (choice2 != 'Y' && choice2 != 'N');


				database.seekg(0);			// Reset pointer in file to the beginning of the file
				while (!database.eof())		// Run through file while pointer is not at the End of File (EOF).
				{
					getline(database, line);	// Take in an entire line of data from the database
												// Insert spaces at appropriate spots to allow for sub-divide the data that will be compared. It needs to have 4 groups of 4 for the 16 digits.

					string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
					int rep_SID, rep_birth_day, rep_birth_year;
					string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

					// Put data in temp file
					ifstream filein("records.txt"); //File to read from
					ofstream fileout("text.txt"); //Temporary file

					while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
						rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
						rep_S4 >> rep_S5 >> end_tag)
					{
						if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4))
						{
							rep_ID1 = replacement1;
							rep_ID2 = replacement2;
							rep_ID3 = replacement3;
							rep_ID4 = replacement4;
						}
						fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
							" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
							rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;

					}

					filein.close();
					fileout.close();

					// Put data in back in original file
					ifstream filein2("text.txt"); //File to read from
					ofstream fileout2("records.txt"); //Temporary file

					string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
					int ret_SID, ret_birth_day, ret_birth_year;
					string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

					while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
						ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
						ret_S4 >> ret_S5 >> end_tag)
					{
						if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4))
						{
							ret_ID1 = rep_ID1;
							ret_ID2 = rep_ID2;
							ret_ID3 = rep_ID3;
							ret_ID4 = rep_ID4;
						}
						fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
							" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
							ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;

					}

					filein2.close();
					fileout2.close();
				}
			}
		}

		if (token != 1)
		{
			cout << "Data cannot be found!" << endl << endl;
		}

		database.close();
		if (!database.is_open())
		{
			cout << "\n\nFile has closed successfully." << endl;
		}
	}
}

// -------------------------------
//    General Meeting Sign-In
// -------------------------------
void GM_Update()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag, quarter;
	int get_SID, get_birth_day, get_birth_year, token = 0;
	get_GM GM;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	// Open database
	ifstream database;
	database.open("records.txt");

	// Test to see if file has opened
	if (database.is_open())
	{
		cout << "File has successfully been opened!" << endl << endl;	// Verification that file has been opened succesfully
		cin.ignore();	// Ignore previous input to allow for new input.

		GM = get_GM_info();
		int position = GM.quarter.find("_");
		GM.quarter = GM.quarter.substr(position + 1);
		if (GM.quarter == "F")
		{
			GM.quarter = "Fall";
		}
		else if (GM.quarter == "W")
		{
			GM.quarter = "Winter";
		}
		else if (GM.quarter == "S")
		{
			GM.quarter = "Spring";
		}
		else
		{
			cout << "An error has occured";
			GM.quarter = "error";
		}

		do
		{
			// Do while to test for a minimum card input (bounds may need to be changed later)
			do
			{
				token = 0;
				cout << "Please swipe card for member lookup ('cancel' to quit): ";	// Intro message
				getline(cin, search_ID);		// Take in all data form card swipe

				if (search_ID == "cancel")
				{
					search_ID = "%B00000000000000^Emeritus/Papa  ^54894878740000000000000      ?;00000000000000000=000000000000000000000000?";
					break;
				}
				// Used to test length intially. If failed, display message
				if (search_ID.length() < 95)
				{
					cout << "Card read error. Please retry swipe." << endl << endl;	// If executed, the min length was not reached by the card swipe, usually read error
				}
			} while (search_ID.length() < 95);	// Bound check to see if min data entry was reached

			cout << endl << endl << endl << endl << endl;
			size_t pos = search_ID.find(";");
			string place_holder = search_ID.substr(pos + 1);	// Push one (1) position past the semi colon. Will be start of the card number
			search_ID = place_holder.substr(0, 16);	// Take in 16 places from the intial card number

													// Insert spaces at appropriate spots to allow for sub-divide the data that will be compared. It needs to have 4 groups of 4 for the 16 digits.
			search_ID1 = search_ID.substr(0, 4);
			search_ID2 = search_ID.substr(4, 4);
			search_ID3 = search_ID.substr(8, 4);
			search_ID4 = search_ID.substr(12, 4);

			string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
			string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
			int rep_SID, rep_birth_day, rep_birth_year, count = 0;
			// Put data in temp file
			ifstream filein("records.txt"); //File to read from
			ofstream fileout("text.txt"); //Temporary file

			while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
				rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
				rep_S4 >> rep_S5 >> end_tag)
			{
				if ((rep_ID1 == search_ID1) && (rep_ID2 == search_ID2) && (rep_ID3 == search_ID3) && (rep_ID4 == search_ID4))
				{
					token = 1;

					if (GM.together == "rep_F1")
					{
						rep_F1 = "Yes";
					}
					else if (GM.together == "rep_F2")
					{
						rep_F2 = "Yes";
					}
					else if (GM.together == "rep_F3")
					{
						rep_F3 = "Yes";
					}
					else if (GM.together == "rep_F4")
					{
						rep_F4 = "Yes";
					}
					else if (GM.together == "rep_F5")
					{
						rep_F5 = "Yes";
					}
					else if (GM.together == "rep_W1")
					{
						rep_W1 = "Yes";
					}
					else if (GM.together == "rep_W2")
					{
						rep_W2 = "Yes";
					}
					else if (GM.together == "rep_W3")
					{
						rep_W3 = "Yes";
					}
					else if (GM.together == "rep_W4")
					{
						rep_W4 = "Yes";
					}
					else if (GM.together == "rep_W5")
					{
						rep_W5 = "Yes";
					}
					else if (GM.together == "rep_S1")
					{
						rep_S1 = "Yes";
					}
					else if (GM.together == "rep_S2")
					{
						rep_S2 = "Yes";
					}
					else if (GM.together == "rep_S3")
					{
						rep_S3 = "Yes";
					}
					else if (GM.together == "rep_S4")
					{
						rep_S4 = "Yes";
					}
					else if (GM.together == "rep_S5")
					{
						rep_S5 = "Yes";
					}
					else
					{
						cout << "An error has occurred! Please seek data loss immediately!!" << endl << endl;
					}
					// Setup database retrieval for user to easily read.
					cout << "\n\n\n\n\n\n\n\n\n";
					if (rep_F1 == "Yes")
					{
						count++;
					}
					if (rep_F2 == "Yes")
					{
						count++;
					}
					if (rep_F3 == "Yes")
					{
						count++;
					}
					if (rep_F4 == "Yes")
					{
						count++;
					}
					if (rep_F5 == "Yes")
					{
						count++;
					}
					if (rep_W1 == "Yes")
					{
						count++;
					}
					if (rep_W2 == "Yes")
					{
						count++;
					}
					if (rep_W3 == "Yes")
					{
						count++;
					}
					if (rep_W4 == "Yes")
					{
						count++;
					}
					if (rep_W5 == "Yes")
					{
						count++;
					}
					if (rep_S1 == "Yes")
					{
						count++;
					}
					if (rep_S2 == "Yes")
					{
						count++;
					}
					if (rep_S3 == "Yes")
					{
						count++;
					}
					if (rep_S4 == "Yes")
					{
						count++;
					}
					if (rep_S5 == "Yes")
					{
						count++;
					}

					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					if (count == 10)
					{
						cout << endl << endl;
						cout << "\t\t\t*****************************************************************" << endl;
						cout << "\t\t\t*  Congratulations! You are now considered a current member!!!  *" << endl;
						cout << "\t\t\t*****************************************************************" << endl;
					}

					cout << "\n\n\n\n\n\n\n\n\n\n";
					cout << rep_first_name << " " << rep_last_name << " has signed in for General Meeting: " << GM.number << ", this " << GM.quarter << " Quarter." << endl;

					Summer_opportunites(rep_first_name, rep_last_name, rep_SID);
				}

				fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
					" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
					rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
			}

			filein.close();
			fileout.close();

			// Put data in back in original file
			ifstream filein2("text.txt"); //File to read from
			ofstream fileout2("records.txt"); //Temporary file

			string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major, ret_gender;
			string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;
			int ret_SID, ret_birth_day, ret_birth_year;
			while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >> ret_gender >>
				ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
				ret_S4 >> ret_S5 >> end_tag)
			{
				if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4))
				{
					ret_first_name == rep_first_name;
				}
				fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major << " " << ret_gender <<
					" " << ret_F1 << " " << ret_F2 << " " << ret_F3 << " " << ret_F4 << " " << ret_F5 << " " << ret_W1 << " " << ret_W2 << " " <<
					ret_W3 << " " << ret_W4 << " " << ret_W5 << " " << ret_S1 << " " << ret_S2 << " " << ret_S3 << " " << ret_S4 << " " << ret_S5 << " " << end_tag << endl;
			}

			filein2.close();
			fileout2.close();

			// Test if the data is not found in database
			if ((token != 1) && (search_ID != "0000000000000000"))
			{
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nMember doesn't exist." << endl << endl;
			}

			// Close file and verify
			database.close();
			if (!database.is_open())
			{
				cout << "\n\nThe file has successfully closed!" << endl << endl << endl;
			}

		} while (search_ID != "0000000000000000");

		string copy_name;

		cout << "Please enter a name to name the saved copy of the master data: ";
		getline(cin, copy_name);
		copy_name = (copy_name + ".txt");







		string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major, rep_gender;
		string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
		int rep_SID, rep_birth_day, rep_birth_year, count = 0;
		// Put data in temp file
		ifstream filein("records.txt"); //File to read from
		ofstream fileout(copy_name); //Temporary file

		while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >> rep_gender >>
			rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
			rep_S4 >> rep_S5 >> end_tag)
		{
			fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major << " " << rep_gender <<
				" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
				rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
		}

		filein.close();
		fileout.close();
	}
	// Verify that the file has opened successfully.
	else
	{
		cout << "The file has failed to open. Data may be corrupt! Please verify filename and location." << endl;
	}
}

// -------------------------------
//       GM Info Collection
// -------------------------------
get_GM get_GM_info()
{
	char quarter_choice;
	string quarter, number, together;
	int number_choice;
	bool numFail;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\nWelcome to the GM selection menu.";

	do
	{
		Quarters();

		cout << "\n\nPlease select which quarter to sign-in: ";
		cin >> quarter_choice;

		if (isalpha(quarter_choice))
		{
			quarter_choice = toupper(quarter_choice);
			cout << quarter_choice << endl;

			if ((quarter_choice != 'A') && (quarter_choice != 'B') && (quarter_choice != 'C'))
			{
				cout << "You have entered an invalid option, please try again." << endl;
			}
		}
		else
		{
			cout << "You have entereed an incorrect value, please try again.\n";
		}

	} while ((quarter_choice != 'A') && (quarter_choice != 'B') && (quarter_choice != 'C'));

	switch (quarter_choice)
	{
	case 'A':
	{
		quarter = "rep_F";
		break;
	}
	case 'B':
	{
		quarter = "rep_W";
		break;
	}
	case 'C':
	{
		quarter = "rep_S";
		break;
	}
	default:
	{
		cout << "An error has occurred. Please try again." << endl;
		break;
	}
	}


	// Loop to rerun through if user gives invalid choice for SID.
	do
	{
		GM_Numbers();

		cout << "\n\nPlease select the GM number to sign-in: ";
		cin >> number_choice;

		numFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (numFail == true)
		{
			cout << "You entered an invalid option, please enter a valid number!" << endl;
		}
	} while ((numFail == true) || ((number_choice != 1) && (number_choice != 2) && (number_choice != 3) && (number_choice != 4) && (number_choice != 5)));

	switch (number_choice)
	{
	case 1:
	{
		number = "1";
		break;
	}
	case 2:
	{
		number = "2";
		break;
	}
	case 3:
	{
		number = "3";
		break;
	}
	case 4:
	{
		number = "4";
		break;
	}
	case 5:
	{
		number = "5";
		break;
	}
	default:
	{
		cout << "An error has occured. Please try again." << endl;
	}
	}

	together = (quarter + number);

	return get_GM{ quarter, number, together };
}

// -------------------------------
//        Display Quarters
// -------------------------------
void Quarters()
{
	cout << endl << endl << endl << endl;
	cout << "\t\t\t-----------------------------" << endl;
	cout << "\t\t\t      Quarter Selection" << endl;
	cout << "\t\t\t-----------------------------" << endl << endl << endl;
	cout << "\t\t\tA) Fall" << endl;
	cout << "\t\t\tB) Winter" << endl;
	cout << "\t\t\tC) Spring" << endl;
}

// -------------------------------
//      GM Number information
// -------------------------------
void GM_Numbers()
{
	cout << endl << endl << endl << endl;
	cout << "\t\t\t-----------------------------" << endl;
	cout << "\t\t\t       Number Selection" << endl;
	cout << "\t\t\t-----------------------------" << endl << endl << endl;
	cout << "\t\t\t1) 1" << endl;
	cout << "\t\t\t2) 2" << endl;
	cout << "\t\t\t3) 3" << endl;
	cout << "\t\t\t4) 4" << endl;
	cout << "\t\t\t5) 5" << endl;
}

// -------------------------------
//    Individual GM information
// -------------------------------
void Individual_GM_data()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_email, get_gender;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year, count = 0, token = 0;;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	// Open database
	ifstream database;
	database.open("records.txt");

	// Test to see if file has opened
	if (database.is_open())
	{
		cout << "File has successfully been opened!" << endl << endl;	// Verification that file has been opened succesfully
		cin.ignore();	// Ignore previous input to allow for new input.
						// Do while to test for a minimum card input (bounds may need to be changed later)
		do
		{
			cout << "Please swipe card for member lookup: ";	// Intro message
			getline(cin, search_ID);		// Take in all data form card swipe

											// Used to test length intially. If failed, display message
			if (search_ID.length() < 95)
			{
				cout << "Card read error. Please retry swipe." << endl << endl;	// If executed, the min length was not reached by the card swipe, usually read error
			}
		} while (search_ID.length() < 95);	// Bound check to see if min data entry was reached

		cout << endl << endl << endl << endl << endl;
		size_t pos = search_ID.find(";");
		string place_holder = search_ID.substr(pos + 1);	// Push one (1) position past the semi colon. Will be start of the card number
		search_ID = place_holder.substr(0, 16);	// Take in 16 places from the intial card number

												// Insert spaces at appropriate spots to allow for sub-divide the data that will be compared. It needs to have 4 groups of 4 for the 16 digits.
		search_ID1 = search_ID.substr(0, 4);
		search_ID2 = search_ID.substr(4, 4);
		search_ID3 = search_ID.substr(8, 4);
		search_ID4 = search_ID.substr(12, 4);


		// Data retrieveal from database to display for user.
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			// To replace major '_' with spaces
			string altered_major = get_major;
			int position = altered_major.find("_");
			while (position != string::npos)
			{
				altered_major.replace(position, 1, " ");
				position = altered_major.find("_", position + 1);
			}

			// If card number matches
			if ((search_ID1 == get_ID1) && (search_ID2 == get_ID2) && (search_ID3 == get_ID3) && (search_ID4 == get_ID4))
			{
				if (get_F1 == "Yes")
				{
					count++;
				}
				if (get_F2 == "Yes")
				{
					count++;
				}
				if (get_F3 == "Yes")
				{
					count++;
				}
				if (get_F4 == "Yes")
				{
					count++;
				}
				if (get_F5 == "Yes")
				{
					count++;
				}
				if (get_W1 == "Yes")
				{
					count++;
				}
				if (get_W2 == "Yes")
				{
					count++;
				}
				if (get_W3 == "Yes")
				{
					count++;
				}
				if (get_W4 == "Yes")
				{
					count++;
				}
				if (get_W5 == "Yes")
				{
					count++;
				}
				if (get_S1 == "Yes")
				{
					count++;
				}
				if (get_S2 == "Yes")
				{
					count++;
				}
				if (get_S3 == "Yes")
				{
					count++;
				}
				if (get_S4 == "Yes")
				{
					count++;
				}
				if (get_S5 == "Yes")
				{
					count++;
				}

				get_last_name.erase(remove(get_last_name.begin(), get_last_name.end(), ','), get_last_name.end());
				// Setup database retrieval for user to easily read.
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				cout << "************************" << endl;
				cout << "     Member GM Data" << endl;
				cout << "************************" << endl;
				cout << get_first_name << " " << get_last_name << "'s personal General meeting data breakdown." << endl << endl;
				cout << "\tFall" << endl;
				cout << "Attended General Meeting 1: " << get_F1 << endl;
				cout << "Attended General Meeting 2: " << get_F2 << endl;
				cout << "Attended General Meeting 3: " << get_F3 << endl;
				cout << "Attended General Meeting 4: " << get_F4 << endl;
				cout << "Attended General Meeting 5: " << get_F5 << endl;
				cout << endl << endl;
				cout << "\tWinter" << endl;
				cout << "Attended General Meeting 1: " << get_W1 << endl;
				cout << "Attended General Meeting 2: " << get_W2 << endl;
				cout << "Attended General Meeting 3: " << get_W3 << endl;
				cout << "Attended General Meeting 4: " << get_W4 << endl;
				cout << "Attended General Meeting 5: " << get_W5 << endl;
				cout << endl << endl;
				cout << "\tSpring" << endl;
				cout << "Attended General Meeting 1: " << get_S1 << endl;
				cout << "Attended General Meeting 2: " << get_S2 << endl;
				cout << "Attended General Meeting 3: " << get_S3 << endl;
				cout << "Attended General Meeting 4: " << get_S4 << endl;
				cout << "Attended General Meeting 5: " << get_S5 << endl;
				//cout << endl << endl;

				token = 1;
			}

		}

		// Test if the data is not found in database
		if (token != 1)
		{
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nData cannot be found!" << endl << endl;
		}

		// Close file and verify
		database.close();
		if (!database.is_open())
		{
			cout << "\nThe file has successfully closed!" << endl;
		}
	}
	// Verify that the file has opened successfully.
	else
	{
		cout << "The file has failed to open. Data may be corrupt! Please verify filename and location." << endl;
	}
}

// -------------------------------
//         Stats Menu code
// -------------------------------
void Stats()
{
	char choice;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t**************************************" << endl;
	cout << "\t\t\t    Welcome to the Statistics Page" << endl;
	cout << "\t\t\t**************************************" << endl << endl << endl;

	Stats_Menu();

	do
	{
		cout << "Please select an option: ";
		cin >> choice;

		if (isalpha(choice))
		{
			choice = toupper(choice);

			if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E')
			{
				cout << "You entered an incorrect option, please try again." << endl;
			}
		}
		else
		{
			cout << "You have entered an incorrect value, please try again." << endl;
		}
	} while (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E');

	switch (choice)
	{
	case 'A':
	{
		stats_birthdays();
		break;
	}
	case 'B':
	{
		stats_attendance_records();
		break;
	}
	case 'C':
	{
		stats_majors();
		break;
	}
	case 'D':
	{
		stats_sign_ins();
		break;
	}
	case 'E': get_individual_GM_members();
		break;
	default:
	{
		cout << "An critical error has occurred. Please check for data loss!" << endl << endl;
		break;
	}
	}
}

// -------------------------------
//        Stats Menu Display
// -------------------------------
void Stats_Menu()
{
	cout << "\t\t\tA) Birthday Months" << endl;	// Break up into months
	cout << "\t\t\tB) Member's Attendance records" << endl;	// Break up into current members vs. non-current members
	cout << "\t\t\tC) Majors" << endl;	// Break up into BCOE majors (individually) and other majors (collectively)
	cout << "\t\t\tD) GM Sign-Ins" << endl;	// Break up into every GM and weigh total members vs. signed in (display current info on each)
											// Give Menu for breakdown by major, breakdown by birth month and breakdown by male and female
	cout << "\t\t\tE) Individual GM member Sign-In" << endl << endl << endl;
}

// -------------------------------
//         Gender Selection
// -------------------------------
string get_Gender()
{
	string gender;
	char option;

	cout << endl << endl << endl;
	cout << "\t\t\tA) Male" << endl;
	cout << "\t\t\tB) Female" << endl;
	cout << endl << endl << endl;

	cout << "Please select your gender: ";
	cin >> option;

	if (isalpha(option))
	{
		option = toupper(option);

		if (option != 'A' && option != 'B')
		{
			cout << "Invalid choice. Please, try again." << endl << endl;
			gender = get_Gender();
		}
	}
	else
	{
		cout << "You entered an invalid entry. Please, try again." << endl << endl;
		gender = get_Gender();
	}

	switch (option)
	{
	case 'A':
	{
		gender = "Male";
		return gender;		// Ignores other errors prior
		break;
	}
	case 'B':
	{
		gender = "Female";
		return gender;		// Ignores other errors prior
		break;
	}
	default:
	{
		cout << "An error has occurred! Check for data loss immediately." << endl;
		break;
	}
	}
}

// -------------------------------
//         Birthday Stats
// -------------------------------
void stats_birthdays()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_gender, get_email;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year, count = 0, pass = 0;
	string month, send_month;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\\n\n\n\n\n\n\n";
	cout << "\t\t\t*************************************************" << endl;
	cout << "\t\t\t   Welcome to the Birthdays Statistitics page" << endl;
	cout << "\t\t\t*************************************************" << endl << endl << endl;

	month = stats_pick_month();
	cout << endl << endl;

	// Open database
	ifstream database;
	database.open("records.txt");

	// Test to see if file has opened
	if (database.is_open())
	{
		cout << "File has successfully been opened!" << endl << endl;	// Verification that file has been opened succesfully
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nAll the members who have birthdays in the month of " << month << " are as follows: " << endl << endl;
		// Data retrieval from database to display for user.
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			if (get_birth_month == month)
			{
				cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " was born on day: " << get_birth_day << " in " << get_birth_year << "." << endl;
				count++;
			}

			if (month == "All")
			{
				break;
			}
		}

		if (month == "All")
		{
			// January
			cout << "-------------" << endl;
			cout << "   January" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "January";
			get_all_months(send_month);
			pass += 1;
			// February
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "  February" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "February";
			get_all_months(send_month);
			pass += 1;
			// March
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "    March" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "March";
			get_all_months(send_month);
			pass += 1;
			// April
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "    April" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "April";
			get_all_months(send_month);
			pass += 1;
			// May
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "     May" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "May";
			get_all_months(send_month);
			pass += 1;
			// June
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "    June" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "June";
			get_all_months(send_month);
			pass += 1;
			// July
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "    July" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "July";
			get_all_months(send_month);
			pass += 1;
			// August
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "    August" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "August";
			get_all_months(send_month);
			pass += 1;
			// September
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "  September" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "September";
			get_all_months(send_month);
			pass += 1;
			// October
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "   October" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "October";
			get_all_months(send_month);
			pass += 1;
			// November
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "   November" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "November";
			get_all_months(send_month);
			pass += 1;
			// December
			cout << endl << endl << endl;
			cout << "-------------" << endl;
			cout << "   December" << endl;
			cout << "-------------" << endl;
			cout << endl << endl;
			send_month = "December";
			get_all_months(send_month);
			pass += 1;
		}

		// Close file and verify
		database.close();
		if (!database.is_open())
		{
			cout << "\n\nThe file has successfully closed!" << endl << endl << endl;
		}
	}
	// Verify that the file has opened successfully.
	else
	{
		cout << "The file has failed to open. Data may be corrupt! Please verify filename and location." << endl;
	}
}

// -------------------------------
//     Attendance Record Stats
// -------------------------------
void stats_attendance_records()
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_gender, get_email;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year, count = 0, token = 0, count2 = 0, people = 0;
	string month;
	double percent, current_members = 0.0, non_current_members = 0.0, total = 0.0;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	// Open database
	ifstream database;
	database.open("records.txt");

	// Test to see if file has opened
	if (database.is_open())
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "__________________________" << endl << endl;
		cout << "      Current Members" << endl;
		cout << "__________________________" << endl << endl;
		// Current Members
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			token = 0;	// Reset the count for next lookup

			if (get_F1 == "Yes")
			{
				token++;
			}
			if (get_F2 == "Yes")
			{
				token++;
			}
			if (get_F3 == "Yes")
			{
				token++;
			}
			if (get_F4 == "Yes")
			{
				token++;
			}
			if (get_F5 == "Yes")
			{
				token++;
			}
			if (get_W1 == "Yes")
			{
				token++;
			}
			if (get_W2 == "Yes")
			{
				token++;
			}
			if (get_W3 == "Yes")
			{
				token++;
			}
			if (get_W4 == "Yes")
			{
				token++;
			}
			if (get_W5 == "Yes")
			{
				token++;
			}
			if (get_S1 == "Yes")
			{
				token++;
			}
			if (get_S2 == "Yes")
			{
				token++;
			}
			if (get_S3 == "Yes")
			{
				token++;
			}
			if (get_S4 == "Yes")
			{
				token++;
			}
			if (get_S5 == "Yes")
			{
				token++;
			}

			if (token >= 10)
			{
				cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " has attended " << token << " General Meetings." << endl;
				count++;
				people = 1;
				current_members += 1;
			}

		}

		if (people == 0)
		{
			cout << "**********************" << endl;
			cout << "*   No data found!   *" << endl;
			cout << "**********************" << endl << endl << endl;
		}

		database.close();
	}

	ifstream database2;
	database2.open("records.txt");

	if (database2.is_open())
	{
		people = 0;	// Reset flag for non-members
		cout << "\n\n\n__________________________" << endl << endl;
		cout << "   Non-Current Members" << endl;
		cout << "__________________________" << endl << endl;		// Non-current members
		while (database2 >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			token = 0;	// Reset the count for next lookup

			if (get_F1 == "Yes")
			{
				token++;
			}
			if (get_F2 == "Yes")
			{
				token++;
			}
			if (get_F3 == "Yes")
			{
				token++;
			}
			if (get_F4 == "Yes")
			{
				token++;
			}
			if (get_F5 == "Yes")
			{
				token++;
			}
			if (get_W1 == "Yes")
			{
				token++;
			}
			if (get_W2 == "Yes")
			{
				token++;
			}
			if (get_W3 == "Yes")
			{
				token++;
			}
			if (get_W4 == "Yes")
			{
				token++;
			}
			if (get_W5 == "Yes")
			{
				token++;
			}
			if (get_S1 == "Yes")
			{
				token++;
			}
			if (get_S2 == "Yes")
			{
				token++;
			}
			if (get_S3 == "Yes")
			{
				token++;
			}
			if (get_S4 == "Yes")
			{
				token++;
			}
			if (get_S5 == "Yes")
			{
				token++;
			}

			if (token < 10)
			{
				cout << (count2 + 1) << ") " << get_first_name << " " << get_last_name << " has attended " << token << " General Meeting(s)." << endl;
				count2++;
				people = 1;
				non_current_members += 1;
			}
		}

		if (people == 0)
		{
			cout << "**********************" << endl;
			cout << "*   No data found!   *" << endl;
			cout << "**********************" << endl << endl << endl;
		}

		database2.close();

		// Calculations based on received data above
		total = (current_members + non_current_members);
		percent = ((current_members / total) * 100);
		cout << endl << endl << endl << "Our calculations show from our data that, out of the " << total << " data values we have, " << percent << "% are current members in SHPE @ UCR, based off only General Meeting, current member requirements." << endl << endl;
	}
	// Verify that the file has opened successfully.
	else
	{
		cout << "The file has failed to open. Data may be corrupt! Please verify filename and location." << endl;
	}

	cout << endl << endl << endl << endl << endl << endl;
}

// -------------------------------
//       Major Breadown Stats
// -------------------------------
void stats_majors()
{
	double Bio = 0.0, ChE = 0.0, CEN = 0.0, CS = 0.0, CSwB = 0.0, EE = 0.0, EnvE = 0.0, MSE = 0.0, MechE = 0.0, others = 0.0;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t-----------------------------------" << endl;
	cout << "\t\t\t\t\t    Statistical Data by Majors" << endl;
	cout << "\t\t\t\t\t-----------------------------------" << endl << endl;

	// Get data all in variables by major, calculations after
	ifstream data;
	data.open("records.txt");

	if (data.is_open())
	{
		string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
		string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_gender, get_email;
		string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
		int get_SID, get_birth_day, get_birth_year, count = 0;

		// Data retrieveal from database to display for user.
		while (data >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			if (get_major == "Bioengineering")
			{
				Bio += 1;
			}
			else if (get_major == "Chemical_Engineering")
			{
				ChE += 1;
			}
			else if (get_major == "Computer_Engineering")
			{
				CEN += 1;
			}
			else if (get_major == "Computer_Science")
			{
				CS += 1;
			}
			else if (get_major == "Computer_Science_with_Business_Applications")
			{
				CSwB += 1;
			}
			else if (get_major == "Electrical_Engineering")
			{
				EE += 1;
			}
			else if (get_major == "Environmental_Engineering")
			{
				EnvE += 1;
			}
			else if (get_major == "Materials_Science_and_Engineering")
			{
				MSE += 1;
			}
			else if (get_major == "Mechanical_Engineering")
			{
				MechE += 1;
			}
			else
			{
				others += 1;
			}
		}

		// Perform Calculations and display info
		double total = (Bio + ChE + CEN + CS + CSwB + EE + EnvE + MSE + MechE + others);
		cout << "Data was calculated using the " << total << " data values we have." << endl;

		// Bioengineering
		cout << "_______________________________" << endl << endl;
		cout << "         Bioengineering" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << Bio << " students are in this major. This is a total of " << ((Bio / total) * 100) << "% of all students on file." << endl << endl;

		// Chemical Engineering
		cout << "_______________________________" << endl << endl;
		cout << "     Chemical Engineering" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << ChE << " students are in this major. This is a total of " << ((ChE / total) * 100) << "% of all students on file." << endl << endl;

		// Computer Engineering
		cout << "_______________________________" << endl << endl;
		cout << "     Computer Engineering" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << CEN << " students are in this major. This is a total of " << ((CEN / total) * 100) << "% of all students on file." << endl << endl;

		// Computer Science
		cout << "_______________________________" << endl << endl;
		cout << "        Computer Science" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << CS << " students are in this major. This is a total of " << ((CS / total) * 100) << "% of all students on file." << endl << endl;

		// Computer Science with Business Applications
		cout << "_______________________________" << endl << endl;
		cout << "    Computer Science w/ BA" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << CSwB << " students are in this major. This is a total of " << ((CSwB / total) * 100) << "% of all students on file." << endl << endl;

		// Electrical Engineering
		cout << "_______________________________" << endl << endl;
		cout << "     Electrical Engineering" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << EE << " students are in this major. This is a total of " << ((EE / total) * 100) << "% of all students on file." << endl << endl;

		// Enviornmental Engineering
		cout << "_______________________________" << endl << endl;
		cout << "   Enviornmental Engineering" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << EnvE << " students are in this major. This is a total of " << ((EnvE / total) * 100) << "% of all students on file." << endl << endl;

		// Material Science and Engineering
		cout << "_______________________________" << endl << endl;
		cout << "   Materials Science and Eng." << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << MSE << " students are in this major. This is a total of " << ((MSE / total) * 100) << "% of all students on file." << endl << endl;

		// Mechanical Engineering
		cout << "_______________________________" << endl << endl;
		cout << "     Mechanical Engineering" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << MechE << " students are in this major. This is a total of " << ((MechE / total) * 100) << "% of all students on file." << endl << endl;

		// Other majors
		cout << "_______________________________" << endl << endl;
		cout << "          Other Majors" << endl;
		cout << "_______________________________" << endl;
		cout << "Our records show that " << others << " students are in other majors outside of BCOE. This is a total of " << ((others / total) * 100) << "% of all students on file." << endl;

		// Close file
		data.close();
	}
}

// -------------------------------
//      Diverse Breadown Stats
// -------------------------------
void stats_sign_ins()
{
	double Bio = 0.0, ChE = 0.0, CEN = 0.0, CS = 0.0, CSwB = 0.0, EE = 0.0, EnvE = 0.0, MSE = 0.0, MechE = 0.0, others = 0.0;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t------------------------------------------" << endl;
	cout << "\t\t\t\t\t  Statistical Data from General Meetings" << endl;
	cout << "\t\t\t\t\t------------------------------------------" << endl << endl;

	// Get data all in variables by major, calculations after
	ifstream data;
	data.open("records.txt");

	if (data.is_open())
	{
		string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
		string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_gender, get_email;
		string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
		int get_SID, get_birth_day, get_birth_year, count = 0;
		get_GM GM;
		double total_data = 0.0, attended = 0.0, Male = 0, Female = 0, Jan = 0.0, Feb = 0.0, Mar = 0.0, Apr = 0.0, May = 0.0, Jun = 0.0, Jul = 0.0, Aug = 0.0, Sep = 0.0, Oct = 0.0, Nov = 0.0, Dec = 0.0;

		// Get which GM to lookup
		GM = get_GM_info();

		// Data retrieval from database to display for user.
		while (data >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
			rep_S4 >> rep_S5 >> end_tag)
		{
			if (GM.together == "rep_F1")
			{
				if (rep_F1 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_F2")
			{
				if (rep_F2 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_F3")
			{
				if (rep_F3 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_F4")
			{
				if (rep_F4 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_F5")
			{
				if (rep_F5 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_W1")
			{
				if (rep_W1 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_W2")
			{
				if (rep_W2 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_W3")
			{
				if (rep_W3 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_W4")
			{
				if (rep_W4 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_W5")
			{
				if (rep_W5 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_S1")
			{
				if (rep_S1 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_S2")
			{
				if (rep_S2 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_S3")
			{
				if (rep_S3 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_S4")
			{
				if (rep_S4 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else if (GM.together == "rep_S5")
			{
				if (rep_S5 == "Yes")
				{
					// Get Major Data
					if (get_major == "Bioengineering")
					{
						Bio += 1;
					}
					else if (get_major == "Chemical_Engineering")
					{
						ChE += 1;
					}
					else if (get_major == "Computer_Engineering")
					{
						CEN += 1;
					}
					else if (get_major == "Computer_Science")
					{
						CS += 1;
					}
					else if (get_major == "Computer_Science_with_Business_Applications")
					{
						CSwB += 1;
					}
					else if (get_major == "Electrical_Engineering")
					{
						EE += 1;
					}
					else if (get_major == "Enviornmental_Engineering")
					{
						EnvE += 1;
					}
					else if (get_major == "Materials_Science_and_Engineering")
					{
						MSE += 1;
					}
					else if (get_major == "Mechanical_Engineering")
					{
						MechE += 1;
					}
					else
					{
						others += 1;
					}

					// Get Gender Data
					if (get_gender == "Male")
					{
						Male += 1;
					}
					else
					{
						Female += 1;
					}

					// Get Month Data
					if (get_birth_month == "January")
					{
						Jan += 1;
					}
					else if (get_birth_month == "February")
					{
						Feb += 1;
					}
					else if (get_birth_month == "March")
					{
						Mar += 1;
					}
					else if (get_birth_month == "April")
					{
						Apr += 1;
					}
					else if (get_birth_month == "May")
					{
						May += 1;
					}
					else if (get_birth_month == "June")
					{
						Jun += 1;
					}
					else if (get_birth_month == "July")
					{
						Jul += 1;
					}
					else if (get_birth_month == "August")
					{
						Aug += 1;
					}
					else if (get_birth_month == "September")
					{
						Sep += 1;
					}
					else if (get_birth_month == "October")
					{
						Oct += 1;
					}
					else if (get_birth_month == "November")
					{
						Nov += 1;
					}
					else if (get_birth_month == "December")
					{
						Dec += 1;
					}
					// Add one if member was there
					attended += 1;
				}
				total_data += 1;	// Add to total count of all data
			}
			else
			{
				cout << "An error has occurred! Please seek data loss immediately!!" << endl << endl;
			}
		}

		// Convert to quarter name
		string quarter;
		if (GM.quarter == "rep_F")
		{
			quarter = "Fall";
		}
		else if (GM.quarter == "rep_W")
		{
			quarter = "Winter";
		}
		else if (GM.quarter == "rep_S")
		{
			quarter = "Spring";
		}

		// Perform Calculations and display info
		double total_majors = (Bio + ChE + CEN + CS + CSwB + EE + EnvE + MSE + MechE + others);
		double total_genders = (Male + Female);
		double total_birthdays = (Jan + Feb + Mar + Apr + May + Jun + Jul + Aug + Sep + Oct + Nov + Dec);

		// Display all data
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "Data for General Meeting " << GM.number << " in the " << quarter << " quarter." << endl << endl << endl << endl;
		cout << "_______________________" << endl << endl;
		cout << "     Gender Stats" << endl;
		cout << "_______________________" << endl << endl << endl;
		cout << "Females in attendance: " << Female << "\t" << ((Female / total_genders) * 100) << "%" << endl;
		cout << "Males in attendance: " << Male << "\t\t" << ((Male / total_genders) * 100) << "%" << endl << endl;
		cout << "Females percentage in total: " << ((Female / total_data) * 100) << "%" << endl;
		cout << "Males percentage in total: " << ((Male / total_data) * 100) << "%" << endl << endl;
		cout << "There are a total of " << total_data << " students in the database." << endl << endl << endl << endl << endl;
		cout << "_______________________" << endl << endl;
		cout << " Birthday Month Stats" << endl;
		cout << "_______________________" << endl << endl << endl;
		cout << "January: " << Jan << "\t\t" << ((Jan / total_birthdays) * 100) << "%" << endl;
		cout << "February: " << Feb << "\t\t" << ((Feb / total_birthdays) * 100) << "%" << endl;
		cout << "March: " << Mar << "\t\t" << ((Mar / total_birthdays) * 100) << "%" << endl;
		cout << "April: " << Apr << "\t\t" << ((Apr / total_birthdays) * 100) << "%" << endl;
		cout << "May: " << May << "\t\t\t" << ((May / total_birthdays) * 100) << "%" << endl;
		cout << "June: " << Jun << "\t\t\t" << ((Jun / total_birthdays) * 100) << "%" << endl;
		cout << "July: " << Jul << "\t\t\t" << ((Jul / total_birthdays) * 100) << "%" << endl;
		cout << "August: " << Aug << "\t\t" << ((Aug / total_birthdays) * 100) << "%" << endl;
		cout << "September: " << Sep << "\t\t" << ((Sep / total_birthdays) * 100) << "%" << endl;
		cout << "October: " << Oct << "\t\t" << ((Oct / total_birthdays) * 100) << "%" << endl;
		cout << "November: " << Nov << "\t\t" << ((Nov / total_birthdays) * 100) << "%" << endl;
		cout << "December: " << Dec << "\t\t" << ((Dec / total_birthdays) * 100) << "%" << endl << endl << endl << endl << endl;
		cout << "_______________________" << endl << endl;
		cout << "      Major Stats" << endl;
		cout << "_______________________" << endl << endl << endl;
		cout << "Bioengineering: " << Bio << "\t\t\t\t\t" << ((Bio / total_majors) * 100) << "%" << endl;
		cout << "Chemical Engineering: " << ChE << "\t\t\t\t\t" << ((ChE / total_majors) * 100) << "%" << endl;
		cout << "Computer Engineering: " << CEN << "\t\t\t\t\t" << ((CEN / total_majors) * 100) << "%" << endl;
		cout << "Computer Science: " << CS << "\t\t\t\t\t" << ((CS / total_majors) * 100) << "%" << endl;
		cout << "Computer Science with Business Applications: " << CSwB << "\t\t" << ((CSwB / total_majors) * 100) << "%" << endl;
		cout << "Electrical Engineering: " << EE << "\t\t\t\t" << ((EE / total_majors) * 100) << "%" << endl;
		cout << "Enviornmental Engineering: " << EnvE << "\t\t\t\t" << ((EnvE / total_majors) * 100) << "%" << endl;
		cout << "Materials Science and Engineering: " << MSE << "\t\t\t" << ((MSE / total_majors) * 100) << "%" << endl;
		cout << "Mechanical Engineering: " << MechE << "\t\t\t\t" << ((MechE / total_majors) * 100) << "%" << endl;
		cout << "Other Majors outside of BCOE: " << others << "\t\t\t\t" << ((others / total_majors) * 100) << "%" << endl << endl;
		// Close file
		data.close();
		cout << endl << endl << endl << endl;
	}
}

// -------------------------------
//      Month Stats Selection
// -------------------------------
string stats_pick_month()
{
	string month;
	bool numFail;
	int choice;

	// Loop to have user select from options of months and to rerun if choice is invalid.
	do
	{
		Months();
		cout << "Please select the month in which you wish to view (Type '13' if you want view the entire year): ";
		cin >> choice;

		numFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (numFail == true)
		{
			cout << "You entered an invalid option, please enter a valid number!" << endl;
		}
	} while ((numFail == true) || (choice < 1) || (choice > 13));

	// Switch statement to run through if user choices are all valid and also returns selections in a struct to be processed.
	switch (choice)
	{
	case 1:
	{
		cout << "\n\nChoice accepted. You picked January." << endl;
		month = "January";
		return month;
		break;
	}
	case 2:
	{
		cout << "\n\nChoice accepted. You picked February." << endl;
		month = "February";
		return month;
		break;
	}
	case 3:
	{
		cout << "\n\nChoice accepted. You picked March." << endl;
		month = "March";
		return month;
		break;
	}
	case 4:
	{
		cout << "\n\nChoice accepted. You picked April." << endl;
		month = "April";
		return month;
		break;
	}
	case 5:
	{
		cout << "\n\nChoice accepted. You picked May." << endl;
		month = "May";
		return month;
		break;
	}
	case 6:
	{
		cout << "\n\nChoice accepted. You picked June." << endl;
		month = "June";
		return month;
		break;
	}
	case 7:
	{
		cout << "\n\nChoice accepted. You picked July." << endl;
		month = "July";
		return month;
		break;
	}
	case 8:
	{
		cout << "\n\nChoice accepted. You picked August." << endl;
		month = "August";
		return month;
		break;
	}
	case 9:
	{
		cout << "\n\nChoice accepted. You picked Septmeber." << endl;
		month = "September";
		return month;
		break;
	}
	case 10:
	{
		cout << "\n\nChoice accepted. You picked October." << endl;
		month = "October";
		return month;
		break;
	}
	case 11:
	{
		cout << "\n\nChoice accepted. You picked November." << endl;
		month = "November";
		return month;
		break;
	}
	case 12:
	{
		cout << "\n\nChoice accepted. You picked December." << endl;
		month = "December";
		return month;
		break;
	}
	case 13:
	{
		cout << "\n\nChoice accepted. You picked to view the year." << endl;
		month = "All";
		return month;
		break;
	}
	default:
	{
		cout << "An error has occured. Try again.";
		break;
	}
	}
}

// -------------------------------
//        All Month Display
// -------------------------------
void get_all_months(string send_month)
{
	string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_gender, get_email;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year, count = 0, token = 0;
	string month;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	// Open database
	ifstream database;
	database.open("records.txt");

	// Test to see if file has opened
	if (database.is_open())
	{
		//cout << "File has successfully been opened!" << endl << endl;	// Verification that file has been opened succesfully
		//cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nAll the members who have birthdays in the month of " << month << " are as follows: " << endl << endl;
		// Data retrieval from database to display for user.
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >>
			get_S4 >> get_S5 >> end_tag)
		{
			if (get_birth_month == send_month)
			{
				cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " was born on day: " << get_birth_day << " in " << get_birth_year << "." << endl;
				count++;
				token = 1;
			}
		}

		if (token != 1)
		{
			cout << "\t******************" << endl;
			cout << "\t*  No birthdays  *" << endl;
			cout << "\t******************" << endl;
		}

		database.close();
	}
	// Verify that the file has opened successfully.
	else
	{
		cout << "The file has failed to open. Data may be corrupt! Please verify filename and location." << endl;
	}
}

// -------------------------------
//       Password Protection
// -------------------------------
int Password()
{
	int authorized = 0;
	string password;

	/*
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t*************************************************************************************************************************************" << endl;
	cout << "\t\t\t\t*************************************************************************************************************************************" << endl;
	cout << "\t\t\t\t****---------***-*******-***---------***---------******----------------*********-***********-***-------------***------------*********" << endl;
	cout << "\t\t\t\t****-***********-*******-***-*******-***-**************-**************-*********-***********-***-***************-**********-*********" << endl;
	cout << "\t\t\t\t****-***********-*******-***-*******-***-**************-***-------****-*********-***********-***-***************-**********-*********" << endl;
	cout << "\t\t\t\t****---------***---------***---------***------*********-***-*****-****-*********-***********-***-***************----------***********" << endl;
	cout << "\t\t\t\t************-***-*******-***-***********-**************-***-******-***-*********-***********-***-***************---******************" << endl;
	cout << "\t\t\t\t************-***-*******-***-***********-**************-***------------*********-***********-***-***************-****-***************" << endl;
	cout << "\t\t\t\t************-***-*******-***-***********-**************-************************-***********-***-***************-*******-************" << endl;
	cout << "\t\t\t\t****---------***-*******-***-***********---------******----------------------***-------------***-------------***-**********-*********" << endl;
	cout << "\t\t\t\t*************************************************************************************************************************************" << endl;
	cout << "\t\t\t\t*************************************************************************************************************************************" << endl;
	*/

	cout << endl << endl;
	cout << "\t\t\t\t\t\t    *********   *       *   *********   *********      ****************         *           *   *************   ************         " << endl;
	cout << "\t\t\t\t\t\t    *           *       *   *       *   *              *              *         *           *   *               *          *         " << endl;
	cout << "\t\t\t\t\t\t    *           *       *   *       *   *              *   *******    *         *           *   *               *          *         " << endl;
	cout << "\t\t\t\t\t\t    *********   *       *   *********   ******         *   *     *    *         *           *   *               **********           " << endl;
	cout << "\t\t\t\t\t\t            *   *********   *           *              *   *      *   *         *           *   *               ***                  " << endl;
	cout << "\t\t\t\t\t\t            *   *       *   *           *              *   ************         *           *   *               *    *               " << endl;
	cout << "\t\t\t\t\t\t            *   *       *   *           *              *                        *           *   *               *       *            " << endl;
	cout << "\t\t\t\t\t\t    *********   *       *   *           *********      **********************   *************   *************   *          *         " << endl << endl << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	cout << "You are entering a program that contains sensitive data that shall not be manipulated by non-authorized users." << endl << endl;
	cout << "Please enter the password to continue: ";
	getline(cin, password);

	if (password == "sHP3 @ UCR")
	{
		authorized = 1;
	}

	return authorized;
}

// -------------------------------
//        GM member filter
// -------------------------------
void get_individual_GM_members()
{
	ifstream database;
	database.open("records.txt");

	if (database.is_open())
	{
		string search_ID, search_ID1, search_ID2, search_ID3, search_ID4, end_tag;
		string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_gender, get_email;
		string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
		int get_SID, get_birth_day, get_birth_year, count = 0, token = 0, count2 = 0;
		string month;
		string GM_quarter, GM_number;
		get_GM GM_info;

		GM_info = get_GM_info();
		//cout << "data: " << GM_info.together << endl;
		cout << endl;
		system("CLS");

		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> get_gender >>
			get_F1 >> get_F2 >> get_F3 >> get_F4 >> get_F5 >> get_W1 >> get_W2 >> get_W3 >> get_W4 >> get_W5 >> get_S1 >> get_S2 >> get_S3 >> get_S4 >> get_S5 >> end_tag)
		{
			if (GM_info.together == "rep_F1")
			{
				if (get_F1 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_F2")
			{
				if (get_F2 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_F3")
			{
				if (get_F3 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_F4")
			{
				if (get_F4 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_F5")
			{
				if (get_F5 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_W1")
			{
				if (get_W1 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_W2")
			{
				if (get_W2 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_W3")
			{
				if (get_W3 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data for this GM." << endl;
					break;
				}
			}
			else if (GM_info.together == "rep_W4")
			{
				if (get_W4 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_W5")
			{
				if (get_W5 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_S1")
			{
				if (get_S1 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_S2")
			{
				if (get_S2 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_S3")
			{
				if (get_S3 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_S4")
			{
				if (get_S4 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}
			else if (GM_info.together == "rep_S5")
			{
				if (get_S5 == "Yes")
				{
					cout << (count + 1) << ") " << get_first_name << " " << get_last_name << " " << get_email << endl;
					count++;
				}

				if (count == 0)
				{
					cout << "There is no data that for this GM.";
					break;
				}
			}

			count2++;
		}
		cout << "\n\nThere are a total of " << count << ", out of " << count2 << " members, who attended General Meeting " << GM_info.number << "." << endl;
		cout << endl << endl << endl << endl << endl;
	}
	else
	{
		cout << "Data has failed to load properly. Check data immediately for errors!!!" << endl;
	}
}

void Summer_opportunites(string fn, string ln, int SID)
{
	char choice;
	string place;

	system("pause");
	system("CLS");

	// Check file for previous entry
	ifstream file;
	file.open("location.txt");

	int ret_SID;
	string ret_fn, ret_ln, ret_opp;
	bool flag = false;

	if (file.is_open())
	{
		// Check for previous entry
		while (file >> ret_SID >> ret_fn >> ret_ln >> ret_opp)
		{
			if (ret_SID == SID)
			{
				cout << "Data presented. No further information required." << endl << endl;
				flag = true;
				choice = 'n';
				break;
			}

			//cout << "Ret_SID: " << ret_SID << endl << "SID: " << SID << endl;
		}
	}

	file.close();

	if (flag == false)
	{
		do
		{
			cout << fn << ", do you have a job/internship lined up for this summer [y/n]? ";
			cin >> choice;
			choice = tolower(choice);
		} while (choice != 'y' && choice != 'n');
	}

	cin.ignore();

	switch (choice)
	{
		case 'y':
		{
			cout << "That is fantastic!!!\nPlease enter the name of the place you got accepted to: "; 
			getline(cin, place);

			// To replace location ' ' with '_'
			string altered_place = place;
			int position = altered_place.find(" ");
			while (position != string::npos)
			{
				altered_place.replace(position, 1, "_");
				position = altered_place.find(" ", position + 1);
			}

			// Writing opportunity to file
			ofstream file2;
			file2.open("location.txt", ios::app);

			if (file2.is_open())
			{
				cout << "\n\nFile opened successfully!\n\n";
				cout << "Entering data into file. Please wait." << endl;

				file2 << SID << " " << fn << " " << ln << " " << altered_place << endl;
			}

			file2.close();

			break;
		}
		case 'n':
		{
			cout << "Thank you for your feedback.\nBe sure to check out RocketSHPE on our website for possible opportunities!!!" << endl;
			break;
		}
		default:
		{
			cout << "Error in choice. Please check data." << endl << endl;
			break;
		}
	}

}