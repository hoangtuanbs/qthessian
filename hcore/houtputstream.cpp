/***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
        Qt Hessian
        HTV-LT
        This class write data to the stream

  ***************************************************************************
  ***************************************************************************
  ***************************************************************************
  ***************************************************************************/
#include "houtputstream.h"


#define BYTE7 56
#define BYTE6 48
#define BYTE5 40
#define BYTE4 32
#define BYTE3 24
#define BYTE2 16
#define BYTE1 8
#define MASK 0xFF
#define MASK2 0xFFFF


/***************************************************************************
***************************************************************************
      Operator << overloaded for QVariant's type
***************************************************************************/
HOutputStream& HOutputStream::operator<< (const QVariant& i) {
    if (i.isNull())
        writeNull();
    else {
        switch (i.type()) {
        case QVariant::Int:
                writeInteger32(i.toInt());
                break;

        case QVariant::LongLong:
                writeInteger64(i.toLongLong());
                break;
        case QVariant::Double:
                writeDouble(i.toDouble());
                break;

        case QVariant::Bool:
                writeBool(i.toBool());
                break;

        case QVariant::DateTime:
                writeDate(i.toDateTime());
                break;
        case QVariant::String:
                writeUTF8String(i.toString());
            break;
        case QVariant::ByteArray:
                writeBinary(i.toByteArray());
            break;

        default:
                throw new HException("Unhandle type");
        }
    }
    return *this;
}


/***************************************************************************
***************************************************************************
      Begin the stream with method named m
***************************************************************************/
void HOutputStream::beginStream(const char* m) {
    // Hessian 2.0
    char c[] = {BC_CALL,0x02,0x0, BC_METHOD, '\0', '\0'};

    int l = strlen(m);
    l &=MASK2;
    c[4] =((l>>BYTE1)& MASK);
    c[5] =((l)& MASK);
    stream.writeRawData(c,6);
    stream.writeRawData(m,l);
}


/***************************************************************************
***************************************************************************
      Begin the stream with method named m
***************************************************************************/
void HOutputStream::beginStream(const QString& m) {
    beginStream(m.toAscii().data());
}


/***************************************************************************
***************************************************************************
      Operator << overload for QVariant's type
***************************************************************************/
void HOutputStream::endStream(){
    stream.writeRawData(&BC_END,1);
}


/***************************************************************************
***************************************************************************
Method name :   writeInteger32
Content     :   this method serialized the 32-bit int into the form
    I BYTE3 BYTE2 BYTE1 BYTE0
***************************************************************************/
void HOutputStream::writeInteger32(const qint32& value) {
    static int nArray = 5;
    char a[] = { BC_INT,
        (value>>BYTE3)&0xff,
        (value>>BYTE2)&MASK,
        (value>>BYTE1)&MASK,
        (value)&MASK };
   stream.writeRawData(a,nArray);
}


/***************************************************************************
***************************************************************************
Method name :   writeInteger64
Content     :   this method serialized the 64-bit int into the form
    L BYTE7 BYTE6 BYTE5 BYTE4 BYTE3 BYTE2 BYTE1 BYTE0
***************************************************************************/
void HOutputStream::writeInteger64(const qint64& value) {
    qDebug() << "Writing " << value;
    static int nArray=9;
    char a[9] = {BC_LONG,
            (value>>BYTE7)&MASK,
            (value>>BYTE6)&MASK,
            (value>>BYTE5)&MASK,
            (value>>BYTE4)&MASK,
            (value>>BYTE3)&MASK,
            (value>>BYTE2)&MASK,
            (value>>BYTE1)&MASK,
            (value)&MASK};
    stream.writeRawData(a,nArray);
}


/***************************************************************************
***************************************************************************
Method name :   writeDouble
Content     :   this method serialized a double number into the form
    D BYTE7 BYTE6 BYTE5 BYTE4 BYTE3 BYTE2 BYTE1 BYTE0
***************************************************************************/
void HOutputStream::writeDouble(const double &d) {
    qDebug() << "Writing " << d;
    quint64 value;
    memcpy(&value, &d, 8);
    static const int nArray=9;
    char a[9] = {BC_DOUBLE,
            (value>>BYTE7)&MASK,
            (value>>BYTE6)&MASK,
            (value>>BYTE5)&MASK,
            (value>>BYTE4)&MASK,
            (value>>BYTE3)&MASK,
            (value>>BYTE2)&MASK,
            (value>>BYTE1)&MASK,
            (value)&MASK};
    stream.writeRawData(a,nArray);
}

/***************************************************************************
***************************************************************************
Method name :   writeBool
Content     :   this method serialized a boolean into byte 'T' or 'F'
dependent on the value.

***************************************************************************/
void HOutputStream::writeBool(const bool &b) {
    if (b)
        stream.writeRawData(&BC_TRUE,1) ;
    else
        stream.writeRawData(&BC_FALSE,1) ;
}

/***************************************************************************
***************************************************************************
Method name :   writeDate
Content     :   this method serialized a QDateTime object into 64-bit int
dependent on the value.

***************************************************************************/
void HOutputStream::writeDate(const QDateTime &d) {
    quint64 value = d.toMSecsSinceEpoch();
    static const int nArray=9;
    char a[9] = {BC_DATE,
            (value>>BYTE7)&MASK,
            (value>>BYTE6)&MASK,
            (value>>BYTE5)&MASK,
            (value>>BYTE4)&MASK,
            (value>>BYTE3)&MASK,
            (value>>BYTE2)&MASK,
            (value>>BYTE1)&MASK,
            (value)&MASK};

    stream.writeRawData(a,nArray) ;
}


/***************************************************************************
***************************************************************************
Method name :   writeString
Content     :   this method serialized a standard 8 bit string, the length
of the string is limited by an 16-bit integer.
***************************************************************************/
void HOutputStream::writeString (const char* m) {
    int i = strlen(m)&MASK2;
    char header[] = { (i>>BYTE1)& MASK, i&MASK};
    stream.writeRawData(header,2);
    stream.writeRawData(m,i);
}


/***************************************************************************
***************************************************************************
Method name :   writeUTF8String
Content     :   this method serialized a 16-bit encoded UTF8 string.
***************************************************************************/
void HOutputStream::writeString (const char* m, int size) {
    int i = size & MASK2;
    char header[] = { (i>>BYTE1)& MASK, i&MASK};
    stream.writeRawData(header,2);
    stream.writeRawData(m,i);
}


/***************************************************************************
***************************************************************************
Method name :   write16Bit Length UTF8String
Content     :   this method serialized a 16-bit length encoded UTF8 string.
This is the elementary function for writing UTF8String
***************************************************************************/
void HOutputStream::writeUTF8StringChunk (const QString& s ){
    QByteArray byteArray =  s.toUtf8();

    int i = s.length()& MASK2;
    char header[] = { (i>>BYTE1)& MASK, i&MASK};
    stream.writeRawData(header,2);
    stream.writeRawData(byteArray.data(),byteArray.length());
}


/***************************************************************************
***************************************************************************
Method name :   writeUTF8String
Content     :   this method serialized a 16-bit encoded UTF8 string.
***************************************************************************/
void HOutputStream::writeUTF8String (const QString& s) {
    QString temp;
    int     i,
            max_index =   ceil(s.length()*1.0/STRING_CHUNK_MAX);

    for (i=0; i< max_index-1; i++){
        stream.writeRawData(&BC_STRING_NON_FINAL, 1);
        temp = s.mid( (i*STRING_CHUNK_MAX), STRING_CHUNK_MAX); // temporary string
        writeUTF8StringChunk(temp);
    } ;

    stream.writeRawData(&BC_STRING, 1);
    temp = s.mid( (i*STRING_CHUNK_MAX), STRING_CHUNK_MAX);
    writeUTF8StringChunk(temp);
}




/***************************************************************************
***************************************************************************
Method name :   writeBinary
Content     :   this method serialized a 16-bit encoded UTF8 string.
***************************************************************************/
void HOutputStream::writeBinary(const QByteArray& b) {
    const char * c = b.data();
    const char * t = c;
    int     i, max_index = ceil(strlen(c)*1.0/BINARY_CHUNK_MAX);
    for (i=0; i< max_index-1; i++){
        stream.writeRawData(&BC_BINARY_NON_FINAL, 1);
        writeString(t, BINARY_CHUNK_MAX);
        t += BINARY_CHUNK_MAX;
    } ;

    stream.writeRawData(&BC_BINARY, 1);
    writeString(t);;
}

void HOutputStream::writeList(const QList<QVariant>&) {

}

void HOutputStream::writeMap(const QMap<QVariant, QVariant>&) {

}

void HOutputStream::writeObject (const QByteArray&) {

}


void HOutputStream::writeNull () {
    stream.writeRawData(&BC_NULL,1);
}
