#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

// Set image
   QPixmap pix("C:/Users/hp/Downloads/New folder/save.png");
   int w = ui->label_pix->width();
   int h = ui->label_pix->height();
   pix = pix.scaled(w, h);
   ui->label_pix->setPixmap(pix);

// Set database
    if(!connOpen()){
        ui->label->setText("Failed to open the database");
    }
    else{
        ui->label->setText("Connected...");
    }

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString username, password;
    username = ui->lineEdit_Username->text();
    password = ui->lineEdit_Password->text();
//check database
    if(!connOpen()){
        QMessageBox::warning(this, "..", "Failed to open the database", QMessageBox::Ok);
        return;
    }

//Open database
    connOpen();
//The QSqlQuery class provides a means of executing(thực hiện)  and manipulating(vận dụng) SQL statements.
    QSqlQuery qry;
    qry.prepare("select * from employeeinfo  where username = " + username + " and password = " + password);

     if(qry.exec()){
        int count = 0;
        while(qry.next()){
            count++;
        }
        if(count == 1){//find
            ui->label->setText("username and password is correct");
            connClose();
            this->hide();
            EmployeeInfo employeeinfo;
            employeeinfo.setModal(true);
            employeeinfo.exec();
        }
        if(count > 1){
            ui->label->setText("Duplicate username and password");
        }
        if(count < 1){//fail
            ui->label->setText("username and password is not correct");
        }
    }

}
