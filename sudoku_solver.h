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
    bool check(int x, int i, int j);
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
    dfSearch(0);
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

void SudokuPlate::nextPlateIndex(int &i, int &j)
{
    if (i < 9 && j < 8)
        j++;
    else if (i < 8 && j == 8)
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
    tempString.assign((std::istreambuf_iterator < char >(ifs)),
                      (std::istreambuf_iterator < char >()));
    //Inject array, traverse plate
    int i = 0, j = 0;
    int s = 0;
    while ( (i < 8 || j < 8) || (i == 8 && j == 8) )
    {
        if (tempString[s] == '\n' || tempString[s] == '\r' || tempString[s] == '|')
        {
            s++;
	    if (i == 8 && j == 8) break;
            continue;
        }
        else if (tempString[s] == empty_symbol)
        {
            plate[i][j] = 0;
            nextPlateIndex(i, j);
        }
        else
        {
            plate[i][j] = tempString[s] - 48;   //convert from ASCII
            nextPlateIndex(i, j);
        }
        s++;
    }

};

#endif
