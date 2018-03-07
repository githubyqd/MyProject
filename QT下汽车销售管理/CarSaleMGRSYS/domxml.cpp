#include "domxml.h"

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

domxml::domxml()
{

}

domxml::~domxml()
{

}

//创建一个xml空文件
void domxml::createXML(QString filePath)
{
    QFile file(filePath);
    if(file.exists())
    {
        cout << "文件已存在";
        return;
    }
    else
    {
        //只写方式打开xml文件
        if(file.open(QIODevice::WriteOnly))
        {
            QDomDocument dom;    //创建xml文件对象

            //创建头部格式<?xml version='1.0' encoding='utf-8'?>
            QDomProcessingInstruction ins;
            ins = dom.createProcessingInstruction("xml",
                "version=\'1.0\' encoding=\'utf-8\'");

            //追加根结点元素
            dom.appendChild(ins);
            QDomElement root = dom.createElement("日销售清单");
            dom.appendChild(root);

            // 利用QTextStream保存文件
            QTextStream stream(&file);
            dom.save(stream, 4);                     //四个字节缩进
            file.close();
        }
        else
        {
            cout << "open WriteOnly err";
            return;
        }
    }
}

//追加结点
void domxml::appendXML(QString filePath, QStringList list)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))   //如果打开文件成功，让文件和xml文档建立关联
    {
        QDomDocument dom;
        if(dom.setContent(&file))
        {
            file.close();                   //关闭文件
            QDomElement root = dom.documentElement();   //获取根结点元素
            QDateTime date = QDateTime::currentDateTime();  //获当前取日期
            QString dateStr = date.toString("yyyy-MM-dd");

            //判断是否有子结点
            if(root.hasChildNodes())
            {
                QDomElement lastEle = root.lastChildElement();
                if(lastEle.attribute("date") == dateStr)
                {
                    writeXML(dom, root, list);
                }
                else
                {
                    //写入日期
                    QDomElement dateEle = dom.createElement("日期");  //创建元素日期
                    QDomAttr dateAtt =
                                dom.createAttribute("date"); //创建属性结点date
                    dateAtt.setNodeValue(dateStr);          //设置结点的值
                    dateEle.setAttributeNode(dateAtt);          //元素和属性关联
                    root.appendChild(dateEle);

                    writeXML(dom, dateEle, list);       //写有效数据
                }
            }
            else
            {
                //写入日期
                QDomElement dateEle = dom.createElement("日期");  //创建元素日期
                QDomAttr dateAtt = dom.createAttribute("date"); //创建属性结点date
                dateAtt.setNodeValue(dateStr);          		//设置结点的值
                dateEle.setAttributeNode(dateAtt);          	//元素和属性关联
                root.appendChild(dateEle);

                writeXML(dom, dateEle, list);       //写有效数据
            }

            //保存文件
            if(file.open(QIODevice::WriteOnly))
            {
                QTextStream stream(&file);
                dom.save(stream, 4);
                file.close();
            }
        }
    }
}

//写入有效数据
void domxml::writeXML(QDomDocument &dom, QDomElement &root, QStringList &list)
{
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("hh-mm-ss");
    QDomElement timeEle = dom.createElement("时间");
    QDomAttr timeAttr = dom.createAttribute("time");
    timeAttr.setNodeValue(timeStr);
    timeEle.setAttributeNode(timeAttr);
    root.appendChild(timeEle);

    //添加元素
    QDomElement factory = dom.createElement("厂家");
    QDomElement brand = dom.createElement("品牌");
    QDomElement price = dom.createElement("报价");
    QDomElement num = dom.createElement("数量");
    QDomElement total = dom.createElement("金额");

    QDomText text = dom.createTextNode(list.at(0));
    factory.appendChild(text);
    text = dom.createTextNode(list.at(1));
    brand.appendChild(text);
    text = dom.createTextNode(list.at(2));
    price.appendChild(text);
    text = dom.createTextNode(list.at(3));
    num.appendChild(text);
    text = dom.createTextNode(list.at(4));
    total.appendChild(text);

    timeEle.appendChild(factory);
    timeEle.appendChild(brand);
    timeEle.appendChild(price);
    timeEle.appendChild(num);
timeEle.appendChild(total);
}

//读数据
void domxml::readXML(QString filePath,
                     QStringList &factoryList,
                     QStringList &brandList,
                     QStringList &priceList,
                     QStringList &numList,
                     QStringList &totalList)
{
    QFile file(filePath);
    QDomDocument doc;
    if(file.open(QIODevice::ReadOnly) && doc.setContent(&file))
    {
        QDomElement root = doc.documentElement();
        file.close();
        QDateTime date = QDateTime::currentDateTime();
        QString dateStr = date.toString("yyyy-MM-dd");
        if(root.hasChildNodes())
        {
            QDomElement lastEle = root.lastChildElement();
            if(lastEle.attribute("date") == dateStr)
            {
                QDomNodeList list = lastEle.childNodes();   //当前日期下的所有子结点
                for(int i = 0; i < list.size(); i++)
                {
                    QDomNodeList subList =
                        list.at(i).toElement().childNodes();//转换成元素找到子结点

                    QString factory = subList.at(0).toElement().text();
                    factoryList.append(factory);
                    QString brand = subList.at(1).toElement().text();
                    brandList.append(brand);
                    QString price = subList.at(2).toElement().text();
                    priceList.append(price);
                    QString num = subList.at(3).toElement().text();
                    numList.append(num);
                    QString total = subList.at(4).toElement().text();
                    totalList.append(total);
                }
            }
            else
            {
                cout << "没有当天日期";
                return;
            }
        }
    }
}

