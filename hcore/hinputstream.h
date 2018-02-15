/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
  File      : hinputstream.h
  Project   : Qt Hessian
  Author(s) : HTV
  Conttent  : The input stream serializes Qt  types into the form that can be
  transferred to the Hessian service.
  Requirement : Qt4.7+, QtNetwork

  Reference: http://hoangtuanonline.com/qthessian
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


#ifndef HINPUTSTREAM_H
#define HINPUTSTREAM_H

#include <QObject>
#include <QIODevice>
#include <QDataStream>

#include "hobject.h"
#include "hconstants.h"
using namespace hessian;


class HInputStream : public QObject
{
    Q_OBJECT
public:
    explicit HInputStream(QIODevice *d);
    HInputStream& operator>>(QVariant& v);

signals:

public slots:

private:
    int version;
    QDataStream stream;
protected:
    qint32 readInt32();
    qint32 parseInt1Byte(quint8*);
    qint32 parseInt2Byte(quint8*);
    qint32 parseInt3Byte(quint8*);
    qint32 parseInt4Byte(quint8*);

    qint64 readInt64();
    qint64 parseLong1Byte (quint8* b);
    qint64 parseLong2Byte (quint8* b);
    qint64 parseLong3Byte (quint8* b);
    qint64 parseLong4Byte (quint8* b);
    qint64 parseLong8Byte (quint8* b);

    double readDouble();
    double parseDouble1Byte(quint8* b);
    double parseDouble2Byte(quint8* b);
    double parseDouble3Byte(quint8* b);
    double parseDouble4Byte(quint8* b);
    double parseDouble8Byte(quint8* b);

    bool readBool();
    bool parseBool(quint8*);

    QDateTime   readDateTime();
    QDateTime   parseDateTime4Byte();
    QDateTime   parseDateTime8Byte();

    QList<HObjectPtr>* readList();

    QList<HObjectPtr>* parseVariableList(quint8* b);
    QList<HObjectPtr>* parseFixedList(quint8* b);
    QList<HObjectPtr>* parseVariableUntypedList(quint8* b);
    QList<HObjectPtr>* parseFixedUntypedList(quint8* b);
    QList<HObjectPtr>* getListOfType(QString s);

    QString     readString();
    QString     parseStringInRange(long&);
    QString     parseStringInRange(int&);
    QString     parseString(int&);
    QString     parseStringSmallChunk(int&);    // 0-32 length
    QString     parseStringMediumChunk(int&);   // 0-1023 length
    QString     parseStringChunk(int&);         // 16 bit length

    QByteArray  parseBinaryShort(int &);    //0-16 length
    QByteArray  parseBinary(int&);          // general
    QByteArray  parseBinaryChunk();         // 0- 16bit
    QByteArray  parseBinarySmallChunk(int&); // 0-1023

    void        readOneElement(QVariant&);
    quint8 *    readData(int length);
    quint8 *    readData(int * length);
    char        readOneByte();
};

#endif // HINPUTSTREAM_H
