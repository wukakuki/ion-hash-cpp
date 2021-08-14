/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_SEXP_H_
#define ION_HASH_CPP_ION_SEXP_H_

#include "IonHash_EXPORTS.h"
#include "IonScalarValue.h"

#include <string>
#include <vector>

namespace Ion {
    class ION_HASH_EXPORTS Sexp : public Ion::Value {
    public:
        std::vector<unsigned char> representation;

        explicit Sexp(Ion::Reader &reader);

        void addTQ() override;

        std::vector<unsigned char> getRepresentation() override;

        Sexp();
    };
};

#endif