#include "SudokuGrid.h"
#include <iostream>
#include <algorithm>
#include <random>

using std::vector;

SudokuGrid::SudokuGrid()
{
    GeneratePuzzle();
}

void SudokuGrid::GeneratePuzzle()
{
    FillGrid();        // Generate a valid Sudoku board
    RemoveNumbers(40); // Remove numbers to create the puzzle (e.g., remove 40 cells)
}

bool SudokuGrid::Validate() const
{
    // Validate rows, columns, and subgrids
    for (int i = 0; i < SIZE; ++i)
    {
        std::vector<bool> rowCheck(SIZE + 1, false);
        std::vector<bool> colCheck(SIZE + 1, false);
        std::vector<bool> boxCheck(SIZE + 1, false);
        for (int j = 0; j < SIZE; ++j)
        {
            // Check row
            if (grid[i][j] != 0)
            {
                if (rowCheck[grid[i][j]])
                {
                    return false; // Duplicate found in row
                }
                rowCheck[grid[i][j]] = true;
            }

            // Check column
            if (grid[j][i] != 0)
            {
                if (colCheck[grid[j][i]])
                {
                    return false; // Duplicate found in column
                }
                colCheck[grid[j][i]] = true;
            }

            // Check subgrid
            int boxRow = 3 * (i / 3) + j / 3;
            int boxCol = 3 * (i % 3) + j % 3;
            if (grid[boxRow][boxCol] != 0)
            {
                if (boxCheck[grid[boxRow][boxCol]])
                {
                    return false; // Duplicate found in subgrid
                }
                boxCheck[grid[boxRow][boxCol]] = true;
            }
        }
    }
    return true; // No duplicates found, board is valid
}

void SudokuGrid::SetCell(int row, int col, int value)
{
    grid[row][col] = value;
}

int SudokuGrid::GetCell(int row, int col) const
{
    return grid[row][col];
}

bool SudokuGrid::IsValidPlacement(int row, int col, int num) const
{
    return IsSafe(row, col, num);
}

bool SudokuGrid::Solve()
{
    int row = 0;
    int col = 0;
    if (!FindEmptyLocation(row, col))
    {
        return true; // Puzzle solved
    }

    vector<int> nums(SIZE);
    int value = 1;
    std::iota(nums.begin(), nums.end(), value);

    std::shuffle(nums.begin(), nums.end(), rng); // Randomize numbers to try

    for (int num : nums)
    {
        if (IsSafe(row, col, num))
        {
            grid[row][col] = num;
            if (Solve())
            {
                return true;
            }
            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

bool SudokuGrid::FillGrid()
{
    // Start with an empty board
    grid = vector<vector<int>>(SIZE, vector<int>(SIZE, 0));
    return Solve();
}

void SudokuGrid::RemoveNumbers(int count)
{
    int removed = 0;
    while (removed < count)
    {
        int i = dist(rng);
        int j = dist(rng);
        if (grid[i][j] != 0)
        {
            grid[i][j] = 0;
            removed++;
        }
    }
}

bool SudokuGrid::IsSafe(int row, int col, int num) const
{
    // Check row for the number
    for (int x = 0; x < SIZE; x++)
    {
        if (grid[row][x] == num)
        {
            return false;
        }
    }

    // Check column for the number
    for (int y = 0; y < SIZE; y++)
    {
        if (grid[y][col] == num)
        {
            return false;
        }
    }

    // Check subgrid for the number
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (grid[r + startRow][c + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool SudokuGrid::FindEmptyLocation(int &row, int &col) const
{
    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            if (grid[r][c] == 0)
            {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}

void SudokuGrid::PrintBoard() const
{
    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}