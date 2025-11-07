// Name: Alex Jacobs, David Nguyen, Gabriel Lira, Jessy Zuniga, Cristine Llano, and Jorge Gonzalez
// Date: 11-3-2025
// Description: Chapter 9 Assignments
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "input.h"


using namespace std;


void Option2();
int computerGuess(int low, int high, int& count);
bool isSafe(const vector<vector<int>> &board, int row, int column, int n);
bool solveNQ(vector<vector<int>>& board, int column, int n);
void print(const vector<vector<int>>& board, int n);



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
            // TODO: Add pattern of asterisks function
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
            // TODO: Add "Tower of Hanoi" function
            break;

        case 4:
        {
            int n = inputInteger("\n\tEnter the board dimension dxd: ", true);

            //this makes a blank board
            //board is a vector, each element inside the board is also a vector
            vector<vector<int>> board;

            for (int i = 0; i < n; i++)
            {
                vector<int> row(n, 0); //makes a vector called row with n columns and each column starts as 0
                board.push_back(row); //attaches that row to the board 
            }

            int position = inputInteger("\n\tEnter the column position (1.." + to_string(n) + ") of the first Queen on row 1: ", 1, n);
            int columnPosition = position - 1;

            board[0][columnPosition] = 1; //this places the queens spot by setting it equal to 1

            if (solveNQ(board, 0, n))
            {
                cout << "\n\t" << n << "-Queens solution\n";
                print(board, n);
                cout << "\n";
            }

            else
            {
                cout << "\n\tNo solution\n";
            }
           
            system("pause");
            break;
        }

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

//precondition: column is valid position to test
//postcondition: returns true if queen location is safe, returns false otherwise 
bool isSafe(const vector<vector<int>> &board, int row, int column, int n)
{
    //if board[row][column] is equal 1 then it means theres already a queen
    //if its equal to 0 then it means empty


    //scans every column in the same row so that two queens in the same row cant attack horizontally
    //if theres a queen, returns false
    for (int j = 0; j < n; j++)
        if (j != column && board[row][j] == 1)
            return false;

    //scans every row in column so that queens cant attack vertically 
    for (int i = 0; i < n; i++)
        if (i != row && board[i][column] == 1)
            return false;

    //scans upper left diagonal so that queens cant attack diagonally
    for (int i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--) 
        if (board[i][j] == 1)
            return false;

    //scans lower right diagonal so that queens cant attack diagonally
    for (int i = row + 1, j = column + 1; i < n && j < n; i++, j++)
        if (board[i][j] == 1)
            return false;

    //scans upper right diagonal so that queens cant attack diagonally
    for (int i = row - 1, j = column + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j] == 1)
            return false;

    //scans lower left diagonal so that queens cant attack diagonally
    for (int i = row + 1, j = column - 1; i < n && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return false;

    //if all checks pass, there is no queen is that spot and position is safe
    return true;

}

//precondition: any queens placed are in safe spot 
//postcondition: returns true if solution found 
bool solveNQ(vector<vector<int>>& board, int column, int n)
{
    //if queens placed successfully, true 
    if (column >= n) 
        return true;

    //loops through each row in this column
    for (int row = 0; row < n; row++)
    {
        if (isSafe(board, row, column, n)) //checks if position is safe 
        {
            board[row][column] = 1; //sets queen at location
            if (solveNQ(board, column + 1, n)) //attempt to solve rest of board with that queen set 
                return true;
            board[row][column] = 0; //removes queen if the location was not safe, "backtrack" 
        }

    }

    return false; //if everything fails 
}

//precondition: n is set
//postcondition: displays board 
void print(const vector<vector<int>>& board, int n)
{
    cout << "\n\t" << char(201);
    for (int i = 0; i < 2 * n - 1; i++) 
        cout << char(205);

    cout << char(187) << "\n\t";

    for (int r = 0; r < n; r++)
    {
        cout << char(186);
        for (int c = 0; c < n; c++)
        {
            if (board[r][c] == 1)
                cout << "Q";
            else
            {
                if (r == n - 1)
                    cout << " ";
                else 
                    cout << "_";
            }
                
            if (c != n - 1)
                cout << char(179);
        }
        cout << char(186) << "\n\t";
    }
    cout << char(200);
    for (int i = 0; i < 2 * n - 1; i++) 
        cout << char(205);
    cout << char(188) << "\n";

}