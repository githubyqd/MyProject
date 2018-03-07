#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "domxml.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void conneDB();     //连接数据库
    void initData();

private slots:
    void on_actionM_triggered();
    void on_actionS_triggered();
    void on_comboBoxFac_currentIndexChanged(const QString &arg1);
    void on_comboBoxBra_currentIndexChanged(const QString &arg1);
    void on_spinBox_valueChanged(int arg1);
    void on_pushButtonCan_clicked();
    void on_pushButtonSur_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
