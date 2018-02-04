#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeStack()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(lowerStack()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(restart()));


    ui->label_3->setText(tr("Witaj w programie:\nSystem eskpercki rozpoznawania alkoholi\n" \
        "\n\nZaznaczaj odpowiedzi aby uzyskać rodzaj \nalkoholu jaki Ciebie interesuje!\n" \
        "W tym celu poruszaj się po programie \nnaciskając poniższe przyciski:\n" \
        "Wstecz -kliknij aby cofnąć się \ndo poprzednęj strony.\nDalej -kliknij aby przejść do następnej strony.\n" \
        "Resetuj -kliknij aby zresetować wybrane do \ntej pory przez Ciebie odpowiedzi. \n" \
        "Miłego użytkowania!\n\nAutor: Michał Majewski, \nUKSW, numer albumu: 90890"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::collectP1()
{
    if(ui->checkBox11->isChecked()==true)
    {
        answer.append(ui->checkBox11->text());

    }
    if(ui->checkBox12->isChecked()==true)
    {
        answer.append("bialy");
    }
    if(ui->checkBox13->isChecked()==true)
    {
         answer.append("zolty");
    }
    if(ui->checkBox14->isChecked()==true)
    {
         answer.append("zloty");
    }
    if(ui->checkBox15->isChecked()==true)
    {
         answer.append("brązowy");
    }
    if(ui->checkBox16->isChecked()==true)
    {
         answer.append(ui->checkBox16->text());
    }
    if(ui->checkBox17->isChecked()==true)
    {
        answer+=ui->checkBox17->text();
    }
    if(ui->checkBox18->isChecked()==true)
    {
         answer.append(ui->checkBox18->text());
    }
    if(ui->checkBox19->isChecked()==true)
    {
         answer.append(ui->checkBox19->text());
    }
}

void MainWindow::collectP2()
{
    double tmp = ui->doubleSpinBox->value();
    answerPercent=tmp;
}

void MainWindow::collectP3()
{
    if(ui->checkBox31->isChecked()==true)
    {
        answer.append(ui->checkBox31->text());
    }
    if(ui->checkBox32->isChecked()==true)
    {
        answer.append("slodki");
    }
    if(ui->checkBox33->isChecked()==true)
    {
        answer.append(ui->checkBox33->text());
    }
    if(ui->checkBox34->isChecked()==true)
    {
        answer.append(ui->checkBox34->text());
    }
    if(ui->checkBox35->isChecked()==true)
    {
        answer.append("ziolowy");
    }
    if(ui->checkBox36->isChecked()==true)
    {
        answer.append("spirytusowy");
    }

}

void MainWindow::collectP4()
{
    if(ui->checkBox41->isChecked()==true)
    {
        answer.append("t");
    }
    else
    {
        answer.append("n");
    }
}

void MainWindow::collectP5()
{
    if(ui->checkBox51->isChecked()==true)
    {
        answer.append("eur");
    }
    if(ui->checkBox52->isChecked()==true)
    {
        answer.append("azj");
    }
    if(ui->checkBox53->isChecked()==true)
    {
        answer.append("amp");
    }
    if(ui->checkBox54->isChecked()==true)
    {
        answer.append("ams");;
    }
    if(ui->checkBox55->isChecked()==true)
    {
        answer.append("afr");
    }
    if(ui->checkBox56->isChecked()==true)
    {
        answer.append("aus");
    }
}

void MainWindow::collectP6()
{
    if(ui->checkBox61->isChecked()==true)
    {
        answer.append(ui->checkBox61->text());
    }
    if(ui->checkBox62->isChecked()==true)
    {
        answer.append("slodki2"); //ze względu na powtórzenie aby rozróżnić pojawia się w smaku słodki2
    }
    if(ui->checkBox63->isChecked()==true)
    {
        answer.append("kwasny");
    }
    if(ui->checkBox64->isChecked()==true)
    {
        answer.append("slony");
    }
    if(ui->checkBox65->isChecked()==true)
    {
        answer.append(ui->checkBox65->text());
    }

}

void MainWindow::collectAll()
{
    this->collectP1();
    this->collectP2();
    this->collectP3();
    this->collectP4();
    this->collectP5();
    this->collectP6();
}

void MainWindow::compareToDb()
{
    QFile file(":/database.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        if(line.at(0)!='#')
        {
            this->compareAnswers(line);
        }
    }
}

void MainWindow::compareAnswers(QString x)
{
    int summary=0; //wynik
    QVector<QString> collector; //zbiera tymczasowe QString odpowiedzi do kontenera
    QString tmp=""; //QString chary
    QString name; //nazwa alkoholu
    int i=0; //wskaznik QString na konkretnego QChar

    for(;i<x.length();i++)
    {
        if(x.at(i)==QChar(':'))
        {
            name=tmp;
            tmp.clear();
            break;
        }
        else
        {
            tmp+=x.at(i);
        }
    }
    i++;

    //odpowiedzi mozliwe na pytanie 1
    for(;i<x.length();i++)
    {
        if(x.at(i)==QChar(','))
        {
            collector.append(tmp);
            tmp.clear();
        }

        else if(x.at(i)==QChar(':'))
        {

            int before=0;
            for(int n=0; n < answer.length(); n++)
                if(collector.contains(answer.at(n)))
                {
                    summary+=4;
                    before++;
                }
            if(before==summary)
            {
                summary-=3;
            }
            else
            {
                summary+=10;
            }
            collector.clear();
            tmp.clear();
            break;
        }
        else
        {
            tmp+=x.at(i);
        }
    }
    i++;

    //odpowiedzi mozliwe na pytanie 2
    for(;i<x.length();i++)
    { 
        if(x.at(i)==QChar(':'))
        {
            double min=0,max=0;
            QString str=collector.first();
            min=str.toDouble();
            str=collector.last();
            max=str.toDouble();
            //za prawidłową odpowiedź jest +10pkt
            if(answerPercent>=min && answerPercent<=max)
            {
                summary+=10;
            }
            //za błędną każda różnica 4% to -7pkt
            else
            {
                int w;
                for(w=1; (w*4)+answerPercent<=min || answerPercent-(w*4)>=max; w++);
                summary+=w*(-7);
            }
            collector.clear();
            tmp.clear();
            break;
        }
        else if(x.at(i)==QChar('-'))
        {
            collector.append(tmp);
            tmp.clear();
        }
        else
        {
            tmp+=x.at(i);
        }

    }
    i++;
    //odpowiedzi mozliwe na pytanie 3
    for(;i<x.length();i++)
    {
        if(x.at(i)==QChar(','))
        {
            collector.append(tmp);
            tmp.clear();
        }

        else if(x.at(i)==QChar(':'))
        {

            int before=0;
            for(int n=0; n < answer.length(); n++)
                if(collector.contains(answer.at(n)))
                {
                    summary+=4;
                    before++;
                }
            if(before==summary)
            {
                summary-=3;
            }
            else
            {
                summary+=10;
            }
            collector.clear();
            tmp.clear();
            break;
        }
        else
        {
            tmp+=x.at(i);
        }
    }
    i++;
    //odpowiedzi mozliwe na pytanie 4
    for(;i<x.length();i++)
    {
        if(x.at(i)==QChar(':'))
        {
            collector.clear();
            tmp.clear();
            break;
        }
        else
        {
            tmp+=x.at(i);
            if(answer.contains(tmp)==true) summary+=10;
            else summary-=7;
        }
    }
    i++;
    //odpowiedzi mozliwe na pytanie 5
    for(;i<x.length();i++)
    {
        if(x.at(i)==QChar(','))
        {
            collector.append(tmp);
            tmp.clear();
        }

        else if(x.at(i)==QChar(':'))
        {

            int before=0;
            for(int n=0; n < answer.length(); n++)
                if(collector.contains(answer.at(n)))
                {
                    summary+=4;
                    before++;
                }
            if(before==summary)
            {
                summary-=3;
            }
            else
            {
                summary+=10;
            }
            collector.clear();
            tmp.clear();
            break;
        }
        else
        {
            tmp+=x.at(i);
        }
    }
    i++;
    //odpowiedzi mozliwe na pytanie 6
    for(;i<x.length();i++)
    {
        if(x.at(i)==QChar(','))
        {
            collector.append(tmp);
            tmp.clear();
        }

        else if(x.at(i)==QChar(':'))
        {

            int before=0;
            for(int n=0; n < answer.length(); n++)
                if(collector.contains(answer.at(n)))
                {
                    summary+=4;
                    before++;
                }
            if(before==summary)
            {
                summary-=3;
            }
            else
            {
                summary+=10;
            }
            collector.clear();
            tmp.clear();
            break;
        }
        else
        {
            tmp+=x.at(i);
        }
    }
    i++;

    result.append(qMakePair(summary,name));
}

void MainWindow::showResults()
{
   this->collectAll();
   this->compareToDb();
}

void MainWindow::sort()
{
    std::sort(result.begin(), result.end());
    std::reverse(result.begin(),result.end());
}

// SLOTS
void MainWindow::changeStack()
{
    if(ui->StackedWidget->currentIndex()<6)
    {
        ui->StackedWidget->setCurrentIndex(ui->StackedWidget->currentIndex()+1);
    }
    else
    {
        this->showResults();
        this->sort();

        QString msg = "Najbardziej pasującą odpowiedzią jest: " + result.at(0).second;
        msg+="\nMniej prawdopodobnymi odpowiedziami są: " + result.at(1).second + " i " + result.at(2).second;
        QMessageBox::information(this,tr("Wyniki"),msg);
        answer.clear();
        result.clear();
        answerPercent=0;
    }
}

void MainWindow::lowerStack()
{
    if(ui->StackedWidget->currentIndex()>0)
    {
        ui->StackedWidget->setCurrentIndex(ui->StackedWidget->currentIndex()-1);
    }

}

void MainWindow::restart()
{
    ui->checkBox11->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox12->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox13->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox14->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox15->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox16->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox17->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox18->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox19->setCheckState(Qt::CheckState::Unchecked);

    ui->doubleSpinBox->setValue(0);

    ui->checkBox31->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox32->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox33->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox34->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox35->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox36->setCheckState(Qt::CheckState::Unchecked);

    ui->checkBox41->setCheckState(Qt::CheckState::Unchecked);

    ui->checkBox51->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox52->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox53->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox54->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox55->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox56->setCheckState(Qt::CheckState::Unchecked);

    ui->checkBox61->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox62->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox63->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox64->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox65->setCheckState(Qt::CheckState::Unchecked);
}

