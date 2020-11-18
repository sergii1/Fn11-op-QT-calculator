#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator* calculator = new Calculator;
    calculator -> show();
    return a.exec();
    delete calculator;
}
