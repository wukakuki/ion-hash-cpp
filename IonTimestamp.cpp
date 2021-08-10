/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonTimestamp.h"
#include "IonDecimal.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FILE__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Timestamp::Timestamp() {
    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::~Timestamp() = default;

Ion::Timestamp::Timestamp(ION_TIMESTAMP &time) : timestamp(time) {
    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    iERR err = ion_reader_read_timestamp(reader.reader, &timestamp);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

void Ion::Timestamp::getBytes() {
    bytes.clear();
    if (isNull) {
        this->bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);
        writer.writeTimestamp(*this);
        this->bytes = writer.getBytes();
    }
}

Ion::Timestamp::Timestamp(const time_t *time) {
    iERR err = ion_timestamp_for_time_t(&this->timestamp, time);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(int year) {
    iERR err = ion_timestamp_for_year(&this->timestamp, year);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(int year, int month) {
    iERR err = ion_timestamp_for_month(&this->timestamp, year, month);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(int year, int month, int day) {
    iERR err = ion_timestamp_for_day(&this->timestamp, year, month, day);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(int year, int month, int day, int hours, int minutes) {
    iERR err = ion_timestamp_for_minute(&this->timestamp, year, month, day, hours, minutes);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(int year, int month, int day, int hours, int minutes, int seconds) {
    iERR err = ion_timestamp_for_second(&this->timestamp, year, month, day, hours, minutes, seconds);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(int year, int month, int day, int hours, int minutes, int seconds, decQuad *p_fraction) {
    iERR err = ion_timestamp_for_fraction(&this->timestamp, year, month, day, hours, minutes, seconds, p_fraction, &Ion::g_IonDecimalContext);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

Ion::Timestamp::Timestamp(int year, int month, int day, int hours, int minutes, int seconds, uint64_t coefficient,
                          int32_t Exponent) {
    std::vector<uint8_t> ret;
    if (coefficient==0) ret.push_back(0);
    // skip the above line if you don't mind an empty vector for "0"
    while(coefficient>0) {
        uint d=coefficient/10;
        ret.push_back(coefficient-(d*10)); // may be faster than x%10
        coefficient=d;
    }
    std::reverse(ret.begin(),ret.end());

    decQuad fraction;

    decQuadFromBCD(&fraction, Exponent, ret.data(), 0);

    iERR err = ion_timestamp_for_fraction(&this->timestamp, year, month, day, hours, minutes, seconds, &fraction, &Ion::g_IonDecimalContext);

    ION_OK(err)

    type = Ion::Types::TIMESTAMP;
}

int Ion::Timestamp::getPrecision() {
    int precision;
    iERR err = ion_timestamp_get_precision(&this->timestamp, &precision);

    ION_OK(err)

    return precision;
}

char *Ion::Timestamp::toString() {
    char *str = (char *) malloc(ION_TIMESTAMP_STRING_LENGTH+1);
    SIZE chars_used;
    iERR err = ion_timestamp_to_string(&this->timestamp, (char *)str, (SIZE)sizeof(str), &chars_used, &Ion::g_IonDecimalContext);
    str[chars_used] = '\0';

    ION_OK(err)

    return str;
}

void Ion::Timestamp::parse(const std::string &str) {
    SIZE chars_used;
    iERR err = ion_timestamp_parse(&this->timestamp, (char *)str.c_str(), (SIZE)strlen(str.c_str()), &chars_used, &Ion::g_IonDecimalContext);

    ION_OK(err)
}

time_t Ion::Timestamp::toTimeT() {
    time_t result;
    iERR err = ion_timestamp_to_time_t(&this->timestamp, &result);

    ION_OK(err)

    return result;
}

int Ion::Timestamp::equals(const Ion::Timestamp time) {
    int result;
    iERR err = ion_timestamp_equals(&this->timestamp, &time.timestamp, &result, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

int Ion::Timestamp::instantEquals(const Ion::Timestamp time) {
    int result;
    iERR err = ion_timestamp_instant_equals(&this->timestamp, &time.timestamp, &result, &Ion::g_IonDecimalContext);

    ION_OK(err)

    return result;
}

void Ion::Timestamp::getThruYear(int &year) {
    iERR err = ion_timestamp_get_thru_year(&this->timestamp, &year);

    ION_OK(err)
}

void Ion::Timestamp::getThruMonth(int &year, int &month) {
    iERR err = ion_timestamp_get_thru_month(&this->timestamp, &year, &month);

    ION_OK(err)
}

void Ion::Timestamp::getThruDay(int &year, int &month, int &day) {
    iERR err = ion_timestamp_get_thru_day(&this->timestamp, &year, &month, &day);

    ION_OK(err)
}

void Ion::Timestamp::getThruMinute(int &year, int &month, int &day, int &hour, int &minute) {
    iERR err = ion_timestamp_get_thru_minute(&this->timestamp, &year, &month, &day, &hour, &minute);

    ION_OK(err)
}

void Ion::Timestamp::getThruSecond(int &year, int &month, int &day, int &hour, int &minute, int &second) {
    iERR err = ion_timestamp_get_thru_second(&this->timestamp, &year, &month, &day, &hour, &minute, &second);

    ION_OK(err)
}

void Ion::Timestamp::getThruFraction(int &year, int &month, int &day, int &hour, int &minute, int &second,
                                     decQuad *fraction) {
    iERR err = ion_timestamp_get_thru_fraction(&this->timestamp, &year, &month, &day, &hour, &minute, &second, fraction);

    ION_OK(err)
}

int Ion::Timestamp::hasLocalOffset() {
    int result;
    iERR err = ion_timestamp_has_local_offset(&this->timestamp, &result);

    ION_OK(err)

    return result;
}

int Ion::Timestamp::getLocalOffset() {
    int result;
    iERR err = ion_timestamp_get_local_offset(&this->timestamp, &result);

    ION_OK(err)

    return result;
}

void Ion::Timestamp::unsetLocalOffset() {
    iERR err = ion_timestamp_unset_local_offset(&this->timestamp);

    ION_OK(err)
}

void Ion::Timestamp::setLocalOffset(int offsetMinutes) {
    iERR err = ion_timestamp_set_local_offset(&this->timestamp, offsetMinutes);

    ION_OK(err)
}