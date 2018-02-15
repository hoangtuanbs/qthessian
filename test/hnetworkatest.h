#ifndef HNETWORKATEST_H
#define HNETWORKATEST_H

#include <QObject>
#include "QtHessian.h"

class HNetworkATest : public QObject
{
    Q_OBJECT
public:
    explicit HNetworkATest(QObject *parent = 0);

    void test();
    void testInteger();
    void testLong();
    void testDouble();
    void testBool();
    void testBinary();
signals:

public slots:
    void sltReceivedData(HCall*);
private:
    HNetworkManager *networkManager;
};

#endif // HNETWORKATEST_H
