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
#include "performancetest.h"
#include "QtHessian.h"

PerformanceTest::PerformanceTest(QObject *parent) :
    QObject(parent)
{

}


void PerformanceTest::test() {
    HNetworkManager * networkManager = new HNetworkManager("http://localhost:8080/TestService/Test");
    HCall c (networkManager, "feedback");
    int parameter;
    c<<parameter;

    long start = QDateTime::currentMSecsSinceEpoch();
    int count = 0;
    for (int i = 0; i < 40000; i ++) {

       c.at(0)->setValue(i);
       c.refresh();
       int j = c.getResult()->toInt();

       if (i!=j) qDebug() << "Feedback(int): " << i <<" failed. Received " << j;
       if (i%1000 ==0) qDebug()<<"Feedback(int): " << i;
       count++;
       c.freeResult();
         /*
        QVariant v(i);
        HCall * c = (networkManager->call("feedbackString", v));
        int j = c->getResult()->toInt();
        if (i!=j) qDebug() << "Feedback(int): " << i <<" failed. Received " << j;
        if (i%1000 ==0) qDebug()<<"Feedback(int): " << i;

        delete c;

        count ++;*/
    }
    long stop = (QDateTime::currentMSecsSinceEpoch() - start );
    qDebug()<< "Send " << count << " numbers takes " << stop;
}

void PerformanceTest::test2() {
    /*
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    HNetworkManager * networkManager = new HNetworkManager("http://localhost:8080/TestService/Test", manager, ASYNCHRONOUS);
    HCall *c;
    start = QDateTime::currentMSecsSinceEpoch();
    count = 1;
    for (int i = 0; i < 40000; i ++) {
        QVariant l ( i);
        c = networkManager->call(QString("feedback"),l);
        connect(c,SIGNAL(callFinished(HCall*)), this,SLOT(sltReceivedData(HCall*)));
    }
    */
}

void PerformanceTest::sltReceivedData(HCall * call) {
    //qDebug() <<" " <<call->getMethod()<<" ("<<*(call->at(0))  <<") = " <<*(call->getResult());

    //int j = call->getResult()->toInt();

    count ++;
    if (count%1000 ==0) qDebug()<<"Feedbacking  " << count;
    if (count==40000) {
        long stop = QDateTime::currentMSecsSinceEpoch() - start;
        qDebug()<<"Takes " << stop;
    }
    call->deleteLater();
}
