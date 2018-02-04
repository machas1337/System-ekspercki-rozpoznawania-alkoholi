#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void changeStack();
    void lowerStack();
    void restart();


private:
    Ui::MainWindow *ui;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<QString> answer;
    double answerPercent;
    QVector<QPair<int, QString>> result;

    //metody zbierające odpowiedzi użytkownika
    void collectP1();
    void collectP2();
    void collectP3();
    void collectP4();
    void collectP5();
    void collectP6();
    void collectAll();
    void compareToDb();
    void compareAnswers(QString x);
    void showResults();
    void sort();


};

#endif // MAINWINDOW_H
