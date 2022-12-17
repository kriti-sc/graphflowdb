#include "src/storage/storage_structure/include/lists/unstructured_property_lists_utils.h"

namespace graphflow {
namespace storage {

void UnstrPropListWrapper::increaseCapacityIfNeeded(uint64_t requiredCapacity) {
    if (requiredCapacity < capacity) {
        return;
    }
    uint64_t newCapacity =
        max(requiredCapacity, (uint64_t)(capacity * StorageConfig::ARRAY_RESIZING_FACTOR));
    unique_ptr<uint8_t[]> newData = make_unique<uint8_t[]>(newCapacity);
    memcpy(newData.get(), data.get(), capacity);
    data.reset();
    data = move(newData);
    capacity = newCapacity;
}

void UnstrPropListWrapper::removePropertyAtOffset(uint64_t offset, uint64_t dataTypeSize) {
    uint64_t sizeToSlide = StorageConfig::UNSTR_PROP_HEADER_LEN + dataTypeSize;
    uint64_t endOffset = offset + StorageConfig::UNSTR_PROP_HEADER_LEN + dataTypeSize;
    memcpy(data.get() + offset, data.get() + endOffset, size - endOffset);
    size -= sizeToSlide;
}

bool UnstrPropListUtils::findKeyPropertyAndPerformOp(UnstrPropListWrapper* updatedList,
    uint32_t propertyKey, std::function<void(UnstrPropListIterator&)> opToPerform) {
    UnstrPropListIterator itr(updatedList);
    while (itr.hasNext()) {
        auto propKeyDataType = itr.readNextPropKeyValue();
        if (propertyKey == propKeyDataType.keyIdx) {
            opToPerform(itr);
            return true;
        } else {
            itr.skipValue();
        }
    }
    return false;
}

UnstructuredPropertyKeyDataType& UnstrPropListIterator::readNextPropKeyValue() {
    memcpy(reinterpret_cast<uint8_t*>(&propKeyDataTypeForRetVal),
        unstrPropListWrapper->data.get() + curOff, StorageConfig::UNSTR_PROP_HEADER_LEN);
    curOff += StorageConfig::UNSTR_PROP_HEADER_LEN;
    return propKeyDataTypeForRetVal;
}

//UnstructuredPropertyKeyDataType& UnstrPropListIterator::readNextPropKeyValueNew(uint64_t size, uint64_t counter) {
//    memcpy(reinterpret_cast<uint8_t*>(&propKeyDataTypeForRetVal.keyIdx),
//           unstrPropListWrapper->data.get() + curOff, StorageConfig::UNSTR_PROP_HEADER_LEN);
//    uint64_t nextCurOff = curOff + StorageConfig::UNSTR_PROP_HEADER_LEN;
//    curOff = (counter*(StorageConfig::UNSTR_PROP_DATATYPE_LEN+<value>)) +
//            ((size/<total size>) - counter -1)*StorageConfig::UNSTR_PROP_HEADER_LEN;
//    memcpy(reinterpret_cast<uint8_t*>(&propKeyDataTypeForRetVal.dataTypeID),
//           unstrPropListWrapper->data.get() + curOff, StorageConfig::UNSTR_PROP_HEADER_LEN);
//    curOff = nextCurOff;
//    return propKeyDataTypeForRetVal;
//}

UnstructuredPropertyKey& UnstrPropListIterator::readNextProp() {
    memcpy(reinterpret_cast<uint8_t*>(&propKeyForRetVal),
           unstrPropListWrapper->data.get() + curOff, StorageConfig::UNSTR_PROP_KEY_IDX_LEN);
    // cout<<"cur for prop: "+ to_string(curOff)<<endl;
    curOff += StorageConfig::UNSTR_PROP_KEY_IDX_LEN;
    return propKeyForRetVal;
}

UnstructuredDataType& UnstrPropListIterator::readNextDatatype(uint8_t totalElementsInList, uint64_t counter) {
    uint64_t curOffOld = curOff;
    // cout<<"old cur for datatype: "+ to_string(curOff)<<endl;
    curOff = curOff + ((counter-1)*(StorageConfig::UNSTR_PROP_DATATYPE_LEN+StorageConfig::UNSTR_PROP_VALUE_LEN)) +
             ((totalElementsInList - counter)*StorageConfig::UNSTR_PROP_KEY_IDX_LEN);
    // cout<<"cur for datatype: "+ to_string(curOff)<<endl;
    memcpy(reinterpret_cast<uint8_t*>(&dataTypeForRetVal),
           unstrPropListWrapper->data.get() + curOff, StorageConfig::UNSTR_PROP_DATATYPE_LEN);
    curOff = curOffOld;
    return dataTypeForRetVal;
}

void UnstrPropListIterator::skipValue() {
    curOff += Types::getDataTypeSize(propKeyDataTypeForRetVal.dataTypeID);
    propKeyDataTypeForRetVal.keyIdx = UINT32_MAX;
}

} // namespace storage
} // namespace graphflow
