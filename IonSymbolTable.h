/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef ION_HASH_CPP_ION_SYMBOL_TABLE_H_
#define ION_HASH_CPP_ION_SYMBOL_TABLE_H_

#include "IonHash_EXPORTS.h"
#include <string>
#include "ionc/ion.h"

#include "IonScalarValue.h"
#include "IonReader.h"

namespace Ion {
    class ION_HASH_EXPORTS Symbol : public Ion::ScalarValue {
    public:
        ION_SYMBOL symbol;
    public:
        Symbol();

        ~Symbol();

        explicit Symbol(ION_SYMBOL &symbol);

        explicit Symbol(Ion::Reader &reader);

        void getBytes() override;
    };

    class ION_HASH_EXPORTS SymbolTable {
    public:
        hSYMTAB symbol_table;
    public:
        SymbolTable();

        ~SymbolTable();

        SymbolTable(hSYMTAB symbol_table);
    };
};

#endif