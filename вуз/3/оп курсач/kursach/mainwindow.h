#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<Qdebug>
#include<QSqlQuery>
#include<QSqlTableModel>
#include <regex>
#include<QString>
#include <QSpinBox>
#include <QSortFilterProxyModel>
#include <QAbstractProxyModel>
#include<QRegularExpression>
#include <QRegExp>
#include "delegate.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();



    void on_search_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase     db;
    QSqlQuery   *query;
    QSqlTableModel *model;
    int row;
    Delegate *mydelegate;
    QSortFilterProxyModel *proxyModel;


};
#endif // MAINWINDOW_H
