#ifndef HUNITTEST_H
#define HUNITTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QTime>
#include "hcore/hcall.h"

#define MAX 100

class HUnitTest : public QObject
{
    Q_OBJECT
public:
    explicit HUnitTest(QObject *parent = 0);

    //Random integer number
    int randInt(int low, int high) {
        return qrand() % (high - low) + low;
    }

    //Random long number
    qint64 randLong(qint64 low, qint64 high) {        
        return qrand() % (high - low) + low;
    }

    //Random double number
    double randDouble(double low, double high){
        return low + qrand()*(high-low)/RAND_MAX;
    }

private:
    HNetworkManager *networkManager;

private slots:
    void testBinary();
    void testInteger();
    void testLong();
    void testDouble();
    void testBool();
    void test2Parameters();

};

#endif // HUNITTEST_H
