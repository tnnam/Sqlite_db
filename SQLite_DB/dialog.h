#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QFileInfo>
#include <QPixmap>
#include "employeeinfo.h"
namespace Ui {
class Dialog;
}

class Dialog : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    //Close database
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
     // Open database
    bool connOpen(){
            mydb = QSqlDatabase::addDatabase("QSQLITE");
            mydb.setDatabaseName("C:/Users/hp/Desktop/SQL/database.db");

            if(!mydb.open()){
                QMessageBox::warning(this, "..", "Failed to open the database", QMessageBox::Ok);
                return false;
            }
            else{
                return true;
            }
    }
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
