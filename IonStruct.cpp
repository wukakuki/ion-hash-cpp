/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonStruct.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <algorithm>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Struct::Struct(Ion::Reader &reader) : Ion::Value(reader) {
    if (!isNull) {
        reader.stepIn();
        reader.currentType = Ion::Type(tid_none);

        while (reader.next().type != tid_EOF) {
            Ion::Value *child = Ion::Value::readAll(reader);
            children.push_back(child);
        }

        reader.stepOut();
    }

    type = Ion::Types::STRUCT;
}

void Ion::Struct::addTQ() {
    int tq = type.binaryTypeId << 4;

    if (isNull) {
        tq |= 0x0f;
    }

    this->serialized.push_back(tq);
}

std::vector<unsigned char> Ion::Struct::getRepresentation() {
    // calculate representation here instead
    std::vector<std::vector<unsigned char>> childrenHashes;
    for (const auto &child : children) {
        childrenHashes.push_back(child->hash());
    }

    // sort field and calculate representation
    std::sort(childrenHashes.begin(), childrenHashes.end(), Ion::Hash::Serialize::ByteArrayComparator);

    representation.clear();
    for (const auto &elem : childrenHashes) {
        representation.insert(representation.end(), elem.begin(), elem.end());
    }

    return representation;
}