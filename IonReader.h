/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_READER_H_
#define ION_HASH_CPP_ION_READER_H_

#include "IonHash_EXPORTS.h"
#include <string>
#include <vector>
#include "ionc/ion.h"

#include "IonType.h"

#ifndef ION_CONTAINER_DEPTH_MAX
#define ION_CONTAINER_DEPTH_MAX 100
#endif
#ifndef ION_ANNOTATION_MAX
#define ION_ANNOTATION_MAX 100
#endif

namespace Ion {
class ION_HASH_EXPORTS Reader {
public:
    hREADER reader;

    Ion::Type currentType;
public:
    explicit Reader(const char *ion_text);
    Reader(const std::vector<unsigned char> &ion_binary);
    ~Reader();
    explicit Reader(hREADER reader);

    Ion::Type next();
    void stepIn() const;
    void stepOut() const;
};
};

#endif