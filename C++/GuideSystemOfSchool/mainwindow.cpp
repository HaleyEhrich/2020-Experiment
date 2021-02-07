#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFont fontSet;
    fontSet.setFamily("KaiTi");
    this->setFont(fontSet);
    ui->setupUi(this);
    this->setWindowTitle("校园导游系统");
    this->resize(950,678);
    this->Map=new Graph();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//SLot defination
void MainWindow::welcomePage(){
    QFont fontSet;
    QWidget* welcomePageWi=new QWidget();
    QVBoxLayout* welcomeGroup=new QVBoxLayout();
    QHBoxLayout* buttonGroup=new QHBoxLayout();
    QLabel* welcomeMessage;//一行字“欢迎使用”
    QPushButton* welcome_group_newGraph,*welcome_group_openGraph,*welcome_group_exit;//两个按钮
    welcomeMessage=new QLabel("与肝胆人共事\n     无字句处读书");
    welcomeMessage->setAlignment(Qt::AlignCenter);
    welcome_group_newGraph=new QPushButton("  新建地图  ");
    welcome_group_openGraph=new QPushButton("  打开地图  ");
    welcome_group_exit = new QPushButton("  退出  ");
    fontSet.setPointSize(35);
    fontSet.setFamily("LiSu");
    fontSet.setBold(true);
    welcomeMessage->setFont(fontSet);
    fontSet.setFamily("KaiTi");
    fontSet.setPointSize(15);
    fontSet.setBold(false);
    welcome_group_newGraph->setFont(fontSet);
    welcome_group_openGraph->setFont(fontSet);
    welcome_group_exit->setFont(fontSet);
    welcome_group_newGraph->setStyleSheet("QPushButton{background-color: rgb(250, 250, 250);border:2px groove grey;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                          "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                          "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    welcome_group_openGraph->setStyleSheet("QPushButton{background-color: rgb(250, 250, 250);border:2px groove grey;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                          "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                          "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
     welcome_group_exit->setStyleSheet("QPushButton{background-color: rgb(250, 250, 250);border:2px groove grey;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                          "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                          "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

    buttonGroup->addStretch(7);
    buttonGroup->addWidget(welcome_group_newGraph);
    buttonGroup->addStretch(1);
    buttonGroup->addWidget(welcome_group_openGraph);
    buttonGroup->addStretch(1);
    buttonGroup->addWidget(welcome_group_exit);
    buttonGroup->addStretch(7);
    welcomeGroup->addStretch();
    welcomeGroup->addWidget(welcomeMessage);
    welcomeGroup->addStretch();

    welcomeGroup->addLayout(buttonGroup);
    welcomePageWi->setLayout(welcomeGroup);
    this->setCentralWidget(welcomePageWi);
    welcomePageWi->show();
    connect(welcome_group_newGraph,SIGNAL(clicked()),this,SLOT(mapOutPage()));
    connect(welcome_group_newGraph,SIGNAL(clicked()),welcomePageWi,SLOT(close()));
    connect(welcome_group_openGraph,SIGNAL(clicked()),this,SLOT(openMap()));
    connect(this,SIGNAL(openMapDataSuc()),welcomePageWi,SLOT(close()));
    connect(this,SIGNAL(openMapDataSuc()),this,SLOT(mapOutPage()));
    //connect(welcome_group_exit,SIGNAL(clicked()),this,SLOT(exitMap()));
    connect(welcome_group_exit,SIGNAL(clicked()),this,SLOT(close()));
}

void MainWindow::mapOutPage(){
    QFont fontSet;
    QWidget* mapPageWi=new QWidget();
    QHBoxLayout* mainPageGroup=new QHBoxLayout();//文本框以及按钮
    QVBoxLayout* buttonGroup=new QVBoxLayout();//保存按钮以及其它4个
    QPlainTextEdit* textShow=new QPlainTextEdit();//文本显示
    QPushButton* choice1=new QPushButton("添加地点");
    QPushButton* choice2=new QPushButton("添加路径");
    QPushButton* choice3=new QPushButton("查找地点");
    QPushButton* choice4=new QPushButton("导航");
    QPushButton* choice5=new QPushButton("更改地点信息");
    QPushButton* choice6=new QPushButton("更改边的权值");
    QPushButton* saveMap=new QPushButton("保存地图");
    QPushButton* exitMap=new QPushButton("退出");
    //属性设置
    this->setCentralWidget(mapPageWi);
    choice1->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    choice2->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    choice3->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    choice4->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    choice5->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    choice6->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    exitMap->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    saveMap->setStyleSheet("QPushButton{background-color: rgb(230, 230, 230);border:2px groove white;border-radius:4px;padding:1px 4px;border-style: outset;}"
                                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    fontSet.setFamily("KaiTi");
    fontSet.setPointSize(13);
    choice1->setFont(fontSet);
    choice2->setFont(fontSet);
    choice3->setFont(fontSet);
    choice4->setFont(fontSet);
    choice5->setFont(fontSet);
    choice6->setFont(fontSet);
    saveMap->setFont(fontSet);
    exitMap->setFont(fontSet);
    textShow->setFont(fontSet);

    buttonGroup->addWidget(choice1);
    buttonGroup->addWidget(choice2);
    buttonGroup->addWidget(choice3);
    buttonGroup->addWidget(choice4);
    buttonGroup->addWidget(choice5);
    buttonGroup->addWidget(choice6);
    buttonGroup->addStretch();
    buttonGroup->addWidget(exitMap);
    buttonGroup->addWidget(saveMap);
    mainPageGroup->addWidget(textShow);
    mainPageGroup->addLayout(buttonGroup);
    textShow->appendPlainText(this->Map->outGraph());
    mapPageWi->setLayout(mainPageGroup);
    mapPageWi->show();
    connect(choice1,SIGNAL(clicked()),this,SLOT(addVertexPage()));
    connect(choice2,SIGNAL(clicked()),this,SLOT(addEdgePage()));
    connect(choice3,SIGNAL(clicked()),this,SLOT(findVertex()));
    connect(choice4,SIGNAL(clicked()),this,SLOT(findShortestRotiune()));
    connect(choice5,SIGNAL(clicked()),this,SLOT(modifiedData()));
    connect(choice6,SIGNAL(clicked()),this,SLOT(modifieEdge()));
    connect(exitMap,SIGNAL(clicked()),this,SLOT(exitMap()));
    connect(saveMap,SIGNAL(clicked()),this,SLOT(saveMap()));
    connect(this,SIGNAL(refreshPage(QString)),textShow,SLOT(clear()));
    connect(this,SIGNAL(refreshPage(QString)),textShow,SLOT(appendPlainText(QString)));
    connect(this,SIGNAL(refreshText(QString)),textShow,SLOT(clear()));
    connect(this,SIGNAL(refreshText(QString)),textShow,SLOT(appendPlainText(QString)));
    connect(this,SIGNAL(saveMapDataSuc()),mapPageWi,SLOT(close()));
    connect(this,SIGNAL(saveMapDataSuc()),this,SLOT(welcomePage()));
}

void MainWindow::addVertexPage(){
    inputVertex* dataInputDia=new inputVertex();
    dataInputDia->show();
    connect(dataInputDia,SIGNAL(dataGet(VertexChain*)),this,SLOT(addVertex(VertexChain*)));
    connect(this,SIGNAL(refreshPage(QString)),dataInputDia,SLOT(close()));

}
void MainWindow::addVertex(VertexChain* data){
    if(!this->Map->addvertex(data)){
        QMessageBox a;
        a.information(nullptr,"Error","编号重复，添加地点失败");
    }else{
        emit refreshPage(this->Map->outGraph());
    }
}

void MainWindow::addEdgePage(){
    inputEdge* dataInputDia=new inputEdge();
    dataInputDia->show();
    connect(dataInputDia,SIGNAL(dataGet(int,int,int)),this,SLOT(addEdge(int,int,int)));
    connect(this,SIGNAL(addEdgeSuc()),dataInputDia,SLOT(close()));
}
void MainWindow::addEdge(int ver1,int ver2,int weight){
    QMessageBox a;
    if(!(this->Map->getVerAdress(ver1) && this->Map->getVerAdress(ver2))){
        a.information(nullptr,"Error","地点不存在");
    }else{
        if(this->Map->addEdge(ver1,ver2,weight)){
            emit refreshPage(this->Map->outGraph());
            emit addEdgeSuc();
        }else{
            a.information(nullptr,"Error","路径已存在");
        }
    }
}

void MainWindow::findVertex(){
    QStringList items; //ComboBox 列表的内容
    items <<"名称查找"<<"编号查找";
    QString dlgTitle="查找方式";
    QString txtLabel="选择查找方式";
    int     curIndex=0; //初始选择项
    bool    editable=false; //ComboBox是否可编辑
    bool    ok=false;
    VertexChain* adressFind=nullptr;
    QString informationFind;
    QString text = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
    if(ok==true){
        if(text!="名称查找"){
            int minValue=0, maxValue=50,stepValue=1; //范围，步长
            int value=-1;
            value=QInputDialog::getInt(this,"查找","请输入地点编号",0,minValue,maxValue,stepValue,&ok);
            _hashTable a(this->Map);
            adressFind=a.findVertexChain(value);
            //adressFind=this->Map->getVerAdress(value);
            if(adressFind==nullptr){
                informationFind="未能找到";
            }
            else{
                informationFind=QString::fromStdString(adressFind->outVertex());
            }
        }else{
            QString value;
            value=QInputDialog::getText(this,"查找","请输入地点名称",QLineEdit::Normal,"",&ok);
            adressFind=this->Map->getVerAdress(value.toStdString());
            if(adressFind==nullptr){
                informationFind="未能找到";
            }
            else{
                informationFind=QString::fromStdString(adressFind->outVertex());
            }
        }
        if(ok==true){
            QMessageBox a;
            a.information(this,"查找结果",informationFind);
        }
    }
}

void MainWindow::findShortestRotiune(){
    QStringList items; //ComboBox 列表的内容
    items <<"名称查找"<<"编号查找";
    QString dlgTitle="导航";
    QString txtLabel="选择查找方式";
    int     curIndex=0; //初始选择项
    bool    editable=false; //ComboBox是否可编辑
    bool    ok=false;
    QString informationFind;
    VertexChain* Start,*End;
    QMessageBox a;
    QString text = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
    if(ok){
        if(text=="名称查找"){
            QString ver1,ver2;
            ver1=QInputDialog::getText(this,"数据输入","请输入起始地点名称",QLineEdit::Normal,"",&ok);
            if(ok==true){
                ver2=QInputDialog::getText(this,"数据输入","请输入终点地点名称",QLineEdit::Normal,"",&ok);
                if(ok==true){
                    Start=this->Map->getVerAdress(ver1.toStdString());
                    End=this->Map->getVerAdress(ver2.toStdString());
                }
            }

        }else{
            int minValue=0, maxValue=50,stepValue=1; //范围，步长
            int ver1,ver2;
            ver1=QInputDialog::getInt(this,"数据输入","请输入起始地点编号",0,minValue,maxValue,stepValue,&ok);
            if(ok){
                ver2=QInputDialog::getInt(this,"数据输入","请输入终点地点编号",0,minValue,maxValue,stepValue,&ok);
                if(ok){
                    Start=this->Map->getVerAdress(ver1);
                    End=this->Map->getVerAdress(ver2);
                }
            }
        }
        if(ok){
            if(Start!=nullptr && End!=nullptr){
                informationFind=QString::fromStdString(Start->findShortestRote(End));
                a.information(this,"结果",informationFind);
            }else{
                if(Start==nullptr&&End!=nullptr){
                    a.information(this,"Error","起点地点不存在");
                }else if(Start!=nullptr&&End==nullptr){
                    a.information(this,"Error","终点地点不存在");
                }else{
                    a.information(this,"Error","起点/终点地点不存在");
                }
            }
        }

    }
}

void MainWindow::modifiedData(){
    QMessageBox a;
    if(this->Map->graphIsEmpty()==true){
        a.information(this,"Tip","大兄弟，地图是空的，你没得改");
    }else{
        QStringList items; //ComboBox 列表的内容
        QString dlgTitle="更改地点信息";
        QString txtLabel="选择更改那个点";
        int     curIndex=0; //初始选择项
        bool    editable=false; //ComboBox是否可编辑
        bool    ok=false;
        VertexChain* adressFind=nullptr;
        VertexChain* getNameList=this->Map->getFirAdress();
        while(getNameList!=nullptr){
            items <<QString::fromStdString(getNameList->getName());
            getNameList=getNameList->getNextVerAdress();
        }
        QString nameOfVerneedChange = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
        if(ok==true){
            adressFind=this->Map->getVerAdress(nameOfVerneedChange.toStdString());
            if(adressFind==nullptr){
                a.information(this,"Error","没有这个地点");
            }
            else{
                items.clear();
                items << "更改编号" << "更改名称" << "更改简介信息" << "更改编号、名称"  << "更改编号、更改简介信息" << "更改名称、简介信息" << "小孩才做选择，我全都要";
                txtLabel="选择改什么信息";
                QString whatToChange= QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
                if(ok==true){
                    VertexChain* getNumList=this->Map->getFirAdress();
                    if(whatToChange=="更改编号"){
                        items.clear();
                        for(int i=0;i<300;++i)
                            items << QString("%1").arg(i);
                        while(getNumList!=nullptr){
                            items.removeOne(QString("%1").arg(getNumList->getVertex()));
                            getNumList=getNumList->getNextVerAdress();
                        }
                        txtLabel="选择新的编号";
                        QString textNum = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
                        if(ok==true){
                            adressFind->setVertex(textNum.toInt());
                            emit refreshPage(this->Map->outGraph());
                        }
                    }else if(whatToChange== "更改名称"){
                        QString value=QInputDialog::getText(this,"更改信息","请输入新的地点名称",QLineEdit::Normal,"",&ok);
                        if(ok==true){
                            adressFind->setName(value.toStdString());
                            emit refreshPage(this->Map->outGraph());
                        }
                    }else if(whatToChange== "更改简介信息"){
                        QString value=QInputDialog::getText(this,"更改信息","请输入新的简介",QLineEdit::Normal,"",&ok);
                        if(ok==true){
                            adressFind->setInf(value.toStdString());
                            emit refreshPage(this->Map->outGraph());
                        }
                    }else if(whatToChange== "更改编号、名称"){
                        items.clear();
                        for(int i=0;i<300;++i)
                            items << QString("%1").arg(i);
                        while(getNumList!=nullptr){
                            items.removeOne(QString("%1").arg(getNumList->getVertex()));
                            getNumList=getNumList->getNextVerAdress();
                        }
                        txtLabel="选择新的编号";
                        QString textNum = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
                        if(ok==true){
                            adressFind->setVertex(textNum.toInt());
                            emit refreshPage(this->Map->outGraph());
                        }
                        QString value=QInputDialog::getText(this,"更改信息","请输入新的地点名称",QLineEdit::Normal,"",&ok);
                                                if(ok==true){
                                                    adressFind->setName(value.toStdString());
                                                    emit refreshPage(this->Map->outGraph());
                                                }
                    }else if(whatToChange== "更改编号、更改简介信息"){
                        items.clear();
                        for(int i=0;i<300;++i)
                            items << QString("%1").arg(i);
                        while(getNumList!=nullptr){
                            items.removeOne(QString("%1").arg(getNumList->getVertex()));
                            getNumList=getNumList->getNextVerAdress();
                        }
                        txtLabel="选择新的编号";
                        QString textNum = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
                        if(ok==true){
                            adressFind->setVertex(textNum.toInt());
                            emit refreshPage(this->Map->outGraph());
                        }
                        QString value=QInputDialog::getText(this,"更改信息","请输入新的简介",QLineEdit::Normal,"",&ok);
                        if(ok==true){
                            adressFind->setInf(value.toStdString());
                            emit refreshPage(this->Map->outGraph());
                        }
                    }else if(whatToChange== "更改名称、简介信息"){
                        QString value=QInputDialog::getText(this,"更改信息","请输入新的地点名称",QLineEdit::Normal,"",&ok);
                        if(ok==true){
                            adressFind->setName(value.toStdString());
                            emit refreshPage(this->Map->outGraph());
                        }
                        value=QInputDialog::getText(this,"更改信息","请输入新的简介",QLineEdit::Normal,"",&ok);
                        if(ok==true){
                            adressFind->setInf(value.toStdString());
                            emit refreshPage(this->Map->outGraph());
                        }
                    }else if(whatToChange== "小孩才做选择，我全都要"){
                        items.clear();
                        for(int i=0;i<300;++i)
                            items << QString("%1").arg(i);
                        while(getNumList!=nullptr){
                            items.removeOne(QString("%1").arg(getNumList->getVertex()));
                            getNumList=getNumList->getNextVerAdress();
                        }
                        txtLabel="选择新的编号";
                        QString textNum = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
                        if(ok==true){
                            adressFind->setVertex(textNum.toInt());
                            emit refreshPage(this->Map->outGraph());
                        }
                        QString value=QInputDialog::getText(this,"更改信息","请输入新的地点名称",QLineEdit::Normal,"",&ok);
                        if(ok==true){
                            adressFind->setName(value.toStdString());
                            emit refreshPage(this->Map->outGraph());
                        }
                        value=QInputDialog::getText(this,"更改信息","请输入新的简介",QLineEdit::Normal,"",&ok);
                        if(ok==true){
                            adressFind->setInf(value.toStdString());
                            emit refreshPage(this->Map->outGraph());
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::modifieEdge(){
    QMessageBox a;
    if(this->Map->graphIsEmpty()==true){
        a.information(this,"Tip","大兄弟，地图是空的，你没得改");
    }else{
        QStringList items; //ComboBox 列表的内容
        QString dlgTitle="更改信息";
        QString txtLabel="选择起点";
        int     curIndex=0; //初始选择项
        bool    editable=false; //ComboBox是否可编辑
        bool    ok=false;
        VertexChain* ver1,*ver2;
        VertexChain* getNameList=this->Map->getFirAdress();
        while(getNameList!=nullptr){
            items <<QString::fromStdString(getNameList->getName());
            getNameList=getNameList->getNextVerAdress();
        }
        QString nameOfVer = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
        if(ok==true){
            ver1=this->Map->getVerAdress(nameOfVer.toStdString());
            items.clear();
            LinkList* getLinkList=ver1->getLinklistAdr();
            while(getLinkList!=nullptr){
                items << QString::fromStdString(getLinkList->getVerAdress()->getName());
                getLinkList=getLinkList->getNext();
            }
            if(items.empty()==true){
                a.information(this,"Tip","该点没有可达点");
            }else{
                txtLabel="选择终点";
                nameOfVer = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
                if(ok==true){
                    ver2=this->Map->getVerAdress(nameOfVer.toStdString());
                    int weight=QInputDialog::getInt(this,"更改信息","输入新的权值",0,1,3000,1,&ok);
                    if(ok==true){
                        ver1->setWeight(ver2,weight);
                        emit refreshPage(this->Map->outGraph());
                    }
                }
            }
        }
    }
}

void MainWindow::saveMap(){
    QMessageBox a;
    QDialog b;
    QString filePath;
    if(this->Map->graphIsEmpty()==true){
        a.information(this,"Tip","地图为空，无需保存");
        emit saveMapDataSuc();
        emit refreshPage(this->Map->outGraph());
    }else{
        filePath=QFileDialog::getSaveFileName(this,"选择存入文件",QDir::currentPath(),"地图文件(*.graph);;文本文件(*.txt)");
        if(filePath.isEmpty()!=true){
            if(this->Map->saveMapData(filePath.toStdString())==true){
                this->Map->freeMap();
                emit saveMapDataSuc();
                emit refreshPage(this->Map->outGraph());
            }else{
                a.information(this,"Error","保存失败");
            }
        }
    }
}

void MainWindow::openMap(){
    QMessageBox a;
    QDialog b;
    QString filePath;
    if(this->Map->graphIsEmpty()==false){
        QString dlgTitle="注意";
        QString strInfo="还有图数据未保存，是否保存";
        QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
        QMessageBox::StandardButton result;//返回选择的按钮
        result=QMessageBox::question(this, dlgTitle, strInfo,
                          QMessageBox::Yes|QMessageBox::No,
                          defaultBtn);
        if(result==QMessageBox::Yes){
            this->saveMap();
        }else{
            this->Map->freeMap();
        }
    }
    filePath=QFileDialog::getOpenFileName(this,"选择文件",QDir::currentPath(),"地图文件(*.graph);;文本文件(*.txt);;all(*.*)");
    if(filePath.isEmpty()!=true){
        if(this->Map->openMap(filePath.toStdString())==true){
            emit openMapDataSuc();
            emit refreshPage(this->Map->outGraph());
        }else{
            a.information(this,"Error","打开失败");
        }
    }
}

void MainWindow::exitMap(){
    if(this->Map->graphIsEmpty()==false){
        QString dlgTitle="注意";
        QString strInfo="还有图数据未保存，是否保存";
        QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
        QMessageBox::StandardButton result;//返回选择的按钮
        result=QMessageBox::question(this, dlgTitle, strInfo,
                          QMessageBox::Yes|QMessageBox::No,
                          defaultBtn);
        if(result==QMessageBox::Yes){
            this->saveMap();
        }else{
            this->Map->freeMap();
            emit MainWindow::saveMapDataSuc();
        }
    }
    emit MainWindow::saveMapDataSuc();
}

void MainWindow::on_New_map_triggered()
{
    if(this->Map->graphIsEmpty()==false){
        QString dlgTitle="注意";
        QString strInfo="还有图数据未保存，是否保存";
        QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
        QMessageBox::StandardButton result;//返回选择的按钮
        result=QMessageBox::question(this, dlgTitle, strInfo,
                          QMessageBox::Yes|QMessageBox::No,
                          defaultBtn);
        if(result==QMessageBox::Yes){
            this->saveMap();
        }else{
            this->Map->freeMap();
        }
    }
    emit MainWindow::saveMapDataSuc();
    emit MainWindow::openMapDataSuc();
}

void MainWindow::on_SaveMap_triggered()
{
    this->saveMap();
}

void MainWindow::on_save_as_graph_triggered()
{
    QMessageBox a;
    QDialog b;
    QString filePath;
    if(this->Map->graphIsEmpty()==true){
        a.information(this,"Tip","地图为空，无需保存");
    }else{
        filePath=QFileDialog::getSaveFileName(this,"选择存入文件",QDir::currentPath(),"地图文件(*.graph)");
        if(filePath.isEmpty()!=true){
            if(this->Map->saveMapData(filePath.toStdString())==true){
                this->Map->freeMap();
                emit saveMapDataSuc();
                emit refreshPage(this->Map->outGraph());
            }else{
                a.information(this,"Error","保存失败");
            }
        }
    }
}

void MainWindow::on_save_as_txt_triggered()
{
    QMessageBox a;
    QDialog b;
    QString filePath;
    if(this->Map->graphIsEmpty()==true){
        a.information(this,"Tip","地图为空，无需保存");
    }else{
        filePath=QFileDialog::getSaveFileName(this,"选择存入文件",QDir::currentPath(),"文本文件(*.txt)");
        if(filePath.isEmpty()!=true){
            if(this->Map->saveMapData(filePath.toStdString())==true){
                this->Map->freeMap();
                emit saveMapDataSuc();
                emit refreshPage(this->Map->outGraph());
            }else{
                a.information(this,"Error","保存失败");
            }
        }
    }
}

void MainWindow::on_Open_map_triggered()
{
    if(this->Map->graphIsEmpty()==false){
        QString dlgTitle="注意";
        QString strInfo="还有图数据未保存，是否保存";
        QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
        QMessageBox::StandardButton result;//返回选择的按钮
        result=QMessageBox::question(this, dlgTitle, strInfo,
                          QMessageBox::Yes|QMessageBox::No,
                          defaultBtn);
        if(result==QMessageBox::Yes){
            this->saveMap();
        }else{
            this->Map->freeMap();
        }
    }
    emit MainWindow::saveMapDataSuc();
    this->openMap();
}

void MainWindow::on_Exit_this_map_triggered()
{
    if(this->Map->graphIsEmpty()==false){
        QString dlgTitle="注意";
        QString strInfo="还有图数据未保存，是否保存";
        QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
        QMessageBox::StandardButton result;//返回选择的按钮
        result=QMessageBox::question(this, dlgTitle, strInfo,
                          QMessageBox::Yes|QMessageBox::No,
                          defaultBtn);
        if(result==QMessageBox::Yes){
            this->saveMap();
        }else{
            this->Map->freeMap();
            emit MainWindow::saveMapDataSuc();
        }
    }
    emit MainWindow::saveMapDataSuc();
}

void MainWindow::on_Add_locate_triggered()
{
    this->addVertexPage();
    emit MainWindow::refreshText(this->Map->outGraph());
    emit MainWindow::openMapDataSuc();
}

void MainWindow::on_Add_routine_triggered()
{
    this->addEdgePage();
    emit MainWindow::refreshText(this->Map->outGraph());
    emit MainWindow::openMapDataSuc();
}

void MainWindow::on_Show_all_routine_triggered()
{
    if(this->Map->graphIsEmpty()==false){
        this->Map->Floyd();
        string routine;
        for(VertexChain* ver1=this->Map->getFirAdress();ver1!=nullptr;ver1=ver1->getNextVerAdress()){
            for(VertexChain* ver2=this->Map->getFirAdress();ver2!=nullptr;ver2=ver2->getNextVerAdress()){
                if(ver1!=ver2){
                    routine+=ver1->findShortestRote(ver2)+"\n";
                }
                //routine+=this->Map->findShortestRote_Floyd(ver1->getVertex(),ver2->getVertex());
            }
        }
        QMessageBox a;
        a.information(this,"所有最短路径",QString::fromStdString(routine));
    }else{
        QMessageBox a;
        a.information(this,"Ooooops!","空地图");
    }

}

void MainWindow::on_Edit_locate_triggered()
{
    this->modifiedData();
}


//QGroupBox* welcome_group;//欢迎组件盒子
//    welcome_group=new QGroupBox("WELCOME",this);
//    welcomeMessage=new QLabel("欢迎使用校园导游系统",welcome_group);
//    welcomeMessage->setAlignment(Qt::AlignCenter);
//    welcome_group_newGraph=new QPushButton("新建地图",welcome_group);
//    welcome_group_openGraph=new QPushButton("打开地图",welcome_group);
//    welcome_group->move(30,50);
//    welcomeMessage->move(30,50);
//    welcome_group_newGraph->move(30,120);
//    welcome_group_openGraph->move(30,180);
//    welcome_group->resize(340,300);
//    welcomeMessage->resize(280,40);
//    welcome_group_newGraph->resize(280,30);
//    welcome_group_openGraph->resize(280,30);
//connect(welcome_group_newGraph,SIGNAL(clicked()),welcome_group,SLOT(close()));
//connect(this,SIGNAL(openMapDataSuc()),welcome_group,SLOT(close()));

//connect(this,SIGNAL(saveMapDataSuc()),this->centralWidget(),SLOT(close()));

