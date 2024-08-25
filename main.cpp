#include <cstdio>
#include <iostream>

#include "SudokuGrid.h"

int main(int argc, char *argv[])
{
    printf("Hello, from Sudoku!\n");

    SudokuGrid sudoku;
    sudoku.GeneratePuzzle();

    sudoku.PrintBoard();
}
