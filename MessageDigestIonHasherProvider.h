/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_MESSAGE_DIGESTION_HASHER_PROVIDER_H_
#define ION_HASH_CPP_MESSAGE_DIGESTION_HASHER_PROVIDER_H_

#include "IonHash_EXPORTS.h"
#include "IonHasherProvider.h"
#include "MessageDigestIonHasher.h"

#include "openssl/sha.h"
#include "openssl/hmac.h"
#include "openssl/kdf.h"
#include "openssl/bio.h"
#include "openssl/evp.h"

namespace Ion {
    namespace Hash {
        class ION_HASH_EXPORTS MessageDigestHasherProvider : public Ion::Hash::HasherProvider {
        private:
            const EVP_MD *_evpMd;
        public:
            explicit MessageDigestHasherProvider(const EVP_MD *evpMd = EVP_sha256()) : _evpMd(evpMd) {
            }

            Ion::Hash::Hasher *newHasher() override {
                return new Ion::Hash::MessageDigestHasher(_evpMd);
            }
        };
    }
}

#endif