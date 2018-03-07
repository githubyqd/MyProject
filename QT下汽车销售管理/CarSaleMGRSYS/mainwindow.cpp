#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
//#include "domxml.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionM_triggered();    			//切换到车辆管理页面
    conneDB();								//连接数据库
    initData();                             //初始化数据
    domxml::createXML("../demo.xml");        //创建空文件

    //追加写入有效数据到XML
    QStringList list;
    list<<"二汽神龙"<<"毕加索"<<"39"<<"1"<<"39";
    domxml::appendXML("../demo.xml", list);

    QStringList factoryList;
    QStringList brandList;
    QStringList priceList;
    QStringList numList;
    QStringList totalList;
    domxml::readXML("../demo.xml", factoryList, brandList, priceList, numList, totalList);
    for(int i = 0; i < factoryList.size(); i++)
    {
        QString str = QString("%1:%2:卖出了%3,单价:%4,总价:%5")
            .arg(factoryList.at(i))
            .arg(brandList.at(i))
            .arg(numList.at(i))
            .arg(priceList.at(i))
            .arg(totalList.at(i));
        ui->textEdit->append(str);
        qDebug() << str.toUtf8().data();
    }
  }

MainWindow::~MainWindow()
{
    delete ui;
}

//切换到车辆管理界面
void MainWindow::on_actionM_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->carM);
    ui->label->setText("车辆管理");
}

//切换到销售统计界面
void MainWindow::on_actionS_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->carC);
    ui->label->setText("销售统计");
}

//连接数据库
void MainWindow::conneDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");	//不指定标识连接名
    db.setHostName("127.0.0.1");						//数据服务器IP
    db.setUserName("root");								//数据库用户名
    db.setPassword("123456");							//密码
    db.setDatabaseName("car");							//使用要连接的数据库
    if(!db.open())										//打开数据库
    {
        QMessageBox::warning(this, "数据库打开失败", db.lastError().text());
        return;
    }
}

//初始化数据
void MainWindow::initData()
{
    //取出数据库汽车名字添加到下拉框
    QSqlQueryModel *model = new QSqlQueryModel(this);  //查询结果模型
    model->setQuery("selsect name from factory");
    ui->comboBoxFac->setModel(model);

    ui->comboBoxBra->clear();				//品牌下拉框清空
    ui->lineEditPri->clear();				//报价清空
    ui->labelLas->setText("0");				//剩余数量
    ui->lineEditTol->setEnabled(false);		//金额
    ui->spinBox->setValue(0);
    ui->spinBox->setEnabled(false);
}

//厂家下拉框槽
void MainWindow::on_comboBoxFac_currentIndexChanged(const QString &arg1)
{
    if(arg1 ==  "请选择厂家")
    {
        ui->comboBoxBra->clear();
        ui->lineEditPri->clear();
        ui->labelLas->setText("0");
        ui->lineEditTol->clear();
        ui->spinBox->setValue(0);
        ui->spinBox->setEnabled(false);
        ui->pushButtonSur->setEnabled(false);
    }
    else
    {
        ui->comboBoxBra->clear();
        QSqlQuery query;
        QString sql = QString("select name from brand where factory = '%1'").arg(arg1);
        query.exec(sql);
        while(query.next())
        {
            QString name = query.value(0).toString();   //第0列
            ui->comboBoxBra->addItem(name);
        }
        ui->spinBox->setEnabled(true);
    }
}

//品牌下拉框槽
void MainWindow::on_comboBoxBra_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;				//查询操作，通常和query.next()使用
    QString sql = QString("select price, last from brand where factory = '%1' and name = '%2'").arg(ui->comboBoxFac->currentText().arg(arg1));
    query.exec(sql);
    while(query.next())
    {
        int price = query.value("price").toInt();
        int last = query.value("last").toInt();
        ui->lineEditPri->setText(QString::number(price));
        ui->labelLas->setText(QString::number(last));
    }
}

//数量选择框槽
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->pushButtonSur->setEnabled(false);
    }
    else
    {
        ui->pushButtonSur->setEnabled(true);
    }

    //根据选择查询
    QString factorystr = ui->comboBoxFac->currentText();
    QString brandstr = ui->comboBoxBra->currentText();
    QSqlQuery query;
    QString sql = QString("seldect sum, last from brand where factory = '%1' and name = '%2'").arg(factorystr).arg(brandstr);
    query.exec(sql);

    //剩余量
    int last;
    while(query.next())
    {
        last = query.value("last").toInt();
    }
    if(arg1 > last)
    {
        ui->spinBox->setValue(last);
        return;
    }

    int tmpNum = last - arg1;
    ui->labelLas->setText(QString::number(tmpNum));

    //金额报价
    int price = ui->lineEditPri->text().toInt();
    int sum = price * arg1;
    ui->lineEditTol->setText(QString::number(sum));
}

//取消
void MainWindow::on_pushButtonCan_clicked()
{
    ui->comboBoxFac->setCurrentIndex(0);
    ui->labelLas->setText("0");
}

//确认购买
void MainWindow::on_pushButtonSur_clicked()
{
    int num = ui->spinBox->value();
    int last = ui->labelLas->text().toInt();

    QSqlQuery query;
    QString sql = QString("select sell from brand where factory = '1%'and name = '2%'").arg(ui->comboBoxFac->currentText()).arg(ui->comboBoxBra->currentText());
    query.exec(sql);

    int sell ;
    while(query.next())
    {
        sell = query.value("sell").toInt();
    }
    sell += num;
    sql = QString("update brand set sell = 1%, last = %2 where brand = '3%' and factory = '4%'").arg(sell).arg(last).arg(ui->comboBoxFac->currentText()).arg(ui->comboBoxBra->currentText());
    query.exec(sql);

    //数据更新到XML
    QStringList list;
    list << ui->comboBoxFac->currentText() << ui->comboBoxBra->currentText()<< ui->lineEditPri->text()<< QString::number(num)<<ui->lineEditTol->text();
    domxml::appendXML("../demo.xml", list);

    ui->pushButtonSur->setEnabled(false);
    on_pushButtonCan_clicked();
}
