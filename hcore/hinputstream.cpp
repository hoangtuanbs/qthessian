/***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
    File      : hinputstream.cpp
    Project   : Qt Hessian
    Author(s) : HTV
    Conttent  : Stream parser
    Requirement : Qt4.7+, QtNetwork

    Reference: http://hoangtuanonline.com/qthessian
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/

#include "hinputstream.h"
#include "hexception.h"






/***************************************************************************
****************************************************************************
Method name :   Constructor
Content     :   Constructor with and QIODevice
****************************************************************************/
HInputStream::HInputStream(QIODevice* d) :
    stream(d) {
    if ((!d->isReadable())|| (!d->isReadable())) throw new HIOException ();
#ifndef _DEBUG_
    //char *c;
    quint8  *e = readData(4);

    if (e[0] !='H') throw new HInvalidTagException('H',  e[0]);
    version = e[1];
    delete []e;
#endif
}

/***************************************************************************
****************************************************************************
Method name :   operator>> overloading
Content     :   general input for QVariant's types
****************************************************************************/
HInputStream& HInputStream::operator >>(QVariant& v) {
    readOneElement(v);
    return *this;
}

/***************************************************************************
****************************************************************************
Method name :   readInt32
Content     :   Read a 32-bit integer
****************************************************************************/
qint32 HInputStream::readInt32() {
    qint32 ret = 0;
    quint8  *b = readData(1);

    if (*b>=0x80&& *b <=0xBF) ret = parseInt1Byte(b);
    else
    switch (*b) {
        case 0xC0:
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC4:
        case 0xC5:
        case 0xC6:
        case 0xC7:
        case 0xC8:
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCC:
        case 0xCD:
        case 0xCE:
        case 0xCF:
            /* two octet compact int */
            ret = parseInt2Byte(b);
            break;

        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            /* three octet compact int */
            ret = parseInt3Byte(b);
            break;
        case 0x49:
            ret= parseInt4Byte(0);
            break;
        default: throw new HInvalidTagException('I', *b);
    }
    delete [] b;
    return ret;
}

/***************************************************************************
****************************************************************************
Method name :   readInt64
Content     :   Read a 64-bit integer
Note        :   Use only when you are expecting a long integer from
the stream
****************************************************************************/
qint64 HInputStream::readInt64() {
    qint64 ret = 0;
    quint8  *b = readData(1);

    switch (*b) {
        case 0xD8:
        case 0xD9:
        case 0xDA:
        case 0xDB:
        case 0xDC:
        case 0xDD:
        case 0xDE:
        case 0xDF:
        case 0xE0:
        case 0xE1:
        case 0xE2:
        case 0xE3:
        case 0xE4:
        case 0xE5:
        case 0xE6:
        case 0xE7:
        case 0xE8:
        case 0xE9:
        case 0xEA:
        case 0xEB:
        case 0xEC:
        case 0xED:
        case 0xEE:
        case 0xEF:

            ret = parseLong1Byte(b);
            break;

        case 0xF0:
        case 0xF1:
        case 0xF2:
        case 0xF3:
        case 0xF4:
        case 0xF5:
        case 0xF6:
        case 0xF7:
        case 0xF8:
        case 0xF9:
        case 0xFA:
        case 0xFB:
        case 0xFC:
        case 0xFD:
        case 0xFE:
        case 0xFF:

            ret = parseLong2Byte(b);
            break;

        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:

            ret = parseLong3Byte(b);
            break;
        case 0x59:
            ret = parseLong4Byte(b);
            break;
        case 0x4C:
            ret = parseLong8Byte(b);
            break;
        default: throw new HInvalidTagException('L', *b);
    }
    delete [] b;
    return ret;
}

/***************************************************************************
****************************************************************************
Method name :   readDouble
Content     :   Read double from stream
Note        :   Use only when you are expecting a double from the stream
****************************************************************************/
double  HInputStream::readDouble() {
    double ret=0;
    quint8 *b = readData(1);
    switch (*b) {
    case 0x5b:
    case 0x5c:
            ret = parseDouble1Byte(b);
            break;
        case 0x5D:
            ret = parseDouble2Byte(b);
            break;
        case 0x5E:
            ret = parseDouble3Byte(b);
            break;
        case 0x5F:
            ret = parseDouble4Byte(b);
            break;
        case 0x44:
            //if (e[0]!='D') throw HInvalidTagException('D', e[0]);
            ret = parseDouble8Byte(b);

            break;
        default: throw HIOException ();
    }
    delete []b;

    return ret;
}

/***************************************************************************
                    BOOLEAN
  **************************************************************************/

bool HInputStream::readBool() {
    quint8  * b = readData(1);

    bool ret = parseBool(b);
    delete []b;

    return ret;
}

/***************************************************************************
                    Read datetime
  **************************************************************************/

QDateTime HInputStream::readDateTime() {
    quint8  * b = readData(1);
    switch (*b) {
    case 0x4a:
        return parseDateTime8Byte();
        break;
    case 0x4b:
        return parseDateTime4Byte();
        break;
    default: throw new HInvalidDataFormat();
    }

    delete []b;
    //return ret;
}

/***************************************************************************
                    Read String
  **************************************************************************/

QString HInputStream::readString(){
    int tag  = readOneByte()&0xFF;

    return parseString(tag);
}



void HInputStream::readOneElement(QVariant& v) {
    quint8 *b  = (quint8*) readData(1);

    int length = b[0]&0xff;
    switch (length) {

        /* 0x00 - 0x1F */
    case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
    case 0x08: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0E: case 0x0F:
    case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
    case 0x18: case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D: case 0x1E: case 0x1F:

        /* utf8 string length 32 */
        v.setValue(parseStringSmallChunk(length));
        break;

    case 0x20: case 0x21:case 0x22:case 0x23:case 0x24:case 0x25:case 0x26:case 0x27:
    case 0x28:case 0x29:case 0x2A:case 0x2B:case 0x2C:case 0x2D:case 0x2E:case 0x2F:

        v.setValue(parseBinaryShort(length));
        /* read binary data length 0-16 */
        break;

    case 0x30:case 0x31:case 0x32:case 0x33:
        /* read string */
        v.setValue(parseStringMediumChunk(length));
        break;

    case 0x34:case 0x35:case 0x36:case 0x37:
        v.setValue(parseBinarySmallChunk(length));
        /* read binary 0-1024*/
        break;

    case 0x38:case 0x39:case 0x3A:case 0x3B:case 0x3C:case 0x3D:case 0x3E:case 0x3F:
        /* Read Long 3 byte*/
        v.setValue (parseLong3Byte(b));
        break;

    case 0x41:
        v.setValue(parseBinary(length));
        /* Read binary nonfinal */
        break;
    case 0x42:
        v.setValue(parseBinary(length));
        /* Read binary final */
        break;

    case 0x43:
        /* Read object definition */
        break;
    case 0x44:
        /* Read double */
        v.setValue(parseDouble8Byte(b));
        break;

    case 0x46:
        v.setValue(parseBool(b));
        /* Read boolean */
    case 0x47:
        /* reserved*/
        break;

    case 0x48:
        /* untyped map */
        break;
    case 0x49:
        /*32-bit signed integer ('I')*/
        v.setValue(parseInt4Byte(b));
        break;
    case 0x4a:
        /* 64-bit UTC millisecond date*/
        v.setValue(parseDateTime8Byte());
        break;
    case 0x4b:
        /* 32-bit UTC minute date*/
        v.setValue (parseDateTime4Byte());
        break;
    case 0x4c:
        /**# 64-bit signed long integer ('L') */
        v.setValue (parseLong8Byte(b));
        break;

    case 0x4d:
        /*# map with type ('M') */
        break;
    case 0x4e:
        /* null ('N')*/
        v.setValue(QVariant());
        break;
    case 0x4f:
        /* object instance ('O')*/
        break;
    case 0x50:
        break;

    case 0x51:
        /* reference to map/list/object - integer ('Q')*/
        break;
    case 0x52:
        /* utf-8 string non-final chunk ('R')*/
        v.setValue (parseString(length));
        break;
    case 0x53:
        /* utf-8 string final chunk ('S') */
        v.setValue (parseString(length));
        break;
    case 0x54:
        /* # boolean true ('T')*/
        v.setValue(parseBool(b));
        break;
    case 0x55:
        /*# variable-length list/vector ('U')*/
        break;
    case 0x56:
        /*# fixed-length list/vector ('V')*/
        break;
    case 0x57:
        /* variable-length untyped list/vector ('W') */
        break;
    case 0x58:
        /* fixed-length untyped list/vector ('X') */
        break;
    case 0x59:
        /* long encoded as 32-bit int ('Y') */
        v.setValue(parseLong4Byte(b));
        break;
    case 0x5a:
        /*  list/map terminator ('Z') */
        break;
    case 0x5b:
        /* double 0.0 */
        v.setValue (parseDouble1Byte(b));
        break;
    case 0x5c:
        /* double 1.0 */
        v.setValue(parseDouble1Byte(b));
        break;

    case 0x5d:
        /* double represented as byte (-128.0 to 127.0) */
        v.setValue(parseDouble2Byte(b));
        break;

    case 0x5e:
        /* double represented as short (-32768.0 to 327676.0) */
        v.setValue(parseDouble3Byte(b));
        break;

    case 0x5f:
        /*double represented as float*/
        v.setValue(parseDouble4Byte(b));
        break;

    case 0x60:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:
    case 0x68:case 0x69:case 0x6A:case 0x6B:case 0x6C:case 0x6D:case 0x6E:case 0x6F:
        /* object with direct type */
        break;

    case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:case 0x77:
        /* fixed list with direct length */
        break;

    case 0x78:case 0x79:case 0x7A:case 0x7B:case 0x7C:case 0x7D:case 0x7E:case 0x7F:
        /* fixed untyped list with direct length*/
        break;

    case 0x80:case 0x81:case 0x82:case 0x83:case 0x84:case 0x85:case 0x86:case 0x87:
    case 0x88:case 0x89:case 0x8A:case 0x8B:case 0x8C:case 0x8D:case 0x8E:case 0x8F:
    case 0x90:case 0x91:case 0x92:case 0x93:case 0x94:case 0x95:case 0x96:case 0x97:
    case 0x98:case 0x99:case 0x9A:case 0x9B:case 0x9C:case 0x9D:case 0x9E:case 0x9F:
    case 0xA0:case 0xA1:case 0xA2:case 0xA3:case 0xA4:case 0xA5:case 0xA6:case 0xA7:
    case 0xA8:case 0xA9:case 0xAA:case 0xAB:case 0xAC:case 0xAD:case 0xAE:case 0xAF:
    case 0xB0:case 0xB1:case 0xB2:case 0xB3:case 0xB4:case 0xB5:case 0xB6:case 0xB7:
    case 0xB8:case 0xB9:case 0xBA:case 0xBB:case 0xBC:case 0xBD:case 0xBE:case 0xBF:
        v.setValue(parseInt1Byte(b));
        break;

    case 0xC0:case 0xC1:case 0xC2:case 0xC3:case 0xC4:case 0xC5:case 0xC6:case 0xC7:
    case 0xC8:case 0xC9:case 0xCA:case 0xCB:case 0xCC:case 0xCD:case 0xCE:case 0xCF:

        /* two octet compact int */
        v.setValue(parseInt2Byte(b));
        break;

    case 0xD0:case 0xD1:case 0xD2:case 0xD3:case 0xD4:case 0xD5:case 0xD6:case 0xD7:

                /* three octet compact int */
        v.setValue (parseInt3Byte(b));
        break;

    case 0xD8:case 0xD9:case 0xDA:case 0xDB:case 0xDC:case 0xDD:case 0xDE:case 0xDF:
    case 0xE0:case 0xE1:case 0xE2:case 0xE3:case 0xE4:case 0xE5:case 0xE6:case 0xE7:
    case 0xE8:case 0xE9:case 0xEA:case 0xEB:case 0xEC:case 0xED:case 0xEE:case 0xEF:
        /* one octect compact long*/
        v.setValue(parseLong1Byte(b));
        break;

    case 0xF0:case 0xF1:case 0xF2:case 0xF3:case 0xF4:case 0xF5:case 0xF6:case 0xF7:
    case 0xF8:case 0xF9:case 0xFA:case 0xFB:case 0xFC:case 0xFD:case 0xFE:case 0xFF:
        /* two octet compact long */
        v.setValue (parseLong2Byte(b));
        break;
    }
}


inline char HInputStream::readOneByte() {
    char d;
    stream.readRawData(&d, 1);
    return d;
}

inline quint8* HInputStream::readData(int length) {
    quint8 *c = new quint8[length];
    char *d = (char*)c;
    int i = stream.readRawData(d, length);
    if (length!=i) throw new HIOException();
    return c;
}

inline quint8* HInputStream::readData(int * length) {
    quint8 *c = new quint8[*length];
    char *d = (char*)c;
    int i = stream.readRawData(d, *length);
    *length = i;
    return c;
}



QList<HObjectPtr>* HInputStream::readList() {
    QList<HObjectPtr>* ret =0;
    quint8 * b = readData(1);
    quint8 * e;
    char *f;
    switch (*b) {
    case 0x55:
        e = readData( 1);
        f = (char*) readData(*e);
        ret = getListOfType(QString(f));
        delete []f;
        delete []e;
        break;
    }

    return ret;
}

QList<HObjectPtr>* HInputStream::parseVariableList(quint8* b) {
    QList<HObjectPtr>* ret=0;

    return ret;
}

QList<HObjectPtr>* HInputStream::parseFixedList(quint8* b) {
    QList<HObjectPtr>* ret=0;

    return ret;
}

QList<HObjectPtr>* HInputStream::parseVariableUntypedList(quint8* b) {
    QList<HObjectPtr>* ret=0;

    return ret;
}

QList<HObjectPtr>* HInputStream::parseFixedUntypedList(quint8* b) {
    QList<HObjectPtr>* ret=0;

    return ret;
}

QList<HObjectPtr>* HInputStream::getListOfType(QString s) {
    QList<HObjectPtr>* ret=0;

    if (s.compare("[int")==0) return (QList<HObjectPtr>* )new QList <HInteger*>;
    if (s.compare("[boolean") ==0) return (QList<HObjectPtr>* )new QList <HBool*>;
    if (s.compare("[long") ==0) return (QList<HObjectPtr>* )new QList <HLong*>;
    if (s.compare("[double")==0) return (QList<HObjectPtr>* )new QList <HDouble*>;
    if (s.compare("[date")==0) return (QList<HObjectPtr>* )new QList <HDate*>;
    if (s.compare("[string")==0) return (QList<HObjectPtr>* )new QList <HString*>;
    //if (s.compare("list")) return (QList<HObjectPtr>* )new QList <QList*>;


    return ret;
}


/*=================================================================================
===================================================================================
===================================================================================
===================================================================================
                            Individual parser
===================================================================================
===================================================================================*/


/**********************************************************************************
***********************************************************************************
                             Double parser
***********************************************************************************
***********************************************************************************/

/****************************1 byte float******************************************/
inline double  HInputStream::parseDouble1Byte(quint8* b) {
    switch (b[0]) {
        case 0x5B: return 0.0;
            break;
        case 0x5C: return 1.0;
            break;
        default: throw new HInvalidTagException(0x5B, b[0]);
    };

}

/****************************** 2 byte float************************************/
inline double  HInputStream::parseDouble2Byte(quint8* b) {
    quint8 *c = readData(1);
    char d=0;
    d|=*c;
    delete []c;
    return d*1.0;
}

/****************************** 3 byte float************************************/
inline double  HInputStream::parseDouble3Byte(quint8* b) {
    char *c = (char*) readData(2);
    double ret = 256.0*c[0] +(c[1]&0xff);
    delete []c;
    return ret;
}

/****************************** 4 byte float************************************/
inline double  HInputStream::parseDouble4Byte(quint8* c) {
    quint8 *b = readData(4);
    double ret = (b[0]<<BYTE3)|(b[1]<<BYTE2)|(b[2]<<BYTE1)|b[3];
    delete []b;
    return ret /1000.0;
}

/****************************** 8 byte float************************************/
inline double  HInputStream::parseDouble8Byte(quint8* c) {
    double ret;
    quint8 *b = readData(8);
    int i;
    for (i=0; i<4; i++) {
        ret = b[i];
        b[i] = b[7-i];
        b[7-i] = ret;
    }
    memcpy(&ret,b,8);
    delete []b;
    return ret;
}




/********************************************************************************
  *******************************************************************************
                             Long parser
  *******************************************************************************
*********************************************************************************/

/**************************** 1 byte integer*************************************/
inline qint64 HInputStream::parseLong1Byte (quint8* b) {
    return b[0] - 0xE0;
}

/**************************** 2 byte integer*************************************/
inline qint64 HInputStream::parseLong2Byte (quint8* b) {
    quint8 *c = readData(1);
    quint64 ret = ((b[0]-0xF8)<<8) | c[0];
    delete []c;
    return ret;
}

/**************************** 3 byte integer*************************************/
inline qint64 HInputStream::parseLong3Byte (quint8* b) {
    quint8 *c = readData(2);
    quint64 ret = ((b[0] - 0x3C) << 16) | (c[0] << 8) | c[1];
    delete []c;
    return ret;
}

/**************************** 4 byte integer*************************************/
inline qint64 HInputStream::parseLong4Byte (quint8* b) {
    quint8 *c = readData(4);
    quint64 ret = (c[0] << BYTE3) | (c[1] << BYTE2) | (c[2] << BYTE1) | c[3];
    delete []c;
    return ret;
}

/**************************** 8 byte integer*************************************/
inline qint64 HInputStream::parseLong8Byte (quint8* b) {
    quint64 ret;
    quint8 *c = readData(8);

    int i;
    for (i=0; i<4; i++) {
        ret = c[i];
        c[i] = c[7-i];
        c[7-i] = ret;
    }
    memcpy(&ret,c,8);

    delete []c;

    return ret;
}



/********************************************************************************
  *******************************************************************************
                             Integer parser
  *******************************************************************************
*********************************************************************************/

/****************************One byte integer************************************/
inline qint32 HInputStream::parseInt1Byte(quint8* b) {
    return *b- 0x90;
}

/****************************Two byte integer************************************/
inline qint32 HInputStream::parseInt2Byte(quint8* b) {
    qint32 ret=0;
    quint8 *c = readData(1);
    ret = ((b[0] - 0xC8) << 8) | *c;
    delete []c;
    return ret;
}

/****************************Three byte integer************************************/
inline qint32 HInputStream::parseInt3Byte(quint8* b) {
    qint32 ret=0;
    quint8 *c = readData(2);
    ret = ((b[0] - 0xD4) << 16) | (c[0] << 8) | c[1];
    delete []c;
    return ret;
}

/****************************Four byte integer*************************************/
inline qint32 HInputStream::parseInt4Byte(quint8* b) {
    qint32 ret=0;
    quint8 *c = readData(4);
    ret = (c[0] << 24) | (c[1] << 16) | (c[2]<<8) |c[3];
    delete []c;
    return ret;
}

/********************************************************************************
  *******************************************************************************
                             Datetime parser
  *******************************************************************************
*********************************************************************************/

/****************************8Byte           ************************************/
inline QDateTime   HInputStream::parseDateTime8Byte() {
    QDateTime ret;
    ret.setMSecsSinceEpoch(parseLong8Byte(0));
    return ret;
}
/****************************4 byte integer**************************************/
inline QDateTime   HInputStream::parseDateTime4Byte() {
    QDateTime ret;
    ret.setMSecsSinceEpoch(parseLong4Byte(0)*60000);
    return ret;
}

/********************************************************************************
  *******************************************************************************
                             String parser
  *******************************************************************************
*********************************************************************************/

inline QString HInputStream::parseStringInRange(long& size) {
    char b[size+1];
    stream.readRawData(b, size);
    b[size] = '\0';
    return QString(b);

}

inline QString HInputStream::parseStringInRange(int& size) {
    char b[size+1];
    stream.readRawData(b, size);
    b[size] = '\0';
    return QString(b);

}

inline QString HInputStream::parseString(int& tag) {
    QString ret="";
    while (tag == BC_STRING_CHUNK) {
        ret.append(parseStringChunk(tag));

        tag = readOneByte();

    };
    switch (tag) {
    case 'S':
        ret.append(parseStringChunk(tag));
        break;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
        ret.append(parseStringMediumChunk(tag));
    default:
        ret.append(parseStringSmallChunk(tag));
    }
    return ret;
}

inline QString    HInputStream:: parseStringSmallChunk(int& tag) {
    return parseStringInRange(tag);
}


inline QString    HInputStream:: parseStringMediumChunk(int& tag) {
    char b = readOneByte();
    int size = ((tag-BC_STRING_SHORT)<<8)|(b&0xFF);
    return parseStringInRange(size);
}

inline QString    HInputStream:: parseStringChunk(int& tag) {
    char b[2];
    long length;
    stream.readRawData(b, 2);
    length = ((b[0]&0xFF)<<8) | (b[1]&0xFF);
    return parseStringInRange(length);
}

/********************************************************************************
  *******************************************************************************
                             Bool parser
  *******************************************************************************
*********************************************************************************/

inline bool HInputStream::parseBool(quint8* b) {
    switch (*b) {
    case 'T': return true;
    case 'F': return false;
    default: throw new HInvalidDataFormat();
    }
}
/********************************************************************************
  *******************************************************************************
                             Binary parser
  *******************************************************************************
*********************************************************************************/

/****************************0-16 byte parser**************************************/
inline QByteArray  HInputStream::parseBinaryShort(int & b) {
    int length = b-0x20;
    char* buffer = (char*) readData(length);
    QByteArray ret (buffer, length);
    return ret;

}

/****************************General binary parser**************************************/
inline QByteArray  HInputStream::parseBinary(int& tag) {
    QByteArray ret;
    ret.clear();

    // non final chunk
    do {
        ret.append(parseBinaryChunk());
        if (tag == BC_BINARY_CHUNK) tag = readOneByte();
    } while(tag == BC_BINARY_CHUNK);

    // final chunks
    if (tag == BC_BINARY) // up to 16 bit length
        ret.append(parseBinaryChunk());
    else if (tag >= BC_BINARY_SHORT_MIN && tag <= BC_BINARY_SHORT_MAX) // up to 1023 byte
            ret.append(parseBinarySmallChunk(tag));
        else
            ret.append(parseBinaryShort(tag)); // up to 16 byte
    return ret;
}


/****************************16 bit parser**************************************/
QByteArray  HInputStream::parseBinaryChunk() {
    quint8 * lengthA = readData(2);
    int length = ((lengthA[0]<<8) | lengthA[1]);

    char* b = (char*) readData(length);
    QByteArray ret (b, length);

    delete b;
    delete  [] lengthA;

    return ret;
}

/****************************0-1023 byte parser**************************************/
QByteArray  HInputStream::parseBinarySmallChunk(int& tag) {
    quint8 * lengthA = readData(1);
    int length = ((tag-0x34)<<8) | *lengthA;

    char* b = (char*) readData(length);
    QByteArray ret (b, length);

    delete b;
    delete   lengthA;

    return ret;
}
