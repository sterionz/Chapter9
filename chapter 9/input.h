#pragma once

// Original by the prof
// J.T.Z.R added color functions
// C.L added color to all errors. Thank you!!!
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>

//#include "Exam1-General-Functions.h"
using namespace std;

// Color functions and values.
enum textColors
{
	Black = 30, Red = 31, Green = 32,
	Yellow = 33, Blue = 34, Magenta = 35,
	Cyan = 36, White = 37,
	BrightBlack = 90, BrightRed = 91, BrightGreen = 92,
	BrightYellow = 93, BrightBlue = 94, BrightMagenta = 95,
	BrightCyan = 96, BrightWhite = 97
};

//***********************************************************************************************
//	Definition of function (set_txt_color).
// Any text after the function is run will be changed 
// to a new color. To revert back to white, use reset_color();
// Parameters (unsigned short int or txt color enum) 
// Accepts (color)
// Returns (Void)
// Added by (J.T.Z.R)
// Created by (geeksforgeeks) 
// Link - https://www.geeksforgeeks.org/how-to-change-console-color-in-cpp/
// This gave the original functions used.
// Link - https://stackoverflow.com/a/76026809
// This gave the idea to change \033 to \x1b
// Link - https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
// Extra reading.
// Data Added           : 03/24/2025
// Changes Done         : nullptr
// Changes Date Added   : nullptr
//***********************************************************************************************
void set_txt_color(unsigned short int textColor)
{
	// praise geeks for geeks and  stack overflow.
	cout << "\x1b[" << textColor << "m";
}

// Resets the text color to default white. should be used after set_txt_color
void reset_color()
{
	cout << "\x1b[0m";
}

//PreCondition: spaces (boolean true or false)
//PostCondition: returns a string including space character(s) or without space character 
string inputString(string prompt, bool spaces)
{
	string input = "";

	cout << prompt;
	if (spaces)
		getline(cin, input);
	else
	{
		cin >> input;
		cin.clear();
		cin.ignore(999, '\n');
	}
	return input;
}

//PreCondition: valid string of options
//PostCondition: returns an uppercase  of the option (char)
char inputChar(string prompt, string options)
{
	char input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a character type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
		{
			bool found = false;
			for (int i = 0; i < options.length(); i++)
				if ((toupper(options.at(i))) == toupper(input))
				{
					found = true;
					break;
				}
			if (found)
			{
				cin.clear();
				cin.ignore(999, '\n');
				break;
			}
			else
				set_txt_color(BrightRed);
				cout << "ERROR: Invalid input. Must be one of '" << options << "' character.\n";
				reset_color();
		}
	} while (true);
	return toupper(input);
}

//PreCondition: valid yes (char) or no (char)
//PostCondition: returns an uppercase  yes (char) or no (char) 
char inputChar(string prompt, char yes, char no)
{
	char input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a character type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (tolower(input) != tolower(yes) && tolower(input) != tolower(no))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a '" << static_cast<char>(toupper(yes)) << "' or '" << static_cast<char>(toupper(no)) << "' character.\n";
			reset_color();
		}
			
		else
		{
			cin.clear();
			cin.ignore(999, '\n');
			break;
		}
	} while (true);
	return toupper(input);
}

//PreCondition: alphaOrDigit (boolean true or false)
//PostCondition: returns an alphabet or a digit character
char inputChar(string prompt, bool alphaOrDigit)
{
	char input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a character type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (alphaOrDigit && !isalpha(input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be an alphabet character.\n";
			reset_color();
		}
			
		else if (!alphaOrDigit && !isdigit(input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a digit character.\n";
			reset_color();
		}
			
		else
		{
			cin.clear();
			cin.ignore(999, '\n');
			break;
		}
	} while (true);
	return input;
}

//PreCondition: NA
//PostCondition: returns any character
char inputChar(string prompt)
{
	char input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a character type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return toupper(input);
}

//PreCondition: NA
//PostCondition: returns any integer value
int inputInteger(string prompt)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: posNeg (boolean true or false)
//PostCondition: returns a positive integer value (posNeg = true) or a negative integer value (poseNeg = false)
int inputInteger(string prompt, bool posNeg)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input <= 0)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a positive number.\n";
			reset_color();
		}
			
		else if (!posNeg && input >= 0)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a negative number.\n";
			reset_color();
		}
			
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: start (integer) and greater (boolean true or false)
//PostCondition: returns an integer value greater than start or lesser than start
int inputInteger(string prompt, int start, bool greater)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (greater && input < start)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a greater than or equal to " << start << ".\n";
			reset_color();
		}
			
		else if (!greater && input > start)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a lesser than or equal to " << start << ".\n";
			reset_color();
		}
		
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: startRange (integer) and endRange (integer)
//PostCondition: returns an integer value within range (start Range and endRange)
int inputInteger(string prompt, int startRange, int endRange)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
			reset_color();
		}
			
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: NA
//PostCondition: returns any double value
double inputDouble(string prompt)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a double type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: posNeg (boolean true or false)
//PostCondition: returns a positive double value (posNeg = true) or a negative double value (poseNeg = false)
double inputDouble(string prompt, bool posNeg)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a double type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input <= 0.0)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a positive number.\n";
			reset_color();
		}
			
		else if (!posNeg && input >= 0.0)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a negative number.\n";
			reset_color();
		}
			
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: start(integer) and greater(boolean true or false)
//PostCondition: returns an integer value greater than start or lesser than start
double inputDouble(string prompt, double start, bool posNeg)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a double type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input <= start)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be greater than or equal to " << start << ".\n";
			reset_color();
		}
			
		else if (!posNeg && input >= start)
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be lesser than or equal to " << start << ".\n";
			reset_color();
		}
			
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: startRange (integer) and endRange (integer)
//PostCondition: returns an integer value within range (start Range and endRange)
double inputDouble(string prompt, double startRange, double endRange)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be a double type.\n";
			reset_color();
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
		{
			set_txt_color(BrightRed);
			cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
			reset_color();
		}
			
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

