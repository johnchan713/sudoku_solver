#include "sudoku_solver.h"

int main()
{

    SudokuPlate su;
    su.parsePlate("sudoku_input.txt");
    su.printPlate();

    //std::cout << "hello world" << std::endl;

    return 0;
}
