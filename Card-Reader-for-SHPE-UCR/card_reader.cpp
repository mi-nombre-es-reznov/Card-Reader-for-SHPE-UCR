// Created by Nicholas Perez-Aguilar
// Start Date: 15 Aug 18
// Card reader test for SHPE @ UCR
//
//
// Last Modified: 22 Aug 18
//
// This program will allow for the user to pick between the options of adding a new member, looking up a member, or even updating
// a members data. It has bound checks almost everywhere and cannot easily be broken, from observations thus far. User data will be
// displayed on the screen for the user to see but also is constantly opening and closing files to write and save data, this is also
// a security measure employed to, hopefully, protect the external data as much as possible. The data consists of card number (SID card
// UCR specific), first and last name, Student ID number, netID, email, birthday, and even member's major.

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

// -------------------------------
//              Main
// -------------------------------
int main()
{
	char retry;

	/* ------------------------------------------
		 	 SHPE Menu Internal File Intro
	   ------------------------------------------ */
	cout << "\t\t\t-------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t              Welcome to the SHPE @ UCR card reader database                   " << endl;
	cout << "\t\t\t-------------------------------------------------------------------------------" << endl;

	do
	{
		option_selection();		// Main Menu operations following input to main display
		
		// Loop for input validation
		do
		{
			retry = Retry();	// Asks about looping Main Menu (Main) again
		} while (retry != 'y' && retry != 'n');

	} while(retry == 'y');

	// Closing message at the very end of the program
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
	string major;
	data.open("records.txt", ios::app);
	if (data.is_open())
	{
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
		data << last_name <<", " << first_name << " ";

		// Get student ID number
		do
		{
			cout << "Student ID number: ";
			cin >> ID;

			numFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if(numFail == true)
			{
				cout << "You entered an invalid option, please enter a valid number!" << endl;
			}
		} while (numFail == true);
		data << ID << " ";

		// Get student netID
		cout << "netID: ";
		cin >> netID;
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
	cout << "\t\tB) Retrieve member data" << endl;
	cout << "\t\tC) Update user info" << endl;
	cout << "\t\tD) Retrieve all user data" << endl;
	cout << "\t\tE) General Meeting Sign-In" << endl;
	cout << "\t\tF) Exit program" << endl;
}

// -------------------------------
//         Choice Selection
// -------------------------------
void option_selection()
{
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
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_email;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year;

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
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >> 
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
				cout << end_tag << endl;
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
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_email, get_birth_month, get_major, replace;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year;
	replacements replaced;
	Bday birthday;
	ifstream database;
	database.open("records.txt");

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
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >>
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
				while(!database.eof())		// Run through file while pointer is not at the End of File (EOF).
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

							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

							
							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
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
								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;
							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
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
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
								rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
								rep_S4 >> rep_S5 >> end_tag) 
							{
								if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_first_name == get_first_name))
								{
									rep_first_name = replaced.replacement;
								}
								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
								ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
								ret_S4 >> ret_S5 >> end_tag) 
							{
								if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_first_name == ret_first_name))
								{
									ret_first_name == rep_first_name;
								}
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
								rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
								rep_S4 >> rep_S5 >> end_tag) 
							{
								if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_last_name == get_last_name))
								{
									rep_last_name = replaced.replacement;
								}
								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
								ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
								ret_S4 >> ret_S5 >> end_tag) 
							{
								if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_last_name == ret_last_name))
								{
									ret_last_name == rep_last_name;
								}
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
								rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
								rep_S4 >> rep_S5 >> end_tag) 
							{
								if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_SID == get_SID))
								{
									rep_SID = replaced.SID;
								}

								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;
							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
								ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
								ret_S4 >> ret_S5 >> end_tag) 
							{
								if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_SID == ret_SID))
								{
									ret_SID = rep_SID;
								}
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
								rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
								rep_S4 >> rep_S5 >> end_tag) 
							{
								if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_netID == get_netID))
								{
									rep_netID = replaced.replacement;
								}

								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
								ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
								ret_S4 >> ret_S5 >> end_tag) 
							{
								if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_netID == ret_netID))
								{
									ret_netID = rep_netID;
								}
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
								rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
								rep_S4 >> rep_S5 >> end_tag) 
							{
								if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_email == get_email))
								{
									rep_email = replaced.replacement;
								}

								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
								ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
								ret_S4 >> ret_S5 >> end_tag) 
							{
								if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_last_name == ret_last_name))
								{
									ret_email = rep_email;
								}
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
								rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
								rep_S4 >> rep_S5 >> end_tag) 
							{
								if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_birth_day == get_birth_day) && (rep_birth_month == get_birth_month) && (rep_birth_year == get_birth_year))
								{
									rep_birth_day = replaced.day;
									rep_birth_month = replaced.replacement;
									rep_birth_year = replaced.year;
								}

								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
								ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
								ret_S4 >> ret_S5 >> end_tag) 
							{
								if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (ret_birth_day == rep_birth_day) && (ret_birth_month == rep_birth_month) && (ret_birth_year == rep_birth_year))
								{
									ret_birth_day = rep_birth_day;
									ret_birth_month = rep_birth_month;
									ret_birth_year = rep_birth_year;
								}
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
							string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
							int rep_SID, rep_birth_day, rep_birth_year;
							string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

							// Put data in temp file
							ifstream filein("records.txt"); //File to read from
							ofstream fileout("text.txt"); //Temporary file

							while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
								rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
								rep_S4 >> rep_S5 >> end_tag) 
							{
								if ((rep_ID1 == get_ID1) && (rep_ID2 == get_ID2) && (rep_ID3 == get_ID3) && (rep_ID4 == get_ID4) && (rep_major == get_major))
								{
									rep_major = replaced.replacement;
								}

								fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
									" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
									rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
							}

							filein.close();
							fileout.close();

							// Put data in back in original file
							ifstream filein2("text.txt"); //File to read from
							ofstream fileout2("records.txt"); //Temporary file

							string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
							int ret_SID, ret_birth_day, ret_birth_year;
							string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

							while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
								ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
								ret_S4 >> ret_S5 >> end_tag) 
							{
								if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4) && (rep_last_name == ret_last_name))
								{
									ret_major = rep_major;
								}
								fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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
		return replacements{ choice, "null" , 0};
	}

	// Switch statement to run through choices
	switch (choice)
	{
		case 'A':
		{
			// Update Card number
			card_num = (num1 + num2 + num3 + num4);
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

			cout << "\n\nYour documented card number is: " << card_num << "." << endl;
			cout << "Your requested new card number is: " << replacement_card << "." << endl;

			do
			{
				cout << "Is this correct? (y or n): ";
				cin >> choice2;
				choice2 = toupper(choice2);

				if (choice2 == 'Y')
				{
					cout << "Understood! We are working on ammending your information." << endl;
					return replacements{choice, replacement_card, 0};
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
			cout << "Please enter replacement first name (no spaces): ";
			cin >> replacement_first;

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
					return replacements{choice, replacement_first, 0};
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
			cout << "Please enter replacement last name (no spaces): ";
			cin >> replacement_last;

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
					return replacements{choice, replacement_last, 0};
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
					return replacements{choice, "none", replacement_SID};
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
			cout << "Please give an updated netID: ";
			cin >> replacement_netID;

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
					return replacements{choice, replacement_netID, 0};
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
			cout << "Please give your updated email (no spaces): ";
			cin >> replacement_email;

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
					return replacements{choice, replacement_email, 0};
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
					return replacements{ choice, birthday.month, 0, birthday.day, birthday.year};
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
					return replacements{choice, "canceled", 0};
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
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_birth_month, get_major, get_email;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;
	int get_SID, get_birth_day, get_birth_year;

	ifstream retrieve;
	retrieve.open("records.txt");

	if (retrieve.is_open())
	{
		cout << "File has opened successfully." << endl << endl;

		// Data retrieval from database to display all users.
		while (retrieve >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >>
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
				cout << end_tag << endl;
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
	string get_ID1, get_ID2, get_ID3, get_ID4, get_first_name, get_last_name, get_netID, get_email, get_birth_month, get_major, replace;
	string line, last_name;
	int get_SID, get_birth_day, get_birth_year, SID;
	char choice, choice2;
	string card_num, replacement_card, replacement_first, replacement_last, replacement_netID, replacement_email, replacement_major;
	int replacement_SID, position = 0, token = 0;
	bool numFail;
	string get_F1, get_F2, get_F3, get_F4, get_F5, get_W1, get_W2, get_W3, get_W4, get_W5, get_S1, get_S2, get_S3, get_S4, get_S5;


	ifstream database;
	database.open("records.txt");
	// Test if database is open
	if (database.is_open())
	{
		cout << "File has successfully been opened!" << endl << endl;	// Database has opened successfully
		
		cout << "Please enter your last name: ";
		getline(cin, last_name);
		int position = last_name.find(" ");
		if(position > 0)
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
		while (database >> get_ID1 >> get_ID2 >> get_ID3 >> get_ID4 >> get_last_name >> get_first_name >> get_SID >> get_netID >> get_email >> get_birth_day >> get_birth_month >> get_birth_year >> get_major >>
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
				card_num = (get_ID1 + get_ID2 + get_ID3 + get_ID4);
				//cin.ignore();
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

				cout << "\n\nYour documented card number is: " << card_num << "." << endl;
				cout << "Your requested new card number is: " << replacement_card << "." << endl;

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
					string replacement1 = replacement_card.substr(0, 4);
					string replacement2 = replacement_card.substr(4, 4);
					string replacement3 = replacement_card.substr(8, 4);
					string replacement4 = replacement_card.substr(12, 4);

					string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
					int rep_SID, rep_birth_day, rep_birth_year;
					string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;

					// Put data in temp file
					ifstream filein("records.txt"); //File to read from
					ofstream fileout("text.txt"); //Temporary file

					while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
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
						fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
							" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
							rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;

					}

					filein.close();
					fileout.close();

					// Put data in back in original file
					ifstream filein2("text.txt"); //File to read from
					ofstream fileout2("records.txt"); //Temporary file

					string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
					int ret_SID, ret_birth_day, ret_birth_year;
					string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;

					while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
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
						fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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

			string rep_ID1, rep_ID2, rep_ID3, rep_ID4, rep_last_name, rep_first_name, rep_netID, rep_email, rep_birth_month, rep_major;
			string rep_F1, rep_F2, rep_F3, rep_F4, rep_F5, rep_W1, rep_W2, rep_W3, rep_W4, rep_W5, rep_S1, rep_S2, rep_S3, rep_S4, rep_S5;
			int rep_SID, rep_birth_day, rep_birth_year;
			// Put data in temp file
			ifstream filein("records.txt"); //File to read from
			ofstream fileout("text.txt"); //Temporary file

			while (filein >> rep_ID1 >> rep_ID2 >> rep_ID3 >> rep_ID4 >> rep_last_name >> rep_first_name >> rep_SID >> rep_netID >> rep_email >> rep_birth_day >> rep_birth_month >> rep_birth_year >> rep_major >>
				rep_F1 >> rep_F2 >> rep_F3 >> rep_F4 >> rep_F5 >> rep_W1 >> rep_W2 >> rep_W3 >> rep_W4 >> rep_W5 >> rep_S1 >> rep_S2 >> rep_S3 >>
				rep_S4 >> rep_S5 >> end_tag)
			{
				if ((rep_ID1 == search_ID1) && (rep_ID2 == search_ID2) && (rep_ID3 == search_ID3) && (rep_ID4 == search_ID4))
				{
					token = 1;
					// Setup database retrieval for user to easily read.
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					cout << rep_first_name << " " << rep_last_name << " has signed in for General Meeting: " << GM.number << ", this " << GM.quarter << " Quarter." << endl;

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
				}

				fileout << rep_ID1 << " " << rep_ID2 << " " << rep_ID3 << " " << rep_ID4 << " " << rep_last_name << " " << rep_first_name << " " << rep_SID << " " << rep_netID << " " << rep_email << " " << rep_birth_day << " " << rep_birth_month << " " << rep_birth_year << " " << rep_major <<
					" " << rep_F1 << " " << rep_F2 << " " << rep_F3 << " " << rep_F4 << " " << rep_F5 << " " << rep_W1 << " " << rep_W2 << " " <<
					rep_W3 << " " << rep_W4 << " " << rep_W5 << " " << rep_S1 << " " << rep_S2 << " " << rep_S3 << " " << rep_S4 << " " << rep_S5 << " " << end_tag << endl;
			}

			filein.close();
			fileout.close();

			// Put data in back in original file
			ifstream filein2("text.txt"); //File to read from
			ofstream fileout2("records.txt"); //Temporary file

			string ret_ID1, ret_ID2, ret_ID3, ret_ID4, ret_last_name, ret_first_name, ret_netID, ret_email, ret_birth_month, ret_major;
			string ret_F1, ret_F2, ret_F3, ret_F4, ret_F5, ret_W1, ret_W2, ret_W3, ret_W4, ret_W5, ret_S1, ret_S2, ret_S3, ret_S4, ret_S5;
			int ret_SID, ret_birth_day, ret_birth_year;
			while (filein2 >> ret_ID1 >> ret_ID2 >> ret_ID3 >> ret_ID4 >> ret_last_name >> ret_first_name >> ret_SID >> ret_netID >> ret_email >> ret_birth_day >> ret_birth_month >> ret_birth_year >> ret_major >>
				ret_F1 >> ret_F2 >> ret_F3 >> ret_F4 >> ret_F5 >> ret_W1 >> ret_W2 >> ret_W3 >> ret_W4 >> ret_W5 >> ret_S1 >> ret_S2 >> ret_S3 >>
				ret_S4 >> ret_S5 >> end_tag)
			{
				if ((ret_ID1 == rep_ID1) && (ret_ID2 == rep_ID2) && (ret_ID3 == rep_ID3) && (ret_ID4 == rep_ID4))
				{
					ret_first_name == rep_first_name;
				}
				fileout2 << ret_ID1 << " " << ret_ID2 << " " << ret_ID3 << " " << ret_ID4 << " " << ret_last_name << " " << ret_first_name << " " << ret_SID << " " << ret_netID << " " << ret_email << " " << ret_birth_day << " " << ret_birth_month << " " << ret_birth_year << " " << ret_major <<
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

		}while (search_ID != "0000000000000000");
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