#include "SudokuGrid.h"

#include <iostream>

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
    // Validate rows
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

            // Check 3x3 subgrid (box)
            int boxRow = 3 * (i / 3) + j / 3;
            int boxCol = 3 * (i % 3) + j % 3;
            if (grid[boxRow][boxCol] != 0)
            {
                if (boxCheck[grid[boxRow][boxCol]])
                {
                    return false; // Duplicate found in 3x3 subgrid
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
    auto row = 0;
    auto col = 0;
    if (!FindEmptyLocation(row, col))
    {
        return true; // Puzzle solved
    }

    vector<int> nums(SIZE);
    auto value = 1;
    std::generate(nums.begin(), nums.end(), [&value]()
                  { return value++; });

    std::shuffle(nums.begin(), nums.end(), rng); // Randomize numbers to try

    for (auto num : nums)
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
    auto removed = 0;
    while (removed < count)
    {
        auto i = dist(rng);
        auto j = dist(rng);
        if (grid[i][j] != 0)
        {
            grid[i][j] = 0;
            removed++;
        }
    }
}

bool SudokuGrid::IsSafe(int row, int col, int num) const
{
    // Check row, column, and 3x3 box for the number
    for (auto x = 0; x < SIZE; x++)
    {
        if (grid[row][x] == num || grid[x][col] == num)
        {
            return false;
        }
    }

    auto startRow = row - row % 3;
    auto startCol = col - col % 3;
    for (auto r = 0; r < 3; r++)
    {
        for (auto d = 0; d < 3; d++)
        {
            if (grid[r + startRow][d + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool SudokuGrid::FindEmptyLocation(int &row, int &col) const
{
    for (row = 0; row < SIZE; row++)
    {
        for (col = 0; col < SIZE; col++)
        {
            if (grid[row][col] == 0)
            {
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
        for (auto cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}