/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonSexp.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <algorithm>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Sexp::Sexp(Ion::Reader &reader) : Ion::Value(reader) {
    reader.stepIn();

    while (!isNull && reader.next().type != tid_EOF) {
        children.push_back(Ion::Value::readAll(reader));
    }

    reader.stepOut();

    type = Ion::Types::SEXP;
}

void Ion::Sexp::addTQ() {
    int tq = type.binaryTypeId << 4;

    if (isNull) {
        tq |= 0x0f;
    }

    this->serialized.push_back(tq);
}

std::vector<unsigned char> Ion::Sexp::getRepresentation() {
    representation.clear();
    for (const auto &child : children) {
        std::vector<unsigned char> childSerialized = child->serializeValue();
        representation.insert(representation.end(), childSerialized.begin(), childSerialized.end());
    }
    return representation;
}