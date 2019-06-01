#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTranslator>
#include <json.h>
#include <QComboBox>

int arrSize = 0;
//QtJson::JsonObject obj[arrSize];


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QString file_path = "Example.json";
    QFile file_obj(file_path);
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<<file_path;
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();

    qDebug()<<json_string;

    bool ok;

    QtJson::JsonObject result = QtJson::parse(json_string,ok).toMap();
    qDebug()<<result<<"\n";
    QtJson::JsonObject arr2 =  result["appconfig"].toMap();
    qDebug()<<arr2<<"\n";
    QtJson::JsonArray arr =  arr2["tags"].toList();
    qDebug()<<arr<<"\n";
    qDebug()<<arr.size()<<"\n";
    arrSize = arr.size();
    ui->setupUi(this);

    int x=100;
    int y=100;
    int objNameIt=0;

    foreach(QVariant plug, arr)
    {
// https://stackoverflow.com/questions/24362946/how-can-i-cast-a-qvariant-to-custom-class
          //qvariant_cast<CustomType>(myVariant); =  myVariant.valu<CustomType>();
        qDebug()<<plug.value<QVariantMap>().value("name").toString();
        qDebug()<<plug.value<QVariantMap>().value("address").toString();
        qDebug()<<plug.value<QVariantMap>().value("type").toString();

        objNameIt = objNameIt + 1;
        m_textEdit = new QTextEdit(plug.value<QVariantMap>().value("name").toString(),this);
        // set size and location of the textEdit
        m_textEdit->setGeometry(QRect(QPoint(x, y),
        QSize(200, 30)));
        m_textEdit->setObjectName("text"+QString::number(objNameIt));

        y=y+40;
        objNameIt = objNameIt + 1;
        m_textEdit = new QTextEdit(plug.value<QVariantMap>().value("address").toString(),this);
        // set size and location of the textEdit
        m_textEdit->setGeometry(QRect(QPoint(x, y),
        QSize(200, 30)));
        m_textEdit->setObjectName("text"+QString::number(objNameIt));

        y=y+40;
        objNameIt = objNameIt + 1;
        m_textEdit = new QTextEdit(plug.value<QVariantMap>().value("type").toString(),this);
        // set size and location of the textEdit
        m_textEdit->setGeometry(QRect(QPoint(x, y),
        QSize(200, 30)));
        m_textEdit->setObjectName("text"+QString::number(objNameIt));

        y=y+60;

    }


   // y = y + 100;
    m_button = new QPushButton("Create Json", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(100, y),
    QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

}

void MainWindow::handleButton()
{
    QtJson::JsonObject obj[arrSize];
    QList<QTextEdit *> combo_list = findChildren<QTextEdit *>();
    QString asd = combo_list.at(0)->toPlainText();

 //   qDebug()<<combo_list;
    qDebug()<<asd;

    for(int i=0,a=0; i<arrSize;i++)
    {
        obj[i]["name"] = combo_list.at(a)->toPlainText();
        a = a + 1;
        obj[i]["address"] = combo_list.at(a)->toPlainText();
        a = a + 1;
        obj[i]["type"] = combo_list.at(a)->toPlainText();
         a = a + 1;

    }

//    obj[0]["name"] = "ulas";
//    obj[0]["address"] = "kartal";

//    obj[1]["name"] = "ulas";
//    obj[1]["address"] = "kartal";

//    obj[2]["name"] = "ulas";
//    obj[2]["address"] = "kartal";

    QtJson::JsonArray Jarr;
    for(int i=0; i<arrSize;i++)
    {
        Jarr.append(obj[i]);
    }
//    Jarr.append(obj[0]);
//    Jarr.append(obj[1]);
//    Jarr.append(obj[2]);

    QtJson::JsonObject Jobj;
    Jobj["tags"] = Jarr;

    qDebug()<<Jobj;
    QtJson::setPrettySerialize(true);

    QByteArray data = QtJson::serialize(Jobj);
    qDebug()<<data;

    QString filename="Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) ) // overwrite a file
    {
        QTextStream stream( &file );
        stream << data;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
