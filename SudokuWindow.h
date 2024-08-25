#ifndef SudokuWindow_H
#define SudokuWindow_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>

#include "SudokuGrid.h"

class SudokuWindow
    : public QWidget
{
    Q_OBJECT

public:
    SudokuWindow(QWidget *parent = nullptr);

private slots:
    void GeneratePuzzle();
    void ValidatePuzzle();
    void CellChanged();

private:
    SudokuGrid sudokuGrid;
    bool isPuzzleGenerated = false;

    QGridLayout *gridLayout;
    std::vector<std::vector<QLineEdit *>> cells;

    void UpdateGUI();
    void SetCellColor(int row, int col, const QColor &color);
};

#endif // SudokuWindow_H
