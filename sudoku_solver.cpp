#include "sudoku_solver.h"

int main()
{

    SudokuPlate su;
    su.parsePlate("sudoku_input.txt");
    su.printPlate();
    std::cout << "\n======SOLVED PUZZLE======\n" << std::endl;
    su.solvePlate();
    su.printPlate();

    return 0;
}
