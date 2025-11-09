#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <experimental/iterator>

class SudokuPlate
{
 private:
    int plate[9][9] = { 0 };
    const char empty_symbol = 'x';
    std::string tempString;
    std::unordered_set < int >r[9]; //checking set
    std::unordered_set < int >c[9];
    std::unordered_set < int >box[3][3];

 public:
    SudokuPlate()
    {
    };
    ~SudokuPlate()
    {
    };

    void nextPlateIndex(int &i, int &j);
    void printPlate();
    void parsePlate(std::string fileName);
    void printString()
    {
        std::cout << tempString << std::endl;
    }
    void solvePlate();
    bool dfSearch(int idx);
    bool dfSearchOptimized();
    bool check(int x, int i, int j);
    int countPossibilities(int i, int j);
    void printSet(std::unordered_set < int >const &s);

};

void SudokuPlate::printSet(std::unordered_set < int >const &s)
{
    std::copy(s.begin(), s.end(), std::experimental::make_ostream_joiner(std::cout, " "));
}

void SudokuPlate::solvePlate()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (plate[i][j] != 0)
            {
                int k = plate[i][j];
                r[i].insert(k);
                c[j].insert(k);
                box[i / 3][j / 3].insert(k);
            }
    // Use optimized solver with most-constrained-variable heuristic
    dfSearchOptimized();
};

bool SudokuPlate::dfSearch(int idx)
{
    if (idx == 81)
        return true;
    int i = idx / 9;
    int j = idx % 9;
    if (plate[i][j] != 0)
        return dfSearch(idx + 1);
    for (int k = 1; k <= 9; k++)
    {
        if (check(k, i, j))
        {
            plate[i][j] = k;
            r[i].insert(k);
            c[j].insert(k);
            box[i / 3][j / 3].insert(k);
            if (dfSearch(idx + 1))
                return true;
            plate[i][j] = 0;
            r[i].erase(k);
            c[j].erase(k);
            box[i / 3][j / 3].erase(k);
        }
    }
    return false;
};

//check if the row, column and the 3x3 box contains the number
bool SudokuPlate::check(int x, int i, int j)
{
    return ((r[i].count(x) == 0) && (c[j].count(x) == 0) && (box[i / 3][j / 3].count(x) == 0));
};

// Count how many valid values can be placed at position (i,j)
int SudokuPlate::countPossibilities(int i, int j)
{
    if (plate[i][j] != 0)
        return 0; // Already filled

    int count = 0;
    for (int k = 1; k <= 9; k++)
    {
        if (check(k, i, j))
            count++;
    }
    return count;
};

// Optimized solver using most-constrained-variable heuristic
bool SudokuPlate::dfSearchOptimized()
{
    // Find the empty cell with fewest possibilities (most constrained)
    int minPossibilities = 10;
    int bestI = -1, bestJ = -1;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (plate[i][j] == 0)
            {
                int possibilities = countPossibilities(i, j);

                // If no valid values, this path is invalid
                if (possibilities == 0)
                    return false;

                // Choose cell with fewest possibilities
                if (possibilities < minPossibilities)
                {
                    minPossibilities = possibilities;
                    bestI = i;
                    bestJ = j;
                }
            }
        }
    }

    // If no empty cell found, puzzle is solved
    if (bestI == -1)
        return true;

    // Try each valid value for the most constrained cell
    for (int k = 1; k <= 9; k++)
    {
        if (check(k, bestI, bestJ))
        {
            plate[bestI][bestJ] = k;
            r[bestI].insert(k);
            c[bestJ].insert(k);
            box[bestI / 3][bestJ / 3].insert(k);

            if (dfSearchOptimized())
                return true;

            // Backtrack
            plate[bestI][bestJ] = 0;
            r[bestI].erase(k);
            c[bestJ].erase(k);
            box[bestI / 3][bestJ / 3].erase(k);
        }
    }

    return false;
};

void SudokuPlate::nextPlateIndex(int &i, int &j)
{
    if (j < 8)
        j++;
    else if (i < 8)
    {
        j = 0;
        i++;
    }
}

void SudokuPlate::printPlate()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << plate[i][j] << " ";
	    if ( j == 2 || j == 5 )
		    std::cout << "| ";
        }
	if ( i == 2 || i == 5 )
		std::cout << std::endl << "---------------------";
        std::cout << std::endl;
    }
};

void SudokuPlate::parsePlate(std::string fileName)
{
    tempString = "";

    std::ifstream ifs(fileName);
    if (!ifs.is_open())
    {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    tempString.assign((std::istreambuf_iterator < char >(ifs)),
                      (std::istreambuf_iterator < char >()));

    //Inject array, traverse plate
    int i = 0, j = 0;
    int s = 0;
    int cellCount = 0;

    while (s < tempString.length() && cellCount < 81)
    {
        char ch = tempString[s];

        // Skip whitespace, newlines, and separators
        if (ch == '\n' || ch == '\r' || ch == '|' || ch == ' ')
        {
            s++;
            continue;
        }

        // Process empty cells
        if (ch == empty_symbol)
        {
            plate[i][j] = 0;
            cellCount++;
            nextPlateIndex(i, j);
        }
        // Process digit cells
        else if (ch >= '1' && ch <= '9')
        {
            plate[i][j] = ch - '0';   //convert from ASCII
            cellCount++;
            nextPlateIndex(i, j);
        }
        else if (ch >= '0' && ch <= '9')
        {
            // Treat '0' as empty cell
            plate[i][j] = 0;
            cellCount++;
            nextPlateIndex(i, j);
        }

        s++;
    }

    if (cellCount != 81)
    {
        std::cerr << "Warning: Expected 81 cells, but parsed " << cellCount << " cells" << std::endl;
    }
};

#endif
