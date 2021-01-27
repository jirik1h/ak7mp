#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QKeyEvent>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool operatorActive;
    QChar currentOperator;
    QString number;
    bool isNumber;
    void getResult();
    const int DIGIT_LIMIT = 16;
    QStringList list;

private slots:
    void numberGroupClicked(QAbstractButton*);
    void actionGroupClicked(QAbstractButton*);
    void on_actionDel_clicked();
    void on_actionCalc_clicked();
    void on_comma_clicked();
    void on_actionClear_clicked();
    void on_actionSign_clicked();

};
#endif // MAINWINDOW_H
