/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonFloat.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Float::Float() {
    type = Ion::Types::FLOAT;
}

Ion::Float::~Float() {
}

Ion::Float::Float(double &value) : value(value) {
    type = Ion::Types::FLOAT;
}

Ion::Float::Float(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    iERR err = ion_reader_read_double(reader.reader, &value);

    ION_OK(err)

    type = Ion::Types::FLOAT;
}

void Ion::Float::getBytes() {
    bytes.clear();
    if (isNull) {
        this->bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeFloat(*this);
        this->bytes = writer.getBytes();
    }
}

int Ion::Float::isNegativeZero() {
    return ion_float_is_negative_zero(this->value);
}
