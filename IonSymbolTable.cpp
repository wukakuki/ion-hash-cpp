/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonSymbolTable.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Symbol::Symbol() {
    type = Ion::Types::SYMBOL;
}

Ion::Symbol::~Symbol() = default;

Ion::Symbol::Symbol(ION_SYMBOL &symbol) : symbol(symbol) {
    type = Ion::Types::SYMBOL;
}

Ion::Symbol::Symbol(Ion::Reader &reader) : Ion::ScalarValue(reader) {
    iERR err = ion_reader_read_ion_symbol(reader.reader, &symbol);

    ION_OK(err)

    type = Ion::Types::SYMBOL;
}

void Ion::Symbol::getBytes() {
    bytes.clear();
    if (isNull) {
        this->bytes.push_back(type.binaryTypeId << 4 | 0x0f);
    } else {
        Ion::Writer writer(true);

        Ion::String str(symbol.value);

        writer.writeString(str);
        this->bytes = writer.getBytes();
    }
}

Ion::SymbolTable::SymbolTable() {
    iERR err = ion_symbol_table_open(&symbol_table, nullptr);

    ION_OK(err)
}

Ion::SymbolTable::~SymbolTable() {
    iERR err = ion_symbol_table_close(symbol_table);

    ION_OK(err)
}

Ion::SymbolTable::SymbolTable(hSYMTAB symbol_table) : symbol_table(symbol_table) {
}
