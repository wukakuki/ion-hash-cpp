/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonWriter.h"
#include "IonDecimal.h"

#include "ionc/ion.h"
#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Writer::Writer(bool isBinary) {
    isClosed = false;
    iERR err = ion_stream_open_memory_only(&ion_stream);

    ION_OK(err)

    ION_WRITER_OPTIONS options;
    memset(&options, 0, sizeof(ION_WRITER_OPTIONS));
    options.decimal_context = &Ion::g_IonDecimalContext;
    options.max_container_depth = ION_CONTAINER_DEPTH_MAX;
    options.max_annotation_count = ION_ANNOTATION_MAX;

    options.output_as_binary = isBinary;

    err = ion_writer_open(&writer, ion_stream, &options);

    ION_OK(err)
}

Ion::Writer::~Writer() {
    if (!isClosed) {
        isClosed = true;

        iERR err;
        err = ion_writer_close(writer);

        ION_OK(err)

        err = ion_stream_close(ion_stream);

        ION_OK(err)
    }
}

Ion::Writer::Writer(hWRITER writer) : writer(writer) {
    isClosed = false;
}

std::vector<unsigned char> Ion::Writer::getBytes() {
    if (isClosed) {
        return {};
    }
    isClosed = true;

    iERR err = ion_writer_close(writer);

    ION_OK(err)

    POSITION pos;
    pos = ion_stream_get_position(ion_stream);

    err = ion_stream_seek(ion_stream, 0);

    ION_OK(err)

    SIZE len;
    BYTE *out = (BYTE *)(malloc((size_t)pos));
    err = ion_stream_read(ion_stream, out, (SIZE)pos, &len);

    ION_OK(err)

    err = ion_stream_close(ion_stream);

    ION_OK(err)

    if (len != (SIZE)pos) {
        ION_OK(IERR_EOF);
    }

    return std::vector<unsigned char>(out, out + len);
}

void Ion::Writer::writeAllValues(Ion::Reader &reader) {
    iERR err = ion_writer_write_all_values(writer, reader.reader);

    ION_OK(err)
}

void Ion::Writer::writeNull(Ion::Type &type) {
    iERR err = ion_writer_write_typed_null(writer, type.type);

    ION_OK(err)
}

void Ion::Writer::writeBoolean(Ion::Bool &value) {
    iERR err = ion_writer_write_bool(writer, value.value);

    ION_OK(err)
}

void Ion::Writer::writeInt(Ion::Int &value) {
    iERR err = ion_writer_write_ion_int(writer, value.value);

    ION_OK(err)
}

void Ion::Writer::writeFloat(Ion::Float &value) {
    iERR err = ion_writer_write_double(writer, value.value);

    ION_OK(err)
}

void Ion::Writer::writeDecimal(Ion::Decimal &value) {
    iERR err = ion_writer_write_ion_decimal(writer, &value.value);

    ION_OK(err)
}

void Ion::Writer::writeTimestamp(Ion::Timestamp &value) {
    iERR err = ion_writer_write_timestamp(writer, &value.timestamp);

    ION_OK(err)
}

void Ion::Writer::writeClob(Ion::Clob &value) {
    iERR err = ion_writer_write_clob(writer, (BYTE *)value.value.c_str(), (SIZE)value.value.size());

    ION_OK(err)
}

void Ion::Writer::writeBlob(Ion::Blob &value) {
    iERR err = ion_writer_write_blob(writer, (BYTE *)value.value.data(), (SIZE)value.value.size());

    ION_OK(err)
}

void Ion::Writer::writeString(Ion::String &value) {
    iERR err = ion_writer_write_string(writer, &value.value);

    ION_OK(err)
}

void Ion::Writer::stepIn(Ion::Type &type) {
    iERR err = ion_writer_start_container(writer, type.type);

    ION_OK(err)
}

void Ion::Writer::stepOut() {
    iERR err = ion_writer_finish_container(writer);

    ION_OK(err)
}

void Ion::Writer::writeFieldName(Ion::String &fieldName) {
    iERR err = ion_writer_write_field_name(writer, &fieldName.value);

    ION_OK(err)
}

void Ion::Writer::writeFieldName(SID sid) {
    ION_SYMBOL symbol;
    memset(&symbol, 0, sizeof(ION_SYMBOL));
    symbol.sid = sid;
    iERR err = ion_writer_write_field_name_symbol(writer, &symbol);

    ION_OK(err)
}

void Ion::Writer::writeSymbol(Ion::String &value) {
    iERR err = ion_writer_write_symbol(writer, &value.value);

    ION_OK(err)
}

void Ion::Writer::writeSymbol(SID sid) {
    ION_SYMBOL symbol;
    memset(&symbol, 0, sizeof(ION_SYMBOL));
    symbol.sid = sid;
    iERR err = ion_writer_write_ion_symbol(writer, &symbol);

    ION_OK(err)
}

void Ion::Writer::addAnnotation(Ion::String &annotation) {
    iERR err = ion_writer_add_annotation(writer, &annotation.value);

    ION_OK(err)
}

void Ion::Writer::addAnnotation(SID sid) {
    ION_SYMBOL symbol;
    memset(&symbol, 0, sizeof(ION_SYMBOL));
    symbol.sid = sid;
    iERR err = ion_writer_add_annotation_symbol(writer, &symbol);

    ION_OK(err)
}
