/***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
  File      : hobject.h
  Project   : Qt Hessian
  Author(s) : HTV
  Conttent  : The network manager represents the service endpoint
  Requirement : Qt4.7+, QtNetwork

  Reference: http://hoangtuanonline.com/qthessian
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/

#ifndef HOBJECT_H
#define HOBJECT_H

#include <QObject>
#include <QDateTime>
#include <QMap>

#include "hexception.h"

enum ClassType {
    THObject = 0,
    TNull  ,
    TInteger,
    TLong,
    TBool,
    TDate,
    TDateTime,
    TDouble,
    TBinary,
    TString,
    TList,
    TMap,
    TXml,
    TInteger32,
    TTerminator,
    TCall

};

static QString _nameArray[] = {
    "Object",
    "Null",
    "Integer",
    "Long",
    "Bool",
    "Date",
    "DateTime",
    "Double",
    "Binary",
    "String",
    "List",
    "Map",
    "Xml",
    "Integer32",
    "Terminator",
    "Call"
};

namespace hessian {
    static const int MAX_INT32 = 500000000;

    class HObject : public QObject
    {
        Q_OBJECT

    public:
        //HObject(QObject *parent = 0): objectType(THObject), QObject(parent) {}
        HObject (ClassType type, QObject *parent = 0) : QObject(parent), objectType(type) {}

        QString className () const {   return _nameArray[objectType];
        }

        //virtual void getValue (HObject&);
        ClassType getClassType() {return objectType; }

    private:
        ClassType objectType;

    }; // end class HObject
    typedef HObject* HObjectPtr;


    // Box class Integer
    class HInteger : public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef int HType;

        // constructor
        HInteger (QObject *parent =0) : HObject(TInteger, parent) {}

        HInteger (HType value, QObject *parent =0): HObject(TInteger, parent), _value(value)  {}

        // set value
        void setValue (const HType &v) { if (v>MAX_INT32) throw new HValueOutOfRangeException(); _value = v; }
        void setValue (const HInteger &v) { setValue( v.value()); }

        // get value
        HType value () const { return _value; }
        operator HType() const { return _value; }

        HInteger& operator= (HInteger &a) { this->setValue( a.value()); return *this; }
        HInteger& operator= (int &a) { this->setValue( a); return *this; }


    private:
        HType _value;
    }; // end class HInteger



    // Box class Integer32
    class HInteger32 : public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef qint32 HType;

        // constructor
        HInteger32 (QObject *parent =0) : HObject(TInteger32, parent) {}

        HInteger32 (HType value, QObject *parent =0): HObject(TInteger32, parent), _value(value)  {}

        // set value
        void setValue (const HType &v) {  _value = v; }
        void setValue (const HInteger &v) { setValue( v.value()); }

        // get value
        HType value () const { return _value; }
        operator HType() const { return _value; }

        HInteger32& operator= (HInteger32 &a) { this->setValue( a.value()); return *this; }
        HInteger32& operator= (HType &a) { this->setValue( a); return *this; }
    private:
        HType _value;
    }; // end class HInteger

    // Box class Null
    class HNull : public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef void* HType;

        // constructor
        HNull (QObject *parent =0) : HObject(TNull, parent), _value(NULL) {}    

        HType value () const { return _value; }
        operator HType() const { return _value; }

    private:
        HType _value;
    }; // end class HNull


    // Box class int64 (long int)
    class HLong: public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef qint64 HType;

        // constructor
        HLong(QObject *parent =0) : HObject(TLong, parent) {}

        HLong (HType value, QObject *parent =0): HObject(TLong, parent), _value(value)  {}

        HType value () const { return _value; }
        operator HType() const { return _value; }

        // set value
        void setValue (const HType &v) { _value = v; }
        //void setValue (const HType &v) { setValue( v.value()); }

    private:
        HType _value;
    }; // end class HLong


    // Box class boolean (long int)
    class HBool: public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef bool HType;

        // constructor
        HBool(QObject *parent =0) : HObject(TBool, parent) {}

        HBool (HType value, QObject *parent =0): HObject(TBool, parent), _value(value)  {}

        HType value () const { return _value; }
        operator HType() const { return _value; }

        // set value
        void setValue (const HType &v) { _value = v; }

    private:
        HType _value;
    }; // end class HBool


    // Box class DateTime
    class HDateTime: public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef QDateTime HType;
#define  TType TDateTime
        // constructor
        HDateTime(QObject *parent =0) : HObject(TDateTime, parent) {}

        HDateTime (HType value, QObject *parent =0): HObject(TDateTime, parent), _value(value)  {}

        HType value () const { return _value; }
        operator HType() const { return _value; }


        // set value
        void setValue (const HType &v) { _value = v; }

    private:
        HType _value;

#undef TType
    }; // end class HDateTime


    // Box class Date
    class HDate: public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef QDate HType;
#define  TType TDate
        // constructor
        HDate(QObject *parent =0) : HObject(TType, parent) {}

        HDate (HType value, QObject *parent =0): HObject(TType, parent), _value(value)  {}

        HType value () const { return _value; }
        operator HType() const { return _value; }




        //void setValue (const HType &v) { setValue( v.value()); }
    private:
        HType _value;
#undef TType
    }; // end class HDate


    // Box class Double
    class HDouble: public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef double HType;
#define  TType TDouble
        // constructor
        HDouble(QObject *parent =0) : HObject(TType, parent) {}

        HDouble (HType value, QObject *parent =0): HObject(TType, parent), _value(value)  {}

        HType value () const { return _value; }
        operator HType() const { return _value; }

        // set value
        void setValue (const HType &v) { _value = v; }
    private:
        HType _value;
#undef TType
    }; // end class HDouble


    // Box class Binary
    class HBinary: public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef QByteArray HType;
    #define  TType TBinary
        // constructor
        HBinary(QObject *parent =0) : HObject(TType, parent) {}

        HBinary (HType value, QObject *parent =0): HObject(TType, parent), _value(value)  {}

        HType value () const { return _value; }
        operator const char*() { return _value.data(); }
    private:
        HType _value;
#undef TType
    }; // end class HBinary


    // Box class String
    class HString: public HObject {
        Q_OBJECT
    public:
        // type of the object
        typedef QString HType;
#define  TType TString
        // constructor
        HString(QObject *parent =0) : HObject(TType, parent) {}

        HString (HType value, QObject *parent =0): HObject(TType, parent), _value(value)  {}

        HType value () const { return _value; }
        operator HType() const { return _value; }
        bool operator<(const HString& other) const {
            return _value < other._value;
        }

        // set value
        void setValue (const HType &v) { _value = v; }

    protected:
        HType _value;
#undef TType
    }; // end class HString







}


#endif // HOBJECT_H
