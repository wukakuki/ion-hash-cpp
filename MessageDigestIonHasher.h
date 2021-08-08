/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_MESSAGE_DIGESTION_HASHER_H_
#define ION_HASH_CPP_MESSAGE_DIGESTION_HASHER_H_

#include "IonHash_EXPORTS.h"
#include "IonHasher.h"

#include "openssl/sha.h"
#include "openssl/hmac.h"
#include "openssl/kdf.h"
#include "openssl/bio.h"

namespace Ion {
    namespace Hash {
        class ION_HASH_EXPORTS MessageDigestHasher : public Ion::Hash::Hasher {
        public:
            const EVP_MD *_evpMd;
            EVP_MD_CTX *_mdctx;
        public:
            explicit MessageDigestHasher(const EVP_MD *evpMd = EVP_sha256()) : _evpMd(evpMd) {
                _mdctx = EVP_MD_CTX_create();
                EVP_DigestInit_ex(_mdctx, _evpMd, nullptr);
            }

            void update(std::vector<unsigned char> bytes) override {
                EVP_DigestUpdate(_mdctx, bytes.data(), bytes.size());
            }

            std::vector<unsigned char> digest() override {
                std::vector<unsigned char> digest;
                digest.resize(EVP_MD_size(_evpMd));
                unsigned int digest_len;
                EVP_DigestFinal_ex(_mdctx, digest.data(), &digest_len);
                return digest;
            }

            ~MessageDigestHasher() override {
                EVP_MD_CTX_destroy(_mdctx);
            }
        };
    }
}

#endif