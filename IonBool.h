/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_BOOL_H_
#define ION_HASH_CPP_ION_BOOL_H_

#include "IonHash_EXPORTS.h"
#include "IonScalarValue.h"

#include <string>
#include <vector>

namespace Ion {
    class ION_HASH_EXPORTS Bool : public Ion::ScalarValue {
    public:
        BOOL value;
    public:
        std::vector<unsigned char> bytes;

        explicit Bool(Ion::Reader &reader);

        void getBytes() override;
    };
};

#endif