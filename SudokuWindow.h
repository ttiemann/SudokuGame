/**
 * @file SudokuWindow.h
 * @brief Defines the SudokuWindow class.
 */

#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>

#include "SudokuGrid.h"

/**
 * @class SudokuWindow
 * @brief Represents the main window of the Sudoku game.
 * 
 * The SudokuWindow class is a QWidget that provides the user interface for the Sudoku game.
 * It contains a SudokuGrid object to manage the game logic and a grid layout to arrange the cells.
 * The class also provides slots for generating and validating puzzles, as well as handling cell changes.
 */
class SudokuWindow
    : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a SudokuWindow object.
     * @param parent The parent widget.
     */
    SudokuWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Slot for generating a new puzzle.
     */
    void GeneratePuzzle();

    /**
     * @brief Slot for validating the current puzzle.
     */
    void ValidatePuzzle();

    /**
     * @brief Slot for handling cell changes.
     */
    void CellChanged();

private:
    SudokuGrid sudokuGrid; /**< The SudokuGrid object for managing the game logic. */
    bool isPuzzleGenerated = false; /**< Flag indicating whether a puzzle has been generated. */

    QGridLayout *gridLayout; /**< The grid layout for arranging the cells. */
    std::vector<std::vector<QLineEdit *>> cells; /**< The vector of QLineEdit objects representing the cells. */

    /**
     * @brief Updates the GUI based on the current state of the Sudoku grid.
     */
    void UpdateGUI();

    /**
     * @brief Sets the color of a cell at the specified row and column.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param color The color to set for the cell.
     */
    void SetCellColor(int row, int col, const QColor &color);
};
