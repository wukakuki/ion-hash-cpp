/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#include "IonValue.h"
#include "IonNull.h"
#include "IonBool.h"
#include "IonBlob.h"
#include "IonClob.h"
#include "IonInt.h"
#include "IonDecimal.h"
#include "IonFloat.h"
#include "IonTimestamp.h"
#include "IonSymbolTable.h"
#include "IonString.h"
#include "IonStruct.h"
#include "IonSexp.h"
#include "IonList.h"
#include "IonWriter.h"

#include "ionc/ion.h"
#include <cstdlib>
#include <algorithm>

#ifndef ION_OK
#define ION_OK(x) if (x) { printf("In %s, line %d, %s Error: %s\n", __FUNCTION__, __LINE__, __func__, ion_error_to_str(x)); }
#endif

Ion::Value::Value() : Ion::Hash::Serialize(), type(Ion::Type(tid_none)) {
}

Ion::Value::~Value() {
    if (fieldName) {
        delete fieldName;
    }

    for (const auto &child : children) {
        if (child) {
            delete child;
        }
    }
}

Ion::Value::Value(Ion::Reader &reader) : Ion::Hash::Serialize(), type(Ion::Type(tid_none)) {
    SIZE count;
    iERR err;

    err = ion_reader_get_annotation_count(reader.reader, &count);

    ION_OK(err)

    if (count > 0) {
        ION_STRING annotationList[count];
        SIZE numAnnotations;
        err = ion_reader_get_annotations(reader.reader, annotationList, count, &numAnnotations);

        ION_OK(err)

        if (numAnnotations != count) {
            ION_OK(IERR_EOF);
        }

        annotations.clear();
        annotations.reserve(numAnnotations);
        for (int i = 0; i < numAnnotations; i++) {
            Ion::String annotation(annotationList[i]);
            fieldName->isNull = ion_string_is_null(&annotationList[i]);
            annotations.push_back(annotation);
        }
    }

    BOOL isInStruct;
    err = ion_reader_is_in_struct(reader.reader, &isInStruct);

    ION_OK(err)

    if (isInStruct) {
        ION_STRING fieldNameString;
        err = ion_reader_get_field_name(reader.reader, &fieldNameString);

        ION_OK(err)

        fieldName = new Ion::String(fieldNameString);

        fieldName->isNull = ion_string_is_null(&fieldNameString);
    }

    BOOL isValueNull;
    err = ion_reader_is_null(reader.reader, &isValueNull);

    ION_OK(err)

    isNull = isValueNull;
}

Ion::Value *Ion::Value::readAll(Ion::Reader &reader) {
    switch (reader.currentType.binaryTypeId) {
        case type_null:
            return (Ion::Value *) new Ion::Null(reader);
            break;
        case type_bool:
            return (Ion::Value *) new Ion::Bool(reader);
            break;
        case type_pos_int:
            return (Ion::Value *) new Ion::Int(reader);
            break;
        case type_neg_int:
            return (Ion::Value *) new Ion::Int(reader);
            break;
        case type_float:
            return (Ion::Value *) new Ion::Float(reader);
            break;
        case type_decimal:
            return (Ion::Value *) new Ion::Decimal(reader);
            break;
        case type_timestamp:
            return (Ion::Value *) new Ion::Timestamp(reader);
            break;
        case type_symbol:
            return (Ion::Value *) new Ion::Symbol(reader);
            break;
        case type_string:
            return (Ion::Value *) new Ion::String(reader);
            break;
        case type_clob:
            return (Ion::Value *) new Ion::Clob(reader);
            break;
        case type_blob:
            return (Ion::Value *) new Ion::Blob(reader);
            break;
        case type_list:
            return (Ion::Value *) new Ion::List(reader);
            break;
        case type_sexp:
            return (Ion::Value *) new Ion::Sexp(reader);
            break;
        case type_struct:
            return (Ion::Value *) new Ion::Struct(reader);
            break;
        default:
            return (Ion::Value *) new Ion::Null(reader);
            break;
    }
}

std::vector<unsigned char> Ion::Value::writeAll(Ion::Value *ionValue, bool isBinary) {
    Ion::Writer writer(isBinary);

    if (ionValue) {
        ionValue->writeAllInterval(writer);
    }

    return writer.getBytes();
}

void Ion::Value::writeAllInterval(Ion::Writer &writer) {
    if (this->fieldName && !this->fieldName->isNull) {
        writer.writeFieldName(*this->fieldName);
    }

    for (auto elem : this->annotations) {
        writer.addAnnotation(elem);
    }

    if (this->isNull) {
        writer.writeNull(this->type);
    } else {
        switch (this->type.binaryTypeId) {
            case type_null: {
                writer.writeNull(this->type);
                break;
            }
            case type_bool: {
                writer.writeBoolean(*(Ion::Bool *)this);
                break;
            }
            case type_pos_int:
            case type_neg_int: {
                writer.writeInt(*(Ion::Int *)this);
                break;
            }
            case type_float: {
                writer.writeFloat(*(Ion::Float *)this);
                break;
            }
            case type_decimal: {
                writer.writeDecimal(*(Ion::Decimal *)this);
                break;
            }
            case type_timestamp: {
                writer.writeTimestamp(*(Ion::Timestamp *)this);
                break;
            }
            case type_symbol: {
                writer.writeSymbol(*(Ion::String *)this);
                break;
            }
            case type_string: {
                writer.writeString(*(Ion::String *)this);
                break;
            }
            case type_clob: {
                writer.writeClob(*(Ion::Clob *)this);
                break;
            }
            case type_blob: {
                writer.writeBlob(*(Ion::Blob *)this);
                break;
            }
            case type_list:
            case type_sexp:
            case type_struct: {
                writer.stepIn(this->type);
                for (auto elem : this->children) {
                    elem->writeAllInterval(writer);
                }
                writer.stepOut();
                break;
            }
            default:
                writer.writeNull(this->type);
                break;
        }
    }
}

void Ion::Value::handleFieldName() {
    if (fieldName) {
        this->addBeginMarker();

        Ion::Writer writer(true);

        writer.writeString(*fieldName);
        std::vector<unsigned char> scalarBytes = writer.getBytes();

        scalarBytes = std::vector<unsigned char>(scalarBytes.begin() + 4, scalarBytes.end());

        int length = 0;
        if ((scalarBytes[0] & 0x0F) == 0x0E) {
            // read subsequent byte(s) as the "length" field
            for (int i = 1; i < scalarBytes.size(); i++) {
                if ((scalarBytes[i] & 0x80) != 0) {
                    length = i;
                    break;
                }
            }
            //        throw new Error("Problem while reading VarUInt!");
        }

        int offset = 1 + length;
        std::vector<unsigned char> representation(scalarBytes.begin() + offset, scalarBytes.end());

        std::vector<unsigned char> escapedRepresentation = Ion::Hash::Serialize::escape(representation);

        unsigned char tq = 0x70;
        if (fieldName->_isNull()) {
            tq |= 0x0F;
        }

        this->serialized.push_back(tq);

        this->serialized.insert(this->serialized.end(), escapedRepresentation.begin(), escapedRepresentation.end());

        this->addEndMarker();
    }
}

void Ion::Value::handleAnnotationsBegin() {
    if (annotations.size() > 0) {
        this->addBeginMarker();

        // TQ_ANNOTATED_VALUE
        this->serialized.push_back(0xe0);

        for (auto &annotation : annotations) {
            this->addBeginMarker();

            Ion::Writer writer(true);
            writer.writeString(annotation);
            std::vector<unsigned char> scalarBytes = writer.getBytes();

            scalarBytes = std::vector<unsigned char>(scalarBytes.begin() + 4, scalarBytes.end());

            int length = 0;
            if ((scalarBytes[0] & 0x0F) == 0x0E) {
                // read subsequent byte(s) as the "length" field
                for (int i = 1; i < scalarBytes.size(); i++) {
                    if ((scalarBytes[i] & 0x80) != 0) {
                        length = i;
                        break;
                    }
                }
                //        throw new Error("Problem while reading VarUInt!");
            }

            int offset = 1 + length;
            std::vector<unsigned char> representation(scalarBytes.begin() + offset, scalarBytes.end());

            std::vector<unsigned char> escapedRepresentation = Ion::Hash::Serialize::escape(representation);

            unsigned char tq = 0x70;
            if (fieldName->_isNull()) {
                tq |= 0x0F;
            }

            this->serialized.push_back(tq);

            this->serialized.insert(this->serialized.end(), escapedRepresentation.begin(), escapedRepresentation.end());

            this->addEndMarker();
        }
    }
}

void Ion::Value::handleAnnotationsEnd() {
    if (annotations.size() > 0) {
        this->addEndMarker();
    }
}
