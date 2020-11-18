#include "Calculator.h"
#include <math.h>
#include <QDebug>
QPushButton* Calculator::createButton(const QString& str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    if (str == "pi")
    {
        pcmd->setStyleSheet("border: 1px solid gray;");
        return pcmd;
    }
    if (str.contains(QRegExp("[0-9]")) && (!str.contains(QRegExp("[/^]"))))
    {
        pcmd->setStyleSheet("border: 1px solid gray;");
        return pcmd;
    }
    if(str.contains("CE"))
    {
        pcmd->setStyleSheet("background-color: rgb(215, 215, 215); border: 1px solid gray; border-radius:50px;");
        return pcmd;
    }
    pcmd->setStyleSheet("background-color: rgb(255, 151, 57); color: white; border: 1px solid gray;");
    return pcmd;
}

Calculator::Calculator(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
    m_rb_group1 = new QButtonGroup();
    QRadioButton* rb1 = new QRadioButton("Обычный");
    rb1->setChecked(true);
    QRadioButton* rb2 = new QRadioButton("Инженерный");
    connect(rb1, SIGNAL(clicked()), SLOT(changeCalculatorType()));
    connect(rb2, SIGNAL(clicked()), SLOT(changeCalculatorType()));
    m_rb_group1->addButton(rb1);
    m_rb_group1->addButton(rb2);

    m_rb_group2 = new QButtonGroup();
    QRadioButton* rb_dark = new QRadioButton("Темный");
    QRadioButton* rb_light = new QRadioButton("Светлый");
    rb_light->setChecked(true);
    connect(rb_dark, SIGNAL(clicked()), SLOT(changeTheColorTheme()));
    connect(rb_light, SIGNAL(clicked()), SLOT(changeTheColorTheme()));
    m_rb_group2->addButton(rb_light);
    m_rb_group2->addButton(rb_dark);

    m_plcd = new QLCDNumber(12);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);


    QString aButtons[4][5] = {
        {"7", "8", "9", "/", "sqrt"},
        {"4", "5", "6", "*", "1/x"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"}
    };

    //Layout setup
    m_Layout = new QGridLayout;
    m_Layout->addWidget(m_plcd, 0, 0, 1, 5);
    //m_Layout->addWidget(rb1, 1, 0);
    //m_Layout->addWidget(rb2, 1, 1);
    m_Layout->addWidget(rb1, 1, 0);
    m_Layout->addWidget(rb2, 2, 0);
    m_Layout->addWidget(rb_light,1,1);
    m_Layout->addWidget(rb_dark,2,1);
    m_Layout->addWidget(createButton("CE"), 1, 4);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            m_Layout->addWidget(createButton(aButtons[i][j]), i + /*2*/+3, j);
        }
    }
    for (int i = 2; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_Layout->addWidget(createButton(aButtons[i][j]), i + /*2*/+3, j);
        }
    }
    setLayout(m_Layout);
    setFixedSize(400, 370);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Калькулятор(Обычный)");
}

void Calculator::commonCalculator()
{
    m_Layout->addWidget(m_plcd, 0, 0, 1, 5);
    QLayoutItem *item=m_Layout->itemAtPosition(1,8);
    QWidget *i=item->widget();
    if(i)
    {
        m_Layout->removeWidget(i);
        delete i;
    }
    for(int k = 0; k < 2; ++k)
    {
        for (int j = 0; j < 9; ++j)
        {
            QLayoutItem *item=m_Layout->itemAtPosition(k + 3,j);
            QWidget *i=item->widget();
            if(i)
            {
                m_Layout->removeWidget(i);
                delete i;
            }
        }
    }
    for(int k = 2; k < 4; ++k)
    {
        for (int j = 0; j < 8; ++j)
        {
            QLayoutItem *item=m_Layout->itemAtPosition(k + 3,j);
            QWidget *i=item->widget();
            if(i)
            {
                m_Layout->removeWidget(i);
                delete i;
            }
        }
    }
    m_Layout->addWidget(createButton("CE"), 1, 4);
    QString aButtons[4][5] = {{"7", "8", "9", "/", "sqrt"},
                              {"4", "5", "6", "*", "1/x"},
                              {"1", "2", "3", "-"},
                              {"0", ".", "=", "+"}
                             };
    //Layout setup
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            m_Layout->addWidget(createButton(aButtons[i][j]), i + 3, j);
        }
    }
    for (int i = 2; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_Layout->addWidget(createButton(aButtons[i][j]), i + 3, j);
        }
    }
    setFixedSize(400, 370);
    setWindowTitle("Калькулятор(Обычный)");
}

void Calculator::engineerCalculator()
{
    m_Layout->addWidget(m_plcd, 0, 0, 1, 9);
    QLayoutItem *item=m_Layout->itemAtPosition(1,4);
    QWidget *i=item->widget();
    if(i)
    {
        m_Layout->removeWidget(i);
        delete i;
    }

    for(int k = 0; k < 2; ++k)
    {
        for (int j = 0; j < 5; ++j)
        {
            QLayoutItem *item=m_Layout->itemAtPosition(k + 3,j);
            QWidget *i=item->widget();
            if(i)
            {
                m_Layout->removeWidget(i);
                delete i;
            }
        }
    }

    for(int k = 2; k < 4; ++k)
    {
        for (int j = 0; j < 4; ++j)
        {
            QLayoutItem *item=m_Layout->itemAtPosition(k + 3,j);
            QWidget *i=item->widget();
            if(i)
            {
                m_Layout->removeWidget(i);
                delete i;
            }
        }
    }
    m_Layout->addWidget(createButton("CE"), 1, 8);
    QString aButtons[4][9] = {
        {"sinh", "sin", "exp", "x^2", "7", "8", "9", "/", "sqrt"},
        {"cosh", "cos", "ln", "x^3", "4", "5", "6", "*", "1/x"},
        {"tanh", "tan", "log", "x^y", "1", "2", "3", "-", "1/x"},
        {"n!", "pi", "x^(1/3)", "x^(1/y)", "0", ".", "+", "="}
    };
    //Layout setup
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 9; ++j) {
            m_Layout->addWidget(createButton(aButtons[i][j]), i + 3, j);
        }
    }
    for (int i = 2; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            m_Layout->addWidget(createButton(aButtons[i][j]), i + 3, j);
        }
    }
    setFixedSize(600, 370);
    setWindowTitle("Калькулятор(Инженерный)");
}

void Calculator::calculateBinary()
{
    double dOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    double dOperand1 = m_stk.pop().toDouble();
    qDebug()<<"calculateBinary"<<dOperand1<<strOperation<<dOperand2;
    double dResult = 0;
    if (strOperation == "+") {
        dResult = dOperand1 + dOperand2;
    }
    if (strOperation == "-") {
        dResult = dOperand1 - dOperand2;
    }
    if (strOperation == "/") {
        dResult = dOperand1 / dOperand2;
    }
    if (strOperation == "*") {
        dResult = dOperand1 * dOperand2;
    }
    if (strOperation == "x^y") {
        dResult = pow(dOperand1, dOperand2);
    }
    if (strOperation == "x^(1/y)") {
        dResult = pow(dOperand1, 1/dOperand2);
    }
    m_plcd->display(dResult);
}

long factorial(int number)
{
    if(number<=1)
        return 1;
    else
        return number*factorial(number-1);
}

void Calculator::calculateUnary()
{
    QString strOperation = m_stk.pop();
    double dOperand = m_stk.pop().toDouble();
    double dResult = 1;
    qDebug()<<"\n calculateUnary "<<strOperation<<dOperand;
    if (strOperation == "sqrt") {
        dResult = sqrt(dOperand);
    }
    if (strOperation == "1/x") {
        dResult = 1/dOperand;
    }
    if (strOperation == "sinh") {
        dResult = sinh(dOperand);
    }
    if (strOperation == "sin") {
        dResult = sin(dOperand);
    }
    if (strOperation == "exp") {
        dResult = exp(dOperand);
    }
    if (strOperation == "x^2") {
        dResult = dOperand*dOperand;
    }
    if (strOperation == "cosh") {
        dResult = cosh(dOperand);
    }
    if (strOperation == "cos") {
        dResult = cos(dOperand);
    }
    if (strOperation == "ln") {
        dResult = log(dOperand);
    }
    if (strOperation == "x^3") {
        dResult = pow(dOperand, 3.0);
    }
    if (strOperation == "tanh") {
        dResult = tanh(dOperand);
    }
    if (strOperation == "tan") {
        dResult = tan(dOperand);
    }
    if (strOperation == "log") {
        dResult = log10(dOperand);
    }
    if (strOperation == "n!") {
        dResult = factorial(dOperand);
    }
    if (strOperation == "x^(1/3)") {
        dResult = pow(dOperand, double(1)/3);
    }
    qDebug()<<"\n res= "<<dResult;
    m_plcd->display(dResult);
}

void Calculator::slotButtonClicked()
{
    QString str = (dynamic_cast<QPushButton*>(sender()))->text();
    if (str == "CE") {
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }
    if (str == "pi") {
        m_strDisplay = "";
        m_plcd->display(M_PI);
        return;
    }
    qDebug()<<"STR" <<str<<" mstr"<<m_strDisplay;
    if (str.contains(QRegExp("[0-9]")) && (!str.contains(QRegExp("[/^]"))))
    {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else if (str == ".") {
        if((!m_strDisplay.contains(".")) && (m_strDisplay.contains(QRegExp("[0-9]"))))
        {
            m_strDisplay += str;
            m_plcd->display(m_strDisplay);
        }
    }
    else if((str.contains(QRegExp("[-+*=y]{1}")) || (str == "/")))
    {
        qDebug()<<"CONTAIN";
        if (m_stk.count() >= 2)
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            calculateBinary();
            m_stk.clear();
            m_strDisplay = "";
            m_stk.push(QString().setNum(m_plcd->value()));
            if (str != "=")
            {
                m_stk.push(str);
            }
        }
        else
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push (str);
            m_strDisplay = "";
        }
    }
    else
    {
        if (m_stk.count() >= 2)
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            calculateBinary();
            m_stk.clear();
            m_strDisplay = "";
            m_stk.push(QString().setNum(m_plcd->value()));
            if (str != "=")
            {
                m_stk.push(str);
            }
        }
        else
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push (str);
            calculateUnary();
            m_strDisplay = "";
        }
    }
}

void Calculator::changeCalculatorType(){

    if(dynamic_cast<QRadioButton*>(sender())->text() == "Обычный")
        commonCalculator();

    if(dynamic_cast<QRadioButton*>(sender())->text()== "Инженерный" )
        engineerCalculator();

}

void Calculator::changeTheColorTheme(){

    if(dynamic_cast<QRadioButton*>(sender())->text() == "Темный"){
        m_plcd->setStyleSheet("background-color:black; color: white;");
        this->setStyleSheet("background-color:black; color: white;");
    }

    if(dynamic_cast<QRadioButton*>(sender())->text() == "Светлый"){
        m_plcd->setStyleSheet("background-color:white; color:black;");
        this->setStyleSheet("background-color:white; color:black;");
    }
}

