/***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
    File      : houtputstream.h
    Project   : Qt Hessian
    Author(s) : HTV
    Conttent  : The network manager represents the service endpoint
    Requirement : Qt4.7+, QtNetwork

    Reference: http://hoangtuanonline.com/qthessian
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************/
#include "hnetworkatest.h"

HNetworkATest::HNetworkATest(QObject *parent) :
    QObject(parent)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    networkManager = new HNetworkManager("http://localhost:8080/TestService/Test", manager, ASYNCHRONOUS);
    //connect(networkManager, SIGNAL(receiveData(HCall*)), this, SLOT(sltReceivedData(HCall*)));
}


void HNetworkATest::test() {
    /*
    QString s = "This is a test string";
    int i = 0;
    try {
        for (i=0;i < 1000; i ++) {
            s+=s;
            QVariant v(s);
            HCall *c  = (networkManager->call(QString("feedbackString"), v));
            connect(c,SIGNAL(callFinished(HCall*)), this,SLOT(sltReceivedData(HCall*)));
        }
    } catch (HIOException e) {
        qDebug()<<"There is something has happened";
        qDebug()<<e.message();
    }

    testInteger();;*/
}


void HNetworkATest::testInteger() {
    /*

    int i;
    QVariant i1(-2);

    HCall * c = networkManager->call(QString("feedback"),i1);
    connect(c,SIGNAL(callFinished(HCall*)), this,SLOT(sltReceivedData(HCall*)));
    for (i =100; i < 200; i ++ ) {
        QVariant l ( i*40000);
        c = networkManager->call(QString("feedback"),l);
        connect(c,SIGNAL(callFinished(HCall*)), this,SLOT(sltReceivedData(HCall*)));

    }
*/
}


void HNetworkATest::testLong() {
/*
    QVariant j(Q_INT64_C(270000));
    QVariant i1(Q_INT64_C(-99999999999));
    QVariant i2(Q_INT64_C( 99999999999999));
    QVariant *v;
    v = networkManager->call(QString("feedbackLong"), j)->getResult();
    qDebug()<<*v;
    delete v;
    v = networkManager->call(QString("feedbackLong"), i1)->getResult();
    qDebug()<<*v;
    delete v;
    v = networkManager->call(QString("feedbackLong"), i2)->getResult();
    qDebug()<<*v;
    delete v;
*/
}

void HNetworkATest::testDouble() {
    /*
    QVariant d1(0.0);
    QVariant d2(1.0);
    QVariant *v;
    v = networkManager->call(QString("feedbackDouble"), d1)->getResult();
    qDebug()<<*v;
    delete v;
    v = networkManager->call(QString("feedbackDouble"), d2)->getResult();
    qDebug()<<*v;
    delete v;

    QVariant d3(127.0);
    v = networkManager->call(QString("feedbackDouble"), d3)->getResult();
    qDebug()<<*v;
    delete v;
    QVariant d4(-127.0);
    v = networkManager->call(QString("feedbackDouble"), d4)->getResult();
    qDebug()<<*v;
    delete v;
    QVariant d5(-12788.0);
    v = networkManager->call(QString("feedbackDouble"), d5)->getResult();
    qDebug()<<*v;
    delete v;
    QVariant d6(32767.0);
    v = networkManager->call(QString("feedbackDouble"), d6)->getResult();
    qDebug()<<*v;
    delete v;
    QVariant d7(-3276755.78);
    v = networkManager->call(QString("feedbackDouble"), d7)->getResult();
    qDebug()<<*v;
    delete v;
    QVariant d8(3276755.78);
    v = networkManager->call(QString("feedbackDouble"), d8)->getResult();
    qDebug()<<*v;
    delete v;
    */
}

void HNetworkATest::testBool() {
    /*
    QVariant b1(true);
    QVariant *v;
    v = networkManager->call(QString("feedbackBoolean"), b1)->getResult();
    qDebug()<<*v;
    delete v;
    QVariant b2(false);
    v = networkManager->call(QString("feedbackBoolean"), b2)->getResult();
    qDebug()<<*v;
    delete v*/
}


void HNetworkATest::sltReceivedData(HCall * call) {
    qDebug() <<" " <<call->getMethod()<<" ("<<*(call->at(0))  <<") = " <<*(call->getResult());
    call->deleteLater();
}

void HNetworkATest::testBinary() {
    QByteArray buffer;
    int i=0;
    for (i = 0; i<10000;i++)
    buffer.append("abcdefg");

    HCall c (networkManager, "feedbackBinary");

    c<<buffer;
    c.refresh();

    qDebug()<<"Test adding " << *(c.getResult());
}

