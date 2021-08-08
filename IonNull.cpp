/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonNull.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <algorithm>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FILE__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Null::Null(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    type = Ion::Types::_NULL;
    isNull = true;
}

void Ion::Null::getBytes() {
    bytes.clear();
    if (isNull) {
        bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeNull(type);
        bytes = writer.getBytes();
    }

}