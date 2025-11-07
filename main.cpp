// Name: Alex Jacobs, David Nguyen, Gabriel Lira, Jessy Zuniga, Cristine Llano, and Jorge Gonzalez
// Date: 11-6-2025
// Description: Chapter 9 Assignments
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "input.h"
#include "GuessNumber.h"
#include "towerofhanoi.h"


using namespace std;

int computerGuess(int low, int high, int& count);
void printPattern(int value);


int main()
{
    do
    {
        system("cls");

        cout << "\n\tCMPR131 Chapter 9: Recursive Applications by Alex Jacobs, David Nguyen, Gabriel Lira, Jessy Zuniga, Cristine Llano, and Jorge Gonzalez";
        cout << "\n\t" << string(100, char(205));
        cout << "\n\t\t1> Pattern of asterisks and blanks";
        cout << "\n\t\t2> Guess a number";
        cout << "\n\t\t3> Solve Tower of Hanoi";
        cout << "\n\t\t4> Solve n-Queens";
        cout << "\n\t" << string(100, char(196));
        cout << "\n\t\t0. Exit";
        cout << "\n\t" << string(100, char(205));

        int option = inputInteger("\n\t\tOption: ", 0, 4);

        switch (option)
        {
        case 1:
            system("cls");
            cout << "\n\t1> Pattern of astricks and blanks\n";

            //print the pattern
            int start = 2;
            printPattern(start);

            break;

        case 2:
        {
            system("cls");
            int count = 0;

            srand(static_cast<unsigned int>(time(0)));
            int upperLimit = rand() % 951 + 50; // random number between 50–1000

            cout << "\n\t2> Guess your number between 1 to " << upperLimit << ".\n";
            cout << "\n\tThink of a number from 1 to " << upperLimit << ".\n";
            system("pause");

            int number = computerGuess(1, upperLimit, count);

            cout << "\n\tNumber of guesses: " << count << "\n"; // display total at the end
            system("pause");

            break;
        }

        case 3:
            runTowerOfHanoi();
            break;

        case 4:
            // TODO: Add "n-Queens" function
            break;

        case 0:
            return 0;
        }

    } while (true);

}

// Recursive function for guessing
int computerGuess(int low, int high, int& count)
{
    int guess = (low + high) / 2;
    count++;
    char answer = inputChar("\tIs your number " + to_string(guess) + "? (Y-yes or N-no): ", 'Y', 'N');

    if (answer == 'Y')
        return guess;

    char larger = inputChar("\tIs your number larger than " + to_string(guess) + "? (Y-yes or N-no): ", 'Y', 'N');

    if (larger == 'Y')
        return computerGuess(guess + 1, high, count);
    else
        return computerGuess(low, guess - 1, count);
}

//precondition: int start value must be 2
//postcondition: function will print out the pattern
void printPattern(int value)
{
    //stop the loop when pattern is complete
    if (value > 16)
    {
        //pattern is printed :)
    }
    //print '*'
    else if (value % 2 == 0)
    {
        int blanks = 0;
        int keepCount = value;

        //adds to 'blanks' to keep the pattern in line
        for (int i = 0; i < value; i++)
        {
            keepCount = keepCount - 2;

            if (keepCount == 0)
            {
                break;
            }

            blanks++;
        }

        //print the '*'
        cout << "\n\t" << string(blanks * 2, ' ') << "*";

        //continue the pattern
        printPattern(value + 1);
    }
    //print '* * * * * * * * * *'
    else if (value % 9 == 0)
    {
        //print the '*'
        cout << "\n\t* * * * * * * * * *";

        //continue the pattern
        printPattern(value + 1);
    }
    //print '* * * *'
    else if (value == 5 || value == 13)
    {
        int blanks = 0;
        int keepCount = value;

        //adds to 'blanks' to keep the pattern in line
        for (int i = 0; i < value; i++)
        {
            keepCount = keepCount - 5;

            if (keepCount <= 0)
            {
                break;
            }

            blanks++;
        }

        //print the '*'
        cout << "\n\t" << string(blanks * 4, ' ') << "* * * *";

        //continue the pattern
        printPattern(value + 1);
    }
    //print '* *'
    else if (value % 2 != 0)
    {
        int blanks = 0;
        int keepCount = value;

        //adds to 'blanks' to keep the pattern in line
        for (int i = 0; i < value; i++)
        {
            keepCount = keepCount - 3;

            if (keepCount <= 0)
            {
                break;
            }

            blanks++;
        }

        //adjust 'blanks'
        if (blanks == 3)
        {
            blanks++;
        }
        else if (blanks == 4)
        {
            blanks = blanks + 2;
        }

        //print the '*'
        cout << "\n\t" << string(blanks * 2, '  ') << "* *";

        //continue the pattern
        printPattern(value + 1);
    }
}