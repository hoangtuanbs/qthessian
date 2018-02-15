/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
    File        : hcall.h
    Project     : Qt Hessian
    Author(s)   : HTV
    Conttent    : The network manager represents the service endpoint
    Requirement : Qt4.7+, QtNetwork

    Reference   : http://hoangtuanonline.com/qthessian
    Requirement : Qt4.7+, QtNetwork
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/

#ifndef HCALL_H
#define HCALL_H

#include <QBuffer>
#include <QVariant>

#include "QtHessian.h"

class HNetworkManager;
class HCall;
using namespace hessian;

// Box class HCcall
class HCall: public QObject {
    Q_OBJECT
public:
    enum CALL_STATUS { RUNNING, IDLE, ERROR, FINISHED };

    // constructor
    HCall(HNetworkManager* manager, const QString& name);
    ~HCall();

    bool                isFinished ()   { return callStatus== FINISHED; ; }
    void                reset()         { callStatus = IDLE ; result = 0; }
    QVariant*           getResult() ;
    QVector<QVariant*>  getParameterList()   { return list; }
    QVariant*           at(const int& i) ;

    QString             getMethod()                 { return methodName; }
    void            setManager(HNetworkManager*);
    void            setStatus(CALL_STATUS c);
    CALL_STATUS     getStatus() {return callStatus; }

    const QByteArray& getSerializedData();
    void            setReply(QNetworkReply* );
    QNetworkReply*  getNetworkReply() ;

    const QNetworkRequest& getNetworkRequest();

    HCall& operator<< ( QVariant&);
    HCall& operator<< ( qint32& i) ;
    HCall& operator<< ( qint64&) ;
    HCall& operator<< ( bool&) ;
    HCall& operator<< ( QDateTime&) ;
    HCall& operator<< ( double&) ;
    HCall& operator<< ( QString&) ;
    HCall& operator<< ( QByteArray&);

    HCall& operator<< ( QList<QVariant>&);


    QVariant*  operator[](const int& i) ;
    int count() { return list.count () ; }

    void            refresh();
    void            freeResult();

signals:
    void callFinished(HCall* );

public slots:
    void receiveResult(QVariant* r) ;
private slots:
    void sltReplyFinished();
private:
    QString methodName;
    QVector<QVariant*> list;

    QVariant *          result ;
    HNetworkManager*    manager;
    QNetworkReply *     reply;
    QNetworkRequest     request;
    QBuffer             *buffer;
    CALL_STATUS         callStatus;
}; // end class HDouble

#endif // HCALL_H
