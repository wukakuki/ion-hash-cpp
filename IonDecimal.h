/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_DECIMAL_H_
#define ION_HASH_CPP_ION_DECIMAL_H_

#include "IonHash_EXPORTS.h"
#include <string>
#include "ionc/ion.h"

#include "IonInt.h"
#include "IonScalarValue.h"
#include "IonReader.h"

#define ION_DECIMAL_MAX_DIGITS 10000

namespace Ion {
    static decContext g_IonDecimalContext = {
            ION_DECIMAL_MAX_DIGITS,         // max digits
            DEC_MAX_MATH,                   // max exponent
            -DEC_MAX_MATH,                  // min exponent
            DEC_ROUND_HALF_EVEN,            // rounding mode
            DEC_Errors,                     // trap conditions
            0,                              // status flags
            0                               // apply exponent clamp?
    };

    class ION_HASH_EXPORTS Decimal : public Ion::ScalarValue {
    public:
        ION_DECIMAL value;
    public:
        Decimal();

        ~Decimal();

        explicit Decimal(ION_DECIMAL &value);

        explicit Decimal(Ion::Reader &reader);

        void getBytes() override;

        explicit Decimal(const std::string &str);

        explicit Decimal(uint32_t num);

        explicit Decimal(int32_t num);

        explicit Decimal(decQuad *quad);

        explicit Decimal(decNumber *number);

        explicit Decimal(Ion::Int iint);

        char *toString();

        Ion::Int toIonInt();

        int32_t toInt32();

        uint32_t toUint32();

        Ion::Decimal fma(const Ion::Decimal &rhs, const Ion::Decimal &fhs);

        Ion::Decimal add(const Ion::Decimal &rhs);

        Ion::Decimal _and(const Ion::Decimal &rhs);

        Ion::Decimal divide(const Ion::Decimal &rhs);

        Ion::Decimal divideInteger(const Ion::Decimal &rhs);

        Ion::Decimal max(const Ion::Decimal &rhs);

        Ion::Decimal maxMag(const Ion::Decimal &rhs);

        Ion::Decimal min(const Ion::Decimal &rhs);

        Ion::Decimal minMag(const Ion::Decimal &rhs);

        Ion::Decimal multiply(const Ion::Decimal &rhs);

        Ion::Decimal _or(const Ion::Decimal &rhs);

        Ion::Decimal quantize(const Ion::Decimal &rhs);

        Ion::Decimal remainder(const Ion::Decimal &rhs);

        Ion::Decimal remainderNear(const Ion::Decimal &rhs);

        Ion::Decimal rotate(const Ion::Decimal &rhs);

        Ion::Decimal scaleb(const Ion::Decimal &rhs);

        Ion::Decimal shift(const Ion::Decimal &rhs);

        Ion::Decimal subtract(const Ion::Decimal &rhs);

        Ion::Decimal _xor(const Ion::Decimal &rhs);

        Ion::Decimal abs();

        Ion::Decimal invert();

        Ion::Decimal logb();

        Ion::Decimal minus();

        Ion::Decimal plus();

        Ion::Decimal reduce();

        Ion::Decimal toIntegralExact();

        Ion::Decimal toIntegralValue();

        uint32_t digits();

        int32_t getExponent();

        uint32_t radix();

        uint32_t sameQuantum(const Ion::Decimal &rhs);

        uint32_t isInteger();

        uint32_t isSubnormal();

        uint32_t isNormal();

        uint32_t isFinite();

        uint32_t isInfinite();

        uint32_t isNan();

        uint32_t isNegative();

        uint32_t isZero();

        uint32_t isCanonical();

        int32_t compare(const Ion::Decimal &rhs);

        int equals(const Ion::Decimal &rhs);

        void canonical(const Ion::Decimal &rhs);

        void copy(const Ion::Decimal &rhs);

        void copyAbs(const Ion::Decimal &rhs);

        void copyNegate(const Ion::Decimal &rhs);

        void copySign(const Ion::Decimal &rhs, const Ion::Decimal &lhs);
    };
}

#endif