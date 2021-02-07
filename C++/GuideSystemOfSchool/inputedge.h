#ifndef INPUTEDGE_H
#define INPUTEDGE_H

#include <QDialog>

namespace Ui {
class inputEdge;
}

class inputEdge : public QDialog
{
    Q_OBJECT

public:
    explicit inputEdge(QWidget *parent = nullptr);
    ~inputEdge();
public slots:
    void on_buttonBox_accepted();
signals:
    void dataGet(int ver1,int ver2,int weight);
private:
    Ui::inputEdge *ui;
};

#endif // INPUTEDGE_H
