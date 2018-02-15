#ifndef PERFORMANCETEST_H
#define PERFORMANCETEST_H

#include <QObject>
#include "hcore/hcall.h"
class PerformanceTest : public QObject
{
    Q_OBJECT
public:
    explicit PerformanceTest(QObject *parent = 0);
    void test();
    void test2();
signals:

public slots:
   void sltReceivedData(HCall*);

private:
   long start;
   long count;
};

#endif // PERFORMANCETEST_H
