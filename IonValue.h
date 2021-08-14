/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_VALUE_H_
#define ION_HASH_CPP_ION_VALUE_H_

#include "IonHash_EXPORTS.h"
#include "IonType.h"
#include "IonReader.h"
#include "IonSerialize.h"

#include <string>
#include <vector>

namespace Ion {
    class ION_HASH_EXPORTS String;
    class ION_HASH_EXPORTS Writer;

    class ION_HASH_EXPORTS Value : public Ion::Hash::Serialize {
    public:
        std::vector<Ion::String> annotations;
        Ion::String *fieldName{};
        bool isNull{};
        Ion::Type type;
        std::vector<Ion::Value *> children;

        /*typedef union ScalarValue {

        } ScalarValue;*/
        Value();

        ~Value();

        Value(const Value&) = default;

        explicit Value(Ion::Reader &reader);

        static Ion::Value *readAll(Ion::Reader &reader);
        static std::vector<unsigned char> writeAll(Ion::Value *ionValue, bool isBinary);
        void writeAllInterval(Ion::Writer &writer);

        void handleFieldName() override;

        void handleAnnotationsBegin() override;
        void handleAnnotationsEnd() override;
    };
};

#endif