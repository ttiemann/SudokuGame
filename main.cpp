#include <QApplication>

#include "SudokuWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SudokuWindow window;
    window.show();
    return app.exec();
}
