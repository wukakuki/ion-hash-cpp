/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_SERIALIZE_H_
#define ION_HASH_CPP_ION_SERIALIZE_H_

#include "IonHash_EXPORTS.h"
#include <vector>
#include <sstream>
#include <iomanip>

#include "IonHasherProvider.h"
#include "IonHasher.h"
#include "MessageDigestIonHasherProvider.h"

namespace Ion {
    std::string printBytes(std::vector<unsigned char> bytes);

    namespace Hash {
        static const unsigned char BEGIN_MARKER_BYTE = 0x0B;
        static const unsigned char END_MARKER_BYTE = 0x0E;
        static const unsigned char ESCAPE_BYTE = 0x0C;

        class ION_HASH_EXPORTS Serialize {
        public:
            std::vector<unsigned char> hashed;
            bool hashedHasBeenSet;
            std::vector<unsigned char> escapedRepresentation;
            bool escapedRepresentationHasBeenSet;
            std::vector<unsigned char> serialized;
            bool serializedHasBeenSet;

            Ion::Hash::HasherProvider *hasherProvider;
        public:
            explicit Serialize(Ion::Hash::HasherProvider *hasherProvider = new Ion::Hash::MessageDigestHasherProvider(EVP_sha256()));
            virtual ~Serialize();

            virtual std::vector<unsigned char> serializeValue();
            virtual void addTQ() = 0;
            virtual std::vector<unsigned char> getRepresentation() = 0;

            static std::vector<unsigned char> escape(std::vector<unsigned char> bytes);
            void addBeginMarker();
            void addEndMarker();

            virtual void handleFieldName() = 0;
            virtual void handleAnnotationsBegin() = 0;
            virtual void handleAnnotationsEnd() = 0;

            std::vector<unsigned char> hash();

            static bool ByteArrayComparator(std::vector<unsigned char> a, std::vector<unsigned char> b);
        };
    }
};

#endif