#include <cstdio>
#include <iostream>

#include "SudokuGrid.h"

int main()
{
    printf("Hello, from Sudoku!\n");

    SudokuGrid sudoku;
    sudoku.GeneratePuzzle();

    sudoku.PrintBoard();
}
