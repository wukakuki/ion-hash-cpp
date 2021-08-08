/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonClob.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <algorithm>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FILE__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Clob::Clob(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    SIZE length;
    iERR err;
    err = ion_reader_get_lob_size(reader.reader, &length);

    ION_OK(err)

    BYTE *bytes = (BYTE *) calloc(1, length + 1);
    SIZE bytesRead;
    err = ion_reader_read_lob_bytes(reader.reader, bytes, length, &bytesRead);

    ION_OK(err)

    if (length != bytesRead) {
        ION_OK(IERR_EOF);
    }

    value = std::vector<unsigned char>(bytes, bytes + length + 1);

    if (bytes) {
        free(bytes);
    }

    type = Ion::Types::CLOB;
}

void Ion::Clob::getBytes() {
    bytes.clear();
    if (isNull) {
        this->bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeClob(*this);
        this->bytes = writer.getBytes();
    }
}