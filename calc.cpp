#include "calc.h"
#include "ui_calc.h"

#include <QDebug>

double firstNum;

bool userIsTypingSecondNumber = false;

calc::calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calc)
{
    ui->setupUi(this);
    connect(ui -> pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui -> pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui -> pushButton_plusminus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui -> pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui -> pushButton_plus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui -> pushButton_minus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui -> pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui -> pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    ui -> pushButton_plus -> setCheckable(true);
    ui -> pushButton_minus -> setCheckable(true);
    ui -> pushButton_multiply -> setCheckable(true);
    ui -> pushButton_divide -> setCheckable(true);

}

calc::~calc()
{
    delete ui;
}

void calc::digit_pressed()
{
    // qDebug() << "Test";
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui -> pushButton_plus -> isChecked() || ui -> pushButton_minus -> isChecked() ||
            ui -> pushButton_multiply -> isChecked() || ui -> pushButton_divide -> isChecked()) && (!userIsTypingSecondNumber))
    {
        labelNumber = button -> text().toDouble();
        userIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else
    {
        if(ui -> label_2 -> text().contains('.') && button -> text() == "0")
        {
            newLabel = ui -> label_2 -> text() + button -> text();
        }
        else
        {
            labelNumber = (ui -> label_2 -> text() + button -> text()).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }
        // labelNumber = (ui -> label_2 -> text() + button -> text()).toDouble();
    }
    // labelNumber = (ui -> label_2 -> text() + button -> text()).toDouble();

    // newLabel = QString::number(labelNumber, 'g', 15);
    ui -> label_2 -> setText(newLabel);
}

void calc::on_pushButton_dot_released()
{
    ui -> label_2 -> setText(ui -> label_2 -> text() + '.');
}

void calc::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    double labelNumber;
     QString newLabel;
    if(button -> text() == "+/-")
    {
        labelNumber = ui -> label_2 -> text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label_2-> setText(newLabel);
    }

    if(button -> text() == "%")
    {
        labelNumber = ui -> label_2 -> text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label_2-> setText(newLabel);
    }

}

void calc::on_pushButton_clear_released()
{
    ui -> pushButton_plus -> setChecked(false);
    ui -> pushButton_minus -> setChecked(false);
    ui -> pushButton_multiply -> setChecked(false);
    ui -> pushButton_divide -> setChecked(false);

    userIsTypingSecondNumber = false;

    ui -> label_2 -> setText("0");
}

void calc::on_pushButton_equals_released()
{
    double labelNumber, secondNum;
    QString newLabel;
    secondNum = ui -> label_2 -> text().toDouble();

    if(ui -> pushButton_plus -> isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label_2 -> setText(newLabel);
        ui -> pushButton_plus -> setChecked(false);
    }
    else if(ui -> pushButton_minus -> isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label_2 -> setText(newLabel);
        ui -> pushButton_minus -> setChecked(false);
    }
    else if(ui -> pushButton_multiply -> isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label_2 -> setText(newLabel);
        ui -> pushButton_multiply -> setChecked(false);
    }
    else if(ui -> pushButton_divide -> isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label_2 -> setText(newLabel);
        ui -> pushButton_divide -> setChecked(false);
    }

    userIsTypingSecondNumber = false;
}

void calc::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    firstNum = ui -> label_2 -> text().toDouble();
    button -> setChecked(true);

}
