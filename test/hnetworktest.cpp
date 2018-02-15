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
#include "hnetworktest.h"


#include "hcore/hobject.h"
#include "hcore/hcall.h"

using namespace hessian;

HNetworkTest::HNetworkTest(QObject *parent) :
    QObject(parent)
{
    networkManager = new HNetworkManager("http://localhost:8080/TestService/Test");
    //networkManager = new HNetworkManager( "http://hessian.caucho.com/test/test");
}

void HNetworkTest::test() {

    QString s = "abcdefghijklmnopqrstuvwxyz";
    int i=0;
    try {
        for (i=0;i<14;i++) {
            s+=s;
        }
        HCall c (networkManager, "feedbackString");
        c <<s;
        qDebug() <<"Sent " << s.length();
        qDebug()<<"Received " <<c.getResult()->toString().length();

        //c.refresh();
        //qDebug()<<"Received " <<c.getResult()->toString().length();

    } catch (HIOException e) {
        qDebug()<<"There is something has happened";
        qDebug()<<e.message();
    }
   // testBinary();

    //testInteger();;
    //test2Parameters();
    //testLong();
    //testDouble();
    //testBool();
}


void HNetworkTest::testInteger() {

    int i;
    QVariant i1(-2);


    HCall * c = new HCall(networkManager, "feedback");
    //= (networkManager->call(QString("feedback"), i1));

    qDebug() <<c->getMethod()<<"("<<*(c->at(0))<<") ="<< *(c->getResult());

    c->freeResult();
    /*
    for (i =100; i < 200; i ++ ) {
        qint32 l = i*40000;
        QVariant i1(l);
        c->at(0)->setValue(i1);
        c->refresh();
        qDebug() <<c->getMethod()<<"("<<*(c->at(0))<<") ="<< *(c->getResult());
        c->freeResult();
    }
    */
    delete c;
}

void HNetworkTest::testLong() {
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

void HNetworkTest::testDouble() {
    /*?
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
    delete v;*/
}

void HNetworkTest::testBool() {
    /*
    QVariant b1(true);
    QVariant *v;
    v = networkManager->call(QString("feedbackBoolean"), b1)->getResult();
    qDebug()<<*v;
    delete v;
    QVariant b2(false);
    v = networkManager->call(QString("feedbackBoolean"), b2)->getResult();
    qDebug()<<*v;
    delete v;*/
}


void HNetworkTest::test2Parameters() {
    /*
    HCall c (networkManager, "add2");
    int i = 10 , j = 20;
    c<<i<<j;
    c.refresh();
    qDebug()<<"Test adding " << *(c.getResult());*/
}


void HNetworkTest::testBinary() {
    QByteArray buffer;    
    for (int i = 0; i<1000;i++)
        buffer.append("abcdefg");
    qDebug()<<"Test adding " << buffer.size() <<" bytes";
    HCall c (networkManager, "feedbackBinary");
    c<<buffer;
    qDebug()<<"Test received " << c.getResult()->toByteArray().length();
}

