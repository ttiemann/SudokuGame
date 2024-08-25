#include "SudokuWindow.h"

#include <QMessageBox>
#include <QIntValidator>
#include <QPushButton>
#include <QFont>

SudokuWindow::SudokuWindow(QWidget *parent)
    : QWidget(parent)
{
    gridLayout = new QGridLayout(this);

    // Initialize the Sudoku grid layout
    setLayout(gridLayout);

    QFont font("Arial", 16);
    for (auto row = 0; row < SudokuGrid::SIZE; ++row)
    {
        std::vector<QLineEdit *> cellRow;
        for (auto col = 0; col < SudokuGrid::SIZE; ++col)
        {
            auto *cell = new QLineEdit(this);
            cell->setMaxLength(1);
            cell->setFont(font);
            cell->setAlignment(Qt::AlignCenter);
            cell->setValidator(new QIntValidator(1, 9, this));
            connect(cell, &QLineEdit::textChanged, this, &SudokuWindow::CellChanged);
            gridLayout->addWidget(cell, row, col);
            cellRow.push_back(cell);
        }
        cells.push_back(cellRow);
    }

    // Generate Puzzle Button
    auto *generateButton = new QPushButton("Generate Puzzle", this);
    connect(generateButton, &QPushButton::clicked, this, &SudokuWindow::GeneratePuzzle);
    gridLayout->addWidget(generateButton, SudokuGrid::SIZE, 0, 1, 4);

    // Validate Puzzle Button
    auto *validateButton = new QPushButton("Validate Puzzle", this);
    connect(validateButton, &QPushButton::clicked, this, &SudokuWindow::ValidatePuzzle);
    gridLayout->addWidget(validateButton, SudokuGrid::SIZE, 4, 1, 5);

    UpdateGUI();
    isPuzzleGenerated = true;
}

void SudokuWindow::GeneratePuzzle()
{
    isPuzzleGenerated = false;
    sudokuGrid.GeneratePuzzle();
    UpdateGUI();
    isPuzzleGenerated = true;
}

void SudokuWindow::ValidatePuzzle()
{
    if (sudokuGrid.Validate())
    {
        QMessageBox::information(this, "Sudoku", "Puzzle is valid!");
    }
    else
    {
        QMessageBox::warning(this, "Sudoku", "Puzzle is invalid.");
    }
}

void SudokuWindow::CellChanged()
{
    if (!isPuzzleGenerated)
    {
        return;
    }

    for (auto row = 0; row < SudokuGrid::SIZE; ++row)
    {
        for (auto col = 0; col < SudokuGrid::SIZE; ++col)
        {
            QString text = cells[row][col]->text();
            auto value = text.isEmpty() ? 0 : text.toInt();
            sudokuGrid.SetCell(row, col, value);
        }
    }
}

void SudokuWindow::UpdateGUI()
{
    for (auto row = 0; row < SudokuGrid::SIZE; ++row)
    {
        for (auto col = 0; col < SudokuGrid::SIZE; ++col)
        {
            int value = sudokuGrid.GetCell(row, col);
            if (value != 0)
            {
                cells[row][col]->setText(QString::number(value));
                cells[row][col]->setReadOnly(true);
                SetCellColor(row, col, Qt::lightGray);
            }
            else
            {
                cells[row][col]->clear();
                cells[row][col]->setReadOnly(false);
                SetCellColor(row, col, Qt::white);
            }
        }
    }
}

void SudokuWindow::SetCellColor(int row, int col, const QColor &color)
{
    QPalette palette = cells[row][col]->palette();
    palette.setColor(QPalette::Base, color);
    palette.setColor(QPalette::Text, Qt::black);
    cells[row][col]->setPalette(palette);
}
