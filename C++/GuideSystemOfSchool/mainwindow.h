#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QLayout>
#include <QFileDialog>
#include "graph.h"
#include <inputedge.h>
#include "inputvertex.h"
#include "tool.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    //欢迎界面，新建地图，打开地图
    void welcomePage();
    //操作主界面，添加点，添加边，查找等功能
    void mapOutPage();
    //功能界面
    void addVertexPage();//添加地点窗口数据处理
    void addVertex(VertexChain*);//实际操作函数
    void addEdgePage();//添加路径
    void addEdge(int,int,int);
    void findVertex();//查找地点
    void findShortestRotiune();//寻找最短的路径
    void saveMap();
    void openMap();
    void exitMap();
    void modifiedData();
    void modifieEdge();
signals:
    void refreshPage(QString);//刷新文本用，可复用信号
    void refreshText(QString);
    void addEdgeSuc();
    void saveMapDataSuc();
    void openMapDataSuc();

private slots:
    void on_New_map_triggered();

    void on_SaveMap_triggered();

    void on_save_as_graph_triggered();

    void on_save_as_txt_triggered();

    void on_Open_map_triggered();

    void on_Exit_this_map_triggered();

    void on_Add_locate_triggered();

    void on_Add_routine_triggered();

    void on_Show_all_routine_triggered();

    void on_Edit_locate_triggered();

private:
    Ui::MainWindow *ui;
    Graph *Map;
};

#endif // MAINWINDOW_H


