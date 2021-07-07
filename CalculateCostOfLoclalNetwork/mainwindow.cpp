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

    //put our data base in QSqlTableModel
    model = new QSqlTableModel(this,database);
    //set table in widget
    model->setTable("visits");
    //select it
    model->select();
    ui->tableView->setModel(model);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//execute main calculation
void MainWindow::on_pushButton_clicked()
{
    // set price for one pc and one server
    const float SERVER_PRICE  = 345.50;
    const float PC_PRICE =  450.4;
    const float ROUTER_PRICE = 2300.1;

    //get name of visitor
    QString name_of_visitor = ui->lineEdit_3->text();

    QString price_for_PC = ui->lineEdit->text();
    float price_for_pc = price_for_PC.toFloat();
    QString price_for_Server = ui->lineEdit_2->text();
    float price_for_server = price_for_Server.toFloat();

    //if consumer wants to buy router
    if(ui->radioButton->isChecked()){
         float total_price = ((price_for_pc*PC_PRICE)+(price_for_server *SERVER_PRICE)+ROUTER_PRICE);
         QString price = QString::number(total_price);//from string to int
         ui->label_3->setText(price); // set price;
         QMessageBox::information(this,"checked","price ");
    }

    float total_price = ((price_for_pc*PC_PRICE)+(price_for_server *SERVER_PRICE));


    QString price = QString::number(total_price);//from string to int
    ui->label_3->setText(price); // set price;
    //open data base
    database.open();
    if(database.open())
       {
        qDebug("open");
    }
    else{
        qDebug("no open");
    }
    query = new QSqlQuery(database);
    //write down sql request
    query->prepare("INSERT INTO visits (name,price) "
              "VALUES (:name,:price)");
     //bind Values
     query->bindValue(":name",name_of_visitor);
     query->bindValue(":price",price);
     //exec sql request
     query->exec();
     //close data base

     database.close();

}

//add row to end of table
void MainWindow::on_pushButton_2_clicked()
{
    //add row to end of table with method "rowCount"
    model->insertRow(model->rowCount());
}

//delete row
void MainWindow::on_pushButton_3_clicked()
{
    //get selected row
    model->removeRow(row);
}

//get index of row
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}




