/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_TIMESTAMP_H_
#define ION_HASH_CPP_ION_TIMESTAMP_H_

#include "IonHash_EXPORTS.h"
#include <string>
#include "ionc/ion.h"

#include "IonScalarValue.h"
#include "IonReader.h"

namespace Ion {
    class ION_HASH_EXPORTS Timestamp : public Ion::ScalarValue {
    public:
        ION_TIMESTAMP timestamp;
    public:
        Timestamp();

        ~Timestamp();

        explicit Timestamp(ION_TIMESTAMP &time);

        explicit Timestamp(Ion::Reader &reader);

        void getBytes() override;

        explicit Timestamp(const time_t *time);

        explicit Timestamp(int year);

        Timestamp(int year, int month);

        Timestamp(int year, int month, int day);

        Timestamp(int year, int month, int day, int hours, int minutes);

        Timestamp(int year, int month, int day, int hours, int minutes, int seconds);

        Timestamp(int year, int month, int day, int hours, int minutes, int seconds, decQuad *p_fraction);

        int getPrecision();

        char *toString();

        void parse(const std::string &str);

        time_t toTimeT();

        int equals(Ion::Timestamp time);

        int instantEquals(Ion::Timestamp time);

        void getThruYear(int &year);

        void getThruMonth(int &year, int &month);

        void getThruDay(int &year, int &month, int &day);

        void getThruMinute(int &year, int &month, int &day, int &hour, int &minute);

        void getThruSecond(int &year, int &month, int &day, int &hour, int &minute, int &second);

        void getThruFraction(int &year, int &month, int &day, int &hour, int &minute, int &second, decQuad *fraction);

        int hasLocalOffset();

        int getLocalOffset();

        void unsetLocalOffset();

        void setLocalOffset(int offsetMinutes);
    };
}

#endif