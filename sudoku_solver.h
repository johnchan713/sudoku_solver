#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

class SudokuPlate
{
 private:
    short plate[9][9] = { 0 };
    const char empty_symbol = 'x';
    std::string tempString;
    std::unordered_set<short> r[9]; //checking set
    std::unordered_set<short> c[9];
    std::unordered_set<short> box[3][3];

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
    void dfSearch(short n[9][9], short i, short j);
    bool check(short x, short i, short j);

};


void SudokuPlate::solvePlate()
{
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (plate[i][j] != 0)
                { 
			short k = plate[i][j];
			r[i].insert(k);
			c[j].insert(k);
			box[i/3][j/3].insert(k);
                }
           	dfSearch(plate,(short)0,(short)0); 
}

void SudokuPlate::dfSearch(short n[9][9], short i, short j)
{
}

//check if the row, column and the 3x3 box contains the number
bool SudokuPlate::check(short x, short i, short j)
{
	return (r[i].count(x) == 0 && c[j].count(x) == 0 &&
			box[i/3][j/3].count(x) == 0)
}

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
        }
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
    while (i < 8 || j < 8)
    {
        if (tempString[s] == '\n' || tempString[s] == '\r' || tempString[s] == '|')
        {
            s++;
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
