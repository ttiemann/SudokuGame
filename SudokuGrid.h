/**
 * @file SudokuGrid.h
 * @brief Declaration of the SudokuGrid class.
 */

#pragma once

#include <random>
#include <vector>

/**
 * @class SudokuGrid
 * @brief Represents a Sudoku grid.
 */
class SudokuGrid
{
public:
    /**
     * @brief Constructs a SudokuGrid object.
     */
    SudokuGrid();

    /**
     * @brief Generates a new Sudoku puzzle.
     */
    void GeneratePuzzle();

    /**
     * @brief Validates the Sudoku grid.
     * @return True if the grid is valid, false otherwise.
     */
    bool Validate() const;

    /**
     * @brief Sets the value of a cell in the Sudoku grid.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param value The value to set.
     */
    void SetCell(int row, int col, int value);

    /**
     * @brief Gets the value of a cell in the Sudoku grid.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @return The value of the cell.
     */
    int GetCell(int row, int col) const;

    /**
     * @brief Prints the Sudoku grid.
     */
    void PrintBoard() const;

    /**
     * @brief The size of the Sudoku grid.
     */
    static constexpr int SIZE = 9;

private:
    std::vector<std::vector<int>> grid; /**< The Sudoku grid. */

    /**
     * @brief Checks if placing a number in a cell is valid.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param num The number to place.
     * @return True if the placement is valid, false otherwise.
     */
    bool IsValidPlacement(int row, int col, int num) const;

    /**
     * @brief Solves the Sudoku grid.
     * @return True if the grid is solvable, false otherwise.
     */
    bool Solve();

    /**
     * @brief Fills the Sudoku grid with numbers.
     * @return True if the grid is filled, false otherwise.
     */
    bool FillGrid();

    /**
     * @brief Removes numbers from the Sudoku grid.
     * @param count The number of numbers to remove.
     */
    void RemoveNumbers(int count);

    /**
     * @brief Checks if it is safe to place a number in a cell.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param num The number to place.
     * @return True if it is safe to place the number, false otherwise.
     */
    bool IsSafe(int row, int col, int num) const;

    /**
     * @brief Finds an empty location in the Sudoku grid.
     * @param row The row index of the empty location.
     * @param col The column index of the empty location.
     * @return True if an empty location is found, false otherwise.
     */
    bool FindEmptyLocation(int &row, int &col) const;

    std::random_device rd;                                /**< Random number generator seed. */
    std::mt19937 rng{rd()};                               /**< Random number generator. */
    std::uniform_int_distribution<int> dist{0, SIZE - 1}; /**< Random number distribution. */
};