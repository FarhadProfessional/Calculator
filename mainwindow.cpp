#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_calculator = new Calculator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_showCalculator_clicked()
{
    m_calculator->show();
}
