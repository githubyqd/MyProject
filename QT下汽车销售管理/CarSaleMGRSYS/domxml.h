#ifndef DOMXML_H
#define DOMXML_H

//封装一个操作xml的类
#include <QDomComment>                      //文件
#include <QDomProcessingInstruction>        //格式头部
#include <QDomElement>                      //元素
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QDomElement>
#include <QDomAttr>
#include <QDomText>

class domxml
{
public:
    domxml();
    ~domxml();

    static void createXML(QString filePath);
    static void appendXML(QString filePath, QStringList list);
    static void writeXML(QDomDocument &dom, QDomElement &root, QStringList &list);
    static void readXML(QString filePath, QStringList &factoryList,
                        QStringList &brandList,
                        QStringList &priceList,
                        QStringList &numList,
                        QStringList &totalList);

};

#endif // DOMXML_H
