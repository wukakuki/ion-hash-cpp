/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonBool.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <algorithm>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Bool::Bool(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    iERR err = ion_reader_read_bool(reader.reader, &value);

    ION_OK(err)

    type = Ion::Types::BOOL;
}

void Ion::Bool::getBytes() {
    bytes.clear();
    if (isNull) {
        bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeBoolean(*this);
        bytes = writer.getBytes();
    }
}

Ion::Bool::Bool(bool value) {
    this->value = value;
}
