/**************************************************************************
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

#ifndef HOUTPUTSTREAM_H
#define HOUTPUTSTREAM_H

#include <QObject>
#include <QDataStream>
#include <QIODevice>
#include <QDateTime>
#include <QVariant>

#include "QtHessian.h"
#include "hconstants.h"
using namespace hessian;

namespace hessian {
    class HOutputStream : public QObject
    {
        Q_OBJECT
    public:
        explicit HOutputStream(QIODevice *d): stream(d) {}

        HOutputStream& operator<< (const QVariant&);

        void beginStream(const char* );
        void beginStream(const QString& );
        void endStream();


    protected:
        void writeInteger32 (const qint32&);
        void writeInteger64 (const qint64&);
        void writeDouble    (const double&);
        void writeBool      (const bool&);
        void writeDate      (const QDateTime&);
        void writeString    (const char*);
        void writeString    ( const char*, int);
        void writeUTF8StringChunk (const QString& s );

        void writeUTF8String (const QString& s);
        void writeBinary    (const QByteArray&);

        void writeList      (const QList<QVariant>&);
        void writeList      (const QList<quint32>&);
        void writeList      (const QList<quint64>&);
        void writeList      (const QList<double>&);
        void writeList      (const QList<bool>&);
        void writeList      (const QList<QDateTime>&);
        void writeList      (const QList<QString>&);
        void writeList      (const QList<QByteArray>&);

        void writeMap       (const QMap<QVariant, QVariant>&);
        void writeObject    (const QByteArray&);
        void writeNull      ();
        //void writeRef(const)
    private:
        QDataStream stream;
    };
}
#endif // HOUTPUTSTREAM_H
