#include "inputedge.h"
#include "ui_inputedge.h"

inputEdge::inputEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputEdge)
{
    ui->setupUi(this);
    QFont fontSet;
    fontSet.setFamily("KaiTi");
    this->setFont(fontSet);
}

inputEdge::~inputEdge()
{
    delete ui;
}

void inputEdge::on_buttonBox_accepted()
{
    int ver1,ver2,weight;
    ver1=this->ui->vertexNumSpin->value();
    ver2=this->ui->vertexNumSpin2->value();
    weight=this->ui->routineWeight->value();
    emit dataGet(ver1,ver2,weight);
}
