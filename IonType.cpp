/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonType.h"

#include "ionc/ion.h"
#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FILE__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

const Ion::Type Ion::Types::_NULL = Ion::Type(tid_NULL, type_null, "null", true, false, false, false);
const Ion::Type Ion::Types::BOOL = Ion::Type(tid_BOOL, type_bool, "bool", true, false, false, false);
const Ion::Type Ion::Types::POS_INT = Ion::Type(tid_INT, type_pos_int, "int", true, false, true, false);
const Ion::Type Ion::Types::NEG_INT = Ion::Type(tid_INT, type_neg_int, "int", true, false, true, false);
const Ion::Type Ion::Types::FLOAT = Ion::Type(tid_FLOAT, type_float, "float", true, false, true, false);
const Ion::Type Ion::Types::DECIMAL = Ion::Type(tid_DECIMAL, type_decimal, "decimal", true, false, false, false);
const Ion::Type Ion::Types::TIMESTAMP = Ion::Type(tid_TIMESTAMP, type_timestamp, "timestamp", true, false, false, false);
const Ion::Type Ion::Types::SYMBOL = Ion::Type(tid_SYMBOL, type_symbol, "symbol", true, false, false, false);
const Ion::Type Ion::Types::STRING = Ion::Type(tid_STRING, type_string, "string", true, false, false, false);
const Ion::Type Ion::Types::CLOB = Ion::Type(tid_CLOB, type_clob, "clob", true, true, false, false);
const Ion::Type Ion::Types::BLOB = Ion::Type(tid_BLOB, type_blob, "blob", true, true, false, false);
const Ion::Type Ion::Types::LIST = Ion::Type(tid_LIST, type_list, "list", false, false, false, true);
const Ion::Type Ion::Types::SEXP = Ion::Type(tid_SEXP, type_sexp, "sexp", false, false, false, true);
const Ion::Type Ion::Types::STRUCT = Ion::Type(tid_STRUCT, type_struct, "struct", false, false, false, true);

Ion::Type::Type(const ION_TYPE &type) {
    if (type == tid_none) {
        this->type = tid_none;
    } else if (type == tid_EOF) {
        this->type = tid_EOF;
    } else if (type == tid_NULL) {
        *this = Types::_NULL;
    } else if (type == tid_BOOL) {
        *this = Types::BOOL;
    } else if (type == tid_INT) {
        *this = Types::POS_INT;
    } else if (type == tid_FLOAT) {
        *this = Types::FLOAT;
    } else if (type == tid_DECIMAL) {
        *this = Types::DECIMAL;
    } else if (type == tid_TIMESTAMP) {
        *this = Types::TIMESTAMP;
    } else if (type == tid_SYMBOL) {
        *this = Types::SYMBOL;
    } else if (type == tid_STRING) {
        *this = Types::STRING;
    } else if (type == tid_CLOB) {
        *this = Types::CLOB;
    } else if (type == tid_BLOB) {
        *this = Types::BLOB;
    } else if (type == tid_LIST) {
        *this = Types::LIST;
    } else if (type == tid_SEXP) {
        *this = Types::SEXP;
    } else if (type == tid_STRUCT) {
        *this = Types::STRUCT;
    }
}