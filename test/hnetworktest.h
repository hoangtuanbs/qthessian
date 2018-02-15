#ifndef HNETWORKTEST_H
#define HNETWORKTEST_H

#include <QObject>
#include "hcore/hnetworkmanager.h"
class HNetworkTest : public QObject
{
    Q_OBJECT
public:
    explicit HNetworkTest(QObject *parent = 0);
    void test();
    void testInteger();
    void testLong();
    void testDouble();
    void testBool();
    void test2Parameters();
    void testBinary();
signals:

public slots:

private:
    HNetworkManager *networkManager;
};

#endif // HNETWORKTEST_H
