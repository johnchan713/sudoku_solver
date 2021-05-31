#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <iostream>
#include <fstream>
#include <string>

class SudokuPlate
{
 private:
    short plate[9][9] = { 0 };
    const char empty_symbol = 'x';
    std::string tempString;

 public:
    SudokuPlate() {};
    ~SudokuPlate() {};
    void nextPlateIndex(int &i, int &j);
    void printPlate();
    void parsePlate(std::string fileName);
    void printString()
    {
        std::cout << tempString << std::endl;
    }

};

void SudokuPlate::nextPlateIndex(int &i, int& j)
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
