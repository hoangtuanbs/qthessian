/***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
    File      : hnetworkmanager.cpp
    Project   : Qt Hessian
    Author(s) : HTV
    Conttent  : The network manager represents the service endpoint
    Requirement : Qt4.7+, QtNetwork

    Reference: http://hoangtuanonline.com/qthessian

  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************/


#include "hnetworkmanager.h"
#include "houtputstream.h"
#include "hinputstream.h"


/***************************************************************************
****************************************************************************
                    Constructor
****************************************************************************/
HNetworkManager::HNetworkManager(const QString& host, QNetworkAccessManager* manager, OperationMode mode , QObject *parent) :
    QObject(parent), hostUrl(host), operationMode(mode)
{
    networkManager = manager;
}


/***************************************************************************
****************************************************************************

Method name :   call
Content     :   this method makes call the service addressed by
networkManager
****************************************************************************/
QVariant* HNetworkManager::call( HCall* arg) {

    arg->setStatus(HCall::RUNNING);
    QNetworkReply * reply = networkManager->post(arg->getNetworkRequest(), arg->getSerializedData());;

    if (operationMode == ASYNCHRONOUS) {
        arg->setReply(reply);
        return 0;
    } else {
        // execute an event loop to process the request
        QEventLoop eventLoop;
        // also dispose the event loop after the reply has arrived
        connect(networkManager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
        eventLoop.exec();
        QVariant* v = processNetworkReply(reply);
        arg->receiveResult(v);
        delete reply;
        return v;
    }
}



/***************************************************************************
****************************************************************************
Method name :   pressNetworkReply
Content     :   Slot to process network reply
****************************************************************************/
QVariant* HNetworkManager::processNetworkReply(QNetworkReply *reply) {
    QVariant *v = new QVariant() ;
    HInputStream in (reply);
    in>>*v;
    return v;
}
