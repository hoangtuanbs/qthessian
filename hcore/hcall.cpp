 /***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
    File      : hcall.cpp
    Project   : Qt Hessian
    Author(s) : HTV
    Conttent  : The network manager represents the service endpoint
    Requirement : Qt4.7+, QtNetwork

    Reference: http://hoangtuanonline.com/qthessian
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************/
#include "hcall.h"
#include "hnetworkmanager.h"


/***************************************************************************
****************************************************************************
                    Network manager construction
****************************************************************************/
HCall::HCall(HNetworkManager* _manager, const QString& name): methodName (name), manager(_manager) {
    result = 0;
    buffer = 0;
    callStatus = IDLE;
    request.setUrl(manager->getURL());
}

/********************************************************************************
Method  :   getResult
Content :   Return the result stored . If there is no result stored, the function
will query the server.
*********************************************************************************/
QVariant* HCall::getResult() {
    // if this is a finished call
    if (callStatus == FINISHED) {
        return result;
    } else if (result==0) { // if there is no result
        refresh();
        return result;
    }
    return 0;
    // remember to clear result after fetching
}


/********************************************************************************
Method  :   refresh
Content :   Query server to get new result
*********************************************************************************/
void HCall::refresh() {

    // if there is a stored value, release it
    if (result!=0) {
        freeResult();
    }

    // if this call is working, then wait until it is finished
    if (getStatus()==RUNNING) {
        QEventLoop eventLoop;
        // also dispose the event loop after the reply has arrived
        connect(this, SIGNAL(callFinished(HCall*)), &eventLoop, SLOT(quit()));
        eventLoop.exec();
    }

    // start the call
    setStatus(RUNNING);
    manager->call(this);
}


/********************************************************************************
Method  :   receiveResult
Content :   This serves as an intermediate layer
*********************************************************************************/
void HCall::receiveResult(QVariant* r) {
    result = r;
    setStatus(FINISHED);
}

/********************************************************************************
Method  :   setStatus
Content :   Change status of the call
*********************************************************************************/
void HCall::setStatus(CALL_STATUS c) {
    callStatus = c;
    if (c==FINISHED) emit callFinished(this);
}

/********************************************************************************
Method  :   freeResult
Content :   Free the result
*********************************************************************************/
void HCall::freeResult() {
    if (result) {
        delete result;
    }
    result = 0;
}

/********************************************************************************
Method  :   getResult
Content :   Return
*********************************************************************************/
void HCall::setReply(QNetworkReply * rep) {
    reply = rep;
    connect(reply,SIGNAL(finished()), this, SLOT(sltReplyFinished()));
}


QNetworkReply* HCall::getNetworkReply() {
    return reply;
}

/********************************************************************************
Method  :   sltReplyFinish
Content :   This is for data processing
*********************************************************************************/

void HCall::sltReplyFinished() {
    result = new QVariant() ;
    HInputStream in (reply);
    in>>*result;
    this->setStatus(FINISHED);
}



/********************************************************************************
Method  :   Operators overloading
*********************************************************************************/


HCall& HCall::operator<< (QVariant& t) {
    list.append(&t);
    return *this;
}

HCall& HCall::operator<< ( qint32& i)  {
    list.append(new QVariant(i));
    return *this;
}


HCall& HCall::operator<< ( qint64& i) {
    list.append(new QVariant(i));
    return *this;
}

HCall& HCall::operator<< ( bool& i) {
    list.append(new QVariant(i));
    return *this;
}

HCall& HCall::operator<< ( QDateTime& i)  {
    list.append(new QVariant(i));
    return *this;
}

HCall& HCall::operator<< ( double& i)  {
    list.append(new QVariant(i));
    return *this;
}

HCall& HCall::operator<< ( QString& i)  {
    list.append(new QVariant(i));
    return *this;
}

HCall& HCall::operator<< (QByteArray& i) {
    list.append(new QVariant(i));
    return *this;
}


QVariant*  HCall::operator[](const int& i)  {
    return this->at(i);
}

QVariant*   HCall::at(const int& i)                   {
    while (i>=list.size()) {
        list.append(new QVariant());
    }
    return list[i];
}
/********************************************************************************
Method  :   Destructor
Content :
*********************************************************************************/
HCall::~HCall () {
    if (result) freeResult();
    int i;
    for (i = 0; i < list.size(); i++) {
        QVariant * v = list.at(i);
        delete v;
    }
    list.clear();
}


/********************************************************************************
Method  :   getSerializedData
Content :   return the serialized stream from the parameter list and method name
*********************************************************************************/
const QByteArray& HCall::getSerializedData() {
    // buffer to temporary store data
    if (buffer!=0) delete buffer;

    buffer = new QBuffer(this);
    buffer->open(QBuffer::ReadWrite);

    HOutputStream out(buffer);

    out.beginStream(this->getMethod());
    int i;
    for (i=0; i < this->count(); i ++) {
        out<<*(list.at(i));
    }
    out.endStream();
    return buffer->data();
}


/********************************************************************************
Method  :   getNetworkRequest
Content :   return the networkRequest generated by the service URL
*********************************************************************************/
const QNetworkRequest& HCall::getNetworkRequest() {
    return request;
}
