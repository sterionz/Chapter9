
// Name: Alex Jacobs, David Nguyen, Gabriel Lira, Jessy Zuniga, Cristine Llano, and Jorge Gonzalez
// Date: 11-3-2025
// Description: Chapter 9 Assignments
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "input.h"
#include "towerofhanoi.h"

using namespace std;

void option1();


int computerGuess(int low, int high, int& count);

bool isSafe(const vector<vector<int>>& board, int row, int column, int n);
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
            option1();
            cout << "\n\n";
            break;

        case 2:
        {
            system("cls");
            int count = 0;

            srand(static_cast<unsigned int>(time(0)));
            int upperLimit = rand() % 951 + 50; // random number between 50–1000

            cout << "\n\t2> Guess your number between 1 to " << upperLimit << ".\n";
            cout << "\n\tThink of a number from 1 to " << upperLimit << ".\n";


            int number = computerGuess(1, upperLimit, count);

            cout << "\n\tNumber of guesses: " << count << "\n"; // display total at the end


            break;
        }

        case 3:
            runTowerOfHanoi();
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

            if (solveNQ(board, 1, n)) //this has to be 1 because row 0 already contains the user's queen 
            {
                cout << "\n\t" << n << "-Queens solution\n";
                print(board, n);
                cout << "\n";
            }

            else
            {
                cout << "\n\tNo solution\n";
            }
            break;
        }

        case 0:
            return 0;
        }

        system("pause");

    } while (true);

}

//==============================================================================================
//Alex Jacobs

// Recursive function for guessing
int computerGuess(int low, int high, int& count)
{
    if (low > high)
    {
        cout << "\n\tNumber cannot be zero.\n";
        return -1;
    }

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

//==============================================================================================

//==============================================================================================
// Jessy Zuniga 

// Preconditions:
// - recursionDepth is a non-negative integer (>= 0), representing the current recursion depth.
//   For the top-level call, recursionDepth should be chosen based on desired pattern size (e.g., 3 for a max row of 8 asterisks).
// - indent is a non-negative integer (>= 0), representing the starting horizontal offset for this pattern.
// Postconditions:
// - The fractal asterisk pattern for the given recursionDepth has been printed.
// - No return value;
// - The pattern size scales with 2^recursionDepth (widest row length), and total lines printed is ( 2^{recursionDepth + 1} - 1).
// - For recursionDepth > 0, the function has made two recursive calls.
// - If recursionDepth == 0, only a single indented asterisk is printed.
void printPattern(int recursionDepth, int indent, bool enableTrace = false, int level = 0) {
    static const int SPACING = 8;
    // Print entry trace
    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Entering print_pattern(" << recursionDepth << ", " << indent << ")" << '\n';
    }

    // Step 1: Check base case
    // This handles the smallest unit of the pattern: a single asterisk.
    if (recursionDepth == 0) {

        // Print base case trace
        if (enableTrace) {
            cout << string(level * SPACING, ' ');
            std::cout << "Printing single *: with indent " << indent << " (spaces: " << indent * 2 << ")" << "\n";
        }

        // Prints a single asterisk prefixed with (indent * 2) spaces for alignment.
        // The multiplication by 2 accounts for each "* " being 2 characters wide.
        cout << string(indent * 2, ' ') << "*" << "\n";

        // Print exit trace for base case (conditional)
        if (enableTrace) {
            cout << string(level * SPACING, ' ');
            cout << "Exiting base case(" << recursionDepth << ", " << indent << ")" << '\n';;
        }

        // Exits the function early for the base case.
        return;
    }

    // Trace upper recursive call
    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        std::cout << "Calling upper sub-pattern: print_pattern(" << recursionDepth - 1 << ", " << indent << ")" << "\n";
    }

    // Step 2: Recursive call for the upper sub-pattern
    // This creates a smaller, self-similar pattern shifted to the left (no added indent).
    printPattern(recursionDepth - 1, indent, enableTrace, level + 1);

    // Step 3: Construct and print the central row
    // This is the "base" or widest row for the current depth.
    // Calculates the number of asterisks: 2^recursionDepth (e.g., 8 for depth 3).
    int num = 1 << recursionDepth;
    // Initializes an empty string to build the row.
    string row = "";
    // Loops to append "* " num times.
    for (int i = 0; i < num; ++i) {
        // Appends one "* " to the row string.
        row += "* ";
    }
    // Removes the trailing space from the last "* " to avoid extra whitespace at the end of the row.
    row = row.substr(0, row.size() - 1);

    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Printing central row: with indent " << indent << " (spaces: " << indent * 2 << "), row length " << num << '\n';
    }

    // Prints the row prefixed with (indent * 2) spaces for alignment.
    cout << string(indent * 2, ' ') << row << "\n";

    // Step 4: Prepare for lower sub-pattern
    // Calculates the additional indent for the lower branch: 2^(recursionDepth - 1), which shifts it right by half the central row's length.
    int add = 1 << (recursionDepth - 1);

    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Calling lower sub-pattern: print_pattern(" << recursionDepth - 1 << ", " << indent + add << ")" << '\n';
    }

    // Step 5: Recursive call for the lower sub-pattern
    // This creates another smaller, self-similar pattern shifted to the right.
    printPattern(recursionDepth - 1, indent + add, enableTrace, level + 1);

    // Print exit trace 
    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Exiting Func End (" << recursionDepth << ", " << indent << ")" << '\n';
    }
}

// Same as print pattern except it only prints out the traces.
void printPatternTrace(int recursionDepth, int indent, bool enableTrace = true, int level = 0) {
    static const int SPACING = 8;

    // Print entry trace
    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Entering print_pattern(" << recursionDepth << ", " << indent << ")" << '\n';
    }

    // Step 1: Check base case
    // This handles the smallest unit of the pattern: a single asterisk.
    if (recursionDepth == 0) {

        // Print base case trace
        if (enableTrace) {
            cout << string(level * SPACING, ' ');
            cout << "Printing single *: with indent " << indent << " (spaces: " << indent * 2 << ")" << '\n';
        }

        // Print exit trace for base case
        if (enableTrace) {
            cout << string(level * SPACING, ' ');
            cout << "Exiting base case(" << recursionDepth << ", " << indent << ")" << '\n';
        }

        // Exits the function early for the base case.
        return;
    }

    // Trace upper recursive call
    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Calling upper sub-pattern: print_pattern(" << recursionDepth - 1 << ", " << indent << ")" << '\n';
    }

    // Step 2: Recursive call for the upper sub-pattern
    // This creates a smaller, self-similar pattern shifted to the left (no added indent).
    printPatternTrace(recursionDepth - 1, indent, enableTrace, level + 1);

    // Step 3: Construct and print the central row
    // This is the "base" or widest row for the current depth.
    // Calculates the number of asterisks: 2^recursionDepth (e.g., 8 for depth 3).
    int num = 1 << recursionDepth;
    // Initializes an empty string to build the row.
    string row = "";

    // Removes the trailing space from the last "* " to avoid extra whitespace at the end of the row.
    row = row.substr(0, row.size() - 1);

    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Printing central row: with indent " << indent << " (spaces: " << indent * 2 << "), row length " << num << '\n';
    }

    // Prints the row prefixed with (indent * 2) spaces for alignment.
    cout << string(indent * 2, ' ') << row << "\n";

    // Step 4: Prepare for lower sub-pattern
    // Calculates the additional indent for the lower branch: 2^(recursionDepth-1), which shifts it right by half the central row's length.
    int add = 1 << (recursionDepth - 1);

    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Calling lower sub-pattern: print_pattern(" << recursionDepth - 1 << ", " << indent + add << ")" << '\n';
    }

    // Step 5: Recursive call for the lower sub-pattern
    // This creates another smaller, self-similar pattern shifted to the right.
    printPatternTrace(recursionDepth - 1, indent + add, enableTrace, level + 1);

    // Print exit trace
    if (enableTrace) {
        cout << string(level * SPACING, ' ');
        cout << "Exiting Func End (" << recursionDepth << ", " << indent << ")" << '\n';
    }
}

void option1() {
    int depth = 3; // Default recursion depth
    const int INDENT = 4; // Fixed indent spaces per level

    const int RECURSE_MAX = 10; // MAX RECURSION ALLOWED
    do {

        system("cls");

        cout << "\n\t" << "1> Pattern of astricks and blanks";
        cout << "\n\t" << string(100, char(205));
        cout << "\n\t" << "1. Print out the pattern depth = 3";
        cout << "\n\t" << "2. Print out the traces depth = 3";
        cout << "\n\t" << "3. Set custom recursion depth";
        cout << "\n\t" << "4. custom recursion depth and display the pattern";
        cout << "\n\t" << "5. custom recursion depth and display the traces";
        cout << "\n\t" << string(100, char(205));
        cout << "\n\t" << "0. Return to Main Menu";
        cout << "\n\t" << string(100, char(205));

        switch (inputInteger("\n\tEnter your choice: ", 0, 5)) {

        case 1:
        {
            cout << "\n\n";
            printPattern(3, INDENT);
            break;
        }
        case 2:
        {
            cout << "\n\n";
            printPatternTrace(3, INDENT);
            break;
        }
        case 3:
        {
            cout << "\n\n";
            depth = inputInteger(("Enter custom recursion depth (0-" + to_string(RECURSE_MAX) + "): "), 0, RECURSE_MAX);
            cout << "\n\tDepth of Recursion set.";
            break;
        }
        case 4:
        {
            cout << "\n\n";
            printPattern(depth, INDENT);
            break;
        }
        case 5:
        {
            cout << "\n\n";
            printPatternTrace(depth, INDENT);
            break;
        }

        case 0:
        {
            cout << "\n\tReturn to main menu!!!\n\n";
            return;
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
        cout << "\n\n\t";
        system("pause");
    } while (true);


}

//==============================================================================================

//==============================================================================================
// Cristine Llano 

//precondition: row and column is in valid position to test, all queens in previous rows are placed safely
//postcondition: returns true if queen location is safe, returns false otherwise 
bool isSafe(const vector<vector<int>>& board, int row, int column, int n)
{


    //check same column in previous rows only (vertical attack)
    for (int i = 0; i < row; i++)
        if (board[i][column] == 1)
            return false;

    //scans upper left diagonal so that queens cant attack diagonally
    for (int i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;


    //scans upper right diagonal so that queens cant attack diagonally
    for (int i = row - 1, j = column + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j] == 1)
            return false;

    //if all checks pass, there is no queen is that spot and position is safe
    return true;

}

//precondition: any queens in previous rows are placed safely
//postcondition: attempts to place queens from this row to the bottom, returns true if solution for board is found
bool solveNQ(vector<vector<int>>& board, int row, int n)
{
    //if queens placed successfully, true 
    if (row == n) return true;

    //if this row already has a queen (user pre-placed, row 0), skip to next row
    for (int column = 0; column < n; column++)
        if (board[row][column] == 1)
            return solveNQ(board, row + 1, n); //skips to next row

    //try placing a queen in each column of this row
    for (int column = 0; column < n; column++)
    {
        if (isSafe(board, row, column, n)) //checks if position is safe 
        {
            board[row][column] = 1; //place queen at location
            if (solveNQ(board, row + 1, n)) //attempt to solve rest of board with that queen set 
                return true; //continue with next row
            board[row][column] = 0; //removes queen if the location was not safe, "backtrack" 
        }
    }
    return false; //no solution
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

//==============================================================================================
