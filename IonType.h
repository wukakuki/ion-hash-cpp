/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_TYPE_H_
#define ION_HASH_CPP_ION_TYPE_H_

#include "IonHash_EXPORTS.h"
#include "ionc/ion.h"
#include <string>

#define type_null         0
#define type_bool         1
#define type_pos_int      2
#define type_neg_int      3
#define type_float        4
#define type_decimal      5
#define type_timestamp    6
#define type_symbol       7
#define type_string       8
#define type_clob         9
#define type_blob         10
#define type_list         11
#define type_sexp         12
#define type_struct       13

namespace Ion {
    class ION_HASH_EXPORTS Type {
    public:
        ION_TYPE type;
    public:
        int binaryTypeId;
        std::string name;
        bool isScalar;
        bool isLob;
        bool isNumeric;
        bool isContainer;

        Type(ION_TYPE type, int binaryTypeId, std::string name, bool isScalar, bool isLob, bool isNumeric,
             bool isContainer) :
                type(type), binaryTypeId(binaryTypeId), name(name), isScalar(isScalar), isLob(isLob),
                isNumeric(isNumeric),
                isContainer(isContainer) {
        }

        Type(const ION_TYPE &type = tid_none);
    };

    class ION_HASH_EXPORTS Types {
    public:
        static const Type _NULL;
        static const Type BOOL;
        static const Type POS_INT;
        static const Type NEG_INT;
        static const Type FLOAT;
        static const Type DECIMAL;
        static const Type TIMESTAMP;
        static const Type SYMBOL;
        static const Type STRING;
        static const Type CLOB;
        static const Type BLOB;
        static const Type LIST;
        static const Type SEXP;
        static const Type STRUCT;
    };
};

#endif