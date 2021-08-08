/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonReader.h"
#include "IonDecimal.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FILE__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Reader::Reader(const char *ion_text) {
    ION_READER_OPTIONS options;
    memset(&options, 0, sizeof(ION_READER_OPTIONS));
    options.decimal_context = &Ion::g_IonDecimalContext;
    options.max_container_depth = ION_CONTAINER_DEPTH_MAX;
    options.max_annotation_count = ION_ANNOTATION_MAX;

    iERR err = ion_reader_open_buffer(&reader, (BYTE *) ion_text, (SIZE) strlen(ion_text), &options);

    ION_OK(err)
}

Ion::Reader::Reader(const std::vector<unsigned char> &ion_binary) {
    ION_READER_OPTIONS options;
    memset(&options, 0, sizeof(ION_READER_OPTIONS));
    options.decimal_context = &Ion::g_IonDecimalContext;
    options.max_container_depth = ION_CONTAINER_DEPTH_MAX;
    options.max_annotation_count = ION_ANNOTATION_MAX;

    iERR err = ion_reader_open_buffer(&reader, (BYTE *) ion_binary.data(), (SIZE) ion_binary.size(), &options);

    ION_OK(err)
}

Ion::Reader::~Reader() {
    iERR err = ion_reader_close(reader);

    ION_OK(err)
}

Ion::Reader::Reader(hREADER reader) : reader(reader) {
}

Ion::Type Ion::Reader::next() {
    ION_TYPE valueType;
    iERR err = ion_reader_next(reader, &valueType);

    ION_OK(err)

    currentType = Ion::Type(valueType);

    return currentType;
}

void Ion::Reader::stepIn() const {
    iERR err = ion_reader_step_in(reader);

    ION_OK(err)
}

void Ion::Reader::stepOut() const {
    iERR err = ion_reader_step_out(reader);

    ION_OK(err)
}
