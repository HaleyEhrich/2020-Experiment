#ifndef INPUTVERTEX_H
#define INPUTVERTEX_H

#include <QDialog>
#include "graph.h"

namespace Ui {
class inputVertex;
}

class inputVertex : public QDialog
{
    Q_OBJECT

public:
    explicit inputVertex(QWidget *parent = nullptr);
    ~inputVertex();
public slots:
    void on_buttonBox_accepted();
signals:
    void dataGet(VertexChain*);
private:
    Ui::inputVertex *ui;
};

#endif // INPUTVERTEX_H
