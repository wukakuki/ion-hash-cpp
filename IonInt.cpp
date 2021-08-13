/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonInt.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Int::Int() {
    iERR err = ion_int_alloc(nullptr, &value);

    ION_OK(err)

    type = Ion::Types::POS_INT;
}

Ion::Int::~Int() {
    ion_int_free(value);
}

Ion::Int::Int(ION_INT *value) {
    iERR err;
    err = ion_int_copy(this->value, value, nullptr);

    ION_OK(err)

    int32_t signum;
    err = ion_int_signum(value, &signum);

    ION_OK(err)

    if (signum >= 0) {
        type = Ion::Types::POS_INT;
    } else {
        type = Ion::Types::NEG_INT;
    }
}

Ion::Int::Int(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    iERR err;
    err = ion_int_alloc(nullptr, &value);

    ION_OK(err)

    err = ion_reader_read_ion_int(reader.reader, value);

    ION_OK(err)

    int32_t signum;
    err = ion_int_signum(value, &signum);

    ION_OK(err)

    if (signum >= 0) {
        type = Ion::Types::POS_INT;
    } else {
        type = Ion::Types::NEG_INT;
    }
}

void Ion::Int::getBytes() {
    bytes.clear();
    if (isNull) {
        this->bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeInt(*this);
        this->bytes = writer.getBytes();
    }
}

Ion::Int::Int(const Ion::String &str, const bool isHex, const bool isBinary) {
    iERR err;

    err = ion_int_alloc(nullptr, &value);

    ION_OK(err)

    if (isHex) {
        ION_STRING strValue = str.value;

        err = ion_int_from_hex_string(value, &strValue);
    } else if (isBinary) {
        ION_STRING strValue = str.value;

        err = ion_int_from_binary_string(value, &strValue);
    } else {
        ION_STRING strValue = str.value;

        err = ion_int_from_string(value, &strValue);
    }

    ION_OK(err)

    int32_t signum;
    err = ion_int_signum(value, &signum);

    ION_OK(err)

    if (signum >= 0) {
        type = Ion::Types::POS_INT;
    } else {
        type = Ion::Types::NEG_INT;
    }
}

Ion::Int::Int(const char *p_chars, SIZE char_limit, const bool isHex, const bool isBinary) {
    iERR err;

    err = ion_int_alloc(nullptr, &value);

    ION_OK(err)

    if (isHex) {
        err = ion_int_from_hex_chars(value, p_chars, char_limit);
    } else if (isBinary) {
        err = ion_int_from_binary_chars(value, p_chars, char_limit);
    } else {
        err = ion_int_from_chars(value, p_chars, char_limit);
    }

    ION_OK(err)

    int32_t signum;
    err = ion_int_signum(value, &signum);

    ION_OK(err)

    if (signum >= 0) {
        type = Ion::Types::POS_INT;
    } else {
        type = Ion::Types::NEG_INT;
    }
}

Ion::Int::Int(BYTE *buf, SIZE limit, const bool isAbs, bool isNegative) {
    iERR err;

    err = ion_int_alloc(nullptr, &value);

    ION_OK(err)

    if (isAbs) {
        err = ion_int_from_abs_bytes(value, buf, limit, isNegative);
    } else {
        err = ion_int_from_bytes(value, buf, limit);
    }

    ION_OK(err)

    int32_t signum;
    err = ion_int_signum(value, &signum);

    ION_OK(err)

    if (signum >= 0) {
        type = Ion::Types::POS_INT;
    } else {
        type = Ion::Types::NEG_INT;
    }
}

Ion::Int::Int(const Ion::Int &other) {
    iERR err = ion_int_copy(value, other.value, nullptr);

    ION_OK(err)
}

Ion::Int::Int(int64_t value) {
    iERR err;

    err = ion_int_alloc(nullptr, &this->value);

    ION_OK(err)

    err = ion_int_from_long(this->value, value);

    ION_OK(err)

    int32_t signum;
    err = ion_int_signum(this->value, &signum);

    ION_OK(err)

    if (signum >= 0) {
        type = Ion::Types::POS_INT;
    } else {
        type = Ion::Types::NEG_INT;
    }
}

bool Ion::Int::_isNull() const {
    int isNull;
    iERR err = ion_int_is_null(value, &isNull);

    ION_OK(err)

    if (err) {
        return false;
    }

    return (bool)isNull;
}

bool Ion::Int::isZero() const {
    int isZero;
    iERR err = ion_int_is_zero(value, &isZero);

    ION_OK(err)

    if (err) {
        return false;
    }

    return (bool)isZero;
}

int Ion::Int::compare(Ion::Int other) const {
    int result;
    iERR err = ion_int_compare(value, other.value, &result);

    ION_OK(err)

    if (err) {
        return 0;
    }

    return result;
}

int32_t Ion::Int::signum() const {
    int signum;
    iERR err = ion_int_signum(value, &signum);

    ION_OK(err)

    if (err) {
        return 0;
    }

    return signum;
}

SIZE Ion::Int::highestBitSet() const {
    SIZE pos;
    iERR err = ion_int_highest_bit_set(value, &pos);

    ION_OK(err)

    if (err) {
        return 0;
    }

    return pos;
}

SIZE Ion::Int::charLength() const {
    SIZE len;
    iERR err = ion_int_char_length(value, &len);

    ION_OK(err)

    if (err) {
        return 0;
    }

    return len;
}

BYTE *Ion::Int::toChar(SIZE &p_written) const {
    SIZE len = this->charLength();

    BYTE *p_str = (BYTE *)malloc(len);
    iERR err = ion_int_to_char(value, p_str, len, &p_written);

    ION_OK(err)

    if (err) {
        return nullptr;
    }

    if (p_written != len) {
        ION_OK(IERR_EOF);
    }

    return p_str;
}

Ion::String Ion::Int::toString() const {
    Ion::String str;
    iERR err = ion_int_to_string(value, nullptr, &str.value);

    ION_OK(err)

    if (err) {
        return {};
    }

    return str;
}

SIZE Ion::Int::byteLength(bool toAbs) const {
    SIZE len;
    iERR err;
    if (toAbs) {
        err = ion_int_abs_bytes_length(value, &len);
    } else {
        err = ion_int_byte_length(value, &len);
    }

    ION_OK(err)

    if (err) {
        return 0;
    }

    return len;
}

BYTE *Ion::Int::toBytes(SIZE startingIntByteOffset, SIZE &p_written, bool toAbs) const {
    SIZE len = this->byteLength(toAbs);

    BYTE *p_str = (BYTE *)malloc(len);
    iERR err;
    if (toAbs) {
        err = ion_int_to_abs_bytes(value, startingIntByteOffset, p_str, len, &p_written);
    } else {
        err = ion_int_to_bytes(value, startingIntByteOffset, p_str, len, &p_written);
    }

    ION_OK(err)

    if (err) {
        return nullptr;
    }

    if (p_written != len - startingIntByteOffset) {
        ION_OK(IERR_EOF);
    }

    return p_str;
}

int64_t Ion::Int::toInt64() const {
    int64_t int64;
    iERR err = ion_int_to_int64(value, &int64);

    ION_OK(err)

    if (err) {
        return 0;
    }

    return int64;
}

int32_t Ion::Int::toInt32() const {
    int32_t int32;
    iERR err = ion_int_to_int32(value, &int32);

    ION_OK(err)

    if (err) {
        return 0;
    }

    return int32;
}
