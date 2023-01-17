#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include<iostream>

int column;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



mydelegate=new Delegate(this);
db= QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("./train.db");
if(db.open()){
    qDebug("open");
}
else{
    qDebug("faggot");
}
query=new QSqlQuery(db);
query->exec("CREATE TABLE TRAINS(DESTONATION TEXT, NUMBER TEXT, TIME TEXT);");
model= new QSqlTableModel(this, db);
model->setTable("TRAINS");
model->select();
ui->tableView->setModel(model);
ui->tableView->setItemDelegate(mydelegate);
proxyModel = new QSortFilterProxyModel();
proxyModel->setSourceModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     model->insertRow(model->rowCount());

}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row=index.row();
    column=index.column();

}


void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(row);
}





void MainWindow::on_search_textChanged(const QString &arg1)
{
    int columFind; // По какой колонке будем искать
      ui->tableView->setModel(proxyModel);


      //Устанавливаем регулярное выражения для фильтра
      QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(QRegExp::FixedString);
      QRegExp regExp(ui->search->text(),Qt::CaseInsensitive,syntax);
      QString list = regExp.pattern();

         proxyModel->setFilterFixedString(list);
}

