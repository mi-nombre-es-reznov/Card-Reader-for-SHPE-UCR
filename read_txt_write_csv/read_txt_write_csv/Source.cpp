// Nicholas Perez-Aguilar
// 8 May 2019
// Description: Read from .txt and write to .csv for card reader program.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Call functions
int get_num_birthday(string);
int binary_rep(string);

int main()
{
	string txt, csv;

	cout << "\t\t\t\t\tWELCOME TO THE TXT -> CSV DATA TRANSFER PROGRAM" << endl << endl << endl;

	cout << "Please enter the name of the .txt file (w/o extension): ";
	cin >> txt;

	cout << endl << endl << "Please enter the name that you want to the .csv file to be (w/o extension): ";
	cin >> csv;

	system("CLS");

	// Initialize input and output
	ifstream file_txt;
	ofstream file_csv;

	// Add extensions
	txt = (txt + ".txt");
	csv = (csv + ".csv");
	
	file_txt.open(txt);
	file_csv.open(csv, ios::app);
	if (file_txt.is_open() && file_csv.is_open())
	{
		int id1, id2, id3, id4, SID, day, year, num_month;
		int num_f1, num_f2, num_f3, num_f4, num_f5, num_w1, num_w2, num_w3, num_w4, num_w5, num_s1, num_s2, num_s3, num_s4, num_s5;
		string last, first, netID, email, month, major, sex, f1, f2, f3, f4, f5, w1, w2, w3, w4, w5, s1, s2, s3, s4, s5, end;

		// Titles
		file_csv << "Month " << "," << " Year " << "," << " Major " << "," << "Sex" << "," << "GM Fall 1" << "," << "GM Fall 2" << "," << "GM Fall 3" << "," << 
			"GM Fall 4" << "," << "GM Fall 5" << "," << "GM Winter 1" << "," << "GM Winter 2" << "," << "GM Winter 3" << "," << "GM Winter 4" << "," << "GM Winter 5" << 
			"," << "GM Spring 1" << "," << "GM Spring 2" << "," << "GM Spring 3" << "," << "GM Spring 4" << "," << "GM Spring 5" << endl;

		while (file_txt >> id1 >> id2 >> id3 >> id4 >> last >> first >> SID >> netID >> email >> day >> month >> year >> major >> sex >> f1 >> f2 >> f3 >> f4 >> f5 >>
			w1 >> w2 >> w3 >> w4 >> w5 >> s1 >> s2 >> s3 >> s4 >> s5 >> end)
		{
			// Get birthday month
			num_month = get_num_birthday(month);

			// Get binary representation of GM attendance
			num_f1 = binary_rep(f1);
			num_f2 = binary_rep(f2);
			num_f3 = binary_rep(f3);
			num_f4 = binary_rep(f4);
			num_f5 = binary_rep(f5);
			num_w1 = binary_rep(w1);
			num_w2 = binary_rep(w2);
			num_w3 = binary_rep(w3);
			num_w4 = binary_rep(w4);
			num_w5 = binary_rep(w5);
			num_s1 = binary_rep(s1);
			num_s2 = binary_rep(s2);
			num_s3 = binary_rep(s3);
			num_s4 = binary_rep(s4);
			num_s5 = binary_rep(s5);

			file_csv << num_month << "," << year << "," << major << "," << sex << "," << num_f1 << "," << num_f2 << "," << num_f3 << "," << num_f4 << "," << num_f5 <<
				"," << num_w1 << "," << num_w2 << "," << num_w3 << "," << num_w4 << "," << num_w5 << "," << num_s1 << "," << num_s2 << "," << num_s3 << "," << 
				num_s4 << "," << num_s5 << endl;
		}

		file_txt.close();
		file_csv.close();

		cout << "Data has transfered successfully!!!" << endl << endl;

		system("pause");
		system("CLS");
		cout << "\n\n\n\n\n\n\n\n\n\nThank you for using NCompEng Technologies!" << endl << endl;
	}
	else
	{
		cout << "Files failed to open properly" << endl << endl;
	}

	system("pause");
	return 0;
}

int get_num_birthday(string m)
{
	int month;

	if (m == "January")
	{
		month = 1;
	}
	else if (m == "February")
	{
		month = 2;
	}
	else if (m == "March")
	{
		month = 3;
	}
	else if (m == "April")
	{
		month = 4;
	}
	else if (m == "May")
	{
		month = 5;
	}
	else if (m == "June")
	{
		month = 6;
	}
	else if (m == "July")
	{
		month = 7;
	}
	else if (m == "August")
	{
		month = 8;
	}
	else if (m == "September")
	{
		month = 9;
	}
	else if (m == "October")
	{
		month = 10;
	}
	else if (m == "November")
	{
		month = 11;
	}
	else if (m == "December")
	{
		month = 12;
	}
	else
	{
		month = 0;
	}

	return month;
}

int binary_rep(string GM)
{
	int attended;

	if (GM == "Yes")
	{
		attended = 1;
	}
	else if (GM == "No")
	{
		attended = 0;
	}
	else
	{
		attended = -1;
	}

	return attended;
}