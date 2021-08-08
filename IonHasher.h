/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_HASHER_H_
#define ION_HASH_CPP_ION_HASHER_H_

#include "IonHash_EXPORTS.h"
#include <vector>

namespace Ion {
    namespace Hash {
        class ION_HASH_EXPORTS Hasher {
        public:
            virtual void update(std::vector<unsigned char> bytes) = 0;
            virtual std::vector<unsigned char> digest() = 0;
            virtual ~Hasher() = default;
        };
    }
}

#endif