#include "src/common/include/vector/operations/vector_cast_operations.h"

#include "src/common/types/include/value.h"

namespace graphflow {
namespace common {

void VectorCastOperations::castStructuredToUnstructuredValue(
    ValueVector& operand, ValueVector& result) {
    assert(operand.dataType != UNSTRUCTURED && result.dataType == UNSTRUCTURED);
    auto outValues = (Value*)result.values;
    if (operand.state->isFlat()) {
        auto pos = operand.state->getPositionOfCurrIdx();
        auto resPos = result.state->getPositionOfCurrIdx();
        switch (operand.dataType) {
        case BOOL: {
            outValues[resPos].val.booleanVal = operand.values[pos];
            outValues[resPos].dataType = BOOL;
        } break;
        case INT64: {
            outValues[resPos].val.int64Val = ((int64_t*)operand.values)[pos];
            outValues[resPos].dataType = INT64;
        } break;
        case DOUBLE: {
            outValues[resPos].val.doubleVal = ((double_t*)operand.values)[pos];
            outValues[resPos].dataType = DOUBLE;
        } break;
        case DATE: {
            outValues[resPos].val.dateVal = ((date_t*)operand.values)[pos];
            outValues[resPos].dataType = DATE;
        } break;
        case TIMESTAMP: {
            outValues[resPos].val.timestampVal = ((timestamp_t*)operand.values)[pos];
            outValues[resPos].dataType = TIMESTAMP;
        } break;
        case INTERVAL: {
            outValues[resPos].val.intervalVal = ((interval_t*)operand.values)[pos];
            outValues[resPos].dataType = INTERVAL;
        } break;
        case STRING: {
            result.addGFStringToUnstructuredVector(resPos, ((gf_string_t*)operand.values)[pos]);
            outValues[resPos].dataType = STRING;
        } break;
        default:
            assert(false);
        }
    } else {
        switch (operand.dataType) {
        case BOOL: {
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                outValues[pos].val.booleanVal = operand.values[pos];
                outValues[pos].dataType = BOOL;
            }
        } break;
        case INT64: {
            auto intValues = (int64_t*)operand.values;
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                outValues[pos].val.int64Val = intValues[pos];
                outValues[pos].dataType = INT64;
            }
        } break;
        case DOUBLE: {
            auto doubleValues = (double_t*)operand.values;
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                outValues[pos].val.doubleVal = doubleValues[pos];
                outValues[pos].dataType = DOUBLE;
            }
        } break;
        case DATE: {
            auto dateValues = (date_t*)operand.values;
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                outValues[pos].val.dateVal = dateValues[pos];
                outValues[pos].dataType = DATE;
            }
        } break;
        case TIMESTAMP: {
            auto timestampValues = (timestamp_t*)operand.values;
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                outValues[pos].val.timestampVal = timestampValues[pos];
                outValues[pos].dataType = TIMESTAMP;
            }
        } break;
        case INTERVAL: {
            auto intervalValues = (interval_t*)operand.values;
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                outValues[pos].val.intervalVal = intervalValues[pos];
                outValues[pos].dataType = INTERVAL;
            }
        } break;
        case STRING: {
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                result.addGFStringToUnstructuredVector(pos, ((gf_string_t*)operand.values)[pos]);
                outValues[pos].dataType = STRING;
            }
        } break;
        default:
            assert(false);
        }
    }
}

void VectorCastOperations::castStructuredToString(ValueVector& operand, ValueVector& result) {
    assert((operand.dataType == INT64 || operand.dataType == DOUBLE || operand.dataType == BOOL ||
               operand.dataType == DATE || operand.dataType == TIMESTAMP ||
               operand.dataType == INTERVAL) &&
           result.dataType == STRING);
    if (operand.state->isFlat()) {
        auto pos = operand.state->getPositionOfCurrIdx();
        auto resPos = result.state->getPositionOfCurrIdx();
        string val;
        switch (operand.dataType) {
        case BOOL: {
            val = TypeUtils::toString(((bool*)operand.values)[pos]);
        } break;
        case INT64: {
            val = TypeUtils::toString(((int64_t*)operand.values)[pos]);
        } break;
        case DOUBLE: {
            val = TypeUtils::toString(((double_t*)operand.values)[pos]);
        } break;
        case DATE: {
            val = Date::toString(((date_t*)operand.values)[pos]);
        } break;
        case TIMESTAMP: {
            val = Timestamp::toString(((timestamp_t*)operand.values)[pos]);
        } break;
        case INTERVAL: {
            val = Interval::toString(((interval_t*)operand.values)[pos]);
        } break;
        default:
            assert(false);
        }
        result.addString(resPos, val);
    } else {
        switch (operand.dataType) {
        case BOOL: {
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                result.addString(pos, TypeUtils::toString(((bool*)operand.values)[pos]));
            }
        } break;
        case INT64: {
            auto intValues = (int64_t*)operand.values;
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                result.addString(pos, TypeUtils::toString(intValues[pos]));
            }
        } break;
        case DOUBLE: {
            auto doubleValues = (double_t*)operand.values;
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                result.addString(pos, TypeUtils::toString(doubleValues[pos]));
            }
        } break;
        case DATE: {
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                result.addString(pos, Date::toString(((date_t*)operand.values)[pos]));
            }
        } break;
        case TIMESTAMP: {
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                result.addString(pos, Timestamp::toString(((timestamp_t*)operand.values)[pos]));
            }
        } break;
        case INTERVAL: {
            for (auto i = 0u; i < operand.state->selectedSize; i++) {
                auto pos = operand.state->selectedPositions[i];
                result.addString(pos, Interval::toString(((interval_t*)operand.values)[pos]));
            }
        } break;
        default:
            assert(false);
        }
    }
}

void VectorCastOperations::castUnstructuredToBoolValue(ValueVector& operand, ValueVector& result) {
    assert(operand.dataType == UNSTRUCTURED && result.dataType == BOOL);
    auto inValues = (Value*)operand.values;
    if (!operand.state->isFlat()) {
        for (auto i = 0u; i < operand.state->selectedSize; i++) {
            auto pos = operand.state->selectedPositions[i];
            if (inValues[pos].dataType != BOOL) {
                throw std::invalid_argument("Don’t know how to treat that as a predicate: “" +
                                            DataTypeNames[inValues[pos].dataType] + "(" +
                                            inValues[pos].toString() + ")”.");
            }
            result.values[pos] = inValues[pos].val.booleanVal;
        }
    } else {
        auto pos = operand.state->getPositionOfCurrIdx();
        auto resPos = result.state->getPositionOfCurrIdx();
        if (inValues[pos].dataType != BOOL) {
            throw std::invalid_argument("Don’t know how to treat that as a predicate: “" +
                                        DataTypeNames[inValues[pos].dataType] + "(" +
                                        inValues[pos].toString() + ")”.");
        }
        result.values[resPos] = inValues[pos].val.booleanVal;
    }
}

void VectorCastOperations::castStringToDate(ValueVector& operand, ValueVector& result) {
    assert(operand.dataType == STRING && result.dataType == INTERVAL);
    auto inValues = (gf_string_t*)operand.values;
    auto resultValues = (date_t*)result.values;
    if (!operand.state->isFlat()) {
        for (auto i = 0u; i < operand.state->selectedSize; i++) {
            auto pos = operand.state->selectedPositions[i];
            resultValues[pos] =
                Date::FromCString((const char*)inValues[pos].getData(), inValues[pos].len);
        }
    } else {
        auto pos = operand.state->getPositionOfCurrIdx();
        auto resPos = result.state->getPositionOfCurrIdx();
        resultValues[resPos] =
            Date::FromCString((const char*)inValues[pos].getData(), inValues[pos].len);
    }
}

void VectorCastOperations::castStringToTimestamp(ValueVector& operand, ValueVector& result) {
    assert(operand.dataType == STRING && result.dataType == INTERVAL);
    auto inValues = (gf_string_t*)operand.values;
    auto resultValues = (timestamp_t*)result.values;
    if (!operand.state->isFlat()) {
        for (auto i = 0u; i < operand.state->selectedSize; i++) {
            auto pos = operand.state->selectedPositions[i];
            resultValues[pos] =
                Timestamp::FromCString((const char*)inValues[pos].getData(), inValues[pos].len);
        }
    } else {
        auto pos = operand.state->getPositionOfCurrIdx();
        auto resPos = result.state->getPositionOfCurrIdx();
        resultValues[resPos] =
            Timestamp::FromCString((const char*)inValues[pos].getData(), inValues[pos].len);
    }
}

void VectorCastOperations::castStringToInterval(ValueVector& operand, ValueVector& result) {
    assert(operand.dataType == STRING && result.dataType == INTERVAL);
    auto inValues = (gf_string_t*)operand.values;
    auto resultValues = (interval_t*)result.values;
    if (!operand.state->isFlat()) {
        for (auto i = 0u; i < operand.state->selectedSize; i++) {
            auto pos = operand.state->selectedPositions[i];
            resultValues[pos] =
                Interval::FromCString((const char*)inValues[pos].getData(), inValues[pos].len);
        }
    } else {
        auto pos = operand.state->getPositionOfCurrIdx();
        auto resPos = result.state->getPositionOfCurrIdx();
        resultValues[resPos] =
            Interval::FromCString((const char*)inValues[pos].getData(), inValues[pos].len);
    }
}

} // namespace common
} // namespace graphflow
