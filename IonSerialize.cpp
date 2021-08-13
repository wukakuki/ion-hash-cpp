/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonSerialize.h"

#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

std::string Ion::printBytes(std::vector<unsigned char> bytes) {
    std::stringstream ss;
    ss << std::hex;

    for (int i = 0; i < bytes.size(); i ++) {
        if (i != 0) {
            ss << ' ';
        }
        ss << std::setw(2) << std::setfill('0') << (0xff & (unsigned char)bytes[i]);
    }

    return ss.str();
}

Ion::Hash::Serialize::Serialize(Ion::Hash::HasherProvider *hasherProvider) : hasherProvider(hasherProvider) {
}

Ion::Hash::Serialize::~Serialize() {
}

std::vector<unsigned char> Ion::Hash::Serialize::serializeValue() {
    this->serialized.clear();

    this->escapedRepresentation = Ion::Hash::Serialize::escape(this->getRepresentation());

//    this->serialized.reserve(this->escapedRepresentation.size() + 3);

    this->handleFieldName();

    this->handleAnnotationsBegin();

    this->addBeginMarker();

    this->addTQ();

    this->serialized.insert(this->serialized.end(), this->escapedRepresentation.begin(), this->escapedRepresentation.end());

    this->addEndMarker();

    this->handleAnnotationsEnd();

    serializedHasBeenSet = true;

    return this->serialized;
}

std::vector<unsigned char> Ion::Hash::Serialize::escape(std::vector<unsigned char> bytes) {
    std::vector<unsigned char> escaped;
    for (int j = 0; j < bytes.size(); ++j) {
        unsigned char b = bytes[j];
        if (b == Ion::Hash::BEGIN_MARKER_BYTE || b == Ion::Hash::END_MARKER_BYTE || b == Ion::Hash::ESCAPE_BYTE) {
            escaped.push_back(Ion::Hash::ESCAPE_BYTE);
        }
        escaped.push_back(b);
    }
    return escaped;
}

void Ion::Hash::Serialize::addBeginMarker() {
    this->serialized.push_back(Ion::Hash::BEGIN_MARKER_BYTE);
}

void Ion::Hash::Serialize::addEndMarker() {
    this->serialized.push_back(Ion::Hash::END_MARKER_BYTE);
}

std::vector<unsigned char> Ion::Hash::Serialize::hash() {
    this->serializeValue();
    Ion::Hash::Hasher *hasher = this->hasherProvider->newHasher();
    hasher->update(serialized);

    this->hashed = hasher->digest();
    this->hashedHasBeenSet = true;
    if (hasher) {
        delete hasher;
    }
    return this->hashed;
}

bool Ion::Hash::Serialize::ByteArrayComparator(std::vector<unsigned char> a, std::vector<unsigned char> b) {
    int i = 0;
    while (i < a.size() && i < b.size()) {
        int a_byte = a[i];
        int b_byte = b[i];
        if (a_byte != b_byte) {
            if (a_byte - b_byte < 0) {
                return true;
            } else {
                return false;
            }
        }
        i += 1;
    }

    int len_diff = a.size() - b.size();
    if (len_diff < 0) {
        return true;
    } else if (len_diff > 0) {
        return false;
    } else {
        // equal
        return false;
    }
}
