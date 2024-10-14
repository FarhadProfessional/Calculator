#pragma once

#include <QWidget>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void digit_pressed();

    void on_pushButton_decimal_released();

    void unary_operation_pressed();

    void on_pushButton_Clear_released();
    void on_pushButton_equal_released();

    void binary_operation_pressed();

private:
    void customizeUi();
    void handleDigitPressed(const QString &buttonText);
    void handleBinaryOperationPressed(const QString &buttonText);

private:
    Ui::Calculator *ui;

    double firstNum;
    bool userIsTypingSecondNumber = false;
};
