/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonString.h"
#include "IonWriter.h"

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::String::String() {
    ion_string_init(&value);

    type = Ion::Types::STRING;
}

Ion::String::String(ION_STRING &str) : value(str) {
    type = Ion::Types::STRING;
}

Ion::String::String(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    iERR err = ion_reader_read_string(reader.reader, &value);

    ION_OK(err)

    type = Ion::Types::STRING;
}

void Ion::String::getBytes() {
    bytes.clear();
    if (isNull) {
        this->bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeString(*this);
        this->bytes = writer.getBytes();
    }
}

Ion::String::String(std::string &str) {
    ion_string_assign_cstr(&value, (char *)str.c_str(), str.length());

    type = Ion::Types::STRING;
}

Ion::String::String(char *str, SIZE len) {
    ion_string_assign_cstr(&value, str, len);

    type = Ion::Types::STRING;
}

char *Ion::String::strdup() {
    return ion_string_strdup(&value);
}

int Ion::String::getLength() {
    return ion_string_get_length(&value);
}

BYTE Ion::String::getByte(int idx) {
    return ion_string_get_byte(&value, idx);
}

BYTE *Ion::String::_getBytes() {
    return ion_string_get_bytes(&value);
}

bool Ion::String::_isNull() {
    return ion_string_is_null(&value);
}

bool Ion::String::isEqual(Ion::String other) {
    return ion_string_is_equal(&value, &other.value);
}
