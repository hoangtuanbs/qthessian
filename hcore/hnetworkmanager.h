/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
  File      : hnetworkmanager.h
  Project   : Qt Hessian
  Author(s) : HTV
  Conttent  : The network manager represents the service endpoint
  Requirement : Qt4.7+, QtNetwork,

  Reference: http://hoangtuanonline.com/qthessian
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/
#ifndef HNETWORKMANAGER_H
#define HNETWORKMANAGER_H

#include <QObject>
#include <QVariant>


#include "hcall.h"

class HCall;
using namespace hessian;

enum OperationMode {
    ASYNCHRONOUS = 1,
    SYNCHRONOUS
};



class HNetworkManager : public QObject {
    Q_OBJECT

public:
    explicit HNetworkManager(const QString& host, QNetworkAccessManager* manager = new QNetworkAccessManager(), OperationMode mode = SYNCHRONOUS, QObject *parent = 0);

    QVariant* call( HCall *arg );
    HCall* call(const QString &call, QVariant &arg );
    HCall* call(const char call[], QVariant &arg );
    QUrl    getURL() {return hostUrl;};
signals:
    void receiveData(HCall*);

private:
    QUrl hostUrl;
    QNetworkAccessManager *networkManager;

    OperationMode operationMode;
    QVariant* processNetworkReply(QNetworkReply*);

};



#endif // HNETWORKMANAGER_H
