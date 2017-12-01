#include "employeeinfo.h"
#include "ui_employeeinfo.h"

EmployeeInfo::EmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeInfo)
{
    ui->setupUi(this);
    Dialog conn;
    if(!conn.connOpen()){
        ui->labelSecStatus->setText("Failed to open the database");
    }
    else{
        ui->labelSecStatus->setText("Connected...");
    }
}

EmployeeInfo::~EmployeeInfo()
{
    delete ui;
}

void EmployeeInfo::on_saveButton_clicked()
{
    QString surname, name, eid, age;
    eid = ui->IDLineEdit->text();
    surname = ui->SurnameLineEdit->text();
    name = ui->NameLineEdit->text();
    age = ui->AgeLineEdit->text();

//check database
    if(!conn.connOpen()){
        QMessageBox::warning(this, "..", "Failed to open the database", QMessageBox::Ok);
        return;
    }

//Open database
    conn.connOpen();
//The QSqlQuery class provides a means of executing(thực hiện)  and manipulating(vận dụng) SQL statements.
    QSqlQuery qry;
    qry.prepare("insert into employeeinfo (eid, name, surname, age) values ('"+eid+"', '"+name+"', '"+surname+"', '"+age+"')");

     if(qry.exec()){
//        QMessageBox msgBox;
//        msgBox.setText("The document has been modified");
//        msgBox.setInformativeText("Do you want to save your changes?");
//        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//        msgBox.setDefaultButton(QMessageBox::Save);
//        int ret  = msgBox.exec();
//        switch (ret) {
//        case QMessageBox::Save:
//            //  Save was clicked
//            conn.connClose();
//            break;
//        case QMessageBox::Discard:
//            //Don't Save was clicked
//            break;
//         case QMessageBox::Cancel:
//            // Cancel was click
//            break;
//        default:
//            // should never be reached
//            break;
         QMessageBox::critical(this, tr("Save"), tr("Saved"));
         conn.connClose();
    }
     else{
         //check and put out error
         QMessageBox::critical(this, tr("error::"), qry.lastError().text());
     }
}
