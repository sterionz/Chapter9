#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>

const int NUM_PEGS = 3;

void drawTowers(const vector<vector<int>>& pegs, int n);
void moveTower(int n, int from, int to, int aux, vector<vector<int>>& pegs, int& moveCount, int totalDisks);


static string draw_disk(int size)
{
    ostringstream ss;
    ss << size;
    string num = ss.str();

    int total_width = size * 2 + 1;
    int side_width = (total_width - (int)num.size()) / 2;

    string disk;
    disk.append(side_width, '=');
    disk += num;
    disk.append(side_width, '=');

    return disk;
}

void runTowerOfHanoi()
{
    system("cls");

    cout << "Tower of Hanoi (Recursive)";
    cout << "\n" << string(100, char(196));

    char again;

    do
    {
        int n = inputInteger("\n\n\tEnter the number of rings (1..64): ", 1, 64);

        vector<vector<int>> pegs(NUM_PEGS);
        for (int i = n; i >= 1; --i)
            pegs[0].push_back(i);

        cout << endl;
        drawTowers(pegs, n);

        int moveCount = 0;
        moveTower(n, 0, 2, 1, pegs, moveCount, n);

        cout << "\tThe computer has solved the game in " << moveCount << " moves.";
        again = toupper(inputChar("\n\n\tPlay again? (Y-yes or N-no): ", static_cast<string>("YN")));
        cout << endl;

    } while (again == 'Y' || again == 'y');
}

// Draw the three towers
void drawTowers(const vector<vector<int>>& pegs, int n)
{
    // Convert pegs to stack-like visualization order
    vector<vector<int>> peg_contents = pegs;

    if (n <= 9)
    {
        int peg_width = n * 2 + 1;
        for (int row = n - 1; row >= 0; --row)
        {
            cout << "\t";
            for (int peg = 0; peg < 3; ++peg)
            {
                if ((int)peg_contents[peg].size() > row)
                {
                    int disk = peg_contents[peg][row];
                    string line = draw_disk(disk);
                    int padding = (peg_width - (int)line.size()) / 2;
                    cout << setw(padding + line.size()) << line
                        << setw(peg_width - padding - (int)line.size() + 1) << "";
                }
                else
                {
                    int padding = peg_width / 2;
                    cout << setw(padding + 1) << "|"
                        << setw(peg_width - padding) << "";
                }
            }
            cout << "\n";
        }

        // Draw base
        cout << "\t";
        for (int i = 0; i < 3; ++i)
            cout << string(peg_width, '=') << " ";
        cout << "\n\t";
        int half = peg_width / 2;
        cout << setw(half + 1) << "A"
            << setw(peg_width + 2) << "B"
            << setw(peg_width + 2) << "C\n\n";
    }
    else
    {
        // Simplified view for inputs of 10 and above
        int num_width = static_cast<int>(to_string(n).size());
        int peg_width = num_width + 5;


        for (int row = n - 1; row >= 0; --row)
        {
            cout << "\t";
            for (int peg = 0; peg < 3; ++peg)
            {
                if ((int)pegs[peg].size() > row)
                {
                    string disk = to_string(pegs[peg][row]);
                    int padding = (peg_width - static_cast<int>(disk.size())) / 2;
                    cout << setw(padding + (int)disk.size()) << disk
                        << setw(peg_width - padding - (int)disk.size() + 1) << "";
                }
                else
                {
                    int padding = peg_width / 2;
                    cout << setw(padding + 1) << "|"
                        << setw(peg_width - padding) << "";
                }
            }
            cout << "\n";
        }

        cout << "\t";
        for (int i = 0; i < 3; ++i)
            cout << string(peg_width, '=') << " ";
        cout << "\n\t";

        int half = peg_width / 2;
        cout << setw(half + 1) << "A"
            << setw(peg_width + 1) << "B"
            << setw(peg_width + 3) << "C\n\n";
    }
}

// Recursive move function
void moveTower(int n, int from, int to, int aux, vector<vector<int>>& pegs, int& moveCount, int totalDisks)
{
    if (n == 0) return;

    moveTower(n - 1, from, aux, to, pegs, moveCount, totalDisks);

    ++moveCount;
    int disk = pegs[from].back();
    pegs[from].pop_back();
    pegs[to].push_back(disk);

    cout << "\tMove #" << moveCount << ": disk " << disk
        << " from peg-" << char('A' + from)
        << " to peg-" << char('A' + to) << "...\n\n";

    drawTowers(pegs, totalDisks);

    moveTower(n - 1, aux, to, from, pegs, moveCount, totalDisks);
}
