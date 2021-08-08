/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_STRING_H_
#define ION_HASH_CPP_ION_STRING_H_

#include "IonHash_EXPORTS.h"
#include <string>
#include "ionc/ion.h"

#include "IonScalarValue.h"
#include "IonReader.h"

namespace Ion {
    class ION_HASH_EXPORTS String : public Ion::ScalarValue {
    public:
        ION_STRING value;
    public:
        String();

        ~String() = default;

        explicit String(ION_STRING &str);

        explicit String(Ion::Reader &reader);

        void getBytes() override;

        explicit String(std::string &str);

        String(char *str, SIZE len);

        char *strdup();

        int getLength();

        BYTE getByte(int idx);

        BYTE *_getBytes();

        bool _isNull();

        bool isEqual(Ion::String other);
    };
}

#endif