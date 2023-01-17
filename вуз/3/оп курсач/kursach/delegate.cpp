#include "delegate.h"
#include"common.h"
#include <iostream>
Delegate::Delegate(QObject *parent)
    : QItemDelegate{parent}
{

}
QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{

    if (column==0){
    QRegularExpression rx("(([A-ZА-Яa-zа-я]{1})([a-zа-я]+))");
      QValidator *validator = new QRegularExpressionValidator(rx, parent);
      QLineEdit *edit = new QLineEdit(parent);
      edit->setValidator(validator);
          return edit;
    }
    if (column==1)
    {
        QRegularExpression rx("(([\\d]{4}))");
          QValidator *validator = new QRegularExpressionValidator(rx, parent);
          QLineEdit *edit = new QLineEdit(parent);
          edit->setValidator(validator);
              return edit;
    }
    if (column==2){
        QRegularExpression rx("^([0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
          QValidator *validator = new QRegularExpressionValidator(rx, parent);
          QLineEdit *edit = new QLineEdit(parent);
          edit->setValidator(validator);
              return edit;
    }



}
void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QString value =index.model()->data(index, Qt::EditRole).toString();
         QLineEdit *line = static_cast<QLineEdit*>(editor);
         line->setText(value);
}
void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
       QString value = line->text();
       model->setData(index, value);

}
void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
editor->setGeometry(option.rect);
}
