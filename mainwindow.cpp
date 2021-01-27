#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->displayPanel->clear();

    operatorActive = false;
    isNumber = false;

    ui->actionGroup->connect(ui->actionGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(actionGroupClicked(QAbstractButton*)));
    ui->numberGroup->connect(ui->numberGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(numberGroupClicked(QAbstractButton*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getResult() {
    QString displayLabel = ui->displayPanel->text();

     if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
         displayLabel.QString::chop(1);
     }

     list.append(displayLabel);

     double result = 0;

     bool first = true;

     QString oper = "";

     foreach(QString item, list)
     {
         if(first){
             result = item.toDouble();
             first = false;
             continue;
         }

         if(item == "+" || item == "-" || item == "*" || item == "/"){
             oper = item;
         }else{
             if(oper == "+"){
                 result += item.toDouble();
             }else if(oper == "-"){
                 result -= item.toDouble();
             }else if(oper == "*"){
                 result *= item.toDouble();
             }else if(oper == "/"){
                 result /= item.toDouble();
             }
             oper = "";
         }
     }

     list.clear();

     displayLabel = QString::number(result,'g', DIGIT_LIMIT);

     ui->displayPanel->setText(displayLabel);

}

void MainWindow::numberGroupClicked(QAbstractButton* button)
{
    QString displayLabel = ui->displayPanel->text();

    if (operatorActive) {
         qDebug() << "QString str = " << currentOperator;
        list.append(currentOperator);
        operatorActive = false;
        qDebug() << "QString str = " << list;
        displayLabel.clear();
    }

    if (displayLabel.length() >= DIGIT_LIMIT) {
        return;
    }

    displayLabel.append(button->text());

    ui->displayPanel->setText(displayLabel);
}

void MainWindow::actionGroupClicked(QAbstractButton* button)
{
    QString displayLabel = ui->displayPanel->text();

    qDebug() << "QString str = " << displayLabel;

    if(displayLabel != ""){
        if(!operatorActive){
            list.append(displayLabel);
        }
        isNumber = true;
    }

    if(isNumber){
        currentOperator = button->text().at(0);
        operatorActive = true;
    }

}

void MainWindow::on_actionCalc_clicked()
{
    QString displayLabel = ui->displayPanel->text();

    if (!isNumber || displayLabel.length() < 1 || operatorActive || list.length() < 2) {
        return;
    }

    getResult();

    isNumber = false;

}

void MainWindow::on_actionClear_clicked()
{
    ui->displayPanel->clear();
    operatorActive = false;
    isNumber = false;
    list.clear();
}

void MainWindow::on_actionDel_clicked()
{
    QString displayLabel = ui->displayPanel->text();

    if (displayLabel.length() == 0) {
        return;
    }

    displayLabel.QString::chop(1);
    ui->displayPanel->setText(displayLabel);
}

void MainWindow::on_actionSign_clicked()
{
    QString displayLabel = ui->displayPanel->text();
    double percentage = displayLabel.toDouble();
    percentage *= -1;
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
    ui->displayPanel->setText(displayLabel);
}

void MainWindow::on_comma_clicked()
{
    QString displayLabel = ui->displayPanel->text();

    if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||
        displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }

    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }

    displayLabel.append('.');
    ui->displayPanel->setText(displayLabel);
}

