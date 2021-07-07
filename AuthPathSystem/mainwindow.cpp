#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database=QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("localhost");
    database.setDatabaseName("serverdb");
    database.setPort(5432);
    database.setPassword("root");
    database.setUserName("postgres");
    if(database.open())
       {
        qDebug("open");
    }
    else{
        qDebug("no open");
    }
    query = new QSqlQuery(database);


}
MainWindow::~MainWindow()
{
    delete ui;
}

//recive data and insert in db
void MainWindow::on_pushButton_clicked()
{
        database.open();
        query = new QSqlQuery(database);
      query->prepare("INSERT INTO pocs (id,name) "
                  "VALUES (:id,:name)");
      query->bindValue(":id",1);
      query->bindValue(":name", "Barts");
      query->exec();
      database.close();
}

