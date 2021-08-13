/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonDecimal.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Decimal::Decimal() {
    iERR err = ion_decimal_claim(&value);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

Ion::Decimal::~Decimal() {
    iERR err = ion_decimal_free(&value);

    ION_OK(err)
}

Ion::Decimal::Decimal(ION_DECIMAL &value) : value(value) {
    type = Ion::Types::DECIMAL;
}

Ion::Decimal::Decimal(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    iERR err = ion_reader_read_ion_decimal(reader.reader, &value);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

void Ion::Decimal::getBytes() {
    bytes.clear();
    if (isNull) {
        this->bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeDecimal(*this);
        this->bytes = writer.getBytes();
    }
}

Ion::Decimal::Decimal(const std::string &str) {
    iERR err = ion_decimal_from_string(&this->value, str.c_str(), &Ion::g_IonDecimalContext);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

Ion::Decimal::Decimal(uint32_t num) {
    iERR err = ion_decimal_from_uint32(&this->value, num);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

Ion::Decimal::Decimal(int32_t num) {
    iERR err = ion_decimal_from_int32(&this->value, num);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

Ion::Decimal::Decimal(decQuad *quad) {
    iERR err = ion_decimal_from_quad(&this->value, quad);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

Ion::Decimal::Decimal(decNumber *number) {
    iERR err = ion_decimal_from_number(&this->value, number);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

Ion::Decimal::Decimal(Ion::Int iint) {
    iERR err = ion_decimal_from_ion_int(&this->value, &Ion::g_IonDecimalContext, iint.value);

    ION_OK(err)

    type = Ion::Types::DECIMAL;
}

char *Ion::Decimal::toString() {
    char *str = (char *) malloc(ION_DECIMAL_STRLEN(&this->value));
    iERR err = ion_decimal_to_string(&this->value, str);

    ION_OK(err)

    if (err) {
        if (str) {
            free(str);
        }

        return nullptr;
    }

    return str;
}

Ion::Int Ion::Decimal::toIonInt() {
    Ion::Int result;
    iERR err = ion_decimal_to_ion_int(&this->value, &Ion::g_IonDecimalContext, result.value);

    ION_OK(err)

    return result;
}

int32_t Ion::Decimal::toInt32() {
    int32_t result;
    iERR err = ion_decimal_to_int32(&this->value, &Ion::g_IonDecimalContext, &result);

    ION_OK(err)

    return result;
}

uint32_t Ion::Decimal::toUint32() {
    uint32_t result;
    iERR err = ion_decimal_to_uint32(&this->value, &Ion::g_IonDecimalContext, &result);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::fma(const Ion::Decimal &rhs, const Ion::Decimal &fhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_fma(&result.value, &this->value, &rhs.value, &fhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::add(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_add(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::_and(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_and(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::divide(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_divide(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::divideInteger(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_divide_integer(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::max(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_max(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::maxMag(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_max_mag(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::min(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_min(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::minMag(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_min_mag(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::multiply(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_multiply(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::_or(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_or(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::quantize(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_quantize(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::remainder(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_remainder(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::remainderNear(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_remainder_near(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::rotate(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_rotate(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::scaleb(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_scaleb(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::shift(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_shift(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::subtract(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_subtract(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::_xor(const Ion::Decimal &rhs) {
    Ion::Decimal result;
    iERR err = ion_decimal_xor(&result.value, &this->value, &rhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::abs() {
    Ion::Decimal result;
    iERR err = ion_decimal_abs(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::invert() {
    Ion::Decimal result;
    iERR err = ion_decimal_invert(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::logb() {
    Ion::Decimal result;
    iERR err = ion_decimal_logb(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::minus() {
    Ion::Decimal result;
    iERR err = ion_decimal_minus(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::plus() {
    Ion::Decimal result;
    iERR err = ion_decimal_plus(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::reduce() {
    Ion::Decimal result;
    iERR err = ion_decimal_reduce(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::toIntegralExact() {
    Ion::Decimal result;
    iERR err = ion_decimal_to_integral_exact(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

Ion::Decimal Ion::Decimal::toIntegralValue() {
    Ion::Decimal result;
    iERR err = ion_decimal_to_integral_value(&result.value, &this->value, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

uint32_t Ion::Decimal::digits() {
    return ion_decimal_digits(&this->value);
}

int32_t Ion::Decimal::getExponent() {
    return ion_decimal_get_exponent(&this->value);
}

uint32_t Ion::Decimal::radix() {
    return ion_decimal_radix(&this->value);
}

uint32_t Ion::Decimal::sameQuantum(const Ion::Decimal &rhs) {
    return ion_decimal_same_quantum(&this->value, &rhs.value);
}

uint32_t Ion::Decimal::isInteger() {
    return ion_decimal_is_integer(&this->value);
}

uint32_t Ion::Decimal::isSubnormal() {
    return ion_decimal_is_subnormal(&this->value, &Ion::g_IonDecimalContext);
}

uint32_t Ion::Decimal::isNormal() {
    return ion_decimal_is_normal(&this->value, &Ion::g_IonDecimalContext);
}

uint32_t Ion::Decimal::isFinite() {
    return ion_decimal_is_finite(&this->value);
}

uint32_t Ion::Decimal::isInfinite() {
    return ion_decimal_is_infinite(&this->value);
}

uint32_t Ion::Decimal::isNan() {
    return ion_decimal_is_nan(&this->value);
}

uint32_t Ion::Decimal::isNegative() {
    return ion_decimal_is_negative(&this->value);
}

uint32_t Ion::Decimal::isZero() {
    return ion_decimal_is_zero(&this->value);
}

uint32_t Ion::Decimal::isCanonical() {
    return ion_decimal_is_canonical(&this->value);
}

int32_t Ion::Decimal::compare(const Ion::Decimal &rhs) {
    int32_t result;
    iERR err = ion_decimal_compare(&this->value, &rhs.value, &Ion::g_IonDecimalContext, &result);

    ION_OK(err)

    return result;
}

int Ion::Decimal::equals(const Ion::Decimal &rhs) {
    int result;
    iERR err = ion_decimal_equals(&this->value, &rhs.value, &Ion::g_IonDecimalContext, &result);

    ION_OK(err)

    return result;
}

void Ion::Decimal::canonical(const Ion::Decimal &rhs) {
    iERR err = ion_decimal_canonical(&this->value, &rhs.value);

    ION_OK(err)
}

void Ion::Decimal::copy(const Ion::Decimal &rhs) {
    iERR err = ion_decimal_copy(&this->value, &rhs.value);

    ION_OK(err)
}

void Ion::Decimal::copyAbs(const Ion::Decimal &rhs) {
    iERR err = ion_decimal_copy_abs(&this->value, &rhs.value);

    ION_OK(err)
}

void Ion::Decimal::copyNegate(const Ion::Decimal &rhs) {
    iERR err = ion_decimal_copy_negate(&this->value, &rhs.value);

    ION_OK(err)
}

void Ion::Decimal::copySign(const Ion::Decimal &rhs, const Ion::Decimal &lhs) {
    iERR err = ion_decimal_copy_sign(&this->value, &rhs.value, &lhs.value, &Ion::g_IonDecimalContext);

    ION_OK(err)
}
