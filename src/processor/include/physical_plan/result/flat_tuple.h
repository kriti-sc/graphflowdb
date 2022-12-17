#pragma once

#include <memory>

#include "src/common/types/include/value.h"

using namespace graphflow::common;

namespace graphflow {
namespace processor {

class FlatTuple {

public:
    explicit FlatTuple(const vector<DataType>& valueTypes) {
        values.resize(valueTypes.size());
        nullMask.resize(valueTypes.size());
        for (auto i = 0u; i < valueTypes.size(); i++) {
            values[i] = make_unique<Value>(valueTypes[i]);
            nullMask[i] = false;
        }
    }

    inline Value* getValue(uint32_t valIdx) { return values[valIdx].get(); }

    inline bool isNull(uint32_t valIdx) { return nullMask[valIdx]; }

    inline uint32_t len() { return values.size(); }

    string toString(const vector<uint32_t>& colsWidth, const string& delimiter = "|");

    string toString();

public:
    vector<bool> nullMask;

private:
    vector<unique_ptr<Value>> values;
};

} // namespace processor
} // namespace graphflow
