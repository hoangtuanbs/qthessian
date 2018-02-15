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
#include <QtCore/QCoreApplication>
#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QThread>
#include "test/performancetest.h"

#include "test/hnetworktest.h"
#include "test/hnetworkatest.h"
#include "hunittest.h"

/*
class MyThread : public QThread
 {
 public:
     void run();
 };

 void MyThread::run()
 {
     HNetworkTest::test();
     exec();
 }
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    HUnitTest t;
    QTest::qExec(&t);
    //HNetworkATest atest ;
    //atest.test();


    //PerformanceTest test ;
    //test.test();

    return a.exec();
}
