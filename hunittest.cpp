#include "hunittest.h"

HUnitTest::HUnitTest(QObject *parent) :
    QObject(parent)
{
    networkManager = new HNetworkManager("http://localhost:8080/TestService/Test");    
}

//===================
//Test Binary values
//===================
void HUnitTest::testBinary()
{
    QByteArray buffer;
    int value, value_expected;
    int v, v_e;
    for (int i = 0; i<1023;i++) {
        buffer.append("abcdefg");
    }
    value_expected = buffer.size();
    HCall c (networkManager, "feedbackBinary");
    c<<buffer;
    value = c.getResult()->toByteArray().length();
    QCOMPARE(value, value_expected);

    //test binary length 0-16
    buffer.clear();
    for(int i = 0; i<16;i++)
        buffer.append("");
    v_e = buffer.size();
    c.at(0)->setValue(buffer);
    c.refresh();
    v = c.getResult()->toByteArray().length();
    QCOMPARE(v, v_e);
}

//====================
//Test Integer values
//====================
void HUnitTest::testInteger()
{
    int value, value_expected;
    int v1,v2,v3,v4, v5;
    int v_e1, v_e2, v_e3, v_e4, v_e5;
    int v[MAX], v_e[MAX];

    //test single octet
    QVariant i1(-16);
    value_expected = i1.toInt();
    HCall *c = new HCall(networkManager, "feedback");
    *c<<i1;
    value = c->getResult()->toInt();    
    QCOMPARE(value, value_expected);

    QVariant i2(47);
    v_e1 = i2.toInt();
    c->at(0)->setValue(i2);
    c->refresh();
    v1 = c->getResult()->toInt();
    QCOMPARE(v1, v_e1);


    //test 2 octets
    QVariant i3(-2048);
    v_e2 = i3.toInt();
    c->at(0)->setValue(i3);
    c->refresh();
    v2 = c->getResult()->toInt();
    QCOMPARE(v2, v_e2);

    QVariant i4(2047);
    v_e3 = i4.toInt();
    c->at(0)->setValue(i4);
    c->refresh();
    v3 = c->getResult()->toInt();
    QCOMPARE(v3, v_e3);

    //test 3 octets
    QVariant i5(-262144);
    v_e4 = i5.toInt();
    c->at(0)->setValue(i5);
    c->refresh();
    v4 = c->getResult()->toInt();
    QCOMPARE(v4, v_e4);

    QVariant i6(262143);
    v_e5 = i6.toInt();
    c->at(0)->setValue(i6);
    c->refresh();
    v5 = c->getResult()->toInt();
    QCOMPARE(v5, v_e5);

    //Test random values
    for (int i=0; i<MAX; i++){
        QVariant j(randInt(-100,100));
        v_e[i] = j.toInt();
        c->at(0)->setValue(j);
        c->refresh();
        v[i] = c->getResult()->toInt();
        QCOMPARE(v[i], v_e[i]);
    }

    c->freeResult();
    delete c;
}

//=================
//Test Long values
//=================
void HUnitTest::testLong()
{
    qint64 value, value_expected;
    qint64 v1, v2, v3, v4, v5, v6;
    qint64 v_e1, v_e2, v_e3, v_e4, v_e5, v_e6;
    qint64 v[MAX], v_e[MAX];

    //Test single octet
    QVariant j(-8);
    value_expected = j.toLongLong();
    HCall c(networkManager, "feedbackLong");
    c<<j;
    value = c.getResult()->toLongLong();
    QCOMPARE(value,value_expected);

    QVariant j1(15);
    v_e1 = j1.toLongLong();
    c.at(0)->setValue(j1);
    c.refresh();
    v1 = c.getResult()->toLongLong();
    QCOMPARE(v1, v_e1);

    //Test 2 octets
    QVariant j2(-2048);
    v_e2 = j2.toLongLong();
    c.at(0)->setValue(j2);
    c.refresh();
    v2 = c.getResult()->toLongLong();
    QCOMPARE(v2, v_e2);

    QVariant j3(2047);
    v_e3 = j3.toLongLong();
    c.at(0)->setValue(j3);
    c.refresh();
    v3 = c.getResult()->toLongLong();
    QCOMPARE(v3, v_e3);

    //Test 3 octets
    QVariant j4(-262144);
    v_e4 = j4.toLongLong();
    c.at(0)->setValue(j4);
    c.refresh();
    v4 = c.getResult()->toLongLong();
    QCOMPARE(v4, v_e4);

    QVariant j5(262143);
    v_e5 = j5.toLongLong();
    c.at(0)->setValue(j5);
    c.refresh();
    v5 = c.getResult()->toLongLong();
    QCOMPARE(v5, v_e5);

    //Test 4 octets
    QVariant j6(999999999);
    v_e6 = j6.toLongLong();
    c.at(0)->setValue(j6);
    c.refresh();
    v6 = c.getResult()->toLongLong();
    QCOMPARE(v6, v_e6);

    //Test random values
    for(int i=0; i<MAX;i++){
        QVariant j(randLong(-11111,14667));
        v_e[i] = j.toLongLong();
        c.at(0)->setValue(j);
        c.refresh();
        v[i] = c.getResult()->toLongLong();
        QCOMPARE(v[i], v_e[i]);
    }
}

//===================
//Test Double values
//===================
void HUnitTest::testDouble()
{
    double value, value_expected;
    double v1, v2, v3, v4, v5, v6;
    double v_e1, v_e2, v_e3, v_e4, v_e5, v_e6;
    double v[MAX], v_e[MAX];

    //Test zero
    QVariant d(0.0);
    value_expected = d.toDouble();
    HCall c(networkManager, "feedbackDouble");
    c<< d;
    value = c.getResult()->toDouble();
    QCOMPARE(value, value_expected);

    //Test 1.0
    QVariant d1(1.0);
    v_e1 = d1.toDouble();
    c.at(0)->setValue(d1);
    c.refresh();
    v1 = c.getResult()->toDouble();
    QCOMPARE(v1,v_e1);

    //Test double octet
    QVariant d2(-128.0);
    v_e2 = d2.toDouble();
    c.at(0)->setValue(d2);
    c.refresh();
    v2 = c.getResult()->toDouble();
    QCOMPARE(v2,v_e2);

    QVariant d3(127.0);
    v_e3 = d3.toDouble();
    c.at(0)->setValue(d3);
    c.refresh();
    v3 = c.getResult()->toDouble();
    QCOMPARE(v3,v_e3);

    //Test double short
    QVariant d4(-32768.0);
    v_e4 = d4.toDouble();
    c.at(0)->setValue(d4);
    c.refresh();
    v4 = c.getResult()->toDouble();
    QCOMPARE(v4,v_e4);

    QVariant d5(32767.0);
    v_e5 = d5.toDouble();
    c.at(0)->setValue(d5);
    c.refresh();
    v5 = c.getResult()->toDouble();
    QCOMPARE(v5,v_e5);

    //Test double float
    QVariant d6(99999999.0);
    v_e6 = d6.toDouble();
    c.at(0)->setValue(d6);
    c.refresh();
    v6 = c.getResult()->toDouble();
    QCOMPARE(v6,v_e6);

    for(int i=0; i<MAX; i++){
        QVariant d(randDouble(-1934.5, 2577));
        v_e[i] = d.toDouble();
        c.at(0)->setValue(d);
        c.refresh();
        v[i] = c.getResult()->toDouble();
        QCOMPARE(v[i], v_e[i]);
    }
}

//=================
//Test Bool values
//=================
void HUnitTest::testBool()
{
    bool value , value_expected;
    QVariant b(true);
    value_expected = b.toBool();
    HCall c(networkManager, "feedbackBoolean");
    c<<b;
    value = c.getResult()->toBool();
    QCOMPARE(value, value_expected);
}

//=========================
//Test 2 parameters values
//=========================
void HUnitTest::test2Parameters()
{
    int value, value_expected;
    int i=10, j=20;
    value_expected = i+j;
    HCall c(networkManager, "add2");
    c << i<< j;
    value = c.getResult()->toInt();
    QCOMPARE(value,value_expected);
}
