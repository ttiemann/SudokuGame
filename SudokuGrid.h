#pragma once

#include <random>
#include <vector>

class SudokuGrid
{
public:
    SudokuGrid();
    ~SudokuGrid() = default;

    void GeneratePuzzle();
    bool Validate() const;
    void SetCell(int row, int col, int value);
    int GetCell(int row, int col) const;

    void PrintBoard() const;

    static constexpr int SIZE = 9; // Size of Sudoku grid (9x9)

private:
    std::vector<std::vector<int>> grid;

    bool IsValidPlacement(int row, int col, int num) const;
    bool Solve();
    bool FillGrid();
    void RemoveNumbers(int count);
    bool IsSafe(int row, int col, int num) const;
    bool FindEmptyLocation(int &row, int &col) const;

    // Random number generation utilities
    std::random_device rd;
    std::mt19937 rng{rd()}; // Random number generator
    std::uniform_int_distribution<int> dist{0, SIZE - 1};
};