#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "note.h"
#include "note.cpp"
#include <QTextStream>
#include <QString>
#include <QtSql>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_toggled(bool checked)
{

}


void MainWindow::on_pushButton_clicked()
{
    QString text;

    NoteTest();
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("db_name.sqlite");
    QSqlQuery query;
    QString str = " CREATE  TABLE IF NOT EXIST addressbok ( "
                        "number INTEGER PRIMARY KEY NOT NULL,"
                        "name VARCHAR(15),"
                        "phone VARCHAR(12),"
                        "email VARCHAR(15)"
                  ")";
    if(sdb.open() && query.exec(str)){
        ui->label->setText("Data base ");
    }
    if(sdb.open()){
        ui->label->setText("db c");
    }
    QString text = "234";
    QString strF =
            "INSERT INTO addressbok(number , name,phone,email)"
            "VALUES(%1,'%2','%3','%4');";
    str  = strF.arg(text)
                .arg("Piggy")
                .arg("+474290")
                .arg("piggy@email.ru");
    if(!query.exec(str)){
         ui->label_2->setText("data accepted");
    }
}
