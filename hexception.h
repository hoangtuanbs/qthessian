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
#ifndef HEXCEPTION_H
#define HEXCEPTION_H

#include <QObject>
#include <QtCore>
using namespace std;
namespace hessian {
    class HException {

    public:
        HException(QString message): _message(message) {}
        HException(char *message): _message(message) {}
        HException(const char *message): _message(message) {}
        QString message () { return _message; }

    private:
        QString _message;
    };


    class HIOException: public HException {
    public:
        HIOException(): HException(QString("Input/Output exception")) {}
    };

    class HInvalidDataFormat: public HException {
    public:
        HInvalidDataFormat(): HException(QString("Invalid data format")) {}
    };

    class HInvalidTagException: public HException {
    public:
        HInvalidTagException(char expect, char receive): HException(("Invalid tag, expect " + QString::number(expect )+ " but received " +QString::number(receive) )) {}
    };

    class HValueOutOfRangeException: public HException {
    public:
        HValueOutOfRangeException(): HException(QString("Value is out of range")){}
        HValueOutOfRangeException(int min, int max, int receive): HException(QString("Value is out of range [")+
                                                                             QString::number(min)+", " + QString::number(max)+"] "+
                                                                             "but received " + QString::number(receive)) {};
    };

}
#endif // HEXCEPTION_H
