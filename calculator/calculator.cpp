#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>
#include <QSettings>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    setWindowTitle(tr("Calculator"));
    setFixedSize(QSize(200, 280));
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    QSettings settings;
    move(settings.value("settings/Calculator/windowPosition", "").toPoint());

    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->pushButton_plus_minus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percentage, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);

    customizeUi();
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_0:
        handleDigitPressed("0");
        break;
    case Qt::Key_1:
        handleDigitPressed("1");
        break;
    case Qt::Key_2:
        handleDigitPressed("2");
        break;
    case Qt::Key_3:
        handleDigitPressed("3");
        break;
    case Qt::Key_4:
        handleDigitPressed("4");
        break;
    case Qt::Key_5:
        handleDigitPressed("5");
        break;
    case Qt::Key_6:
        handleDigitPressed("6");
        break;
    case Qt::Key_7:
        handleDigitPressed("7");
        break;
    case Qt::Key_8:
        handleDigitPressed("8");
        break;
    case Qt::Key_9:
        handleDigitPressed("9");
        break;
    case Qt::Key_Plus:
        handleBinaryOperationPressed("+");
        ui->pushButton_plus->setChecked(true);
        break;
    case Qt::Key_Minus:
        handleBinaryOperationPressed("-");
        ui->pushButton_minus->setChecked(true);
        break;
    case Qt::Key_Asterisk:
        handleBinaryOperationPressed("×");
        ui->pushButton_multiply->setChecked(true);
        break;
    case Qt::Key_Slash:
        handleBinaryOperationPressed("÷");
        ui->pushButton_divide->setChecked(true);
        break;
    case Qt::Key_Period:
        on_pushButton_decimal_released();
        break;
    case Qt::Key_Enter:
        on_pushButton_equal_released();
        break;
    case Qt::Key_Return:
        on_pushButton_equal_released();
        break;
    case Qt::Key_Delete:
        on_pushButton_Clear_released();
        break;
    default:
        break;
    }
    QWidget::keyPressEvent(event);
}

void Calculator::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("settings/Calculator/windowPosition", pos());
    QWidget::closeEvent(event);
}

void Calculator::digit_pressed()
{
    // button which we press in the application
    QPushButton *button = (QPushButton *)sender();

    handleDigitPressed(button->text());
}

void Calculator::on_pushButton_decimal_released()
{
    ui->text_area->setText(ui->text_area->text() + ".");
}

void Calculator::unary_operation_pressed()
{
    QPushButton *button = (QPushButton *)sender();
    double labelNumber;
    QString newLabel;

    if (button->text() == "+/-")
    {
        labelNumber = ui->text_area->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->text_area->setText(newLabel);
    }

    if (button->text() == "%")
    {
        labelNumber = ui->text_area->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->text_area->setText(newLabel);
    }
}

void Calculator::on_pushButton_Clear_released()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->text_area->setText("0");
    ui->text_area_up->setText("");
}

void Calculator::on_pushButton_equal_released()
{
    double labelNumber, secondNum;

    ui->text_area_up->setText(ui->text_area_up->text() + ui->text_area->text());
    secondNum = ui->text_area->text().toDouble();
    QString newLabel;

    if (ui->pushButton_plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->text_area->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->text_area->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->text_area->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }
    else if (ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->text_area->setText(newLabel);
        ui->pushButton_multiply->setChecked(false);
    }

    userIsTypingSecondNumber = false;
}

void Calculator::binary_operation_pressed()
{
    QPushButton *button = (QPushButton *)sender();

    handleBinaryOperationPressed(button->text());

    button->setChecked(true);
}

void Calculator::customizeUi()
{
    QString style1 = "border-color:rgb(46, 52, 54); color:rgb(244, 188, 71); background-color:rgb(14, 31, 44);";
    QString style2 = "border-color:rgb(46, 52, 54); color:rgb(211, 71, 40); background-color:rgb(14, 31, 44);";
    QString style3 = "border-color:rgb(46, 52, 54); color:rgb(85, 195, 183); background-color:rgb(14, 31, 44);";
    ui->pushButton_decimal->setStyleSheet(style1);
    ui->pushButton_Clear->setStyleSheet(style1);
    ui->pushButton_plus_minus->setStyleSheet(style1);
    ui->pushButton_percentage->setStyleSheet(style1);
    ui->pushButton_divide->setStyleSheet(style2);
    ui->pushButton_multiply->setStyleSheet(style2);
    ui->pushButton_minus->setStyleSheet(style2);
    ui->pushButton_plus->setStyleSheet(style2);
    ui->pushButton_equal->setStyleSheet(style2);
    ui->text_area->setStyleSheet(style3);
    ui->text_area_up->setStyleSheet(style3);
    ui->pushButton_0->setStyleSheet(style3);
    ui->pushButton_1->setStyleSheet(style3);
    ui->pushButton_2->setStyleSheet(style3);
    ui->pushButton_3->setStyleSheet(style3);
    ui->pushButton_4->setStyleSheet(style3);
    ui->pushButton_5->setStyleSheet(style3);
    ui->pushButton_6->setStyleSheet(style3);
    ui->pushButton_7->setStyleSheet(style3);
    ui->pushButton_8->setStyleSheet(style3);
    ui->pushButton_9->setStyleSheet(style3);
}

void Calculator::handleDigitPressed(const QString &buttonText)
{
    double labelNumber;
    QString newLabel;

    if ((ui->pushButton_plus->isChecked() ||
            ui->pushButton_minus->isChecked() ||
            ui->pushButton_multiply->isChecked() ||
            ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber))
    {
        labelNumber = buttonText.toDouble();
        userIsTypingSecondNumber = true;
         newLabel = QString::number(labelNumber, 'g', 15);
    }
    else
    {
        if (ui->text_area->text().contains('.') && buttonText == "0")
        {
            newLabel = (ui->text_area->text() + buttonText);
        }
        else
        {
            labelNumber = (ui->text_area->text() + buttonText).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }
    }

    ui->text_area->setText(newLabel);
}

void Calculator::handleBinaryOperationPressed(const QString &buttonText)
{
    firstNum = ui->text_area->text().toDouble();

    if (buttonText == "+")
    {
        ui->text_area_up->setText(ui->text_area->text() + "+");
    }
    else if (buttonText == "-")
    {
        ui->text_area_up->setText(ui->text_area->text() + "-");
    }
    else if (buttonText == "×")
    {
        ui->text_area_up->setText(ui->text_area->text() + "×");
    }
    else if (buttonText == "÷")
    {
        ui->text_area_up->setText(ui->text_area->text() + "÷");
    }
}
