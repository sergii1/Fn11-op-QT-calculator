#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStack>
#include <QGridLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>

class QLCDNumber;
class QPushButton;

class Calculator :  public QWidget {
    Q_OBJECT
private:
    QButtonGroup* m_rb_group1;
    QButtonGroup* m_rb_group2;
   // QRadioButton* m_rb1;
   // QRadioButton* m_rb2;
  //  QRadioButton* m_rb_dark;
    //QRadioButton* m_rb_light;
    QLCDNumber* m_plcd;
    QGridLayout* m_Layout;
    QStack<QString> m_stk;
    QString m_strDisplay;

public:
    Calculator(QWidget* pwgt = nullptr);
    QPushButton* createButton(const QString& str);
    void CommonCalculator();
    void EngineerCalculator();
    void calculateBinary();
    void calculateUnary();

public slots:
    void slotButtonClicked();
    void change_calculator_type();
    void change_the_color_theme();
};

#endif // CALCULATOR_H
