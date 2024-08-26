#include <QApplication>

#include "SudokuWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SudokuWindow window;
    window.setWindowTitle("Sudoku");
    window.show();
    return app.exec();
}
