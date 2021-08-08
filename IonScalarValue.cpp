/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonScalarValue.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <iomanip>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FILE__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::ScalarValue::ScalarValue() : Ion::Value() {

}

Ion::ScalarValue::ScalarValue(Ion::Reader &reader) : Ion::Value(reader) {

}

void Ion::ScalarValue::addTQ() {
    if (bytes.size() == 0) {
        this->getBytes();
        bytes = std::vector<unsigned char>(bytes.begin() + 4, bytes.end());

        std::stringstream ss;
        ss << std::hex;

        for (unsigned char i : bytes) {
            if (i != 0) {
                ss << ' ';
            }
            ss << std::setw(2) << std::setfill('0') << (int) i;
        }

    }
    int tq = bytes[0];

    if (type.binaryTypeId == type_symbol) {
        tq = 0x70;
        if (isNull) {
            tq |= 0x0f;
        }
    }

    if (type.binaryTypeId != type_bool && type.binaryTypeId != type_symbol && (tq & 0x0F) != 0x0F/*not a null value*/) {
        tq &= 0xF0;     // zero - out the L nibble
    }

    this->serialized.push_back(tq);
}

std::vector<unsigned char> Ion::ScalarValue::getRepresentation() {
    if (bytes.size() == 0) {
        this->getBytes();
        bytes = std::vector<unsigned char>(bytes.begin() + 4, bytes.end());

        std::stringstream ss;
        ss << std::hex;

        for (unsigned char i : bytes) {
            if (i != 0) {
                ss << ' ';
            }
            ss << std::setw(2) << std::setfill('0') << (int) i;
        }
    }
    int length = 0;
    if ((bytes[0] & 0x0F) == 0x0E) {
        // read subsequent byte(s) as the "length" field
        for (int i = 1; i < bytes.size(); i++) {
            if ((bytes[i] & 0x80) != 0) {
                length = i;
                break;
            }
        }
        //        throw new Error("Problem while reading VarUInt!");
    }

    int offset = 1 + length;
    std::vector<unsigned char> representation(bytes.begin() + offset, bytes.end());

    return representation;
}
