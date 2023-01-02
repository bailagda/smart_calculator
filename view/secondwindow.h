#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QVector>
#include "qcustomplot.h"
#include "mainwindow.h"


#include "../model.h"
#include "../controller.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    void set_str(QString str);
    void make_graph();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SecondWindow *ui;


    QVector<double> x;
    QVector<double> y;
//public slots:
//    void slot();
};
#endif // SECONDWINDOW_H
