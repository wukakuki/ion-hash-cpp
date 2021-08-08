/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_FLOAT_H_
#define ION_HASH_CPP_ION_FLOAT_H_

#include "IonHash_EXPORTS.h"
#include "ionc/ion.h"

#include "IonScalarValue.h"
#include "IonReader.h"

#include <string>

namespace Ion {
    class ION_HASH_EXPORTS Float : public Ion::ScalarValue {
    public:
        double value;
    public:
        Float();

        ~Float();

        explicit Float(double &value);

        explicit Float(Ion::Reader &reader);

        void getBytes() override;

        int isNegativeZero();
    };
};

#endif