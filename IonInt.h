/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_INT_H_
#define ION_HASH_CPP_ION_INT_H_

#include "IonHash_EXPORTS.h"
#include <string>
#include "ionc/ion.h"
#include "IonString.h"
#include "IonScalarValue.h"
#include "IonReader.h"
#include "IonReader.h"

namespace Ion {
    class ION_HASH_EXPORTS Int : public Ion::ScalarValue {
    public:
        ION_INT *value;
    public:
        Int();

        ~Int();

        explicit Int(ION_INT *value);

        explicit Int(Ion::Reader &reader);

        void getBytes() override;

        Int(const Ion::String &str, bool isHex, bool isBinary);

        Int(const char *p_chars, SIZE char_limit, bool isHex, bool isBinary);

        Int(BYTE *buf, SIZE limit, bool isAbs, bool isNegative);

        explicit Int(int64_t value);

        bool _isNull() const;

        bool isZero() const;

        int compare(Ion::Int other) const;

        int32_t signum() const;

        SIZE highestBitSet() const;

        SIZE charLength() const;

        BYTE *toChar(SIZE &p_written) const;

        Ion::String toString() const;

        SIZE byteLength(bool toAbs) const;

        BYTE *toBytes(SIZE startingIntByteOffset, SIZE &p_written, bool toAbs) const;

        int64_t toInt64() const;

        int32_t toInt32() const;
    };
}

#endif