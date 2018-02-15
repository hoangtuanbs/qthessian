#include "hstreamtest.h"
#include <QBuffer>
#include "hcore/houtputstream.h"
#include "hcore/hinputstream.h"
#include "hcore/hobject.h"
#include <QFile>
#include <QDataStream>

using namespace hessian;

HStreamTest::HStreamTest(QObject *parent) :
    QObject(parent)
{
}


void HStreamTest::test() {

    qDebug(("Hessian streaming test. Target file stream. Writing"));
    QFile file("test.txt");
    file.open(QIODevice::WriteOnly);

    HOutputStream out(&file);

    HInteger i (9999);
    HInteger32 i32(2000000);

    out<<i;
    out<<i32;

    file.close();

    qDebug(("Hessian streaming test: Reading"));

    QFile read("test.txt");
    read.open(QIODevice::ReadOnly);
    if (!read.isOpen()) return;

    HInputStream in(&read);

    HInteger j(0);
    HInteger32 j32(0);

    in>>j;
    in>>j32;

    qDebug()<<"Hessian streaming test: "<< ((i.value()==j.value())?"TRUE":"FALSE");
    //qDebug()<<"Hessian streaming test: "<< ((i32.value()==j32.value())?"TRUE":"FALSE");

    read.close();
}


void HStreamTest::test1() {
    qDebug(("Hessian streaming test. Target data byte. Writing"));
    QBuffer data;
    data.open(QBuffer::ReadWrite);
    HOutputStream out(&data);
    HInteger i (9999);
    HInteger32 i32(2000000);

    out<<i;
    out<<i32;

    qDebug(("Hessian streaming test. Target data byte. Reading"));
    QByteArray ba =data.data();
    QBuffer dta(&ba);
    data.close();

    dta.open(QBuffer::ReadWrite);
    HInputStream in(&dta);
    HInteger j(0);
    HInteger32 j32(0);

    in>>j;
    in>>j32;
    qDebug()<<"Hessian streaming test: "<< ((i.value()==j.value())?"TRUE":"FALSE");
    qDebug()<<"Hessian streaming test: "<< ((i32.value()==j32.value())?"TRUE":"FALSE");
    data.close();
    //data2.close();;
}
