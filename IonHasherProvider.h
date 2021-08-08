/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_HASHER_PROVIDER_H_
#define ION_HASH_CPP_ION_HASHER_PROVIDER_H_

#include "IonHash_EXPORTS.h"
#include "IonHasher.h"

namespace Ion {
    namespace Hash {
        class ION_HASH_EXPORTS HasherProvider {
        public:
            virtual Ion::Hash::Hasher *newHasher() = 0;
        };
    }
}

#endif