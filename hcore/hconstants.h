/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
  File      : hconstant.h
  Project   : Qt Hessian
  Author(s) : HTV
  Conttent  : This file defines the constants that were used
  Requirement : Qt4.7+, QtNetwork
  Note        : Constants are dedicated to Hessian 2.0

  Reference: http://hoangtuanonline.com/qthessian
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/

#ifndef HCONSTANTS_H
#define HCONSTANTS_H
namespace hessian {
    static const char BC_CALL    = 'c';
    static const char BC_METHOD  = 'm';
    static const char BC_BINARY   = 'B'; //  chunk
    static const char BC_BINARY_CHUNK = 'A'; // non-final chunk
    static const char BC_BINARY_NON_FINAL = 'b';
    static const char BC_DOUBLE = 'D'; // IEEE 64-bit double
    static const char BC_FALSE = 'F'; // boolean false
    static const char BC_TRUE = 'T';

    static const char BC_INT = 'I'; // 32-bit int
    static const char BC_END = 'z';

    static const char BC_LONG = 'L'; // 64-bit signed integer
    static const char BC_STRING = 'S'; //  string
    static const char BC_STRING_NON_FINAL = 's'; //  string
    static const char BC_STRING_CHUNK ='R';
    static const char BC_MAP = 'M';
    static const char BC_MAP_UNTYPED = 'H';

    static const char BC_NULL = 'N';

    static const char BC_OBJECT = 'O';
    static const char BC_OBJECT_DEF = 'C';
    static const char BC_CLASS_DEF = 'C'; // object/class definition

    static const int BINARY_DIRECT_MIN = 0x20;
    static const int BINARY_DIRECT_MAX = 0x2f;

    static const int BC_BINARY_SHORT_MIN = 0x34; // 2-byte length binary
    static const int BC_BINARY_SHORT_MAX = 0x37; // 2-byte length binary

    static const int BINARY_SHORT_MAX = 0x3ff; // 0-1023 binary

    static const int STRING_CHUNK_MAX = 65535;
    static const int BINARY_CHUNK_MAX = 65535;

    static const int BC_DATE = 0x4a; // 64-bit millisecond UTC date
    static const int BC_DATE_MINUTE = 0x4b; // 32-bit minute UTC date


    static const int BC_DOUBLE_ZERO = 0x5b;
    static const int BC_DOUBLE_ONE = 0x5c;
    static const int BC_DOUBLE_BYTE = 0x5d;
    static const int BC_DOUBLE_SHORT = 0x5e;
    static const int BC_DOUBLE_MILL = 0x5f;


    static const int INT_DIRECT_MIN = -0x10;
    static const int INT_DIRECT_MAX = 0x2f;
    static const int BC_INT_ZERO = 0x90;

    static const int INT_BYTE_MIN = -0x800;
    static const int INT_BYTE_MAX = 0x7ff;
    static const int BC_INT_BYTE_ZERO = 0xc8;



    static const int INT_SHORT_MIN = -0x40000;
    static const int INT_SHORT_MAX = 0x3ffff;
    static const int BC_INT_SHORT_ZERO = 0xd4;

    static const int BC_LIST_VARIABLE =0x55;
    static const int BC_LIST_FIXED = 'V';
    static const int BC_LIST_VARIABLE_UNTYPED = 0x57;
    static const int BC_LIST_FIXED_UNTYPED =0x58;

    static const int BC_LIST_DIRECT = 0x70;
    static const int BC_LIST_DIRECT_UNTYPED = 0x78;
    static const int LIST_DIRECT_MAX = 0x7;

    static const long LONG_DIRECT_MIN = -0x08;
    static const long LONG_DIRECT_MAX =  0x0f;
    static const int  BC_LONG_ZERO = 0xe0;

    static const long LONG_BYTE_MIN = -0x800;
    static const long LONG_BYTE_MAX =  0x7ff;
    static const int  BC_LONG_BYTE_ZERO = 0xf8;

    static const int LONG_SHORT_MIN = -0x40000;
    static const int LONG_SHORT_MAX = 0x3ffff;
    static const int BC_LONG_SHORT_ZERO = 0x3c;

    static const int BC_LONG_INT = 0x59;



    static const int BC_OBJECT_DIRECT = 0x60;
    static const int OBJECT_DIRECT_MAX = 0x0f;

    static const int BC_REF = 0x51;



    static const int BC_STRING_DIRECT = 0x00;
    static const int STRING_DIRECT_MAX = 0x1f;
    static const int BC_STRING_SHORT = 0x30;
    static const int STRING_SHORT_MAX = 0x3ff;



    static const int P_PACKET_CHUNK = 0x4f;
    static const int P_PACKET = 'P';

    static const int P_PACKET_DIRECT = 0x80;
    static const int PACKET_DIRECT_MAX = 0x7f;

    static const int P_PACKET_SHORT = 0x70;
    static const int PACKET_SHORT_MAX = 0xfff;

    static const int BYTE7 = 56;
    static const int BYTE6 = 48;
    static const int BYTE5 = 40;
    static const int BYTE4 = 32;
    static const int BYTE3 = 24;
    static const int BYTE2 = 16;
    static const int BYTE1 = 8;
}
#endif // HCONSTANTS_H
