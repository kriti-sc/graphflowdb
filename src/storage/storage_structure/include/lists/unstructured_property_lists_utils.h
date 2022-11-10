#pragma once

#include <functional>

#include "src/common/include/configs.h"
#include "src/common/types/include/types.h"

namespace graphflow {
namespace storage {

using namespace graphflow::common;

struct UnstructuredPropertyKeyDataType {
    uint32_t keyIdx;
    DataTypeID dataTypeID;
};

struct UnstructuredPropertyKey {
    uint32_t keyIdx;
};

struct UnstructuredDataType {
    DataTypeID dataTypeID;
};

struct UnstrPropListWrapper {

    UnstrPropListWrapper(unique_ptr<uint8_t[]> data, uint64_t size, uint64_t capacity)
        : data{move(data)}, size{size}, capacity{capacity} {}

    unique_ptr<uint8_t[]> data;
    uint64_t size;
    uint64_t capacity;

    inline void clear() { size = 0; }

    inline void incrementSize(uint64_t insertedDataSize) { size += insertedDataSize; }

    void increaseCapacityIfNeeded(uint64_t requiredCapacity);

    // Warning: This is a very slow operation that slides the entire list after the offset to left.
    void removePropertyAtOffset(uint64_t offset, uint64_t dataTypeSize);
};

class UnstrPropListIterator {

public:
    UnstrPropListIterator() : UnstrPropListIterator(nullptr) {}
    UnstrPropListIterator(UnstrPropListWrapper* unstrPropListWrapper)
        : unstrPropListWrapper{unstrPropListWrapper}, curOff{0} {}

    inline bool hasNext() { return curOff < unstrPropListWrapper->size; }

    UnstructuredPropertyKeyDataType& readNextPropKeyValue();
    UnstructuredPropertyKey& readNextProp();
    UnstructuredDataType& readNextDatatype(uint8_t totalElementsInList, uint64_t counter);

    void skipValue();

    inline uint64_t getCurOff() { return curOff; }

    inline uint64_t getDataTypeSizeOfCurrProp() {
        assert(propKeyDataTypeForRetVal.keyIdx != UINT32_MAX);
        return Types::getDataTypeSize(propKeyDataTypeForRetVal.dataTypeID);
    }

    inline uint64_t getDataTypeSizeOfCurrPropNew() {
        assert(propKeyForRetVal.keyIdx != UINT32_MAX);
        return Types::getDataTypeSize(dataTypeForRetVal.dataTypeID);
    }

    inline uint64_t getOffsetAtBeginningOfCurrProp() {
        assert(propKeyDataTypeForRetVal.keyIdx != UINT32_MAX);
        return curOff - StorageConfig::UNSTR_PROP_HEADER_LEN;
    }

    void copyValueOfCurrentProp(uint8_t* dst) {
        memcpy(dst, unstrPropListWrapper->data.get() + curOff, getDataTypeSizeOfCurrProp());
    }

    void copyValueOfCurrentPropNew(uint8_t* dst, uint8_t totalElementsInList, uint64_t counter) {
        int64_t oldCur = curOff;
        curOff = ((counter-1)*(StorageConfig::UNSTR_PROP_DATATYPE_LEN+StorageConfig::UNSTR_PROP_VALUE_LEN)) +
                 ((totalElementsInList - counter)*StorageConfig::UNSTR_PROP_KEY_IDX_LEN) +
                StorageConfig::UNSTR_PROP_DATATYPE_LEN;
        memcpy(dst, unstrPropListWrapper->data.get() + curOff, getDataTypeSizeOfCurrPropNew());
        curOff = oldCur;
    }

private:
    UnstrPropListWrapper* unstrPropListWrapper;
    UnstructuredPropertyKeyDataType propKeyDataTypeForRetVal;
    UnstructuredPropertyKey propKeyForRetVal;
    UnstructuredDataType dataTypeForRetVal;
    uint64_t curOff;
};

class UnstrPropListUtils {
public:
    static bool findKeyPropertyAndPerformOp(UnstrPropListWrapper* updatedList, uint32_t propertyKey,
        std::function<void(UnstrPropListIterator&)> opToPerform);
    //  void (*func)(UnstrPropListIterator& itr)
};

} // namespace storage
} // namespace graphflow
