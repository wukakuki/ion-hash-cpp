/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_WRITER_H_
#define ION_HASH_CPP_ION_WRITER_H_

#include "IonHash_EXPORTS.h"
#include <string>
#include <vector>
#include "ionc/ion.h"

#include "IonType.h"
#include "IonInt.h"
#include "IonFloat.h"
#include "IonDecimal.h"
#include "IonTimestamp.h"
#include "IonString.h"
#include "IonReader.h"
#include "IonValue.h"
#include "IonBlob.h"
#include "IonClob.h"
#include "IonBool.h"

#ifndef ION_CONTAINER_DEPTH_MAX
#define ION_CONTAINER_DEPTH_MAX 100
#endif
#ifndef ION_ANNOTATION_MAX
#define ION_ANNOTATION_MAX 100
#endif

namespace Ion {
class ION_HASH_EXPORTS Writer {
public:
    hWRITER writer;

    ION_STREAM *ion_stream;
private:
    bool isClosed;
public:
    Writer(bool isBinary);
    ~Writer();
    Writer(hWRITER writer);

    // will close the writer too.
    std::vector<unsigned char> getBytes();

    void writeAllValues(Ion::Reader &reader);

    void writeNull(Ion::Type &type);
    void writeBoolean(Ion::Bool &value);
    void writeInt(Ion::Int &value);
    void writeFloat(Ion::Float &value);
    void writeDecimal(Ion::Decimal &value);
    void writeTimestamp(Ion::Timestamp &value);
    void writeClob(Ion::Clob &value);
    void writeBlob(Ion::Blob &value);
    void writeString(Ion::String &value);
    void stepIn(Ion::Type &type);
    void stepOut();
    void writeFieldName(Ion::String &fieldName);
    void writeFieldName(SID sid);
    void writeSymbol(Ion::String &value);
    void writeSymbol(SID sid);
    void addAnnotation(Ion::String &annotation);
    void addAnnotation(SID sid);
};
};

#endif