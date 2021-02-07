#include "inputvertex.h"
#include "ui_inputvertex.h"
#include <QMessageBox>


inputVertex::inputVertex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputVertex)
{
    ui->setupUi(this);
    this->setWindowTitle("添加地点");
    QFont fontSet;
    fontSet.setFamily("KaiTi");
    this->setFont(fontSet);
}

inputVertex::~inputVertex()
{
    delete ui;
}

void inputVertex::on_buttonBox_accepted()
{
    QString str;
    str=this->ui->verNumInput->text();
    if(str.isEmpty()==true){
        QMessageBox a;
        a.information(this,"Error","未输入地点编号");
    }else{
        int verNum=str.toInt();
        str=this->ui->verNameInput->text();
        if(str.isEmpty()==true){
            QMessageBox a;
            a.information(this,"Error","未输入地点名称");
        }else{
            string verName=str.toStdString();
            str=this->ui->verInfInput->toPlainText();
            string verInf=str.toStdString();
            if(verInf.empty()==true){
                emit dataGet(new VertexChain(verNum,verName));
            }else{
                emit dataGet(new VertexChain(verNum,verName,verInf));
            }
        }
    }
}
